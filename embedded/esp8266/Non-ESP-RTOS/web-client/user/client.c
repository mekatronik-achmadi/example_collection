/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    client.c
 * @brief   TCP Client code.
 *
 * @addtogroup Webclient
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "mem.h"
#include "espconn.h"
#include "user_interface.h"
#include "limits.h"

#include "client.h"

/**
 * @brief HTTP Client request arguments
 */
typedef struct{
    char *path;
    int port;
    char *post_data;
    char *headers;
    char *hostname;
    char *buffer;
    int buffer_size;
    bool secure;
}request_args;

/* Additional String Processing Routines */

LOCAL char * ICACHE_FLASH_ATTR esp_strdup(const char * str){
    if(str == NULL){ return NULL;	}

    char * new_str = (char *)os_malloc(os_strlen(str) + 1);
    if(new_str == NULL){ os_printf("esp_strdup: malloc error\r\n"); return NULL; }
    os_strcpy(new_str, str);

    return new_str;
}

LOCAL int ICACHE_FLASH_ATTR esp_isupper(char c){
    return (c >= 'A' && c <= 'Z');
}

LOCAL int ICACHE_FLASH_ATTR esp_isalpha(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

LOCAL int ICACHE_FLASH_ATTR esp_isspace(char c){
    return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}

LOCAL int ICACHE_FLASH_ATTR esp_isdigit(char c){
    return (c >= '0' && c <= '9');
}

LOCAL long ICACHE_FLASH_ATTR esp_strtol(const char *nptr, char **endptr, int base){
    const char *s = nptr;
    unsigned long acc;
    int c;
    unsigned long cutoff;
    int neg = 0, any, cutlim;

    do {
        c = *s++;
    } while (esp_isspace(c));

    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) &&
        c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    } else if ((base == 0 || base == 2) &&
        c == '0' && (*s == 'b' || *s == 'B')) {
        c = s[1];
        s += 2;
        base = 2;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= (unsigned long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if (esp_isdigit(c))
            c -= '0';
        else if (esp_isalpha(c))
            c -= esp_isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }

    if (any < 0) {
        acc = neg ? LONG_MIN : LONG_MAX;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return (acc);
}

LOCAL int ICACHE_FLASH_ATTR chunked_decode(char * chunked, int size){
    char *src = chunked;
    char *end = chunked + size;
    int i, dst = 0;

    do{
        i = esp_strtol(src, (char **) NULL, 16);
        os_printf("Chunk Size:%d\r\n", i);
        if (i <= 0)
            break;

        src = (char *)os_strstr(src, "\r\n") + 2;
        os_memmove(&chunked[dst], src, i);
        src += i + 2;
        dst += i;
    }while(src < end);

    return dst;
}

/* END References */

/**
 * @brief TCP Client Receive Callback
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_revcb(void * arg, char * buf, unsigned short len){
    char json_out[2048];
    struct espconn * conn = (struct espconn *)arg;
    request_args * req = (request_args *)conn->reverse;

    if(req->buffer == NULL){return;}

    const int new_size = req->buffer_size + len;
    char * new_buffer;

    if (new_size > BUFFER_SIZE_MAX || NULL == (new_buffer = (char *)os_malloc(new_size))){
        os_printf("Response too long (%d)\r\n", new_size);
        req->buffer[0] = '\0';
        if (req->secure)
            espconn_secure_disconnect(conn);
        else
            espconn_disconnect(conn);
        return;
    }

    os_memcpy(new_buffer, req->buffer, req->buffer_size);
    os_memcpy(new_buffer + req->buffer_size - 1, buf, len);
    new_buffer[new_size - 1] = '\0';

    os_free(req->buffer);
    req->buffer = new_buffer;
    req->buffer_size = new_size;

    os_printf("Received http:\r\n");
    os_printf("%s\r\n\r\n",new_buffer);
}

/**
 * @brief TCP Client Sent Callback
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_sentcb(void * arg){
    struct espconn * conn = (struct espconn *)arg;
    request_args * req = (request_args *)conn->reverse;

    if (req->post_data == NULL) {
        os_printf("All http request sent\r\n\r\n");
    }
    else {
        os_printf("ESP8266 sending request body\r\n");
        if (req->secure)
            espconn_secure_sent(conn, (uint8_t *)req->post_data, strlen(req->post_data));
        else
            espconn_sent(conn, (uint8_t *)req->post_data, strlen(req->post_data));

        os_printf(req->post_data);

        os_free(req->post_data);
        req->post_data = NULL;
    }
}

/**
 * @brief TCP Client Connect Callback
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_conncb(void * arg){
    os_printf("Connected\r\n");

    struct espconn *conn = (struct espconn *)arg;
    request_args *req = (request_args *)conn->reverse;

    espconn_regist_recvcb(conn, tcp_client_revcb);
    espconn_regist_sentcb(conn, tcp_client_sentcb);

    const char *method = "GET";
    char post_headers[1024] = "";

    if(req->post_data != NULL){
        method = "POST";
        os_sprintf(post_headers, "Content-Length: %d\r\n", strlen(req->post_data));
    }

    if(req->headers == NULL){
        req->headers = "";
    }

    char buf[69 + strlen(method) + strlen(req->path) + strlen(req->hostname) +
                 strlen(req->headers) + strlen(post_headers)];

    int len = os_sprintf(buf,
                         "%s %s HTTP/1.1\r\n"
                         "Host: %s:%d\r\n"
                         "Connection: close\r\n"
                         "User-Agent: ESP8266\r\n"
                         "%s"
                         "%s"
                         "\r\n",
                         method, req->path, req->hostname, req->port, req->headers, post_headers);

    if (req->secure)
        espconn_secure_sent(conn, (uint8_t *)buf, len);
    else
        espconn_sent(conn, (uint8_t *)buf, len);

    os_printf("ESP8266 sending request header\r\n");
    os_printf(buf);

    req->headers = NULL;
}

/**
 * @brief TCP Client Disconnect Callback
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_disconncb(void * arg){
    os_printf("client disconnected\r\n");
    struct espconn *conn = (struct espconn *)arg;

    if(conn == NULL){
        os_printf("Connection pointer is NULL\r\n");
        return;
    }

    if(conn->reverse != NULL){
        request_args * req = (request_args *)conn->reverse;
        int http_status = -1;
        int body_size = 0;
        char * body = "";

        if(req->buffer == NULL){
            os_printf("Buffer shouldn't be NULL\r\n");
        }
        else if(req->buffer[0] != '\0'){
            const char * version10 = "HTTP/1.0 ";
            const char * version11 = "HTTP/1.1 ";
            if (os_strncmp(req->buffer, version10, strlen(version10)) != 0
                && os_strncmp(req->buffer, version11, strlen(version11)) != 0) {
                os_printf("Invalid version in %s\n", req->buffer);
            }
            else{
                http_status = atoi(req->buffer + strlen(version10));
                body = (char *)os_strstr(req->buffer, "\r\n\r\n") + 2;
                *body++ = '\0';
                *body++ = '\0';

                body_size = req->buffer_size - (body - req->buffer);
                if(os_strstr(req->buffer, "Transfer-Encoding: chunked")){
                    body_size = chunked_decode(body, body_size);
                    body[body_size] = '\0';
                }
            }
        }

        os_free(req->buffer);
        os_free(req->hostname);
        os_free(req->path);
        os_free(req);
    }

    espconn_delete(conn);
    if(conn->proto.tcp != NULL){ os_free(conn->proto.tcp); }
    os_free(conn);
}

/**
 * @brief TCP Client Error Callback
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_errorcb(void *arg, sint8 errType){
    os_printf("disconnected with error: %d\r\n",errType);
    tcp_client_disconncb(arg);
}

/**
 * @brief Main HTTP Client Callback
 * @param URL Hostname
 * @param Resolved Address
 * @param Cumulative Arguments
 * @details Not to be called directly except from HTTP request routine
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_http(const char * hostname, ip_addr_t * addr, void * arg){
    request_args * req = (request_args *)arg;

    if(addr == NULL){
        os_printf("DNS failed for %s\r\n", hostname);
        os_free(req->buffer);
        os_free(req->post_data);
        os_free(req->headers);
        os_free(req->path);
        os_free(req->hostname);
        os_free(req);
    }
    else{
        os_printf("DNS found %s as " IPSTR "\r\n", hostname, IP2STR(addr));

        struct espconn * conn = (struct espconn *)os_malloc(sizeof(struct espconn));
        conn->type = ESPCONN_TCP;
        conn->state = ESPCONN_NONE;
        conn->proto.tcp = (esp_tcp *)os_malloc(sizeof(esp_tcp));
        conn->proto.tcp->local_port = espconn_port();
        conn->proto.tcp->remote_port = req->port;
        conn->reverse = req;

        os_memcpy(conn->proto.tcp->remote_ip, addr, 4);

        espconn_regist_connectcb(conn, tcp_client_conncb);
        espconn_regist_disconcb(conn, tcp_client_disconncb);
        espconn_regist_reconcb(conn, tcp_client_errorcb);

        if(req->secure){
            espconn_secure_set_size(ESPCONN_CLIENT,5120); // set SSL buffer size
            espconn_secure_connect(conn);
        }else{
            espconn_connect(conn);
        }
    }
}

/**
 * @brief DNS found/resolved callback
 * @param[in] Resolved Hostname URL
 * @param[in] Resolved IP Address
 * @param[in] Complete DNS resolver arguments
 */
LOCAL void ICACHE_FLASH_ATTR dns_found_cb(const char *hostname, ip_addr_t *ipaddr, void *arg){
    request_args *req = (request_args *)arg;
    os_printf("DNS resolved\r\n");
    tcp_client_http(hostname, ipaddr, req);
}

/**
 * @brief Basic/RAW client request
 * @param[in] Hostname URL
 * @param[in] Port number
 * @param[in] Secure SSL
 * @param[in] Path URL
 * @param[in] POST data
 * @param[in] Data headers
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_raw(const char * hostname, int port, bool secure, const char * path, const char * post_data, const char * headers){
    request_args *req = (request_args *)os_malloc(sizeof(request_args));

    req->hostname = esp_strdup(hostname);
    req->path = esp_strdup(path);
    req->port = port;
    req->secure = secure;
    req->headers = esp_strdup(headers);
    req->post_data = esp_strdup(post_data);

    req->buffer_size = 1;
    req->buffer = (char *)os_malloc(1);
    req->buffer[0] = '\0';

    ip_addr_t addr;
    err_t error = espconn_gethostbyname((struct espconn *)req,hostname,&addr,&dns_found_cb);

    if(error==ESPCONN_OK){
        os_printf("DNS resolved\r\n");
        tcp_client_http(hostname, &addr, req);
    }
    else if(error==ESPCONN_INPROGRESS){os_printf("DNS pending\r\n");}
    else if(error==ESPCONN_ARG){os_printf("DNS argument error %s\r\n",hostname);}
    else{os_printf("DNS error code %d\r\n", error);}
}

/**
 * @brief HTTP client request
 * @param Request URL
 * @param POST data
 * @param Data headers
 */
LOCAL void ICACHE_FLASH_ATTR tcp_client_request(const char * url, const char * post_data, const char * headers){
    char hostname[128] = "";
    int port = 80;
    bool secure = false;

    bool is_http  = os_strncmp(url, "http://",  strlen("http://"))  == 0;
    bool is_https = os_strncmp(url, "https://", strlen("https://")) == 0;

    if(is_http){ url += strlen("http://"); }
    else if(is_https) {
        port = 443;
        secure = true;
        url += strlen("https://");
    }
    else{ os_printf("URL is not HTTP or HTTPS %s\r\n", url); return; }

    char * path = os_strchr(url, '/');
    if(path == NULL){ path = os_strchr(url, '\0'); }

    char * colon = os_strchr(url, ':');
    if(colon > path){ colon = NULL; }

    if (colon == NULL) {
        os_memcpy(hostname, url, path - url);
        hostname[path - url] = '\0';
    }
    else{
        port = atoi(colon + 1);
        if (port == 0) { os_printf("Port error %s\r\n", url); return; }

        os_memcpy(hostname, url, colon - url);
        hostname[colon - url] = '\0';
    }

    if(path[0] == '\0'){ path = "/"; }

    tcp_client_raw(hostname, port, secure, path, post_data, headers);
}

void ICACHE_FLASH_ATTR tcp_client_get(const char * url){
    tcp_client_request(url,NULL,NULL);
}

void ICACHE_FLASH_ATTR tcp_client_gethdr(const char * url, const char * headers){
    tcp_client_request(url,NULL,headers);
}

void ICACHE_FLASH_ATTR tcp_client_post(const char * url, const char * post_data, const char * headers){
    tcp_client_request(url,post_data,headers);
}

/** @} */

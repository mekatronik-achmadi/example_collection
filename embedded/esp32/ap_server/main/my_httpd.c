#include "my_includes.h"

static const char *TAG = "httpd";

static char hello_info[RESP_STR_LEN];

/**
 * @brief HTTP GET handler
 *
 */
static esp_err_t hello_get_hndl(httpd_req_t *req){
    char *buf;
    size_t buf_len;

    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if(buf_len > 1){
        buf = malloc(buf_len);
        if(httpd_req_get_hdr_value_str(req,"Host",buf,buf_len)==ESP_OK){
            ESP_LOGI(TAG, "Found header -> Host %s", buf);
        }
        free(buf);
    }

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if(buf_len>1){
        buf = malloc(buf_len);
        if(httpd_req_get_url_query_str(req,buf,buf_len)==ESP_OK){
            ESP_LOGI(TAG, "Found URL query -> %s",buf);
        }
        free(buf);
    }

    //const char *resp_str=(const char*) req->user_ctx;
    const char *resp_str=(const char*) hello_info;
    httpd_resp_send(req,resp_str,HTTPD_RESP_USE_STRLEN);

    if(httpd_req_get_hdr_value_len(req,"Host")==0){
        ESP_LOGI(TAG,"Request headers lost");
    }

    return ESP_OK;
}

static void hello_version(){
    esp_chip_info_t info;
    esp_chip_info(&info);
    sprintf(hello_info,"<font size=\"+2\">Hello World from ESP32:</font><br>");
    sprintf(hello_info+strlen(hello_info),"IDF Version:%d.%d.%d<br>",ESP_IDF_VERSION_MAJOR,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH);
    sprintf(hello_info+strlen(hello_info),"Chip info:<br>");
    sprintf(hello_info+strlen(hello_info),"&nbsp;&nbsp; model:%s<br>",info.model == CHIP_ESP32 ? "ESP32" : "Unknow");
    sprintf(hello_info+strlen(hello_info),"&nbsp;&nbsp; cores:%d<br>",info.cores);
    sprintf(hello_info+strlen(hello_info),"&nbsp;&nbsp; feature:%s%s%s%s%d%s<br>",
           info.features & CHIP_FEATURE_WIFI_BGN ? "/802.11bgn" : "",
           info.features & CHIP_FEATURE_BLE ? "/BLE" : "",
           info.features & CHIP_FEATURE_BT ? "/BT" : "",
           info.features & CHIP_FEATURE_EMB_FLASH ? "/Embedded-Flash:" : "/External-Flash:",
           spi_flash_get_chip_size() / (1024 * 1024), " MB");
    sprintf(hello_info+strlen(hello_info),"&nbsp;&nbsp; revision number:%d\r\n",info.revision);
}

static const httpd_uri_t hello = {
    .uri = "/hello",
    .method = HTTP_GET,
    .handler = hello_get_hndl,
    .user_ctx = "Hello World"
};

/**
 * @brief An error handler function
 */
esp_err_t http_404_err_hndl(httpd_req_t *req, httpd_err_code_t err){
    if(strcmp("/hello", req->uri)==0){
        httpd_resp_send_err(req,HTTPD_404_NOT_FOUND,"hello URI is not found");
        return ESP_OK;
    }

    httpd_resp_send_err(req,HTTPD_404_NOT_FOUND, "Your Request is not found");
    return ESP_FAIL;
}

static httpd_handle_t start_webserver(void){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    ESP_LOGI(TAG,"Starting server on port: %d",config.server_port);
    if(httpd_start(&server,&config)==ESP_OK){
        ESP_LOGI(TAG, "Register URI handlers");
        httpd_register_uri_handler(server,&hello);
        return server;
    }

    ESP_LOGI(TAG, "Server start error");
    return NULL;
}

#if HTTPD_START_ON_CONNECT
static esp_err_t stop_webserver(httpd_handle_t server){
    return httpd_stop(server);
}

static void disconn_hndl(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        if (stop_webserver(*server) == ESP_OK) {
            *server = NULL;
        } else {
            ESP_LOGE(TAG, "Failed to stop http server");
        }
    }
}

static void conn_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}
#endif

void httpdInit(void){
   static httpd_handle_t server = NULL;

   hello_version();

   server = start_webserver();
   if(server==NULL){
       ESP_LOGI(TAG, "Webserver Failed");
   }
   else{
       ESP_LOGI(TAG, "Webserver Success");
   }
}

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

/* error message for debugging */
void error(const char *msg) { perror(msg); exit(0); }

int main(int argc,char *argv[]){
    int portno          = 6500;
    char *host          = "safevision.id";
    char *message_fmt   = "POST /user/resident/register HTTP/1.1\r\n";
    
    
    char *message_body  = \
    "{\n"\
        "\"username\": \"user1\",\n" \
        "\"email\": \"user1@gmail.com\",\n" \
        "\"password\": \"password\"\n" \
    "}\n";
    
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024],message_hdr[1024],response[4096];
    
    /* fill in the parameters */
    sprintf(message_hdr,
            "Content-Type: application/json\r\n" \
            "Accept: application/json\r\n" \
            "Host: domain\r\n" \
            "Content-Length: %i\r\n" \
            "\r\n",
            strlen(message_body));
    sprintf(message,"%s%s%s",message_fmt,message_hdr,message_body);
    printf("Request:\n\n%s\n",message);
    
    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    
    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");
    
    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    
    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }
    
    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);
    
    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);
    
    if (received == total){
        error("ERROR storing complete response from socket");
    }
    
    /* close the socket */
    close(sockfd);
    
    /* process response */
    printf("Response:\n%s\n",response);

    return 0;
}

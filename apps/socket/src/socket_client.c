#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "blogger.h"

#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
    blog_init(LOG_INFO);
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        BLOG(LOG_ERR, "Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        BLOG(LOG_ERR, "Invalid address/ Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        BLOG(LOG_ERR, "Connection Failed");
        return -1;
    }

    char *message = "Hello, Server!";
    BLOG(LOG_INFO, "Sending: %s", message);
    send(sock, message, strlen(message), 0);

    memset(buffer, 0, BUFFER_SIZE);
    int valread = read(sock, buffer, BUFFER_SIZE);
    BLOG(LOG_INFO, "Received: %s, len %d", buffer, valread);

    close(sock);
    return 0;
}

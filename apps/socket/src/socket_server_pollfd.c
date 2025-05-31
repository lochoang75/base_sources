#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "abstract_event.h"
#include "abstract_fd_mon.h"
#include "blogger.h"
#include "threadpool.h"

#define PORT 65432
#define BUFFER_SIZE 1024

static int client_fd_open(const char *file_name __attribute__((unused)), void *user_data __attribute__((unused)))
{
    return -1;
}

static void client_fd_close(int fd, void *user_data __attribute__((unused)))
{
    close(fd);
}

static int client_fd_exception_handle(scheduler_mon_t *scheduler, struct mon_event *event)
{
    close(event->fd);
    free(event->user_data);
    unregister_handler(scheduler, event->fd);
    return 0;
}

static int client_fd_read_handle(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event)
{
    BLOG_ENTER();
    char *buffer = (char*)event->user_data;
    memset(buffer, 0, BUFFER_SIZE);
    int valread = read(event->fd, buffer, BUFFER_SIZE);
    if (valread <= 0) {
        return -1;
    }
    BLOG(LOG_INFO, "Received: %s", buffer);
    BLOG_EXIT();
    return 0;
}

static int client_fd_write_handle(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event)
{
    char *buffer = (char*)event->user_data;
    if (strlen(buffer) > 0)
    {
        send(event->fd, buffer, BUFFER_SIZE, 0);
    }
    return 0;
}

static int client_fd_termiated_handle(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute__((unused)))
{
    return 0;
}

static struct mon_event_handler client_fd_handler = {
    .open = client_fd_open,
    .close = client_fd_close,
    .on_exception = client_fd_exception_handle,
    .on_read = client_fd_read_handle,
    .on_write = client_fd_write_handle,
    .on_terminate = client_fd_termiated_handle,
};

static int server_fd_open(const char *file_name __attribute__((unused)), void *user_data)
{
    struct sockaddr_in *address = (struct sockaddr_in *)user_data;
    int server_fd;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        BLOG(LOG_ERR, "Socket failed");
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        BLOG(LOG_ERR, "setsockopt");
        close(server_fd);
        return -1;
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)address, sizeof(struct sockaddr_in)) < 0) {
        BLOG(LOG_ERR, "Bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        BLOG(LOG_ERR, "Listen");
        close(server_fd);
        return -1;
    }

    BLOG(LOG_INFO, "Server listening on port %d", PORT);
    return server_fd;

}

static void server_fd_close(int fd, void *user_data __attribute__((unused)))
{
    close(fd);
}

static int server_fd_exception_handle(scheduler_mon_t *scheduler , struct mon_event *event)
{
    close(event->fd);
    unregister_handler(scheduler, event->fd);
    return 0;
}

static int server_fd_read_handle(scheduler_mon_t *scheduler, struct mon_event *event)
{
    BLOG_ENTER();
    int server_fd = event->fd;
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    if (buffer == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory for client buffer");
        return 0;
    }
    struct sockaddr *address = (struct sockaddr*)event->user_data;
    int addrlen = sizeof(struct sockaddr_in);
    int new_socket = -1;
    if ((new_socket = accept(server_fd, address, (socklen_t*)&addrlen)) < 0) {
        BLOG(LOG_ERR, "Accept");
        return -1;
    }
    struct mon_request_info *client_request = make_request_info("client_addr", &client_fd_handler);
    set_request_fd(client_request, new_socket);
    set_request_user_data(client_request, buffer);
    register_handler(scheduler, client_request);
    BLOG_EXIT();
    return 0;
}

static int server_fd_write_handle(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute__((unused)))
{
    return 0;
}

static int server_fd_terminated_handle(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute__((unused)))
{
    return 0;
}

static struct mon_event_handler server_fd_handler = {
    .open = server_fd_open,
    .close = server_fd_close,
    .on_exception = server_fd_exception_handle,
    .on_read = server_fd_read_handle,
    .on_write = server_fd_write_handle,
    .on_terminate = server_fd_terminated_handle,
};


int main(int argc __attribute__((unused)), char **argv) {
    blog_init(LOG_DEBUG, argv[0]);
    threadpool_t *tpool = threadpool_create(32, 32, 0);
    if (tpool == NULL)
    {
        BLOG(LOG_ERR, "Failed to create tpool");
        return -1;
    }
    struct scheduler_mon *monitor = open_scheduler("pollfd_socket", eMON_USE_POLL);
    if (monitor == NULL)
    {
        BLOG(LOG_ERR, "Failed to open poll socket");
        return -1;
    }
    struct sockaddr_in address;
    struct mon_request_info *server_request = make_request_info("socket_addr", &server_fd_handler);
    set_request_user_data(server_request, &address);
    register_handler(monitor, server_request);
    start_scheduler(monitor);
    return 0;
}

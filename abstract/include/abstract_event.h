#ifndef ABSTRACT_EVENT_H
#define ABSTRACT_EVENT_H
#include "abstract_enum.h"
#include "abstract_config.h"
#include <stdlib.h>

typedef struct scheduler_mon scheduler_mon_t;
struct mon_event {
    int fd;
    char *file_path;
    size_t file_path_len;
    void *user_data;
};

struct mon_event_handler {
    int (*open)(const char *file_name, void *user_data);
    void (*close)(int fd, void *user_data);
    int (*on_exception)(scheduler_mon_t *scheduler, struct mon_event *event);
    int (*on_read)(scheduler_mon_t *scheduler, struct mon_event *event);
    int (*on_write)(scheduler_mon_t *scheduler, struct mon_event *event);
    int (*on_terminate)(scheduler_mon_t *scheduler, struct mon_event * event);
};

struct mon_request_info {
    char *file_name;
    size_t file_name_len;
    mon_open_mode_t open_mode;
    struct mon_event_handler *handler;
    void *user_data;
    char ext_data[0];
};

ALLOC_MEM_FUNC struct mon_request_info *clone_request_info(struct mon_request_info *info);
ALLOC_MEM_FUNC struct mon_request_info *make_request_info(const char *file_name, struct mon_event_handler *handler);
int set_request_open_mode(struct mon_request_info *info, mon_open_mode_t mode);
int set_request_user_data(struct mon_request_info *info, void *user_data);
void copy_reqeust_info(struct mon_request_info *dst, struct mon_request_info *src);
size_t get_request_info_size(const struct mon_request_info *info);
#endif /*ABSTRACT_EVENT_H*/

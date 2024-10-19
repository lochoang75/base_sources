#ifndef BASE_EVENT_H
#define BASE_EVENT_H

typedef struct scheduler_mon scheduler_mon_t;
struct fd_event {
    int fd;
    char *file_path;
    void *user_data;
};

struct fd_handler {
    int (*open)(scheduler_mon_t *scheduler, void *user_data);
    void (*close)(scheduler_mon_t *scheduler);
    int (*exception)(scheduler_mon_t *scheduler, struct fd_event *event);
    int (*read)(scheduler_mon_t *scheduler, struct fd_event *event);
    int (*write)(scheduler_mon_t *scheduler, struct fd_event *event);
};


#endif /*BASE_EVENT_H*/
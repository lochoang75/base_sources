#ifndef BASE_ENUM_H
#define BASE_ENUM_H
typedef enum fd_mon_type {
    FD_MON_USE_POLL = 0,
    FD_MON_USE_SELECT,
    FD_MON_USE_EPOLL
} fd_mon_type_t;
#endif /*BASE_ENUM_H*/
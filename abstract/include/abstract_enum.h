#ifndef ABSTRACT_ENUM_H
#define ABSTRACT_ENUM_H
typedef enum {
    FD_MON_USE_POLL = 0,
    FD_MON_USE_SELECT,
    FD_MON_USE_EPOLL
} fd_mon_type_t;
#endif /*ABSTRACT_ENUM_H*/

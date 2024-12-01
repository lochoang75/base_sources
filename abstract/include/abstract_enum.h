#ifndef ABSTRACT_ENUM_H
#define ABSTRACT_ENUM_H
typedef enum {
    MON_USE_POLL = 0,
    MON_USE_SELECT,
    MON_USE_EPOLL
} mon_type_t;

typedef enum {
    MON_OPEN_MODE_READ = 0x01,
    MON_OPEN_MODE_WRITE = 0x02
} mon_open_mode_t;
#endif /*ABSTRACT_ENUM_H*/

#ifndef ABSTRACT_ENUM_H
#define ABSTRACT_ENUM_H
typedef enum {
    eMON_USE_POLL = 0,
    eMON_USE_SELECT,
    eMON_USE_EPOLL
} mon_type_t;

typedef enum {
    eMON_OPEN_MODE_READ = 0x01,
    eMON_OPEN_MODE_WRITE = 0x02
} mon_open_mode_t;
#endif /*ABSTRACT_ENUM_H*/

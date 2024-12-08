#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H
/* #define USE_SYSLOG */
#define VERSION_MAJOR    1
#define VERSION_MINOR    0
#define VERSION_REVISION 0
#define LOG_BUFFER_SIZE 4096

/* ALLOC_MEM_FUNC tag function perform memory alloc inside,
    user need to take care of the return
*/
#define ALLOC_MEM_FUNC

/*LOCK_FUNC tag function will lock the calling thread when execute,
    and return in some condition met*/
#define LOCK_FUNC

/*ASYNC_FUNC tag function will run in async mode*/
#define ASYNC_FUNC

#endif /*BASE_CONFIG_H*/

#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H
#include "module_config.h"

/* ALLOC_MEM_FUNC tag function perform memory alloc inside,
    user need to take care of the return
*/
#define ALLOC_MEM_FUNC

/*LOCK_FUNC: tag function will lock the calling thread when execute,
    and return in some condition met*/
#define LOCK_FUNC

/*ASYNC_FUNC: tag function will run in async mode*/
#define ASYNC_FUNC

#endif /*ABSTRACT_CONFIG_H*/

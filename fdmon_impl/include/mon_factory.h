#ifndef MON_FACTORY_H
#define MON_FACTORY_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "abstract_fd_mon.h"

struct scheduler_action *make_fd_mon(mon_type_t type);
#ifdef __cplusplus
}
#endif
#endif /*MON_FACTORY_H*/

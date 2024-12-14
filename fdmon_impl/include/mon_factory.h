#ifndef MON_FACTORY_H
#define MON_FACTORY_H
#include "abstract_fd_mon.h"

struct scheduler_action *make_fd_mon(mon_type_t type);
#endif /*MON_FACTORY_H*/

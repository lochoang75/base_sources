#include "abstract_string_helper.h"

const char *fd_mon_to_string(mon_type_t type)
{
    switch (type)
    {
    case MON_USE_EPOLL:
        return "FD_MON_USE_EPOLL";
    case MON_USE_POLL:
        return "FD_MON_USE_POLL";
    case MON_USE_SELECT:
        return "FD_MON_USE_SELECT";
    default:
        break;
    }
    return "UNKNOWN_FD_MON";
}

#include "mon_factory.h"

#include "blogger.h"
#include "abstract_string_helper.h"

#include "pollfd_mon.h"
#include "epollfd_mon.h"
#include "selectfd_mon.h"

struct scheduler_action *make_fd_mon(mon_type_t type)
{
    struct scheduler_action *action = NULL;
    switch (type)
    {
    case eMON_USE_EPOLL:
        action = epollfd_open_mon();
        break;
    case eMON_USE_POLL:
        action = pollfd_open_mon();
        break;
    case eMON_USE_SELECT:
        action = selectfd_open_mon();
        break;
    default:
        BLOG(LOG_ERR, "Unable to open scheduler for type: %s", fd_mon_to_string(type));
        return action;
    }

    BLOG(LOG_INFO, "Open fd mon at (%p), type %s", action, fd_mon_to_string(type));
    return action;
}

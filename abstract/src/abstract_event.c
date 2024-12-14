#include "abstract_event.h"
#include <stdlib.h>

#include "blogger.h"

ALLOC_MEM_FUNC struct mon_request_info *clone_request_info(struct mon_request_info *info)
{
    if (info == NULL)
    {
        BLOG(LOG_ERR, "Unable to clone request info, input is NULL");
        return NULL;
    }

    struct mon_request_info *clone = malloc(sizeof(struct mon_request_info) + info->file_name_len);
    if (info == NULL)
    {
        BLOG(LOG_ERR, "Unable to allocate memory");
    }
    memset(clone, 0, sizeof(struct mon_request_info) + info->file_name_len);
    clone->file_name = clone->ext_data;
    clone->file_name_len = info->file_name_len;
    clone->open_mode = info->open_mode;
    clone->handler = info->handler;
    clone->user_data = info->user_data;
    memcpy(clone->file_name, info->file_name, info->file_name_len);
    return clone;
}

struct mon_request_info *make_request_info(const char *file_name, struct mon_event_handler *handler)
{
    if (file_name == NULL || handler == NULL)
    {
        BLOG(LOG_WARNING, "file name is (%p), handler (%p)", file_name, handler);
        return NULL;
    }

    int alloc_size = sizeof(struct mon_request_info) + strlen(file_name) + 1;
    struct mon_request_info *request_info = malloc(alloc_size);
    if (request_info == NULL)
    {
        BLOG(LOG_WARNING, "Unable to allocate memory");
        return NULL;
    }
    memset(request_info, 0, alloc_size);
    request_info->file_name = request_info->ext_data;
    request_info->file_name_len = strlen(file_name) + 1;
    request_info->open_mode = eMON_OPEN_MODE_READ | eMON_OPEN_MODE_WRITE;
    request_info->handler = handler;
    request_info->user_data = NULL;
    request_info->fd = -1;
    memcpy(request_info->file_name, file_name, request_info->file_name_len);
    return request_info;
}

int set_request_open_mode(struct mon_request_info *info, mon_open_mode_t mode)
{
    if (info == NULL)
    {
        BLOG(LOG_WARNING, "Info is null, unable to set mode" );
        return -1;
    }

    info->open_mode = mode;
    return 0;
}

int set_request_user_data(struct mon_request_info *info, void *user_data)
{
    if (info == NULL)
    {
        BLOG(LOG_WARNING, "Info is null, unable to set user_data" );
        return -1;
    }

    info->user_data = user_data;
    return 0;
}

int set_request_fd(struct mon_request_info *info, int fd)
{
    if (info == NULL)
    {
        BLOG(LOG_WARNING, "Info is null, unable to set user_data" );
        return -1;
    }

    info->fd = fd;
    return 0;
}

void copy_request_info(struct mon_request_info *dst, struct mon_request_info *src)
{
    dst->file_name_len = src->file_name_len;
    dst->handler = src->handler;
    dst->open_mode = src->open_mode;
    dst->user_data = src->user_data;
    dst->fd = src->fd;
    dst->file_name = dst->ext_data;
    memcpy(dst->file_name, src->file_name, src->file_name_len);
}

size_t get_request_info_size(const struct mon_request_info *info)
{
    size_t request_size = sizeof(struct mon_request_info);
    request_size += info->file_name_len;
    return request_size;
}

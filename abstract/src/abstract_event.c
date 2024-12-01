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
    clone->file_name = clone->ext_data;
    clone->file_name_len = info->file_name_len;
    clone->open_mode = info->open_mode;
    clone->handler = info->handler;
    clone->user_data = info->user_data;
    memcpy(clone->file_name, info->file_name, info->file_name_len);
    return clone;
}

void copy_reqeust_info(struct mon_request_info *dst, struct mon_request_info *src)
{
    dst->file_name_len = src->file_name_len;
    dst->handler = src->handler;
    dst->open_mode = src->open_mode;
    dst->user_data = src->user_data;
    dst->file_name = dst->ext_data;
    memcpy(dst->file_name, src->file_name, src->file_name_len);
}

size_t get_request_info_size(const struct mon_request_info *info)
{
    size_t request_size = sizeof(struct mon_request_info);
    request_size += info->file_name_len;
    return request_size;
}

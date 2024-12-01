#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "abstract_config.h"
#include "abstract_errors.h"
#include "blogger.h"

#define list_for_each(list, pos) \
        for(pos = list->next; !list_is_list_head(list, pos); pos = pos->next)

#define list_forech_reverse(list, pos) \
        for(pos = list->prev; !list_is_list_head(list, pos); pos = pos->prev)

struct list_node {
    struct list_node *next;
    struct list_node *prev;
    void *data;
};

static bool list_is_list_head(struct list_node *list, struct list_node *head)
{
    if (list == head)
    {
        return true;
    } else
    {
        return false;
    }
}

struct list_node *list_init(struct list_node *head)
{
    head->next = head;
    head->prev = head;
    return head;
}

ALLOC_MEM_FUNC base_error_t list_add_tail(struct list_node *list, void *data)
{
    if (list == NULL || data == NULL)
    {
        return kINVALID_MEM;
    }

    struct list_node *node = malloc(sizeof(struct list_node));
    if (node == NULL)
    {
        return kNO_MEM;
    }
    node->data = data;
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
    return kSUCCESS;

    return kERROR;
}

ALLOC_MEM_FUNC base_error_t list_add_head(struct list_node *list, void *data)
{
    if (list == NULL || data == NULL)
    {
        return kINVALID_MEM;
    }

    struct list_node *node = malloc(sizeof(struct list_node));
    if (node == NULL)
    {
        return kNO_MEM;
    }
    node->data = data;
    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;
    return kSUCCESS;
}

struct list_node *list_ref(struct list_node *list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }

    struct list_node *tmp = list;
    for (tmp = list; !list_is_list_head(list, tmp); tmp = tmp->next)
    {
        index--;
    }
    if (index != 0 && list_is_list_head(list, tmp))
    {
        return tmp;
    }
    return NULL;
}

base_error_t list_remove(struct list_node *list, struct list_node *node)
{
    if (list == NULL)
    {
        return kINVALID_MEM;
    }

    base_error_t ret = kINVALID_MEM;
    struct list_node *tmp = list;
    struct list_node *prev = NULL;
    for (tmp = list; !list_is_list_head(list, tmp); tmp = tmp->next)
    {
        if (tmp == node)
        {
            prev->next = tmp->next;
            free(tmp);
            ret = kSUCCESS;
            break;
        }
        prev = tmp;
    }
    return ret;
}

base_error_t list_remove_idx(struct list_node *list, size_t index)
{
    if (list == NULL)
    {
        return kINVALID_MEM;
    }

    base_error_t ret = kINVALID_MEM;
    struct list_node *tmp = list;
    struct list_node *prev = NULL;
    for (tmp = list; !list_is_list_head(list, tmp); tmp = tmp->next)
    {
        if (index == 0)
        {
            prev->next = tmp->next;
            free(tmp);
            ret = kSUCCESS;
            break;
        }
        index --;
        prev = tmp;
    }
    return ret;
}

int list_get_size(struct list_node *list)
{
    int count = 0;
    struct list_node *tmp = list;
    for (tmp = list; !list_is_list_head(list, tmp); tmp = tmp->next)
    {
        count ++;
    }
    return count;
}

base_error_t list_splice(struct list_node *list, struct list_node **other)
{
    if (list == NULL || other == NULL)
    {
        return kINVALID_MEM;
    }
    struct list_node *other_tail = (*other)->prev;
    list->prev->next = (*other)->next;
    list->prev = other_tail;
    *other = NULL;
    return kSUCCESS;
}

base_error_t list_del(struct list_node *list)
{
    if (list == NULL)
    {
        return kINVALID_MEM;
    }
    struct list_node *tmp = list->next;
    do {
        if (tmp == NULL || tmp == list)
        {
            break;
        } else
        {
            struct list_node *tmp_next = tmp->next;
            free(tmp);
            tmp = tmp_next;
        }
    } while (true);
    return kSUCCESS;
}
#endif /*LINKED_LIST_H*/

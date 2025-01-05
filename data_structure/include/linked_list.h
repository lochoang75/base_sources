#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "abstract_config.h"
#include "abstract_errors.h"
#include "blogger.h"

#define container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

#define list_for_each(list, pos) \
        for(pos = (list)->next; !list_is_list_head((list), pos); pos = pos->next)

#define list_forech_reverse(list, pos) \
        for(pos = (list)->prev; !list_is_list_head((list), pos); pos = pos->prev)

#define INIT_HEAD(node) {.next = (node), .prev = (node)}

struct list_node {
    struct list_node *next;
    struct list_node *prev;
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

static struct list_node *list_init(struct list_node *head)
{
    head->next = head;
    head->prev = head;
    return head;
}

static  base_error_t list_add_tail(struct list_node *list, struct list_node *node)
{
    if (list == NULL || node == NULL)
    {
        return kINVALID_MEM;
    }

    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
    return kSUCCESS;

    return kERROR;
}

static base_error_t list_add_head(struct list_node *list, struct list_node *node)
{
    if (list == NULL || node == NULL)
    {
        return kINVALID_MEM;
    }

    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;
    return kSUCCESS;
}

static struct list_node *list_ref(struct list_node *list, size_t index)
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

static base_error_t list_remove(struct list_node *node)
{
    base_error_t ret = kINVALID_MEM;
    struct list_node *prev = node->prev;
    struct list_node *next = node->next;
    prev->next = next;
    next->prev = prev;
    return ret;
}

static int list_get_size(struct list_node *list)
{
    int count = 0;
    struct list_node *tmp = list;
    for (tmp = list; !list_is_list_head(list, tmp); tmp = tmp->next)
    {
        count ++;
    }
    return count;
}

static base_error_t list_splice(struct list_node *list, struct list_node **other)
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

#ifdef __cplusplus
}
#endif
#endif /*LINKED_LIST_H*/

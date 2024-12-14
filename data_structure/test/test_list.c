#include "blogger.h"
#include "signal_handler.h"
#include "linked_list.h"

struct node_data {
    struct list_node node;
    int data;
};


static void print_list_data(struct list_node *head)
{
    struct list_node *item = NULL;
    struct node_data *node_data = NULL;
    list_for_each(head, item)
    {
        node_data = container_of(item, struct node_data, node);
        BLOG(LOG_DEBUG, "%d", node_data->data);
    }
}

int main()
{
    blog_init(LOG_DEBUG);
    struct list_node head;
    struct list_node other;
    BLOG(LOG_INFO, "Init list");
    list_init(&head);
    list_init(&other);
    BLOG(LOG_INFO, "App exit");
    struct node_data node_1 = {.node = {.next = NULL, .prev = NULL}, .data = 0};
    struct node_data node_2 = {.node = {.next = NULL, .prev = NULL}, .data = 1};
    struct node_data node_3 = {.node = {.next = NULL, .prev = NULL}, .data = 2};
    struct node_data node_4 = {.node = {.next = NULL, .prev = NULL}, .data = 3};
    int ret = 0;
    ret = list_add_tail(&head, &node_1.node);
    if (ret)
    {
        BLOG(LOG_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &node_2.node);
    if (ret)
    {
        BLOG(LOG_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &node_3.node);
    if (ret)
    {
        BLOG(LOG_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &node_4.node);
    if (ret)
    {
        BLOG(LOG_ERR, "Failed to add item to list, error %d", ret);
    }
    print_list_data(&head);
    return 0;
}
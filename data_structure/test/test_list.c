#include "blogger.h"
#include "signal_handler.h"
#include "linked_list.h"

static void print_list_data(struct list_node *head)
{
    struct list_node *item = NULL;
    list_for_each(head, item)
    {
        int *data = (int*)item->data;
        BLOG(LEVEL_DEBUG, "%d", *data);
    }
}

int main()
{
    blog_init(LEVEL_DEBUG);
    struct list_node head;
    struct list_node other;
    BLOG(LEVEL_INFO, "Init list");
    list_init(&head);
    list_init(&other);
    BLOG(LEVEL_INFO, "App exit");
    int dummy = 0;
    int dummy_1 = 1;
    int dummy_2 = 2;
    int dummy_3 = 3;
    int ret = 0;
    ret = list_add_tail(&head, &dummy, sizeof(int));
    if (ret)
    {
        BLOG(LEVEL_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &dummy_1, sizeof(int));
    if (ret)
    {
        BLOG(LEVEL_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &dummy_2, sizeof(int));
    if (ret)
    {
        BLOG(LEVEL_ERR, "Failed to add item to list, error %d", ret);
    }
    ret = list_add_tail(&head, &dummy_3, sizeof(int));
    if (ret)
    {
        BLOG(LEVEL_ERR, "Failed to add item to list, error %d", ret);
    }
    print_list_data(&head);
    list_del(&head);
    return 0;
}
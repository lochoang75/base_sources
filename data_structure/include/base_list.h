#ifndef BASE_LIST_H
#define BASE_LIST_H
struct list_node {
    struct list_node *next;
};

struct doubly_list_node {
    struct list_node *next;
    struct list_node *prev;
};
#endif /*BASE_LIST_H*/
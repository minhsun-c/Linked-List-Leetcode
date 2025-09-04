#include <assert.h>
#include <stddef.h>  // offsetof
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* -------- payload node -------- */
struct node {
    int data;
    struct ListNode link;
};

/* -------- helpers -------- */
#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - offsetof(type, member)))

static struct node *new_node(int val)
{
    struct node *n = malloc(sizeof(*n));
    assert(n);
    n->data = val;
    n->link.next = n->link.prev = NULL;
    return n;
}

static struct ListNode *new_head(void)
{
    struct ListNode *h = create_node();
    h->next = h->prev = h;
    return h;
}

static void print_list_data(struct ListNode *head, const char *tag)
{
    printf("%s [size=%d]:", tag, list_size(head));
    struct ListNode *p = head->next;
    while (p != head) {
        struct node *n = container_of(p, struct node, link);
        printf(" %d", n->data);
        p = p->next;
    }
    printf("\n");
}

/* -------- tests -------- */

static void test_create_node(void)
{
    printf("\n== test_create_node ==\n");
    struct ListNode *head = new_head();
    struct node *n = new_node(42);
    head = add_to_head(head, &n->link);

    assert(list_size(head) == 1);
    print_list_data(head, "after create_node");

    head = delete_node(head, &n->link);
    free(n);
    free(head);
}

static void test_push_head_tail(void)
{
    printf("\n== test_push_head_tail ==\n");
    struct ListNode *head = new_head();

    struct node *a = new_node(1);
    struct node *b = new_node(2);
    struct node *c = new_node(3);

    head = add_to_head(head, &a->link);  // [1]
    head = add_to_tail(head, &b->link);  // [1,2]
    head = add_to_head(head, &c->link);  // [3,1,2]

    assert(list_size(head) == 3);
    print_list_data(head, "after push head/tail");

    head = delete_node(head, &a->link);
    free(a);
    head = delete_node(head, &b->link);
    free(b);
    head = delete_node(head, &c->link);
    free(c);
    free(head);
}

static void test_empty_ops(void)
{
    printf("\n== test_empty_ops ==\n");
    struct ListNode *head = new_head();

    assert(list_size(head) == 0);
    print_list_data(head, "empty");

    head = del_head(head);  // no crash
    head = del_tail(head);  // no crash
    assert(list_size(head) == 0);

    free(head);
}

static void test_del_head_tail(void)
{
    printf("\n== test_del_head_tail ==\n");
    struct ListNode *head = new_head();

    struct node *a = new_node(10);
    struct node *b = new_node(20);
    struct node *c = new_node(30);

    add_to_tail(head, &a->link);
    add_to_tail(head, &b->link);
    add_to_tail(head, &c->link);
    print_list_data(head, "initial");

    struct ListNode *old = head->next;  // a
    head = del_head(head);
    free(container_of(old, struct node, link));
    print_list_data(head, "after del_head");

    old = head->prev;  // c
    head = del_tail(head);
    free(container_of(old, struct node, link));
    print_list_data(head, "after del_tail");

    // remove remaining b
    old = head->next;
    head = delete_node(head, old);
    free(container_of(old, struct node, link));
    assert(list_size(head) == 0);

    free(head);
}

static void test_delete_specific_node(void)
{
    printf("\n== test_delete_specific_node ==\n");
    struct ListNode *head = new_head();

    struct node *a = new_node(5);
    struct node *b = new_node(6);
    struct node *c = new_node(7);

    add_to_tail(head, &a->link);
    add_to_tail(head, &b->link);
    add_to_tail(head, &c->link);
    print_list_data(head, "initial");

    head = delete_node(head, &b->link);
    free(b);
    print_list_data(head, "after delete 6");

    head = delete_node(head, &a->link);
    free(a);
    print_list_data(head, "after delete 5");

    head = delete_node(head, &c->link);
    free(c);
    print_list_data(head, "after delete 7");

    assert(list_size(head) == 0);
    free(head);
}

static void test_concat(void)
{
    printf("\n== test_concat ==\n");

    struct ListNode *A = new_head();
    struct ListNode *B = new_head();

    struct node *a1 = new_node(1);
    struct node *a2 = new_node(2);
    struct node *b1 = new_node(100);
    struct node *b2 = new_node(200);

    add_to_tail(A, &a1->link);
    add_to_tail(A, &a2->link);
    add_to_tail(B, &b1->link);
    add_to_tail(B, &b2->link);

    print_list_data(A, "A before");
    print_list_data(B, "B before");

    struct ListNode *C = list_concat(A, B);
    print_list_data(C, "A concat B");

    assert(list_size(C) == 4);

    C = delete_node(C, &a1->link);
    free(a1);
    C = delete_node(C, &a2->link);
    free(a2);
    C = delete_node(C, &b1->link);
    free(b1);
    C = delete_node(C, &b2->link);
    free(b2);

    free(A);  // sentinel
    free(B);  // sentinel
}

/* -------- main -------- */
int main(void)
{
    printf("Linux-style doubly linked list tests\n");

    test_create_node();
    test_push_head_tail();
    test_empty_ops();
    test_del_head_tail();
    test_delete_specific_node();
    test_concat();

    printf("\nAll tests finished.\n");
    return 0;
}

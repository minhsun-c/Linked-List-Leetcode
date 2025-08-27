#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* ---------- helpers just for testing ---------- */

static void assert_size(struct ListNode *head, int expected)
{
    int n = list_size(head);
    printf("[check] size = %d (expected %d)\n", n, expected);
    assert(n == expected);
}

static struct ListNode *find_value(struct ListNode *head, int val)
{
    for (struct ListNode *p = head; p; p = p->next) {
        if (p->val == val)
            return p;
    }
    return NULL;
}

static void free_list(struct ListNode *head)
{
    while (head) {
        struct ListNode *n = head->next;
        free(head);
        head = n;
    }
}

/* ---------- individual scenario tests ---------- */

static void test_empty_ops(void)
{
    printf("\n== test_empty_ops ==\n");
    struct ListNode *head = NULL;
    assert_size(head, 0);

    head = del_head(head);
    assert(head == NULL);
    head = del_tail(head);
    assert(head == NULL);

    printf("print_list (empty): ");
    print_list(head);
}

static void test_push_head_tail(void)
{
    printf("\n== test_push_head_tail ==\n");
    struct ListNode *head = NULL;

    // head insert into empty
    head = add_to_head(head, create_node(10));
    assert(find_value(head, 10) == head);
    assert_size(head, 1);

    // tail append
    head = add_to_tail(head, create_node(20));
    head = add_to_tail(head, create_node(30));
    assert_size(head, 3);

    printf("print_list after head/tail inserts: ");
    print_list(head);

    free_list(head);
}

static void test_del_head_tail(void)
{
    printf("\n== test_del_head_tail ==\n");
    struct ListNode *head = NULL;
    head = add_to_tail(head, create_node(1));
    head = add_to_tail(head, create_node(2));
    head = add_to_tail(head, create_node(3));
    head = add_to_tail(head, create_node(4));
    assert_size(head, 4);
    printf("initial: ");
    print_list(head);

    // delete head (remove 1)
    struct ListNode *old_head = head;
    head = del_head(head);
    // delete functions do NOT free the removed node per spec
    free(old_head);
    assert_size(head, 3);
    assert(head && head->val == 2);
    printf("after del_head: ");
    print_list(head);

    // delete tail (remove 4)
    struct ListNode *p4 = find_value(head, 4);
    head = del_tail(head);
    // p4 should have been last; free it manually
    free(p4);
    assert_size(head, 2);
    assert(find_value(head, 4) == NULL);
    printf("after del_tail: ");
    print_list(head);

    free_list(head);
}

static void test_delete_specific_node(void)
{
    printf("\n== test_delete_specific_node ==\n");
    struct ListNode *head = NULL;
    head = add_to_tail(head, create_node(5));
    head = add_to_tail(head, create_node(6));
    head = add_to_tail(head, create_node(7));
    head = add_to_tail(head, create_node(8));
    printf("initial: ");
    print_list(head);
    assert_size(head, 4);

    // delete middle (value 7)
    struct ListNode *mid = find_value(head, 7);
    assert(mid);
    head = delete_node(head, mid);
    // per contract: not freed -> free it ourselves
    free(mid);
    assert_size(head, 3);
    assert(find_value(head, 7) == NULL);
    printf("after delete_node(7): ");
    print_list(head);

    // delete new head (value 5)
    struct ListNode *old = find_value(head, 5);
    head = delete_node(head, old);
    free(old);
    assert_size(head, 2);
    assert(head && head->val == 6);
    printf("after delete_node(5=head): ");
    print_list(head);

    // delete tail (value 8)
    struct ListNode *tail = find_value(head, 8);
    head = delete_node(head, tail);
    free(tail);
    assert_size(head, 1);
    printf("after delete_node(8=tail): ");
    print_list(head);

    free_list(head);
}

static void test_concat(void)
{
    printf("\n== test_concat ==\n");

    // A: [1,2,3]
    struct ListNode *A = NULL;
    A = add_to_tail(A, create_node(1));
    A = add_to_tail(A, create_node(2));
    A = add_to_tail(A, create_node(3));

    // B: [4,5]
    struct ListNode *B = NULL;
    B = add_to_tail(B, create_node(4));
    B = add_to_tail(B, create_node(5));

    printf("A: ");
    print_list(A);
    printf("B: ");
    print_list(B);

    struct ListNode *C = list_concat(A, B);
    // After concat, C should be [1,2,3,4,5], A should point to the same head,
    // and B nodes are now part of C (no copies)
    assert(C == A);
    assert_size(C, 5);
    printf("A concat B -> C: ");
    print_list(C);

    // Concat with empty A
    struct ListNode *D = NULL;
    struct ListNode *E = NULL;
    E = add_to_tail(E, create_node(42));
    E = add_to_tail(E, create_node(43));
    printf("D (empty): ");
    print_list(D);
    printf("E: ");
    print_list(E);
    struct ListNode *F = list_concat(D, E);
    assert(F == E);
    assert_size(F, 2);
    printf("D concat E -> F: ");
    print_list(F);

    free_list(C);  // frees 1..5
    // F points to E chain (42,43)
    free_list(F);
}

/* ---------- main ---------- */

int main(void)
{
    printf("Singly Linked List Test Runner\n");

    test_empty_ops();
    test_push_head_tail();
    test_del_head_tail();
    test_delete_specific_node();
    test_concat();

    printf("\nAll tests passed (assertions held).\n");
    return 0;
}

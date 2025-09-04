#ifndef __LIST_H
#define __LIST_H

struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
};

/*
 * create_node - Allocates and initializes a new ListNode.
 *
 * @val: Value to store in the node.
 *
 * Returns: Pointer to the newly created node,
 *          or NULL if memory allocation fails.
 */
struct ListNode *create_node();

/*
 * add_to_head - Inserts a node at the beginning of a singly linked list.
 *
 * @head: Pointer to the current head of the list.
 *        May be NULL if the list is empty.
 *
 * @node: Pointer to the node to be inserted.
 *        Must not be NULL. Its 'next' field will be updated.
 *
 * Returns: Pointer to the new head of the list (i.e., the inserted node).
 */
struct ListNode *add_to_head(struct ListNode *head, struct ListNode *node);

/*
 * add_to_tail - Appends a node to the end of the list.
 *
 * @head: Current head of the list (may be NULL).
 * @node: Node to append (must not be NULL). Its 'next' will be set to NULL.
 *
 * Returns: Head of the list (may be the same as input or the new node).
 */
struct ListNode *add_to_tail(struct ListNode *head, struct ListNode *node);

/*
 * list_size - Counts the number of nodes in the list.
 *
 * @head: Head of the list (may be NULL).
 *
 * Returns: Total number of nodes in the list.
 */
int list_size(struct ListNode *head);

/*
 * del_head - Removes the first node of the list.
 *
 * @head: Current head of the list.
 *
 * Returns: New head of the list (i.e., second node or NULL).
 *
 * Note: The removed node is not freed.
 */
struct ListNode *del_head(struct ListNode *head);

/*
 * del_tail - Removes the last node of the list.
 *
 * @head: Current head of the list.
 *
 * Returns: Head of the list (may be NULL if list is empty or has one node).
 *
 * Note: The removed node is not freed.
 */
struct ListNode *del_tail(struct ListNode *head);

/*
 * delete_node_by_value - Deletes a specific node from the list by pointer.
 *
 * @head:   Pointer to the head of the list (may be NULL).
 * @target: Pointer to the node to delete (must not be NULL).
 *
 * Returns: New head of the list (may change if target is the head).
 *
 * Note: If target is not found in the list, list remains unchanged.
 */
struct ListNode *delete_node(struct ListNode *head, struct ListNode *target);

/*
 * list_concat - Appends list B to the end of list A.
 *
 * @lista: Pointer to the head of the first list.
 *          May be NULL (in which case list B becomes the result).
 *
 * @listb: Pointer to the head of the second list.
 *          May be NULL (in which case list A is returned unchanged).
 *
 * Returns: Pointer to the head of the concatenated list.
 *
 * Behavior:
 * - If list A is empty, returns B.
 * - If list A is non-empty, traverses to its tail and links B to it.
 * - The nodes themselves are not copied—just the pointers are updated.
 */
struct ListNode *list_concat(struct ListNode *lista, struct ListNode *listb);


#endif  // __LIST_H

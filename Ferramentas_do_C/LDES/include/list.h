#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct _doubly_node DoublyNode, Node;
typedef struct _doubly_linked_list DoublyLinkedList, List;

Node *Node_create(float val);

List *List_create();
void List_destroy(List **L_ref);
bool List_is_empty(const List *L);
void List_add_first(List *L, float val);
void List_add_last(List *L, float val);
void List_print(const List *L);
void List_inverted_print(const List *L);

void List_remove(List *L, float val);
void List_add_wage(List *L, float val);
float Return_last_val(const List *L);
List* Return_inverted_list(List *L);
List* ReturnList_whitout_repetitive_nodes(List* L);
bool Repetitive_node(List*L,Node* p);
#endif

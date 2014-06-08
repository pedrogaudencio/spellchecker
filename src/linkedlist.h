/* linkedlist interface */

#ifndef LINKEDLIST
#define LINKEDLIST

struct list_node{
	struct list_node* next;
	int number;
};

struct list{
	struct list_node* head;
	struct list_node* tail;
	int size;
};

struct list* list_new();

struct list_node* next(struct list_node* current);

int list_empty(struct list* list);

void list_destroy(struct list* list);

void list_insert_node(struct list* list, int n);
void list_insert(struct list *list, int n);

void list_print(struct list *list);

int list_length(struct list *list);

void list_destroy(struct list* list);

#endif
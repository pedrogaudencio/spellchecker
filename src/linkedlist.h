#ifndef MAX_TEXT_LINES
#define MAX_TEXT_LINES 7 // 500000\0



/* linkedlist interface */

struct list_node{
	struct list_node* next;
	char number[MAX_TEXT_LINES];
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

struct list_node * list_insert_node(struct list_node* tail, char n[]);
struct list_node * list_insert(struct list *list, char n[]);

void list_print(struct list *list);

int list_length(struct list *list);

void list_destroy(struct list* list);

#endif
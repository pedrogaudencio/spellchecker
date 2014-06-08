#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "hashing.h"


struct list* list_new()
{
	struct list* newlist=malloc(sizeof(struct list));
	newlist->head=NULL;
	newlist->tail=NULL;
	newlist->size=0;
	return newlist;
}


struct list_node* next(struct list_node* current)
{
	return current->next;
}


int list_empty(struct list* list)
{
	return list->head==NULL;
}


void list_insert_node(struct list* list, int n)
{
	struct list_node* new_node = malloc(sizeof(struct list_node));
	new_node->number = n;
	new_node->next = NULL;
	list->tail->next=new_node;
	list->tail=new_node;
}


void list_insert(struct list *list, int n)
{
	list->size++;
	if(list_empty(list)){
		list->head=malloc(sizeof(struct list_node));
		list->head->number = n;
		list->tail=list->head;
		list->tail->next = NULL;
	}
	else
		list_insert_node(list, n);
}


void list_print(struct list *list)
{
	struct list_node* current=list->head;
	while(current!=NULL){
		printf("%d ", current->number);
		current=next(current);
	}
}


int list_length(struct list *list)
{
	return list->size;
}

void list_destroy(struct list *list)
{
	if(!list_empty(list)){
		struct list_node* current=list->head;
		while(current!=NULL){
			struct list_node* temp;
			temp=next(current);
			free(current);
			current=temp;
		}
		free(list);
	}
}

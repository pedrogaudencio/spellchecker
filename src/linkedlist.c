#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "hashing.h"


struct list* list_new()
{
	struct list* newlist=malloc(sizeof(struct list));
	newlist->head=NULL;
	newlist->tail=newlist->head;
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


struct list_node * list_insert_node(struct list_node* tail, char n[])
{
	struct list_node* new_node = malloc(sizeof(struct list_node));
	strcpy(new_node->number, n);
	tail->next=new_node;
	tail=new_node;
	//new_node->next=head->next;
	//head->next=new_node;
	return tail;
}


struct list_node * list_insert(struct list *list, char n[])
{
	list->size++;
	if(list_empty(list)){
		list->head=malloc(sizeof(struct list_node));
		strcpy(list->head->number, n);
		return list->head;
	}
	else
		return list_insert_node(list->tail, n);
}


void list_print(struct list *list)
{
	struct list_node* current=list->head;
	while(current!=NULL){
		printf("%s ", current->number);
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
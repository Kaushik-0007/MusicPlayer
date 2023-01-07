#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}


void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{
	node_t *newnode=malloc(sizeof(node_t));
	newnode->prev=NULL;
	newnode->data=data;
	newnode->next=NULL;

	if(list->head==NULL) { 
		list->head=newnode;
		list->tail=newnode;
	}
	else { 
		newnode->next=list->head;
		list->head->prev=newnode;
		list->head=newnode;
	}
	list->size+=1;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{
	node_t *newnode=malloc(sizeof(node_t));
	newnode->prev=NULL;
	newnode->data=data;
	newnode->next=NULL;

	if(list->head==NULL) {
		list->head=newnode;
		list->tail=newnode;
	}
	else {
		newnode->prev=list->tail;
		list->tail->next=newnode;
		list->tail=newnode;
	}
	list->size+=1;
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	node_t *newnode=malloc(sizeof(node_t));
	node_t *p=list->head;

	while(p && p->data!=prev) { 
		p=p->next;
	}
	if(p) { 
		newnode->data=data;
		newnode->next=p->next;
		newnode->prev=p;
		if(p->next) { 
			p->next->prev=newnode;
		}
		else { 
			list->tail=newnode;
		}

		p->next=newnode;
		list->size+=1;
	}
	
}

void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	if(list->head==list->tail) { 
		free(list->head);
		list->head=list->tail=NULL;
	}
	else { 
		list->head=list->head->next;
		free(list->head->prev);
		list->head->prev=NULL;
	}
	list->size-=1;
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{
	if(list->head==list->tail) { 
		free(list->tail);
		list->head=list->tail=NULL;
	}
	else { 
		list->tail=list->tail->prev;
		free(list->tail->next);
		list->tail->next=NULL;

	}
	list->size-=1;
}

void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	node_t *p=list->head;
	
	while (p && p->data!=data) {
		p=p->next;
	}
	if (p) {
		if (p->next && p->prev) {
			node_t *q = p;
			p->prev->next = p->next;
			p->next->prev = p->prev;
			free(q);
			q = NULL;
			list->size-=1;
		}
		else if (p->prev) {
			delete_back(list);
		}
		else {
			delete_front(list);
		}
	}
		
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	

	if(list->head!=NULL) {
	node_t *p=list->head;
	while(p && p->data!=data) {
		p=p->next;
	}
	return p;
	}
	return NULL;

}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}


#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_t* create_queue()   // return a newly created empty queue
{
	// DO NOT MODIFY!!!
	queue_t* Q = (queue_t*) malloc(sizeof(queue_t));
	Q->list = create_list();
	Q->front = Q->list->head;
	Q->rear = Q->list->tail;
	Q->size = Q->list->size;
	return Q;
}

void enqueue(queue_t* q, int data) // TODO: insert data at the end of a queue
{
	node_t *newnode=malloc(sizeof(node_t));
	newnode->prev=NULL;
	newnode->data=data;
	newnode->next=NULL;

	if(q->front==NULL) { 
		q->front=newnode;
		q->rear=newnode;
	}
	
	else { 
		q->rear->next=newnode;
		newnode->prev=q->rear;
		q->rear=newnode;
	}
	q->size+=1;

}

int dequeue(queue_t* q) 	// TODO: return the data at the front of a queue and remove it. Return -1 if queue is empty
{
	if(q->front==NULL)
		return -1; 
	else { 
		int ele=q->front->data;
		if(q->front==q->rear) { 
			free(q->front);
			q->front=NULL;
			q->rear=NULL;
		}
		else {
			q->front=q->front->next; 
			free(q->front->prev);
			q->front->prev=NULL;
		}
		return ele;
		q->size-=1;
	}

}

int front(queue_t* q) // TODO: return the data at the front of a queue. Return -1 if queue is empty
{
	if(q->front==NULL) { 
		return -1;
	}
	return q->front->data;

}

int empty(queue_t* q) // return if the queue is empty
{
	// DO NOT MODIFY!!!
	return is_empty(q->list);
}

int queue_size(queue_t* q) // returns the number of elements in the queue
{
	// DO NOT MODIFY!!!
	return q->size;
}

void delete_queue(queue_t* q) // empty the contents of the queue
{
	// DO NOT MODIFY!!!
	delete_list(q->list);
	free(q);
}

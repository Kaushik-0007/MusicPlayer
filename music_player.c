#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*)malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{

	if(where==-1) { 
		insert_front(playlist->list,song_id);
	}
	else if(where==-2) { 
		insert_back(playlist->list,song_id);
	}
	else if(where>=0) { 
		insert_after(playlist->list,song_id,where);
	}
	else { 
		return;
	}

}

void delete_song(playlist_t* playlist, int song_id) // TODO: remove song id from the playlist
{
	delete_node(playlist->list,song_id);

}

song_t* search_song(playlist_t* playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
	return search(playlist->list,song_id);
}

void search_and_play(playlist_t* playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t *p=search(playlist->list,song_id);
	if(p!=NULL) {
	play_song(p->data);
	playlist->last_song=p;
	}
}

void play_next(playlist_t* playlist, music_queue_t* q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if(q->front != NULL){
		play_song(q->front->data);
		dequeue(q);
	}

	else{
		if(playlist->list->head == NULL){
		return ;
	}
		else if(playlist->last_song == NULL){
		play_song(playlist->list->head->data);
		playlist->last_song = playlist->list->head;

	}
		else{
		if(playlist->last_song->next != NULL){
			play_song(playlist->last_song->next->data);
			playlist->last_song = playlist->last_song->next;
		}
		else{
			play_song(playlist->list->head->data);
				playlist->last_song = playlist->list->head;
			
		}
		}
	}
}

void play_previous(playlist_t* playlist) // TODO: play the previous song from the linked list
{

	if (playlist->list->head == NULL)
	{
		return;
	}
	else{
		if (playlist->last_song == NULL){
			playlist->last_song = playlist->list->tail;
			play_song(playlist->list->tail->data);
		}
		else{
			if(playlist->last_song->prev == NULL){
				play_song(playlist->list->tail->data);
				playlist->last_song = playlist->list->tail;
			}
			else{
				play_song(playlist->last_song->prev->data);
				playlist->last_song = playlist->last_song->prev;
			}
		}
	}
	return ;
}

void play_from_queue(music_queue_t* q) // TODO: play a song from the queue
{
	if(q) {
	play_song(q->front->data);
	}
}

void insert_to_queue(music_queue_t* q, int song_id) // TODO: insert a song id to the queue
{
	enqueue(q,song_id);

}

void reverse(playlist_t* playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	song_t *p=playlist->list->head;
	song_t *q=playlist->list->head->next;

	p->next=NULL;
	p->prev=q;

	while(q!=NULL) { 
		q->prev=q->next;
		q->next=p;
		p=q;
		q=q->prev;
	}
	playlist->list->head=p;
} 

void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
	int j = 0;
	node_t *kth_node = playlist->list->head;
	while (kth_node && j<k) {
		kth_node = kth_node->next;
		j++;
	}
	if (kth_node) {
		node_t *ith_node = playlist->list->head;
		int i = 0;
		node_t *knext ,*kprev,*inext,*iprev;
		while (i+k<playlist->list->size) {
			inext = ith_node->next;
			iprev = ith_node->prev;
			knext = kth_node->next;
			kprev = kth_node->prev;
			if (ith_node->next==kth_node) {
				ith_node->prev = kth_node;
				kth_node->next = ith_node;
				kth_node->prev = iprev;
				ith_node->next = knext;
				
				if(knext) {
					knext->prev = ith_node;
				}
				else {
					playlist->list->tail = ith_node;
				}
				if (iprev) {
					iprev->next = kth_node;
				}
				else {
					playlist->list->head = kth_node;
				}
					kth_node = knext;
				
			}
			else {
				ith_node->prev = kprev;
				kth_node->next = inext;
				kth_node->prev = iprev;
				ith_node->next = knext;
				
				inext->prev = kth_node;
				kprev->next = ith_node;
				if(knext) {
					knext->prev = ith_node;
				}
				else {
					playlist->list->tail = ith_node;
				}
				if (iprev) {
					iprev->next = kth_node;
				}
				else {
					playlist->list->head = kth_node;
				}
				ith_node = inext;
				kth_node = knext;
			
			}				
			i++;
		}
	
	}
		
}

void shuffle(playlist_t* playlist, int k) // TODO: perform k_swap and reverse
{
	k_swap(playlist,k);
	reverse(playlist);
}

song_t* debug(playlist_t* playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{

	song_t *slow_p,*fast_p;
	slow_p=fast_p=playlist->list->head;

	while(slow_p && fast_p && fast_p->next) { 
		slow_p=slow_p->next;
		fast_p=fast_p->next->next;
		if(slow_p==fast_p) { 
			return slow_p->next;
		}
	}
	
	return NULL;

}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}


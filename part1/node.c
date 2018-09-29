#include <stdlib.h>
#include <string.h>
//#include "process.h"
#include "node.h"
#include <stdio.h>

struct node* init(char *u,char j, int a,int d){
	 struct node *n = (struct node*) malloc(sizeof(node));
	 n->user = strdup(u);
	 n->job = j;
	 n->arr=a;
	 n->dur=d;
	 n->next=NULL;
	 return n;
}
//inserts node at end of list
int insert(struct node **head, struct node *nnode){
	struct node *cur = *head;
	struct node *prev = NULL;
	while(cur!= NULL){

		if(nnode->arr < cur->arr){
			break; // found location to put user
		}
		prev = cur;
		cur = cur->next;
	}

	if(prev == NULL){ // add to front 
		nnode->next = *head;
		*head = nnode;
		return 1;
	}

	else if(cur == NULL){ // at end
		prev->next = nnode;
		return 1;
	}

	else if(cur!=NULL && prev != NULL){ // in middle
		prev->next = nnode;
		nnode->next = cur;
		return 1;
	}
	return 0; //something went wrong
}

// remove a node
 int pop(struct node **head, char job){
	struct node *cur = *head;
	struct node *prev = cur;
	if(cur!= NULL && cur->job == job){
		struct node *tmp =cur;
		cur=cur->next;
		*head = cur;
		free(tmp);

		return 1;
	}

	while(cur!=NULL && cur->job !=job){
		prev = cur;
		cur = cur->next;
	}

	if(cur == NULL){
		return 0;
	}

	prev->next = cur->next;
	free(cur);
	return 1;
}


void delete_list(struct node **head){
	struct node* cur = *head;
	struct node *tmp;
	while(cur!=NULL){
		tmp = cur->next;
		free(cur);
		cur=tmp;
	}
	*head=NULL;
}

void print_list(struct node **head){
	struct node *cur = *head;
	while(cur!=NULL){
		printf("%s %c %d %d \n",cur->user,cur->job,cur->arr,cur->dur);
		cur=cur->next;
	}
}
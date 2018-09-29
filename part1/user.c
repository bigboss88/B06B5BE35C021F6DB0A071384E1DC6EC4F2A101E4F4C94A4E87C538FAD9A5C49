#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"

struct user* init_USER(char *n,int a){
	struct user *n_user = (struct user*) malloc(sizeof(user));
	n_user->name = strdup(n);
	n_user->fir_arr = a;
	n_user->time = 0;
	n_user->next = NULL;
	return n_user;

}

int insert_USER(struct user **head,char *u,int a){
	struct user *cur = *head;
	struct user *prev = cur;
	while(cur != NULL){
		if(strcmp(cur->name,u)==0){return 0;} //This user is already in the list
		prev =  cur;
		cur = cur->next;
	}
	cur = *head;
	prev = NULL;
	struct user *nuser = init_USER(u,a);
	//Now actually start the insert since we know it's a new user sorted based on arrive time

	while(cur!= NULL){

		if(a < cur->fir_arr){
			break; // found location to put user
		}
		prev = cur;
		cur = cur->next;
	}

	if(prev == NULL){ // add to front 
		nuser->next = *head;
		*head = nuser;
		return 1;
	}

	else if(cur == NULL){ // at end
		prev->next = nuser;
		return 1;
	}

	else if(cur!=NULL && prev != NULL){ // in middle
		prev->next = nuser;
		nuser->next = cur;
		return 1;
	}
	return 0; //something went wrong
}

void delete_USERlist(struct user **head){
	struct user* cur = *head;
	struct user *tmp;
	while(cur!=NULL){
		tmp = cur->next;
		free(cur);
		cur=tmp;
	}
	*head=NULL;
}

int setTime(struct user **head,char *n, int time){
		struct user *cur = *head;
		struct user *prev = cur;
		while(cur != NULL){
		if(strcmp(cur->name,n)==0){break;} //This user is already in the list
		prev =  cur;
		cur = cur->next;
	}

	if(cur == NULL){return 0;} // USer isn't in the list
	cur->time = time;
}

void print_USERlist(struct user **head){
	struct user *cur = *head;
	while(cur!=NULL){
		printf("%s %d \n",cur->name,cur->time);
		cur=cur->next;
	}
}
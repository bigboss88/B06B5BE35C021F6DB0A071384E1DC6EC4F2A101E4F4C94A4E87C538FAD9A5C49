//node.h

#ifndef node_h
#define node_h
struct node{
	char* user;
	char job;
	int arr;
	int dur;
	struct node *next;
}node;
//Returns a node
struct node* init(char *u,char j, int a,int d);
//Adds node into linked list, sorts by arrival time. 
int insert(struct node **head, struct node *nnode);
int pop(struct node **head, char job);
void delete_list(struct node **head);
void print_list(struct node **head);
#endif
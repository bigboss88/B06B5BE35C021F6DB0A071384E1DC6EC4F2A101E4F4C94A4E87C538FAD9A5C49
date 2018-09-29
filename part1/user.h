#ifndef user_h
#define user_h
struct user{
	char *name;
	int time;
	int fir_arr;
	struct user *next;
}user;
struct user* init_USER(char *n,int a);
int insert_USER(struct user **head,char *u,int a);
void delete_USERlist(struct user **head);
int setTime(struct user **head,char *n, int time);
void print_USERlist(struct user **head);
#endif
//#include "process.h"
#include "node.h"
#include "user.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//Test
static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
void work_job(struct node *job){
	pthread_mutex_lock(&mu);
	job->dur = job->dur -1;
	sleep(1);
	printf("	%c",job->job);
	pthread_mutex_unlock(&mu);
}

int find_CPU(struct cpu cpus[], int num_cpu,struct node *job){
//	printf("In find CPU\n");
	int i =0;
	//Firt look to see if the job is being worked on already
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job == job->job){return 0;} // if it's already being worked on then ignore it
	}
	i=0;
	//then look for which cpu it should use, first free one, or take over a longer job
	for(i;i<num_cpu;i++){
		//printf("%c\n",cpus[i].cur_job);
		if(cpus[i].cur_job == '*' ){
			// /printf("Setting in empty cpu\n");
			setWork(&cpus[i],job);
			//printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
	}

	// if they are all full

	i=0;
	for(i;i<num_cpu;i++){
		if(cpus[i].job->dur > job-> dur){ // you'll want to replace this job
			setWork(&cpus[i],job);
		//	printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
	}
	return 0; // else job has to wait
}

int find_CPU2(struct node* cpu_jobs[],int num_cpu,struct node *job){


	int i =0;
	//Firt look to see if the job is being worked on already
	for(i;i<num_cpu;i++){
		if(cpu_jobs[i] != NULL && cpu_jobs[i]->job == job->job){return 0;} // if it's already being worked on then ignore it
	}
	i=0;
	//then look for which cpu it should use, first free one, or take over a longer job
	for(i;i<num_cpu;i++){
		//printf("%c\n",cpus[i].cur_job);
		if(cpu_jobs[i] == NULL){
			// /printf("Setting in empty cpu\n");
			cpu_jobs[i] = job;
			//printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
	}

	// if they are all full

	i=0;
	for(i;i<num_cpu;i++){
		if(cpu_jobs[i] != NULL && cpu_jobs[i]->dur > job->dur){ // you'll want to replace this job
			cpu_jobs[i] = job;
		//	printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
	}
	return 0; // else job has to wait
}
//Does work on all cpus that has a job
int work_CPUS(struct cpu cpus[],int num_cpu){
	int i =0;
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job != '*'){
			doWork(&cpus[i]);
			empty(&cpus[i]);
		}
	}
	return 1;
}

void print_CPUS(struct cpu cpus[],int num_cpu,int time){
	int i =0;
	printf("%d 	",time);
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job != '*'){
			printf("%c	",cpus[i].cur_job);
		}
		else{
			printf("	");
		}
	}
	printf("\n");
}


void join_Threads(pthread_t threads[],int num_cpu){
	int i=0;
	for(i;i<num_cpu;i++){
		pthread_join(threads[i],NULL);
	}
}

void print_Jobs(struct node* job[], int num){
	int i=0;
	for(i;i<num;i++){
		printf("%c 	",job[i]->job);
	}
	printf("\n");
}

void make_Threads(pthread_t threads[], struct node* cpu_jobs[],int num_cpu){
	int i =0;
	for(i;i<num_cpu;i++){
		if(cpu_jobs[i]!=NULL){
			pthread_create(&threads[i],NULL,&work_job,(void *)cpu_jobs[i]);
		}
	}
}

int findNum_Jobs(struct node* cpu_jobs[],int num_cpu){
	int out = 0;
	int i=0;
	for(i;i<num_cpu;i++){
		if(cpu_jobs[i] != NULL){
			out++;
		}
	}
	return out;
}


void clear_job(struct node* jobs[],int num_cpu){
	int i=0;
	for(i;i<num_cpu;i++){
		jobs[i]=NULL;
	}
}
int main(int argc, char  *argv[]){
	if(argc != 2){printf("%d Worng number of inputs, should be ./run int\n",argc);return 0;}
	int num_cpu = atoi(argv[1]);
	if(num_cpu < 1){printf("Can't have less than 1 cpu\n");return 0;}
	//printf("%d \n",num_cpu );
	pthread_t cpus[num_cpu];
	struct node* cpu_jobs[num_cpu];
	char dump[100];
	int time = 0;
	int i =0;
	for(i;i<4;i++){
		scanf("%s",dump);
		//printf("%s\n",dump );
	}
	char user[50];
	char job;
	int arrive;
	int dur;
	i = 0;
	struct node **job_list = (struct node**) malloc(sizeof(struct node));
	struct node *test;
	struct user **user_list = (struct user**) malloc(sizeof(struct user));
	int min =0;
	while(scanf("%s %c %d %d",user,&job,&arrive,&dur)>3){
		if(i==0){
			*job_list = init(user,job,arrive,dur);
			*user_list = init_USER(user,arrive);
			min=arrive;
			//printf("%s %c %d %d \n",user,job,arrive,dur );
		}
		else{
			test = init(user,job,arrive,dur);
			 insert(job_list,test);
			 insert_USER(user_list,user,arrive);
			 //printf("%s %c %d %d \n",user,job,arrive,dur );
			 if(arrive < min){
			 	min = arrive;
			 }
		}
		i++;
	}
	//printf("%d\n",num_cpu );
	printf("time");
	for(i = 0;i<num_cpu;i++){
		cpu_jobs[i]=NULL;
		printf("	CPU%d",i+1);
		
	}
	printf("\n");
	time = min;
	while(*job_list != NULL){ // while there are still jobs
		//if(time == 7 ){print_list(job_list);}
		struct node *cur = (struct node *) malloc(sizeof(struct node));
		cur = *job_list;
		int num_jobs =0;
		while (cur != NULL){ // go through list;
			
			if(cur->arr <= time){ // if it has arrived
				//has arrived and is smallest dur
				//printf("dur of usr %d  arr of user %d\n",cur->dur,cur->arr );
				//print_Jobs(cpu_jobs,num_cpu);
				find_CPU2(cpu_jobs, num_cpu,cur);
				num_jobs = findNum_Jobs(cpu_jobs,num_cpu);
				//printf("Num Jobs %d\n",num_jobs );
			}
			if(cur->dur <= 1){ // if this job is done remove it for some reason it will work on 0 so I set to 1
				struct node *tmp = (struct node *) malloc(sizeof(struct node));
				tmp =cur;
				setTime(user_list,tmp->user,time+1);
				cur = cur->next;
				pop(job_list,tmp->job);
			}
			if(cur == NULL){break;}
			cur = cur->next;
		}
		printf("%d", time);
		//print_CPUS(cpus,num_cpu,time);
		//work_CPUS(cpus,num_cpu);
		//print_Jobs(cpu_jobs,num_cpu);
		//print_list(job_list);
		make_Threads(cpus,cpu_jobs,num_jobs);
		join_Threads(cpus,num_jobs);
		clear_job(cpu_jobs,num_cpu);
		printf("\n");
		time++;
	}
	printf("%d 	IDLE\n", time++);
	printf("\nSummary\n");
	print_USERlist(user_list);
	delete_list(job_list);
	delete_USERlist(user_list);
	pthread_mutex_destroy(&mu);
}
#ifndef cpu_h
#define cpu_h
#include "node.h"
struct cpu{
	struct node *job;
	char cur_job;
}cpu_t;

struct cpu init_CPU();
int setWork(struct cpu *acpu ,struct node *job);
int empty(struct cpu *acpu);
int doWork(struct cpu *acpu);
char hasJob(struct cpu *acpu);
#endif

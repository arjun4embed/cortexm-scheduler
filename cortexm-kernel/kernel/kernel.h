#ifndef KERNEL_H_
#define KERNEL_H_

#include"cortexm.h"
#include<stdint.h>
#define stack_len 256 //each task 1kb
#define MAX_TASKS 3

extern uint32_t stack_pool[MAX_TASKS][stack_len];

struct task {
	uint32_t *psp;
	uint8_t state;
	uint8_t priority;
};

void task_init(struct task *t, uint32_t *stack_base, void (*entry)(void));

extern struct task task_table[MAX_TASKS];
uint32_t schedule_next(void);
extern volatile uint32_t current_task_number;
void systic_init();

#endif /* KERNEL_H_ */


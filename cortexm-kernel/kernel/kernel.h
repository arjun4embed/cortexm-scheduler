#ifndef KERNEL_H_
#define KERNEL_H_

/* =========================
 * Includes
 * ========================= */
#include"cortexm.h"
#include<stdint.h>



/* =========================
 * Kernel Macros
 * ========================= */
#define stack_len 256 //each task 1kb
#define MAX_TASKS 4 //MAX_TASK = USERTASK+1(IDLE TASK)

extern uint32_t stack_pool[MAX_TASKS][stack_len];

/* =========================
 * Task State
 * ========================= */
enum task_state
{
	   READY,
	   TERMINATED
};
/* =========================
 * Task INFO
 * ========================= */
struct task {
	uint32_t *psp;
	uint8_t state;
};
/* =========================
 * Kernel Globals
 * ========================= */
extern struct task task_table[MAX_TASKS];
extern volatile uint32_t current_task_number;
/* =========================
 * Kernel / Scheduler APIs
 * ========================= */
void task_init(struct task *t, uint32_t *stack_base, void (*entry)(void));
void systic_init();
void kernel_start();
void task_exit();
uint32_t schedule_next(void);

#endif /* KERNEL_H_ */


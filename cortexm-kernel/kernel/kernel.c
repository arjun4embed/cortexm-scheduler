#include "kernel.h"
#include<stdint.h>
/* =========================
 * Macros
 * ========================= */
#define IDLE_TASK &task_table[0]
#define IDLE_TASK_PSP task_table[0].psp

/* =========================
 * Globals
 * ========================= */
volatile uint32_t current_task_number = 0;
uint32_t stack_pool[MAX_TASKS][stack_len];
struct task task_table[MAX_TASKS] = { 0 };

/* =========================
 * Kernel / Scheduler APIs Initialization
 * ========================= */
void task_init(struct task *t, uint32_t *stack_base, void (*entry)(void)) {
	t->state = READY;
	uint32_t *psp = stack_base + stack_len;

	//Dummy stack frame
	*(--psp) = 0x01000000;                  //xPSR
	*(--psp) = (uint32_t) entry & ~1U;     //PC
	*(--psp) = 0x00000000;                 //LR
	*(--psp) = 0x00000000;                 // R12
	*(--psp) = 0x00000000;                 // R3
	*(--psp) = 0x00000000;                 // R2
	*(--psp) = 0x00000000;                 // R1
	*(--psp) = 0x00000000;                 // R0

	//calle saved register
	for (int i = 0; i < 8; i++)
		*(--psp) = 0x00000000;              // R4–R11

	t->psp = psp;
}
/* =========================
 * SysTick
 * =======================
 */
void systic_init() {
	SYSTIC->SYST_RVR = (uint32_t) SYSTICK_RELOAD_VALUE;
	SYSTIC->SYST_CVR = (uint32_t) 0x0U;
	SYSTIC->SYST_CSR |= SET_BIT(2);
	SYSTIC->SYST_CSR |= SET_BIT(1);
	SYSTIC->SYST_CSR |= SET_BIT(0);

}

void SysTick_Handler() {

	tick++;

	SCB->ICSR = SET_BIT(28);
}
/* =========================
 * Scheduler Algorithm
 * ========================= */
uint32_t schedule_next(void) {

	for (uint32_t i = 0; i < MAX_TASKS; i++) {
		current_task_number++;

		if (current_task_number >= MAX_TASKS)
			current_task_number = 0;

		if (task_table[current_task_number].state == READY) {
			return (uint32_t) task_table[current_task_number].psp;
		}
	}

	return (uint32_t) IDLE_TASK_PSP;
}
/* =========================
 * PendSV Handler
 * ========================= */
__attribute__((naked)) void PendSV_Handler(void) {
	__asm volatile (
			"MRS   r0, PSP              \n"
			"STMDB r0!, {r4-r11}        \n"
			"LDR   r1, =current_task_number \n"
			"LDR   r2, [r1]             \n"
			"LDR   r3, =task_table      \n"
			"STR   r0, [r3, r2, LSL #3] \n"
			"PUSH {lr}                  \n "
			"BL    schedule_next        \n"
			"POP  {lr}                  \n"
			"LDMIA r0!, {r4-r11}        \n"
			"MSR   PSP, r0              \n"
			"BX    LR                   \n"
	);
}
/* =========================
 * Idle Task
 * ========================= */
void idle_thread() {
	while (1)
		;
}
/* =========================
 * Kernel Control
 * ========================= */
void kernel_start() {
	task_init(&task_table[0], (uint32_t*) stack_pool[0], idle_thread);
	Execption_prio_config();
	set_psp((uint32_t) task_table[0].psp);
	use_psp();
	systic_init();
	__asm volatile ("SVC 0");
}

void task_exit() {
	task_table[current_task_number].state = TERMINATED;

	SCB->ICSR = SET_BIT(28);

	while (1)
		;
}

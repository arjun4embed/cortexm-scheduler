#include "kernel.h"
#include<stdint.h>

volatile uint32_t current_task_number = 0;
uint32_t stack_pool[MAX_TASKS][stack_len];
struct task task_table[MAX_TASKS] = { 0 };
void task_init(struct task *t, uint32_t *stack_base, void (*entry)(void)) {
	uint32_t *psp = stack_base + stack_len;

	//Dummy stack frame
	*(--psp) = 0x01000000;                  // xPSR
	*(--psp) = (uint32_t) entry & ~1U;      // PC
	*(--psp) = 0x00000000;                // LR
	*(--psp) = 0x00000000;                  // R12
	*(--psp) = 0x00000000;                  // R3
	*(--psp) = 0x00000000;                  // R2
	*(--psp) = 0x00000000;                  // R1
	*(--psp) = 0x00000000;                  // R0

	//calle saved register
	for (int i = 0; i < 8; i++)
		*(--psp) = 0x00000000;              // R4–R11

	t->psp = psp;
}

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

uint32_t schedule_next(void) {

	current_task_number++;
	if (current_task_number >= MAX_TASKS)
		current_task_number = 0;

	return (uint32_t) task_table[current_task_number].psp;
}
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

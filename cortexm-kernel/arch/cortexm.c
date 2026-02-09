#include<stdint.h>
#include"cortexm.h"
#include"kernel.h"
/* =========================
 * Globals
 * ========================= */
volatile uint32_t tick;

/* =========================
 * PSP Helpers
 * ========================= */
__attribute__((naked)) void set_psp(uint32_t psp) {
	__asm volatile ("MSR PSP, %0" :: "r"(psp));
}

__attribute__((naked)) void use_psp(void) {
	__asm volatile ("MRS r0, CONTROL; ORR r0, r0, #2; MSR CONTROL, r0; ISB");
}
/* =========================
 * Exception Priority Config
 * ========================= */
void Execption_prio_config() {
	volatile uint8_t *reg = (uint8_t*) &SCB->SHPR3;
	reg[3] = SYSTIC_PRIORITY;
	reg[2] = PENDSV_PRIORITY;
}
/* =========================
 * Fault Handlers
 * ========================= */
void HardFault_Handler() {
	while (1);
}
/* =========================
 * SVC Handler (start first task)
 * ========================= */
__attribute__((naked)) void SVC_Handler(void) {
	__asm volatile (
			"LDR r0, =task_table      \n"
			"LDR r0, [r0]             \n"
			"LDMIA r0!, {r4-r11}      \n"
			"MSR   PSP, r0            \n"
			"MOV   LR, #0xFFFFFFFD    \n"
			"BX    LR                 \n"
	);
}


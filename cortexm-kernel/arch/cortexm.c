#include<stdint.h>
#include"cortexm.h"
#include"kernel.h"

volatile uint32_t tick;
__attribute__((naked)) void set_psp(uint32_t psp) {
	__asm volatile ("MSR PSP, %0" :: "r"(psp));
}

__attribute__((naked)) void use_psp(void) {
	__asm volatile ("MRS r0, CONTROL; ORR r0, r0, #2; MSR CONTROL, r0; ISB");
}

void Execption_prio_config() {
	volatile uint8_t *reg = (uint8_t*) &SCB->SHPR3;
	reg[3] = SYSTIC_PRIORITY;
	reg[2] = PENDSV_PRIORITY;
}
void HardFault_Handler() {
	while (1)
		;
}

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

void kernel_start() {
	Execption_prio_config();
	set_psp((uint32_t) task_table[0].psp);
	use_psp();
	systic_init();
	__asm volatile ("SVC 0");
}

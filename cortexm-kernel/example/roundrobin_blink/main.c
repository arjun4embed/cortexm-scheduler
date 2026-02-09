#include<stdint.h>
#include"kernel.h"
#include "cortexm.h"
#include "gpio.h"
#include "rcc.h"

void delay_ms(uint32_t ms) {
	uint32_t start = tick;
	while ((tick - start) < ms) {

	}
}
void task1_thread() {
	while (1) {
		gpio_pin_set_high(GPIOC_BASE, 3);
		delay_ms(200);
		gpio_pin_set_low(GPIOC_BASE, 3);
		delay_ms(200);

	}
}
void task2_thread() {
	while (1) {
		gpio_pin_set_high(GPIOC_BASE, 2);
		delay_ms(500);
		gpio_pin_set_low(GPIOC_BASE, 2);
		delay_ms(500);

	}
}
void task3_thread() {
	while (1) {
		gpio_pin_set_high(GPIOC_BASE, 10);
		delay_ms(1000);
		gpio_pin_set_low(GPIOC_BASE, 10);
		delay_ms(1000);
	}
}
void task4_thread() {
	while (1) {
		__asm volatile ("NOP");
	}
}
int main() {
	rcc_enable_ahb1(RCC_AHB1_GPIOC);
	gpio_set_output(GPIOC_BASE, 3);
	gpio_set_output(GPIOC_BASE, 2);
	gpio_set_output(GPIOC_BASE, 10);
	task_init(&task_table[1], (uint32_t*) stack_pool[1], task1_thread);
	task_init(&task_table[2], (uint32_t*) stack_pool[2], task2_thread);
	task_init(&task_table[3], (uint32_t*) stack_pool[3], task3_thread);
	task_init(&task_table[4], (uint32_t*) stack_pool[4], task4_thread);
	kernel_start();

}

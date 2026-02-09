#include<stdint.h>
#include"gpio.h"

void gpio_set_output(struct GPIO_REG_DEF *port, uint8_t pin) {
	port->MODER &= ~(3U << (pin * 2U));
	port->MODER |= (1U << (pin * 2U));

	port->OTYPER &= ~(1U << pin);

	port->OSPEEDR &= ~(3U << (pin * 2U));

	port->PUPDR &= ~(3U << (pin * 2U));

}
void gpio_pin_set_high(struct GPIO_REG_DEF  *port, uint8_t pin) {
	port->BSRR = (1U << pin);
}
void gpio_pin_set_low(struct GPIO_REG_DEF  *port, uint8_t pin) {
	port->BSRR = (1U << (pin + 16U));
}
void gpio_pin_toggle(struct GPIO_REG_DEF  *port, uint8_t pin)
{
	port->ODR  ^= (1U << pin);
}
uint8_t gpio_pin_get_state(struct GPIO_REG_DEF *port, uint8_t pin);

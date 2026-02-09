
#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_
#include<stdint.h>
struct GPIO_REG_DEF
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;

};
#define GPIOA_BASE ((struct GPIO_REG_DEF  *)0x40020000U)
#define GPIOB_BASE ((struct GPIO_REG_DEF  *)0x40020400U)
#define GPIOC_BASE ((struct GPIO_REG_DEF  *)0x40020800U)
#define GPIOD_BASE ((struct GPIO_REG_DEF  *)0x40020C00U)
#define GPIOE_BASE ((struct GPIO_REG_DEF  *)0x40021000U)
#define GPIOF_BASE ((struct GPIO_REG_DEF  *)0x40021400U)
#define GPIOG_BASE ((struct GPIO_REG_DEF  *)0x40021800U)
#define GPIOH_BASE ((struct GPIO_REG_DEF  *)0x40021C00U)
#define GPIO_MODE_INPUT     0x0U
#define GPIO_MODE_OUTPUT    0x1U
#define GPIO_MODE_AF        0x2U
#define GPIO_MODE_ANALOG    0x3U

#define GPIO_OTYPE_PP  0x0U
#define GPIO_OTYPE_OD  0x1U


#define GPIO_SPD_L     0x0U
#define GPIO_SPD_M     0x1U
#define GPIO_SPD_H     0x2U
#define GPIO_SPD_VH    0x3U

#define GPIO_PU_NONE   0x0U
#define GPIO_PU_UP     0x1U
#define GPIO_PU_DOWN   0x2U


#define GPIO_BSRR_SET(pin)    (1U << (pin))
#define GPIO_BSRR_CLR(pin)    (1U << ((pin) + 16U))

void gpio_set_output(struct GPIO_REG_DEF *port, uint8_t pin);
void gpio_pin_set_high(struct GPIO_REG_DEF  *port, uint8_t pin);
void gpio_pin_set_low(struct GPIO_REG_DEF  *port, uint8_t pin);
void gpio_pin_toggle(struct GPIO_REG_DEF  *port, uint8_t pin);
uint8_t gpio_pin_get_state(struct GPIO_REG_DEF  *port, uint8_t pin);


#endif

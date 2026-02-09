/*
 * rcc.h
 *
 *  Created on: Feb 8, 2026
 *      Author: menak
 */

#ifndef DRIVER_RCC_H_
#define DRIVER_RCC_H_

#define RCC_BASE_ADDR  0x40023800U

#define RCC  ((struct RCC_REG_DEF*)RCC_BASE_ADDR)

#define RCC_AHB1_GPIOA        (1U << 0)
#define RCC_AHB1_GPIOB        (1U << 1)
#define RCC_AHB1_GPIOC        (1U << 2)
#define RCC_AHB1_GPIOD        (1U << 3)
#define RCC_AHB1_GPIOE        (1U << 4)
#define RCC_AHB1_GPIOF        (1U << 5)
#define RCC_AHB1_GPIOG        (1U << 6)
#define RCC_AHB1_GPIOH        (1U << 7)

struct RCC_REG_DEF
{
    volatile unsigned int CR;
    volatile unsigned int PLLCFGR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;
    volatile unsigned int AHB1RSTR;
    volatile unsigned int AHB2RSTR;
    volatile unsigned int AHB3RSTR;
    volatile unsigned int RESERVED0;
    volatile unsigned int APB1RSTR;
    volatile unsigned int APB2RSTR;
    volatile unsigned int RESERVED1[2];
    volatile unsigned int AHB1ENR;
    volatile unsigned int AHB2ENR;
    volatile unsigned int AHB3ENR;
    volatile unsigned int RESERVED2;
    volatile unsigned int APB1ENR;
    volatile unsigned int APB2ENR;
};
void rcc_enable_ahb1(uint32_t peripheral);

void rcc_disable_ahb1(uint32_t peripheral);

#endif /* DRIVER_RCC_H_ */

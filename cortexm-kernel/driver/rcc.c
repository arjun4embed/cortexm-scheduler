#include<stdint.h>
#include"rcc.h"

void rcc_enable_ahb1(uint32_t peripheral)
{
	RCC->AHB1ENR |=peripheral;
}

void rcc_disable_ahb1(uint32_t peripheral)
{
	RCC->AHB1ENR &= ~(peripheral);
}

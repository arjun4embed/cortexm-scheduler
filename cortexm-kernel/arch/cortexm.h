#ifndef KERNEL_ARCH_ARMV7M_CORTEX_M_H
#define KERNEL_ARCH_ARMV7M_CORTEX_M_H

/* =========================
 * Includes
 * ========================= */
#include"cortexm.h"
#include<stdint.h>

/* =========================
 * CORE Macros
 * ========================= */
#define CPU_FREQ_HZ 16000000U
#define SYSTICK_RELOAD_VALUE (16000U - 1u)// current calculation for 1ms
#define SYSTIC_BASE_ADDR  0xE000E010U
#define SCB_BASE_ADDR  0xE000ED00U
#define SYSTIC ((struct SYSTIC_REG_DEF*)SYSTIC_BASE_ADDR)
#define SCB ((struct SYSTEM_CONTRO_BLOCK_REG_DEF*)SCB_BASE_ADDR)
#define SET_BIT(N) (1U<<(N))
#define INITIAL_XPSR   (0x01000000U)
#define EXC_RETURN_THREAD_PSP  (0xFFFFFFFDU)
#define SYSTIC_PRIORITY  (uint8_t)0XE0
#define PENDSV_PRIORITY  (uint8_t)0XF0
#define RAM_ORIGIN  0x20000000U
#define RAM_LENGTH  (128U *1024)//128KB
#define MSP_START (RAM_ORIGIN + RAM_LENGTH)
#define KERNEL_SIZE  (5U*1024)
#define PSP_START  MSP_START - KERNEL_SIZE
extern volatile uint32_t tick;



/* =========================
 * Registers Structure
 * ========================= */
struct SYSTIC_REG_DEF {
	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;
};
struct SYSTEM_CONTRO_BLOCK_REG_DEF {
	volatile uint32_t CPUID;   // 0x00
	volatile uint32_t ICSR;    // 0x04
	volatile uint32_t VTOR;    // 0x08
	volatile uint32_t AIRCR;   // 0x0C
	volatile uint32_t SCR;     // 0x10
	volatile uint32_t CCR;     // 0x14
	volatile uint32_t SHPR1;   // 0x18
	volatile uint32_t SHPR2;   // 0x1C
	volatile uint32_t SHPR3;   // 0x20
	volatile uint32_t SHCSR;   // 0x24
	volatile uint32_t CFSR;    // 0x28
	volatile uint32_t HFSR;    // 0x2C
	volatile uint32_t DFSR;    // 0x30
	volatile uint32_t MMAR;    // 0x34
	volatile uint32_t BFAR;    // 0x38
	volatile uint32_t AFSR;    // 0x3C
};
/* =========================
 * CORE  APIs
 * ========================= */
__attribute__((naked)) void set_psp(uint32_t psp);
__attribute__((naked)) void use_psp(void);
void Execption_prio_config();
#endif

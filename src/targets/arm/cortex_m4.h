/**
 * @file cortex_m.h
 * @brief Cordelia RTOS Cortex-M Specific Header
 *
 * This file contains Cortex-M specific definitions
 * for the Cordelia Real-Time Operating System (CRTOS).
 *
 * @author kskozgun
 * @version x.y.z
 */

#ifndef __CORTEX_M_H
#define __CORTEX_M_H

#include <stdint.h>

/* Hardware abstraction defines */
#define SCB_ICSR_ADDR       *((volatile uint32_t*)0xE000ED04U)
#define PENDSVSET_BIT       (1U << 28)

#define SYSTICK_VALUE_ADDR  *((volatile uint32_t*)0xE000E018U)

#define XPSR_INITIAL_VALUE 0x01000000 /* Core must start in Thumb mode */
#define EXEC_RT_PSP_HANDLER 0xFFFFFFFD /* Return to PSP & handler mode */


/* Tasks managements variables */
extern tcb_t task_list[MAX_TASKS + IDLE_TASK_PLACEHOLDER]; /* Array to hold task control blocks */
extern uint32_t c_os_current_task; /* Index of the currently running task */
extern uint32_t c_os_next_task;    /* Index of the next task to run */


inline __attribute__((always_inline)) void __enter_context_switch_irq(void)
{
    SCB_ICSR_ADDR |= PENDSVSET_BIT;
}

__attribute__((naked)) static void __start_scheduler(void)
{
    __asm volatile("CPSID I");

    /* Read the first task PSP value and assign it */
    __asm volatile("LDR R0, =task_list");
    __asm volatile("LDR R0, [R0]");
    __asm volatile("MSR PSP, R0");

    /* Switch to PSP mode */
    __asm volatile("MRS R0, CONTROL");
    __asm volatile("ORR R0, R0, #2");
    __asm volatile("MSR CONTROL, R0");
    __asm volatile("ISB");

    /* Launch the first task */
    __asm volatile("POP {R4-R11}");
    __asm volatile("POP {R0-R3}");
    __asm volatile("POP {R12}");
    __asm volatile("POP {LR}");
    __asm volatile("CPSIE I");
    __asm volatile("POP {PC}");
}

static uint32_t get_current_psp_addr(void)
{
    return (uint32_t)&task_list[c_os_current_task].psp_addr;
}

static uint32_t get_next_psp_value(void)
{
    return task_list[c_os_next_task].psp_addr;
}

__attribute__((naked)) static void __context_switch(void)
{
    __asm volatile ("CPSID I");

    /* Save context of current task*/
    __asm volatile("MRS R2, PSP");
    __asm volatile("STMDB R2!, {R4-R11}");

    /* R2 can be updated in function, therefore it stores in stack and read it back after function */
    __asm volatile("PUSH {R2}"); // Save PSP address on stack
    __asm volatile("BL get_current_psp_addr");
    __asm volatile("POP {R2}"); // Restore PSP address from stack
    __asm volatile("STR R2, [R0]");


    /* Restore context of the next task */
    __asm volatile("BL get_next_psp_value");
    __asm volatile("LDMIA R0!, {R4-R11}");
    __asm volatile("MSR PSP, R0");

    /* Assign next-task to current task */
    __asm volatile("LDR R0, =c_os_current_task");
    __asm volatile("LDR R1, =c_os_next_task");
    __asm volatile("LDR R1, [R1]");
    __asm volatile("STR R1, [R0]");

    /* Set LR to EXEC_RT_PSP_HANDLER before return */
    __asm volatile("LDR LR, =%0" : : "i"(EXEC_RT_PSP_HANDLER)); // Use "i" for immediate value

    /* Return from the function */
    __asm volatile ("CPSIE I");
    __asm volatile("BX LR");
}

#endif /* __CORTEX_M_H */

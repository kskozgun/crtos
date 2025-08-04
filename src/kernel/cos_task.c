/**
 * @file cos_task.c
 * @brief Cordelia RTOS Task Management Source
 *
 * This file contains the task management implementations
 * for the Cordelia Real-Time Operating System (CRTOS).
 * 
 * @author kskozgun
 * @version x.y.z
 */
#include "cos_task.h"
#include "cortex_m4.h"


/**
 * @brief Initialize the stack for a new task
 *
 * This function sets up the initial stack frame for a new task,
 * including the xPSR, PC, and Link registers.
 *
 * @param task_func The function to be executed by the task
 * @param psp_addr The address of the task's Process Stack Pointer (PSP)
 */
static uint32_t cos_init_stack(void (*task_func)(void), uint32_t psp_addr)
{
    uint32_t *psp_value = (uint32_t *)psp_addr + STACK_SIZE;
    // xpsr is set to 0x01000000 for the initial stack frame
    *(--psp_value) = XPSR_INITIAL_VALUE;
    // set pc to the task function address
    *(--psp_value) = (uint32_t)task_func;
    // link-register is set to return to the PSP & handler mode
    *(--psp_value) = EXEC_RT_PSP_HANDLER;
    // rest must be initalized by zero
    for(int i = 0; i < 13;  i++) {
        *(--psp_value) = 0;
    }

    return (uint32_t)psp_value; // Return the updated PSP address
}

void c_os_task_create(tcb_t *tcb, void (*task_func)(void), uint32_t psp_addr)
{
    uint32_t psp_value = cos_init_stack(task_func, psp_addr);
    if (psp_value == 0) {
        // Handle error: stack initialization failed
        return;
    }
    
    tcb->psp_addr = psp_value; // Set the Process Stack Pointer Address
    tcb->task_func = task_func;
    tcb->block_tick = 0; // Initialize block tick to 0
    tcb->state = COS_TASK_READY; // Set initial state to ready
}


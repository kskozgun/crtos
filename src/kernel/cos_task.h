/**
 * @file cos_task.h
 * @brief Cordelia RTOS Task Management Header
 *
 * This file contains the task management definitions
 * for the Cordelia Real-Time Operating System (CRTOS).
 * 
 * @author kskozgun
 * @version x.y.z
 */

#ifndef COS_TASK_H
#define COS_TASK_H

#include <stdint.h>
#include "cos_types.h"

/**
 * @addtogroup CRTOS_API CRTOS Function API
 * @brief Core RTOS kernel function interfaces
 * @{
 */

/**
 * @brief Creates a new task in the Cordelia RTOS.
 * @param tcb Pointer to the Task Control Block (TCB) structure.
 * @param task_func Pointer to the task function.
 * @param psp_addr Process Stack Pointer Address.
 *
 * This function initializes the task's stack, assigns the task function and
 * PSP address, and sets the initial state of the task.
 * It should be called before the start the scheduler.
 */
void c_os_task_create(tcb_t *tcb, void (*task_func)(void), uint32_t psp_addr);

/* @} */ // End of CRTOS_API group

#endif // COS_TASK_H
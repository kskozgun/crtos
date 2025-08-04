/**
 * @file cos_kernel.h
 * @brief Cordelia RTOS Kernel Core Header
 *
 * This file contains the core kernel definitions and function pointer examples
 * for the Cordelia Real-Time Operating System (CRTOS).
 *
 * @author kskozgun
 * @version x.y.z
 */

#ifndef COS_KERNEL_H
#define COS_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "cos_types.h"

/**
 * @defgroup CRTOS_API CRTOS Function API
 * @brief Core RTOS kernel function interfaces
 * @{
 */

/**
 * @brief Initialize the kernel.
 *
 * @return None
 */
void c_os_init(void);


/**
 * @brief Adds a task to the kernel's task list.
 *
 * @param task_func Pointer to the task function.
 * @param psp_addr Process Stack Pointer Address.
 * @return None
 *
 * This function registers a new task with the kernel, allowing it to be scheduled
 * and executed. The task function and PSP address should be defined by the user.
 * Stack initialization is handled in the function.
 */
void c_os_add_task(void (*task_func)(void), stack_mem_t psp_addr);


/**
 * @brief Schedules the next task to run in the operating system.
 *
 * This function is responsible for selecting and switching to the next
 * ready task in the cooperative operating system kernel. It manages
 * task states and ensures that the highest-priority ready task is executed.
 *
 * @note This function should be called periodically or when a task yields
 *       control to the scheduler.
 */
void c_os_task_schedule(void);


/**
 * @brief Start the RTOS scheduler.
 * 
 * This function initializes the scheduler and begins task execution. 
 * It transfers control to the first task and never returns to the caller.
 * 
 * @note This function should be called after all tasks have been added.
 * @return None
 */
void c_os_start(void);


/**
 * @brief Blocks the current task for a specified number of ticks.
 *
 * This function sets the current task's state to blocked and schedules
 * the next task to run after the specified tick count.
 *
 * @param tick_count Number of ticks to block the current task.
 * @return None
 */
void c_os_task_block_tick(uint32_t tick_count);


/**
 * @brief Yields control to the scheduler, allowing other tasks to run.
 *
 * This function is used by a task to voluntarily give up its execution time,
 * allowing the scheduler to select another task to run.
 *
 * @return None
 */
void c_os_task_yield(void);

/** @} */ // End of CRTOS_API group

#ifdef __cplusplus
}
#endif

#endif // COS_KERNEL_H

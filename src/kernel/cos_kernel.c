/**
 * @file cos_kernel.h
 * @brief Cordelia RTOS Kernel Core Header
 *
 * This file contains the core kernel implementation
 * for the Cordelia Real-Time Operating System (CRTOS).
 *
 * @author kskozgun
 * @version x.y.z
 */

#include "cos_kernel.h"
#include "cos_task.h"

#include "cortex_m4.h"


/**
 * @brief idle task stack to hold the stack frame of idle task.
 */
uint32_t idle_stack[IDLE_STACK_SIZE] __attribute__((aligned(8)));


/* Task list has 1 idle task placeholder */
static uint32_t global_tick_count = 0;
tcb_t task_list[MAX_TASKS + IDLE_TASK_PLACEHOLDER];       /* Array to hold task control blocks */
uint32_t c_os_current_task = 0;                           /* Index of the currently running task */
uint32_t c_os_next_task = 0;                              /* Index of the next task to run */


static void c_os_fetch_next_task(void)
{
    c_os_next_task = (c_os_current_task + 1) % MAX_TASKS;

    /* If the next task is blocked, find the next ready task */
    for(uint32_t i = 0; i < MAX_TASKS; i++) {
        if(task_list[c_os_next_task].state == COS_TASK_READY) {
            return;
        }

        c_os_next_task = (c_os_next_task + 1) % MAX_TASKS;
    }

    /* If all tasks are blocked, switch to idle task */
    c_os_next_task = MAX_TASKS;
}

/**
 * @brief Idle task is used when all task are blocked and not ready to run.
 */
void c_os_idle_task(void)
{
    while(1) {
        (void)0; /* Placeholder for idle task logic */
    }
}

void c_os_init(void)
{
    /* Initialize idle task */
    c_os_task_create(&task_list[MAX_TASKS], c_os_idle_task, (uint32_t)idle_stack);
}

void c_os_add_task(void (*task_func)(void), stack_mem_t psp_addr)
{
    if (c_os_current_task >= MAX_TASKS ) {
        // Handle error: too many tasks
        return;
    }

    c_os_task_create(&task_list[c_os_current_task], task_func, (uint32_t)psp_addr);
    c_os_current_task++;
}


__attribute__((noreturn)) void c_os_start(void)
{

    /* Reset the current task index */
    c_os_current_task = 0;

    /* Target HW start function */
    __start_scheduler();
    while(1) { /* Should never reach here */ }
}


void c_os_task_schedule(void)
{
    /* Compare block ticks with global tick count and update task states */
    for (uint32_t i = 0; i < MAX_TASKS; i++) {
        if(task_list[i].block_tick == global_tick_count) {
            task_list[i].block_tick = 0;
            task_list[i].state = COS_TASK_READY;
        }
    }

    /* Fetch the next task to run */
    c_os_fetch_next_task();
}

void c_os_task_block_tick(uint32_t tick_count)
{
    task_list[c_os_current_task].block_tick = global_tick_count + tick_count;
    task_list[c_os_current_task].state = COS_TASK_BLOCKED;

    c_os_fetch_next_task();
    __enter_context_switch_irq();
}

void c_os_task_yield(void)
{
    c_os_fetch_next_task();
    __enter_context_switch_irq();
}


void SysTick_Handler(void)
{
	global_tick_count++;
	c_os_task_schedule();
    __enter_context_switch_irq();
}

__attribute__((naked)) void PendSV_Handler(void)
{
    __context_switch();
}

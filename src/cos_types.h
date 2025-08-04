/**
 * @file cos_types.h
 * @brief Type definitions for Cordelia RTOS
 *
 * This file contains type definitions used throughout the
 * Cordelia Real-Time Operating System (CRTOS).
 * 
 * @author kskozgun
 * @version x.y.z
 */
#ifndef COS_TYPES_H
#define COS_TYPES_H

#include <stdint.h>
#include "cos_config.h"

#define IDLE_TASK_PLACEHOLDER (1U)      /* Placeholder for idle task in task list */
#define IDLE_TASK_INDEX (MAX_TASKS)     /* Index of the idle task in task list */

/**
 * @defgroup CRTOS Type Definitions
 * @brief This module defines the types used in Cordelia RTOS.
 * @{
 */


/**
 * @brief Task state type definition.
 */
typedef enum {
    COS_TASK_READY,   /**< Task is ready to run */
    COS_TASK_BLOCKED, /**< Task is blocked */
} cos_task_state_t;

/**
 * @brief Stack memory type definition. It ensure that the stack is aligned to 8 bytes.
 */
typedef uint32_t stack_mem_t[STACK_SIZE] __attribute__((aligned(8)));

/**
 * @brief Task Control Block type definition.
 */
typedef struct {
    uint32_t psp_addr;       /** < Process Stack Pointer Address*/
    uint32_t block_tick;     /** < Number of ticks to block task*/
    cos_task_state_t state;  /** < Current state of the task */
    void (*task_func)(void); /** < Pointer to the task function */
} tcb_t;

/** @} */ // End of CRTOS_Types

#endif /* COS_TYPES_H */
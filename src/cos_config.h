/**
 * @file config.h
 * @brief Configuration settings for Cordelia RTOS
 * 
 * This file contains compile-time configuration options for the
 * Cordelia Real-Time Operating System (CRTOS).
 * 
 * @author kskozgun
 * @version x.y.z
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*==============================================================================
 * SYSTEM CONFIGURATION
 *============================================================================*/

/* Add your configuration defines here */

#define MAX_TASKS             (4U)      /* Maximum tasks number */
#define STACK_SIZE            (250U)    /* Stack size in word */
#define IDLE_STACK_SIZE       (25U)     /* Idle task stack size in word */

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */
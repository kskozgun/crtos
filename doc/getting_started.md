# Getting Started

## Configuration 

The task's stack size and number of task must be set in ***cos_config.h*** file. 

```C
#define TASKS_NO           4     /* Maximum tasks number */
#define STACK_SIZE          250   /* Stack size in word */
```

***Note***: `TASKS_NO` should be exactly the same as the number of tasks added by the user. For example, if you add 3 tasks using `c_os_add_task()`, then `TASKS_NO` must be set to 3.


## Task and Stacks 

`Stacks` and `Tasks` must be defined by user. Each task has the same stack memory at the moment.

Since `stack_mem_t` ensure the 8-byte aligment, it must be used for stack memory definition.

```C
/* Stack memory define */
stack_mem_t stack_1;

/* Task define */
void task_1(void)
{
    while(1)
    {
        // Do stuff
    }
    // never reach here
}
```

## Scheduler

Scheduler starts with `c_os_start` function. Each task must be added in scheduler with corresponding stack memory.

```C
#include "c_os_kernel.h"

...

/* Add tasks */
c_os_add_task(task_1, stack_1);

/* Add other tasks ... */

/* Start scheduler */
c_os_start();

// Never reach in here

```

After starting scheduler, first task starts immediately, the `c_os_start` function never return.





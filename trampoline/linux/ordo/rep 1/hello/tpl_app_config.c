/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application only_one_periodic_task
 * Automatically generated by goil on Mon May  9 18:46:08 2016
 * from root OIL file hello.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include "tpl_app_config.h"

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * std = 1
 */

CONST(tpl_application_mode, OS_CONST) std = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  0 /* task Task1 :  */ ,
  1 /* task Task0 : std */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task Task1 identifier */
#define Task1_id 0
CONST(TaskType, AUTOMATIC) Task1 = Task1_id;

/* Task Task0 identifier */
#define Task0_id 1
CONST(TaskType, AUTOMATIC) Task0 = Task0_id;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc  
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Counters related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Counter SystemCounter descriptor
 */

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = 32767;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  /* ticks per base       */  1,
  /* max allowed value    */  32767,
  /* minimum cycle        */  1,
  /* current tick         */  0,
  /* current date         */  0,
#if WITH_OSAPPLICATION == YES
    /* OS Application id    */  
#endif
    /* first alarm          */  NULL_PTR,
    /* next alarm to raise  */  NULL_PTR
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
FUNC(tpl_bool, OS_CODE) tpl_call_counter_tick()
{
  tpl_counter_tick(&SystemCounter_counter_desc);

  if (tpl_kern.need_schedule)
  {
    tpl_schedule_from_running();
    LOCAL_SWITCH_CONTEXT()
  }

  return TRUE;
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*=============================================================================
 * Descriptor(s) of the idle task(s)
 */
/*-----------------------------------------------------------------------------
 * Task IDLE_TASK descriptor
 */
#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task IDLE_TASK function prototype
 */

FUNC(void, OS_APPL_CODE) idle_function(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task IDLE_TASK stack
 */
#define APP_Task_IDLE_TASK_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word IDLE_TASK_stack_zone[IDLE_STACK_SIZE/sizeof(tpl_stack_word)];
#define APP_Task_IDLE_TASK_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK IDLE_TASK_stack = {IDLE_TASK_stack_zone, IDLE_STACK_SIZE};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_STACK &IDLE_TASK_stack

/*
 * Task IDLE_TASK context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT IDLE_TASK_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_CONTEXT &IDLE_TASK_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task IDLE_TASK
 */
CONST(tpl_proc_static, OS_CONST) IDLE_TASK_task_stat_desc = {
  /* context                  */  IDLE_TASK_CONTEXT,
  /* stack                    */  IDLE_TASK_STACK,
  /* entry point (function)   */  idle_function,
  /* internal ressource       */  NULL,
  /* task id                  */  IDLE_TASK_ID,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  0,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task IDLE_TASK
 */
VAR(tpl_proc, OS_VAR) IDLE_TASK_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  0,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task Task1 descriptor
 */
#define APP_Task_Task1_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Task1 function prototype
 */

FUNC(void, OS_APPL_CODE) Task1_function(void);
#define APP_Task_Task1_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Task1 stack
 */
#define APP_Task_Task1_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word Task1_stack_zone[32768/sizeof(tpl_stack_word)];
#define APP_Task_Task1_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK Task1_stack = {Task1_stack_zone, 32768};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define Task1_STACK &Task1_stack

/*
 * Task Task1 context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT Task1_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define Task1_CONTEXT &Task1_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Task1
 */
CONST(tpl_proc_static, OS_CONST) Task1_task_stat_desc = {
  /* context                  */  Task1_CONTEXT,
  /* stack                    */  Task1_STACK,
  /* entry point (function)   */  Task1_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Task1_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Task1
 */
VAR(tpl_proc, OS_VAR) Task1_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task Task0 descriptor
 */
#define APP_Task_Task0_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Task0 function prototype
 */

FUNC(void, OS_APPL_CODE) Task0_function(void);
#define APP_Task_Task0_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Task0 stack
 */
#define APP_Task_Task0_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word Task0_stack_zone[32768/sizeof(tpl_stack_word)];
#define APP_Task_Task0_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK Task0_stack = {Task0_stack_zone, 32768};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define Task0_STACK &Task0_stack

/*
 * Task Task0 context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT Task0_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define Task0_CONTEXT &Task0_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Task0
 */
CONST(tpl_proc_static, OS_CONST) Task0_task_stat_desc = {
  /* context                  */  Task0_CONTEXT,
  /* stack                    */  Task0_STACK,
  /* entry point (function)   */  Task0_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Task0_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Task0
 */
VAR(tpl_proc, OS_VAR) Task0_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Task1_task_stat_desc,
  &Task0_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Task1_task_desc,
  &Task0_task_desc,
  &IDLE_TASK_task_desc
};



#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */

/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[4];
VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[4] = {
  0,
  0,
  0
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  NULL,                      /* no running task static descriptor   */
  &IDLE_TASK_task_stat_desc, /* elected task to run is idle task    */
  NULL,                      /* no running task dynamic descriptor  */
  &IDLE_TASK_task_desc,      /* elected task to run is idle task    */
  INVALID_PROC_ID,           /* no running task so no ID            */
  INVALID_PROC_ID,           /* idle task has no ID                 */
  NO_NEED_SWITCH,            /* no context switch needed at start   */
  FALSE,                     /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  1,                         /* at early system startup, we run in  */
                             /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1] = {

  "Task1",
  "Task0",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */

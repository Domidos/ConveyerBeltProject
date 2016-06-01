/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Stromregler'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 19 14:35:39 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include "Stromregler.h"               /* Model's header file */
#include "rtwtypes.h"

/* ANSI C headers */
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* VxWorks headers */
#include <vxWorks.h>
#include <taskLib.h>
#include <sysLib.h>
#include <semLib.h>
#include <rebootLib.h>
#include <logLib.h>

/* this sets the standard stack size for spawned tasks used by the model.
 * this can be changed by compiling with '-DSTACK_SIZE=nnn' where nnn is
 * the stack size desired.
 */
#ifndef STACK_SIZE
#define STACK_SIZE                     16384
#endif

static int_T tSubRate_1(SEM_ID sem)
{
  while (1) {
    semTake(sem, WAIT_FOREVER);

    /* Set model inputs associated to subrate here */

    /* Step the model for sample time for tid */
    Stromregler_step1();

    /* Get model outputs here */

    /* Write model outputs associated to subrate here */
  }

  return(1);
}

static int_T tBaseRate(SEM_ID sem, SEM_ID startStopSem, SEM_ID taskSemList[])
{
  static int_T taskCounter[2] = { 0, 0 };

  while (1) {
    if (rtmGetErrorStatus(Stromregler_M) != (NULL)) {
      fprintf(stderr,"Error status: %s \n", rtmGetErrorStatus(Stromregler_M));
      semGive(startStopSem);
      return(1);
    }

    if (semTake(sem,NO_WAIT) != ERROR) {
      logMsg("Rate for BaseRate task too fast.\n",0,0,0,0,0,0);
    } else {
      semTake(sem, WAIT_FOREVER);
    }

    if (taskCounter[1] == 0) {
      semGive(taskSemList[1]);
      if (semTake(taskSemList[1],NO_WAIT) != ERROR) {
        logMsg("Rate for SubRate task %d is too fast.\n",1,0,0,0,0,0);
        semGive(taskSemList[1]);
      }
    }

    taskCounter[1]++;
    if (taskCounter[1] == 10) {
      taskCounter[1]= 0;
    }

    /* Set model inputs associated with base rate here */

    /* Step the model for base rate */
    Stromregler_step0();

    /* Get model outputs here */
  }
}

/*
 * Spawn Stromregler_main as an independent VxWorks task from your
 * application code, specifying its O/S priority
 */
int_T Stromregler_main(int_T priority)
{
  const char *status;
  real_T requestedSR, actualSR;
  int_T VxWorksTIDs[2];
  SEM_ID rtTaskSemaphoreList[2];
  SEM_ID rtClockSem, startStopSem;
  printf("Warning: The simulation will run forever. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  if (priority <= 0 || priority > 255-(2)+1) {
    priority = 30;
  }

  rtClockSem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
  startStopSem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);

  /* Initialize model */
  Stromregler_initialize();
  requestedSR = 1.0 / 0.005;
  sysAuxClkDisable();
  sysAuxClkRateSet((int_T)(requestedSR + 0.5));
  actualSR = (real_T) sysAuxClkRateGet();
  printf("Actual sample rate in Hertz: %f\n",actualSR);
  rtTaskSemaphoreList[1] = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
  VxWorksTIDs[1] = taskSpawn("tRate1",
    priority + 1, VX_FP_TASK, STACK_SIZE, (FUNCPTR)tSubRate_1,
    (int_T) rtTaskSemaphoreList[1], 0, 0, 0, 0, 0, 0, 0, 0, 0);
  VxWorksTIDs[0] = taskSpawn("tBaseRate",
    priority, VX_FP_TASK, STACK_SIZE, (FUNCPTR)tBaseRate, (int_T) rtClockSem,
    (int_T) startStopSem, (int_T) rtTaskSemaphoreList, 0, 0, 0, 0, 0, 0, 0);
  if (sysAuxClkConnect((FUNCPTR) semGive, (int_T) rtClockSem) == OK) {
    rebootHookAdd((FUNCPTR) sysAuxClkDisable);
    printf("\nSimulation starting\n");
    sysAuxClkEnable();
  }

  semTake(startStopSem, WAIT_FOREVER);
  sysAuxClkDisable();
  taskDelete(VxWorksTIDs[0]);
  semDelete(rtClockSem);
  semDelete(startStopSem);
  taskDelete(VxWorksTIDs[1]);
  semDelete(rtTaskSemaphoreList[1]);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Stromregler_terminate();
  return(EXIT_SUCCESS);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

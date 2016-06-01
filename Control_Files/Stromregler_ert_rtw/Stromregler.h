/*
 * File: Stromregler.h
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

#ifndef RTW_HEADER_Stromregler_h_
#define RTW_HEADER_Stromregler_h_
#include <stddef.h>
#ifndef Stromregler_COMMON_INCLUDES_
# define Stromregler_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Stromregler_COMMON_INCLUDES_ */

#include "Stromregler_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay2_DSTATE;            /* '<S1>/Unit Delay2' */
  real_T UnitDelay_DSTATE;             /* '<S1>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real_T UnitDelay3_DSTATE;            /* '<S1>/Unit Delay3' */
} DW_Stromregler_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Regelgre_Drehzahl;            /* '<Root>/Regelgrˆﬂe_Drehzahl' */
  real_T RegelgroeeI;                  /* '<Root>/RegelgroeﬂeI' */
} ExtU_Stromregler_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Stellgroee_I;                 /* '<Root>/Stellgroeﬂe_I' */
  real_T Stellgroee_Drehzahl;          /* '<Root>/Stellgroeﬂe_Drehzahl' */
} ExtY_Stromregler_T;

/* Real-time Model Data Structure */
struct tag_RTM_Stromregler_T {
  const char_T *errorStatus;
};

/* Block states (auto storage) */
extern DW_Stromregler_T Stromregler_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Stromregler_T Stromregler_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Stromregler_T Stromregler_Y;

/* Model entry point functions */
extern void Stromregler_initialize(void);
extern void Stromregler_step0(void);
extern void Stromregler_step1(void);
extern void Stromregler_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Stromregler_T *const Stromregler_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('GesamtmodellII/Stromregler')    - opens subsystem GesamtmodellII/Stromregler
 * hilite_system('GesamtmodellII/Stromregler/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'GesamtmodellII'
 * '<S1>'   : 'GesamtmodellII/Stromregler'
 */
#endif                                 /* RTW_HEADER_Stromregler_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: Stromregler.c
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

#include "Stromregler.h"
#include "Stromregler_private.h"

/* Block states (auto storage) */
DW_Stromregler_T Stromregler_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Stromregler_T Stromregler_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Stromregler_T Stromregler_Y;

/* Real-time model */
RT_MODEL_Stromregler_T Stromregler_M_;
RT_MODEL_Stromregler_T *const Stromregler_M = &Stromregler_M_;

/* Model step function for TID0 */
void Stromregler_step0(void)           /* Sample time: [0.005s, 0.0s] */
{
  real_T rtb_AntiWindup2;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/Gain2'
   *  Gain: '<S1>/Gain3'
   *  Inport: '<Root>/RegelgroeﬂeI'
   *  UnitDelay: '<S1>/Unit Delay2'
   *  UnitDelay: '<S1>/Unit Delay3'
   */
  rtb_AntiWindup2 = (0.005000000000000001 * Stromregler_DW.UnitDelay2_DSTATE +
                     0.015 * Stromregler_U.RegelgroeeI) +
    Stromregler_DW.UnitDelay3_DSTATE;

  /* Saturate: '<S1>/Anti Wind up2' */
  if (rtb_AntiWindup2 > 9.0) {
    rtb_AntiWindup2 = 9.0;
  } else {
    if (rtb_AntiWindup2 < -9.0) {
      rtb_AntiWindup2 = -9.0;
    }
  }

  /* End of Saturate: '<S1>/Anti Wind up2' */

  /* Outport: '<Root>/Stellgroeﬂe_I' */
  Stromregler_Y.Stellgroee_I = rtb_AntiWindup2;

  /* Update for UnitDelay: '<S1>/Unit Delay2' incorporates:
   *  Update for Inport: '<Root>/RegelgroeﬂeI'
   */
  Stromregler_DW.UnitDelay2_DSTATE = Stromregler_U.RegelgroeeI;

  /* Update for UnitDelay: '<S1>/Unit Delay3' */
  Stromregler_DW.UnitDelay3_DSTATE = rtb_AntiWindup2;
}

/* Model step function for TID1 */
void Stromregler_step1(void)           /* Sample time: [0.05s, 0.0s] */
{
  real_T rtb_Sum;

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/Regelgrˆﬂe_Drehzahl'
   *  UnitDelay: '<S1>/Unit Delay'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  rtb_Sum = (-0.015714285714285712 * Stromregler_DW.UnitDelay_DSTATE + 0.03 *
             Stromregler_U.Regelgre_Drehzahl) + Stromregler_DW.UnitDelay1_DSTATE;

  /* Outport: '<Root>/Stellgroeﬂe_Drehzahl' */
  Stromregler_Y.Stellgroee_Drehzahl = rtb_Sum;

  /* Update for UnitDelay: '<S1>/Unit Delay' incorporates:
   *  Update for Inport: '<Root>/Regelgrˆﬂe_Drehzahl'
   */
  Stromregler_DW.UnitDelay_DSTATE = Stromregler_U.Regelgre_Drehzahl;

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  Stromregler_DW.UnitDelay1_DSTATE = rtb_Sum;
}

/* Model initialize function */
void Stromregler_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Stromregler_M, (NULL));

  /* states (dwork) */
  Stromregler_DW.UnitDelay2_DSTATE = 0.0;
  Stromregler_DW.UnitDelay_DSTATE = 0.0;
  Stromregler_DW.UnitDelay1_DSTATE = 0.0;
  Stromregler_DW.UnitDelay3_DSTATE = 0.0;

  /* external inputs */
  Stromregler_U.Regelgre_Drehzahl = 0.0;
  Stromregler_U.RegelgroeeI = 0.0;

  /* external outputs */
  Stromregler_Y.Stellgroee_I = 0.0;
  Stromregler_Y.Stellgroee_Drehzahl = 0.0;
}

/* Model terminate function */
void Stromregler_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: pruebaj2.c
 *
 * Code generated for Simulink model 'pruebaj2'.
 *
 * Model version                  : 1.72
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Sep 17 15:20:04 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pruebaj2.h"
#include "pruebaj2_private.h"

/* Block signals (auto storage) */
B_pruebaj2_T pruebaj2_B;

/* Continuous states */
X_pruebaj2_T pruebaj2_X;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_pruebaj2_T pruebaj2_Y;


double get_1(void){
	return pruebaj2_Y.Out1;
	}
	

/* Real-time model */
RT_MODEL_pruebaj2_T pruebaj2_M_;
RT_MODEL_pruebaj2_T *const pruebaj2_M = &pruebaj2_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  pruebaj2_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  pruebaj2_step();
  pruebaj2_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  pruebaj2_step();
  pruebaj2_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  pruebaj2_step();
  pruebaj2_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void pruebaj2_step(void)
{
  if (rtmIsMajorTimeStep(pruebaj2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&pruebaj2_M->solverInfo,
                          ((pruebaj2_M->Timing.clockTick0+1)*
      pruebaj2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(pruebaj2_M)) {
    pruebaj2_M->Timing.t[0] = rtsiGetT(&pruebaj2_M->solverInfo);
  }

  /* Outport: '<Root>/Out1' incorporates:
   *  TransferFcn: '<Root>/VSI  line Z2'
   */
  pruebaj2_Y.Out1 = pruebaj2_X.VSIlineZ2_CSTATE;

  /* Step: '<Root>/Step' */
  pruebaj2_B.Step = !(pruebaj2_M->Timing.t[0] < 0.0);

  /* TransferFcn: '<Root>/VSI  line Z1' */
  pruebaj2_B.VSIlineZ1 = 0.0;
  pruebaj2_B.VSIlineZ1 += pruebaj2_X.VSIlineZ1_CSTATE;
  if (rtmIsMajorTimeStep(pruebaj2_M)) {
    rt_ertODEUpdateContinuousStates(&pruebaj2_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++pruebaj2_M->Timing.clockTick0;
    pruebaj2_M->Timing.t[0] = rtsiGetSolverStopTime(&pruebaj2_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      pruebaj2_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void pruebaj2_derivatives(void)
{
  XDot_pruebaj2_T *_rtXdot;
  _rtXdot = ((XDot_pruebaj2_T *) pruebaj2_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z2' */
  _rtXdot->VSIlineZ2_CSTATE = 0.0;
  _rtXdot->VSIlineZ2_CSTATE += -pruebaj2_X.VSIlineZ2_CSTATE;
  _rtXdot->VSIlineZ2_CSTATE += pruebaj2_B.VSIlineZ1;

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z1' */
  _rtXdot->VSIlineZ1_CSTATE = 0.0;
  _rtXdot->VSIlineZ1_CSTATE += -pruebaj2_X.VSIlineZ1_CSTATE;
  _rtXdot->VSIlineZ1_CSTATE += pruebaj2_B.Step;
}

/* Model initialize function */
void pruebaj2_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)pruebaj2_M, 0,
                sizeof(RT_MODEL_pruebaj2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&pruebaj2_M->solverInfo,
                          &pruebaj2_M->Timing.simTimeStep);
    rtsiSetTPtr(&pruebaj2_M->solverInfo, &rtmGetTPtr(pruebaj2_M));
    rtsiSetStepSizePtr(&pruebaj2_M->solverInfo, &pruebaj2_M->Timing.stepSize0);
    rtsiSetdXPtr(&pruebaj2_M->solverInfo, &pruebaj2_M->derivs);
    rtsiSetContStatesPtr(&pruebaj2_M->solverInfo, (real_T **)
                         &pruebaj2_M->contStates);
    rtsiSetNumContStatesPtr(&pruebaj2_M->solverInfo,
      &pruebaj2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&pruebaj2_M->solverInfo,
      &pruebaj2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&pruebaj2_M->solverInfo,
      &pruebaj2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&pruebaj2_M->solverInfo,
      &pruebaj2_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&pruebaj2_M->solverInfo, (&rtmGetErrorStatus
      (pruebaj2_M)));
    rtsiSetRTModelPtr(&pruebaj2_M->solverInfo, pruebaj2_M);
  }

  rtsiSetSimTimeStep(&pruebaj2_M->solverInfo, MAJOR_TIME_STEP);
  pruebaj2_M->intgData.y = pruebaj2_M->odeY;
  pruebaj2_M->intgData.f[0] = pruebaj2_M->odeF[0];
  pruebaj2_M->intgData.f[1] = pruebaj2_M->odeF[1];
  pruebaj2_M->intgData.f[2] = pruebaj2_M->odeF[2];
  pruebaj2_M->intgData.f[3] = pruebaj2_M->odeF[3];
  pruebaj2_M->contStates = ((X_pruebaj2_T *) &pruebaj2_X);
  rtsiSetSolverData(&pruebaj2_M->solverInfo, (void *)&pruebaj2_M->intgData);
  rtsiSetSolverName(&pruebaj2_M->solverInfo,"ode4");
  rtmSetTPtr(pruebaj2_M, &pruebaj2_M->Timing.tArray[0]);
  pruebaj2_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &pruebaj2_B), 0,
                sizeof(B_pruebaj2_T));

  /* states (continuous) */
  {
    (void) memset((void *)&pruebaj2_X, 0,
                  sizeof(X_pruebaj2_T));
  }

  /* external outputs */
  pruebaj2_Y.Out1 = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z2' */
  pruebaj2_X.VSIlineZ2_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z1' */
  pruebaj2_X.VSIlineZ1_CSTATE = 0.0;
}

/* Model terminate function */
void pruebaj2_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

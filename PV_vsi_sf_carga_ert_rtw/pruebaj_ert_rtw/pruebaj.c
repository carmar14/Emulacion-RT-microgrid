/*
 * File: pruebaj.c
 *
 * Code generated for Simulink model 'pruebaj'.
 *
 * Model version                  : 1.71
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Sep 17 15:21:19 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pruebaj.h"
#include "pruebaj_private.h"

/* Continuous states */
X_pruebaj_T pruebaj_X;

/* External inputs (root inport signals with auto storage) */
ExtU_pruebaj_T pruebaj_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_pruebaj_T pruebaj_Y;

void set_1(double e){
	pruebaj_U.In1=e;
	}
double get_1(void){
	return pruebaj_Y.Out1;
	}
	
/* Real-time model */
RT_MODEL_pruebaj_T pruebaj_M_;
RT_MODEL_pruebaj_T *const pruebaj_M = &pruebaj_M_;

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
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  pruebaj_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  pruebaj_step();
  pruebaj_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  pruebaj_step();
  pruebaj_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  pruebaj_step();
  pruebaj_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void pruebaj_step(void)
{
  if (rtmIsMajorTimeStep(pruebaj_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&pruebaj_M->solverInfo,((pruebaj_M->Timing.clockTick0+
      1)*pruebaj_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(pruebaj_M)) {
    pruebaj_M->Timing.t[0] = rtsiGetT(&pruebaj_M->solverInfo);
  }

  /* Outport: '<Root>/Out1' incorporates:
   *  TransferFcn: '<Root>/VSI  line Z1'
   */
  pruebaj_Y.Out1 = pruebaj_X.VSIlineZ1_CSTATE;
  if (rtmIsMajorTimeStep(pruebaj_M)) {
    rt_ertODEUpdateContinuousStates(&pruebaj_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++pruebaj_M->Timing.clockTick0;
    pruebaj_M->Timing.t[0] = rtsiGetSolverStopTime(&pruebaj_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      pruebaj_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void pruebaj_derivatives(void)
{
  XDot_pruebaj_T *_rtXdot;
  _rtXdot = ((XDot_pruebaj_T *) pruebaj_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z1' incorporates:
   *  Derivatives for Inport: '<Root>/In1'
   */
  _rtXdot->VSIlineZ1_CSTATE = 0.0;
  _rtXdot->VSIlineZ1_CSTATE += -pruebaj_X.VSIlineZ1_CSTATE;
  _rtXdot->VSIlineZ1_CSTATE += pruebaj_U.In1;
}

/* Model initialize function */
void pruebaj_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)pruebaj_M, 0,
                sizeof(RT_MODEL_pruebaj_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&pruebaj_M->solverInfo, &pruebaj_M->Timing.simTimeStep);
    rtsiSetTPtr(&pruebaj_M->solverInfo, &rtmGetTPtr(pruebaj_M));
    rtsiSetStepSizePtr(&pruebaj_M->solverInfo, &pruebaj_M->Timing.stepSize0);
    rtsiSetdXPtr(&pruebaj_M->solverInfo, &pruebaj_M->derivs);
    rtsiSetContStatesPtr(&pruebaj_M->solverInfo, (real_T **)
                         &pruebaj_M->contStates);
    rtsiSetNumContStatesPtr(&pruebaj_M->solverInfo,
      &pruebaj_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&pruebaj_M->solverInfo,
      &pruebaj_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&pruebaj_M->solverInfo,
      &pruebaj_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&pruebaj_M->solverInfo,
      &pruebaj_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&pruebaj_M->solverInfo, (&rtmGetErrorStatus(pruebaj_M)));
    rtsiSetRTModelPtr(&pruebaj_M->solverInfo, pruebaj_M);
  }

  rtsiSetSimTimeStep(&pruebaj_M->solverInfo, MAJOR_TIME_STEP);
  pruebaj_M->intgData.y = pruebaj_M->odeY;
  pruebaj_M->intgData.f[0] = pruebaj_M->odeF[0];
  pruebaj_M->intgData.f[1] = pruebaj_M->odeF[1];
  pruebaj_M->intgData.f[2] = pruebaj_M->odeF[2];
  pruebaj_M->intgData.f[3] = pruebaj_M->odeF[3];
  pruebaj_M->contStates = ((X_pruebaj_T *) &pruebaj_X);
  rtsiSetSolverData(&pruebaj_M->solverInfo, (void *)&pruebaj_M->intgData);
  rtsiSetSolverName(&pruebaj_M->solverInfo,"ode4");
  rtmSetTPtr(pruebaj_M, &pruebaj_M->Timing.tArray[0]);
  pruebaj_M->Timing.stepSize0 = 0.0001;

  /* states (continuous) */
  {
    (void) memset((void *)&pruebaj_X, 0,
                  sizeof(X_pruebaj_T));
  }

  /* external inputs */
  pruebaj_U.In1 = 0.0;

  /* external outputs */
  pruebaj_Y.Out1 = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z1' */
  pruebaj_X.VSIlineZ1_CSTATE = 0.0;
}

/* Model terminate function */
void pruebaj_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: PV_vsi_sf_carga.c
 *
 * Code generated for Simulink model 'PV_vsi_sf_carga'.
 *
 * Model version                  : 1.68
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Sep 17 11:41:37 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PV_vsi_sf_carga.h"
#include "PV_vsi_sf_carga_private.h"

/* Block signals (auto storage) */
B_PV_vsi_sf_carga_T PV_vsi_sf_carga_B;

/* Continuous states */
X_PV_vsi_sf_carga_T PV_vsi_sf_carga_X;

/* Block states (auto storage) */
DW_PV_vsi_sf_carga_T PV_vsi_sf_carga_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_PV_vsi_sf_carga_T PV_vsi_sf_carga_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_PV_vsi_sf_carga_T PV_vsi_sf_carga_Y;

//-------Funciones para asignar entradas-------------
void set_Ipv(double Ipv){
	PV_vsi_sf_carga_U.Ipv=Ipv;
}

//-----Funciones para obtener valores de las salidas-------
double get_I3(void){
	return PV_vsi_sf_carga_Y.i3;
}

double get_SOC(void){
	return PV_vsi_sf_carga_Y.SOC;
}
	
double get_vload(void){
	return PV_vsi_sf_carga_Y.vload;
}	

/* Real-time model */
RT_MODEL_PV_vsi_sf_carga_T PV_vsi_sf_carga_M_;
RT_MODEL_PV_vsi_sf_carga_T *const PV_vsi_sf_carga_M = &PV_vsi_sf_carga_M_;
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

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
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PV_vsi_sf_carga_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void PV_vsi_sf_carga_step(void)
{
  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&PV_vsi_sf_carga_M->solverInfo,
                          ((PV_vsi_sf_carga_M->Timing.clockTick0+1)*
      PV_vsi_sf_carga_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PV_vsi_sf_carga_M)) {
    PV_vsi_sf_carga_M->Timing.t[0] = rtsiGetT(&PV_vsi_sf_carga_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T rtb_batteryVdc;
    real_T rtb_VSIlineZ;
    real_T rtb_TransferFcn2;

    /* TransferFcn: '<Root>/VSI  line Z' */
    rtb_VSIlineZ = 33.333333333333336 * PV_vsi_sf_carga_X.VSIlineZ_CSTATE;

    /* TransferFcn: '<Root>/Transfer Fcn3' */
    PV_vsi_sf_carga_B.TransferFcn3 = 0.0;
    PV_vsi_sf_carga_B.TransferFcn3 += 376.7897513187641 *
      PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
    PV_vsi_sf_carga_B.TransferFcn3 += 0.0 *
      PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1];

    /* Derivative: '<Root>/Derivative1' */
    if ((PV_vsi_sf_carga_DW.TimeStampA >= PV_vsi_sf_carga_M->Timing.t[0]) &&
        (PV_vsi_sf_carga_DW.TimeStampB >= PV_vsi_sf_carga_M->Timing.t[0])) {
      rtb_batteryVdc = 0.0;
    } else {
      rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampA;
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
      if (PV_vsi_sf_carga_DW.TimeStampA < PV_vsi_sf_carga_DW.TimeStampB) {
        if (PV_vsi_sf_carga_DW.TimeStampB < PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampB;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
        }
      } else {
        if (PV_vsi_sf_carga_DW.TimeStampA >= PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampB;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
        }
      }

      rtb_batteryVdc = (PV_vsi_sf_carga_B.TransferFcn3 - *lastU) /
        (PV_vsi_sf_carga_M->Timing.t[0] - rtb_TransferFcn2);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Sum: '<Root>/Sum5' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    PV_vsi_sf_carga_B.vsicurrent = rtb_VSIlineZ - 0.00061 * rtb_batteryVdc;

    /* Outport: '<Root>/i3' */
    PV_vsi_sf_carga_Y.i3 = PV_vsi_sf_carga_B.vsicurrent;

    /* Integrator: '<Root>/Integrator' */
    /* Limited  Integrator  */
    if (PV_vsi_sf_carga_X.Integrator_CSTATE >= 1.0) {
      PV_vsi_sf_carga_X.Integrator_CSTATE = 1.0;
    } else {
      if (PV_vsi_sf_carga_X.Integrator_CSTATE <= 0.0) {
        PV_vsi_sf_carga_X.Integrator_CSTATE = 0.0;
      }
    }

    /* MATLAB Function: '<Root>/MATLAB Function SOC ' incorporates:
     *  Integrator: '<Root>/Integrator'
     */
    /* MATLAB Function 'MATLAB Function SOC ': '<S2>:1' */
    /* '<S2>:1:3' y = -0.03536*u+100; */
    rtb_batteryVdc = -0.03536 * PV_vsi_sf_carga_X.Integrator_CSTATE + 100.0;

    /* Outport: '<Root>/SOC' */
    PV_vsi_sf_carga_Y.SOC = rtb_batteryVdc;

    /* Outport: '<Root>/vload' */
    PV_vsi_sf_carga_Y.vload = PV_vsi_sf_carga_B.TransferFcn3;

    /* Sin: '<Root>/Sine Wave' */
    PV_vsi_sf_carga_B.refvoltage = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0]) * 170.0;

    /* Derivative: '<Root>/Derivative' */
    if ((PV_vsi_sf_carga_DW.TimeStampA_e >= PV_vsi_sf_carga_M->Timing.t[0]) &&
        (PV_vsi_sf_carga_DW.TimeStampB_a >= PV_vsi_sf_carga_M->Timing.t[0])) {
      rtb_TransferFcn2 = 0.0;
    } else {
      rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampA_e;
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
      if (PV_vsi_sf_carga_DW.TimeStampA_e < PV_vsi_sf_carga_DW.TimeStampB_a) {
        if (PV_vsi_sf_carga_DW.TimeStampB_a < PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampB_a;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
        }
      } else {
        if (PV_vsi_sf_carga_DW.TimeStampA_e >= PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_TransferFcn2 = PV_vsi_sf_carga_DW.TimeStampB_a;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
        }
      }

      rtb_TransferFcn2 = (PV_vsi_sf_carga_B.refvoltage - *lastU) /
        (PV_vsi_sf_carga_M->Timing.t[0] - rtb_TransferFcn2);
    }

    /* End of Derivative: '<Root>/Derivative' */

    /* Sum: '<Root>/Sum3' incorporates:
     *  Gain: '<Root>/Gain'
     *  Sum: '<Root>/Sum2'
     */
    PV_vsi_sf_carga_B.Sum3 = (0.00061 * rtb_TransferFcn2 +
      PV_vsi_sf_carga_B.vsicurrent) - rtb_VSIlineZ;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Gain: '<Root>/Gain1'
     *  Gain: '<Root>/Gain4'
     *  Gain: '<S1>/Gain2'
     *  Lookup_n-D: '<Root>/1-D Lookup Table2'
     *  Product: '<Root>/Product2'
     *  Sum: '<S1>/Sum5'
     *  TransferFcn: '<S1>/Transfer Fcn2'
     */
    PV_vsi_sf_carga_B.Sum4 = ((2.0 * PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0] +
      0.0 * PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1]) + 0.002 *
      PV_vsi_sf_carga_B.Sum3) * 2.0 * (2.0 * look1_binlxpw(rtb_batteryVdc,
      PV_vsi_sf_carga_ConstP.uDLookupTable2_bp01Data,
      PV_vsi_sf_carga_ConstP.uDLookupTable2_tableData, 8U)) -
      PV_vsi_sf_carga_B.TransferFcn3;

    /* Sum: '<Root>/Sum7' incorporates:
     *  Constant: '<Root>/Current Panel'
     */
    PV_vsi_sf_carga_B.Sum7 = rtb_VSIlineZ + 1.5;
  }

  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (PV_vsi_sf_carga_DW.TimeStampA == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampA = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
    } else if (PV_vsi_sf_carga_DW.TimeStampB == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampB = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
    } else if (PV_vsi_sf_carga_DW.TimeStampA < PV_vsi_sf_carga_DW.TimeStampB) {
      PV_vsi_sf_carga_DW.TimeStampA = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
    } else {
      PV_vsi_sf_carga_DW.TimeStampB = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
    }

    *lastU = PV_vsi_sf_carga_B.TransferFcn3;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for Derivative: '<Root>/Derivative' */
    if (PV_vsi_sf_carga_DW.TimeStampA_e == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampA_e = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
    } else if (PV_vsi_sf_carga_DW.TimeStampB_a == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampB_a = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
    } else if (PV_vsi_sf_carga_DW.TimeStampA_e < PV_vsi_sf_carga_DW.TimeStampB_a)
    {
      PV_vsi_sf_carga_DW.TimeStampA_e = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
    } else {
      PV_vsi_sf_carga_DW.TimeStampB_a = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
    }

    *lastU = PV_vsi_sf_carga_B.refvoltage;

    /* End of Update for Derivative: '<Root>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    rt_ertODEUpdateContinuousStates(&PV_vsi_sf_carga_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++PV_vsi_sf_carga_M->Timing.clockTick0;
    PV_vsi_sf_carga_M->Timing.t[0] = rtsiGetSolverStopTime
      (&PV_vsi_sf_carga_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      PV_vsi_sf_carga_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PV_vsi_sf_carga_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_PV_vsi_sf_carga_T *_rtXdot;
  _rtXdot = ((XDot_PV_vsi_sf_carga_T *) PV_vsi_sf_carga_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z' */
  _rtXdot->VSIlineZ_CSTATE = 0.0;
  _rtXdot->VSIlineZ_CSTATE += -0.03333333333333334 *
    PV_vsi_sf_carga_X.VSIlineZ_CSTATE;
  _rtXdot->VSIlineZ_CSTATE += PV_vsi_sf_carga_B.Sum4;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -75.357950263752812 *
    PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -72.459567561300787 *
    PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[1] += PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[0] += PV_vsi_sf_carga_B.vsicurrent;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  lsat = (PV_vsi_sf_carga_X.Integrator_CSTATE <= 0.0);
  usat = (PV_vsi_sf_carga_X.Integrator_CSTATE >= 1.0);
  if (((!lsat) && (!usat)) || (lsat && (PV_vsi_sf_carga_B.Sum7 > 0.0)) || (usat &&
       (PV_vsi_sf_carga_B.Sum7 < 0.0))) {
    _rtXdot->Integrator_CSTATE = PV_vsi_sf_carga_B.Sum7;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<Root>/Integrator' */

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -2.0 *
    PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -142122.30337568672 *
    PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[1] += PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[0] += PV_vsi_sf_carga_B.Sum3;
}

/* Model initialize function */
void PV_vsi_sf_carga_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PV_vsi_sf_carga_M, 0,
                sizeof(RT_MODEL_PV_vsi_sf_carga_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PV_vsi_sf_carga_M->solverInfo,
                          &PV_vsi_sf_carga_M->Timing.simTimeStep);
    rtsiSetTPtr(&PV_vsi_sf_carga_M->solverInfo, &rtmGetTPtr(PV_vsi_sf_carga_M));
    rtsiSetStepSizePtr(&PV_vsi_sf_carga_M->solverInfo,
                       &PV_vsi_sf_carga_M->Timing.stepSize0);
    rtsiSetdXPtr(&PV_vsi_sf_carga_M->solverInfo, &PV_vsi_sf_carga_M->derivs);
    rtsiSetContStatesPtr(&PV_vsi_sf_carga_M->solverInfo, (real_T **)
                         &PV_vsi_sf_carga_M->contStates);
    rtsiSetNumContStatesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PV_vsi_sf_carga_M->solverInfo, (&rtmGetErrorStatus
      (PV_vsi_sf_carga_M)));
    rtsiSetRTModelPtr(&PV_vsi_sf_carga_M->solverInfo, PV_vsi_sf_carga_M);
  }

  rtsiSetSimTimeStep(&PV_vsi_sf_carga_M->solverInfo, MAJOR_TIME_STEP);
  PV_vsi_sf_carga_M->intgData.y = PV_vsi_sf_carga_M->odeY;
  PV_vsi_sf_carga_M->intgData.f[0] = PV_vsi_sf_carga_M->odeF[0];
  PV_vsi_sf_carga_M->intgData.f[1] = PV_vsi_sf_carga_M->odeF[1];
  PV_vsi_sf_carga_M->intgData.f[2] = PV_vsi_sf_carga_M->odeF[2];
  PV_vsi_sf_carga_M->intgData.f[3] = PV_vsi_sf_carga_M->odeF[3];
  PV_vsi_sf_carga_M->contStates = ((X_PV_vsi_sf_carga_T *) &PV_vsi_sf_carga_X);
  rtsiSetSolverData(&PV_vsi_sf_carga_M->solverInfo, (void *)
                    &PV_vsi_sf_carga_M->intgData);
  rtsiSetSolverName(&PV_vsi_sf_carga_M->solverInfo,"ode4");
  rtmSetTPtr(PV_vsi_sf_carga_M, &PV_vsi_sf_carga_M->Timing.tArray[0]);
  PV_vsi_sf_carga_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &PV_vsi_sf_carga_B), 0,
                sizeof(B_PV_vsi_sf_carga_T));

  /* states (continuous) */
  {
    (void) memset((void *)&PV_vsi_sf_carga_X, 0,
                  sizeof(X_PV_vsi_sf_carga_T));
  }

  /* states (dwork) */
  (void) memset((void *)&PV_vsi_sf_carga_DW, 0,
                sizeof(DW_PV_vsi_sf_carga_T));

  /* external inputs */
  (void)memset((void *)&PV_vsi_sf_carga_U, 0, sizeof(ExtU_PV_vsi_sf_carga_T));

  /* external outputs */
  (void) memset((void *)&PV_vsi_sf_carga_Y, 0,
                sizeof(ExtY_PV_vsi_sf_carga_T));

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z' */
  PV_vsi_sf_carga_X.VSIlineZ_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  PV_vsi_sf_carga_DW.TimeStampA = (rtInf);
  PV_vsi_sf_carga_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  PV_vsi_sf_carga_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  PV_vsi_sf_carga_DW.TimeStampA_e = (rtInf);
  PV_vsi_sf_carga_DW.TimeStampB_a = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1] = 0.0;
}

/* Model terminate function */
void PV_vsi_sf_carga_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

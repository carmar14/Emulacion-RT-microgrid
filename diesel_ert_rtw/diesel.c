/*
 * File: diesel.c
 *
 * Code generated for Simulink model 'diesel'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:52:14 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "diesel.h"
#include "diesel_private.h"

/* Block signals (default storage) */
B_diesel_T diesel_B;

/* Continuous states */
X_diesel_T diesel_X;

/* Block states (default storage) */
DW_diesel_T diesel_DW;

/* External inputs (root inport signals with default storage) */
ExtU_diesel_T diesel_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_diesel_T diesel_Y;

/* Real-time model */
RT_MODEL_diesel_T diesel_M_;
RT_MODEL_diesel_T *const diesel_M = &diesel_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/* This function updates continuous states using the ODE8 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
#define diesel_NSTAGES                 13

  static real_T rt_ODE8_B[13] = {
    4.174749114153025E-2, 0.0, 0.0, 0.0,
    0.0, -5.54523286112393E-2, 2.393128072011801E-1, 7.03510669403443E-1,
    -7.597596138144609E-1, 6.605630309222863E-1, 1.581874825101233E-1,
    -2.381095387528628E-1, 2.5E-1
  };

  static real_T rt_ODE8_C[13] = {
    0.0, 5.555555555555556E-2, 8.333333333333333E-2, 1.25E-1,
    3.125E-1, 3.75E-1, 1.475E-1, 4.65E-1,
    5.648654513822596E-1, 6.5E-1, 9.246562776405044E-1, 1.0, 1.0
  };

  static real_T rt_ODE8_A[13][13] = {
    /* rt_ODE8_A[0][] */
    { 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[1][] */
    { 5.555555555555556E-2, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[2][] */
    { 2.083333333333333E-2, 6.25E-2, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[3][] */
    { 3.125E-2, 0.0, 9.375E-2, 0.0,
      0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[4][] */
    { 3.125E-1, 0.0, -1.171875, 1.171875,
      0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[5][] */
    { 3.75E-2, 0.0, 0.0, 1.875E-1,
      1.5E-1, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[6][] */
    { 4.791013711111111E-2, 0.0, 0.0, 1.122487127777778E-1,
      -2.550567377777778E-2, 1.284682388888889E-2, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[7][] */
    { 1.691798978729228E-2, 0.0, 0.0, 3.878482784860432E-1,
      3.597736985150033E-2, 1.969702142156661E-1, -1.727138523405018E-1, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[8][] */
    { 6.90957533591923E-2, 0.0, 0.0, -6.342479767288542E-1,
      -1.611975752246041E-1, 1.386503094588253E-1, 9.409286140357563E-1,
      2.11636326481944E-1,
      0.0, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[9][] */
    { 1.835569968390454E-1, 0.0, 0.0, -2.468768084315592,
      -2.912868878163005E-1, -2.647302023311738E-2, 2.8478387641928,
      2.813873314698498E-1,
      1.237448998633147E-1, 0.0, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[10][] */
    { -1.215424817395888, 0.0, 0.0, 1.667260866594577E1,
      9.157418284168179E-1, -6.056605804357471, -1.600357359415618E1,
      1.484930308629766E1,
      -1.337157573528985E1, 5.134182648179638, 0.0, 0.0, 0.0 },

    /* rt_ODE8_A[11][] */
    { 2.588609164382643E-1, 0.0, 0.0, -4.774485785489205,
      -4.350930137770325E-1, -3.049483332072241, 5.577920039936099,
      6.155831589861039,
      -5.062104586736938, 2.193926173180679, 1.346279986593349E-1, 0.0, 0.0 },

    /* rt_ODE8_A[12][] */
    { 8.224275996265075E-1, 0.0, 0.0, -1.165867325727766E1,
      -7.576221166909362E-1, 7.139735881595818E-1, 1.207577498689006E1,
      -2.127659113920403,
      1.990166207048956, -2.342864715440405E-1, 1.758985777079423E-1, 0.0, 0.0 },
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE8_IntgData *intgData = (ODE8_IntgData *) rtsiGetSolverData(si);
  real_T *deltaY = intgData->deltaY;
  real_T *x0 = intgData->x0;
  real_T* f[diesel_NSTAGES];
  int idx,stagesIdx,statesIdx;
  double deltaX;
  int_T nXc = 14;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  f[0] = intgData->f[0];
  f[1] = intgData->f[1];
  f[2] = intgData->f[2];
  f[3] = intgData->f[3];
  f[4] = intgData->f[4];
  f[5] = intgData->f[5];
  f[6] = intgData->f[6];
  f[7] = intgData->f[7];
  f[8] = intgData->f[8];
  f[9] = intgData->f[9];
  f[10] = intgData->f[10];
  f[11] = intgData->f[11];
  f[12] = intgData->f[12];

  /* Save the state values at time t in y and x0*/
  (void) memset(deltaY, 0,
                (uint_T)nXc*sizeof(real_T));
  (void) memcpy(x0, x,
                nXc*sizeof(real_T));
  for (stagesIdx=0;stagesIdx<diesel_NSTAGES;stagesIdx++) {
    (void) memcpy(x, x0,
                  (uint_T)nXc*sizeof(real_T));
    for (statesIdx=0;statesIdx<nXc;statesIdx++) {
      deltaX = 0;
      for (idx=0;idx<stagesIdx;idx++) {
        deltaX = deltaX + h*rt_ODE8_A[stagesIdx][idx]*f[idx][statesIdx];
      }

      x[statesIdx] = x0[statesIdx] + deltaX;
    }

    if (stagesIdx==0) {
      rtsiSetdX(si, f[stagesIdx]);
      diesel_derivatives();
    } else {
      (stagesIdx==diesel_NSTAGES-1)? rtsiSetT(si, tnew) : rtsiSetT(si, t + h*
        rt_ODE8_C[stagesIdx]);
      rtsiSetdX(si, f[stagesIdx]);
      diesel_step();
      diesel_derivatives();
    }

    for (statesIdx=0;statesIdx<nXc;statesIdx++) {
      deltaY[statesIdx] = deltaY[statesIdx] + h*rt_ODE8_B[stagesIdx]*f[stagesIdx]
        [statesIdx];
    }
  }

  for (statesIdx=0;statesIdx<nXc;statesIdx++) {
    x[statesIdx] = x0[statesIdx] + deltaY[statesIdx];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = sqrt(y * y + 1.0) * a;
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void diesel_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_l;
  real_T rtb_TransportDelay_c;
  real_T rtb_integrator_f;
  real_T rtb_TransportDelay_k;
  real_T rtb_integrator_d;
  real_T rtb_TransportDelay_kq;
  real_T rtb_u;
  real_T rtb_Actuador1;
  if (rtmIsMajorTimeStep(diesel_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&diesel_M->solverInfo,((diesel_M->Timing.clockTick0+1)*
      diesel_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(diesel_M)) {
    diesel_M->Timing.t[0] = rtsiGetT(&diesel_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T rtb_Sum13;
    real_T rtb_phi;
    real_T rtb_Product1;

    /* Integrator: '<S11>/integrator' */
    rtb_integrator = diesel_X.integrator_CSTATE;

    /* TransportDelay: '<S11>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&diesel_DW.TransportDelay_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&diesel_DW.TransportDelay_PWORK.TUbufferPtrs
        [1];
      real_T simTime = diesel_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_DW.TransportDelay_IWORK.CircularBufSize,
        &diesel_DW.TransportDelay_IWORK.Last,
        diesel_DW.TransportDelay_IWORK.Tail,
        diesel_DW.TransportDelay_IWORK.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Memory: '<S11>/Memory' */
      diesel_B.Memory = diesel_DW.Memory_PreviousInput;
    }

    /* Switch: '<S11>/Switch' incorporates:
     *  Clock: '<S11>/Clock'
     *  Constant: '<S11>/K1'
     *  Gain: '<S11>/Gain'
     *  RelationalOperator: '<S11>/Relational Operator'
     *  Sum: '<S11>/Sum'
     */
    if (diesel_M->Timing.t[0] >= 0.016666666666666666) {
      diesel_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
    } else {
      diesel_B.Switch = diesel_B.Memory;
    }

    /* End of Switch: '<S11>/Switch' */

    /* Integrator: '<S10>/integrator' */
    rtb_integrator_l = diesel_X.integrator_CSTATE_m;

    /* TransportDelay: '<S10>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_c = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_DW.TransportDelay_IWORK_e.CircularBufSize,
        &diesel_DW.TransportDelay_IWORK_e.Last,
        diesel_DW.TransportDelay_IWORK_e.Tail,
        diesel_DW.TransportDelay_IWORK_e.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Memory: '<S10>/Memory' */
      diesel_B.Memory_d = diesel_DW.Memory_PreviousInput_n;
    }

    /* Switch: '<S10>/Switch' incorporates:
     *  Clock: '<S10>/Clock'
     *  Constant: '<S10>/K1'
     *  Gain: '<S10>/Gain'
     *  RelationalOperator: '<S10>/Relational Operator'
     *  Sum: '<S10>/Sum'
     */
    if (diesel_M->Timing.t[0] >= 0.016666666666666666) {
      diesel_B.Switch_m = (rtb_integrator_l - rtb_TransportDelay_c) * 60.0;
    } else {
      diesel_B.Switch_m = diesel_B.Memory_d;
    }

    /* End of Switch: '<S10>/Switch' */

    /* Integrator: '<S15>/integrator' */
    rtb_integrator_f = diesel_X.integrator_CSTATE_g;

    /* TransportDelay: '<S15>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_k = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_DW.TransportDelay_IWORK_e4.CircularBufSize,
        &diesel_DW.TransportDelay_IWORK_e4.Last,
        diesel_DW.TransportDelay_IWORK_e4.Tail,
        diesel_DW.TransportDelay_IWORK_e4.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Memory: '<S15>/Memory' */
      diesel_B.Memory_dw = diesel_DW.Memory_PreviousInput_l;
    }

    /* Switch: '<S15>/Switch' incorporates:
     *  Clock: '<S15>/Clock'
     *  Constant: '<S15>/K1'
     *  Gain: '<S15>/Gain'
     *  RelationalOperator: '<S15>/Relational Operator'
     *  Sum: '<S15>/Sum'
     */
    if (diesel_M->Timing.t[0] >= 0.016666666666666666) {
      diesel_B.Switch_a = (rtb_integrator_f - rtb_TransportDelay_k) * 60.0;
    } else {
      diesel_B.Switch_a = diesel_B.Memory_dw;
    }

    /* End of Switch: '<S15>/Switch' */

    /* Integrator: '<S14>/integrator' */
    rtb_integrator_d = diesel_X.integrator_CSTATE_j;

    /* TransportDelay: '<S14>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_kq = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_DW.TransportDelay_IWORK_h.CircularBufSize,
        &diesel_DW.TransportDelay_IWORK_h.Last,
        diesel_DW.TransportDelay_IWORK_h.Tail,
        diesel_DW.TransportDelay_IWORK_h.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Memory: '<S14>/Memory' */
      diesel_B.Memory_l = diesel_DW.Memory_PreviousInput_f;
    }

    /* Switch: '<S14>/Switch' incorporates:
     *  Clock: '<S14>/Clock'
     *  Constant: '<S14>/K1'
     *  Gain: '<S14>/Gain'
     *  RelationalOperator: '<S14>/Relational Operator'
     *  Sum: '<S14>/Sum'
     */
    if (diesel_M->Timing.t[0] >= 0.016666666666666666) {
      diesel_B.Switch_l = (rtb_integrator_d - rtb_TransportDelay_kq) * 60.0;
    } else {
      diesel_B.Switch_l = diesel_B.Memory_l;
    }

    /* End of Switch: '<S14>/Switch' */

    /* Gain: '<S5>/Gain1' incorporates:
     *  ComplexToMagnitudeAngle: '<S6>/Complex to Magnitude-Angle'
     *  ComplexToMagnitudeAngle: '<S7>/Complex to Magnitude-Angle'
     *  Product: '<S5>/Product'
     *  RealImagToComplex: '<S6>/Real-Imag to Complex'
     *  RealImagToComplex: '<S7>/Real-Imag to Complex'
     */
    diesel_Y.duty_cycle = rt_hypotd_snf(diesel_B.Switch, diesel_B.Switch_m) *
      rt_hypotd_snf(diesel_B.Switch_a, diesel_B.Switch_l) * 0.5;

    /* Gain: '<S5>/Deg->Rad' incorporates:
     *  ComplexToMagnitudeAngle: '<S6>/Complex to Magnitude-Angle'
     *  ComplexToMagnitudeAngle: '<S7>/Complex to Magnitude-Angle'
     *  Gain: '<S6>/Rad->Deg.'
     *  Gain: '<S7>/Rad->Deg.'
     *  RealImagToComplex: '<S6>/Real-Imag to Complex'
     *  RealImagToComplex: '<S7>/Real-Imag to Complex'
     *  Sum: '<S5>/Sum'
     */
    rtb_phi = (57.295779513082323 * rt_atan2d_snf(diesel_B.Switch_m,
                diesel_B.Switch) - 57.295779513082323 * rt_atan2d_snf
               (diesel_B.Switch_l, diesel_B.Switch_a)) * 0.017453292519943295;

    /* Product: '<S5>/Product1' incorporates:
     *  Trigonometry: '<S5>/Trigonometric Function2'
     */
    rtb_Product1 = diesel_Y.duty_cycle * cos(rtb_phi);

    /* Product: '<S5>/Product3' incorporates:
     *  Trigonometry: '<S5>/Trigonometric Function2'
     */
    rtb_phi = diesel_Y.duty_cycle * sin(rtb_phi);

    /* Outport: '<Root>/potencia' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    diesel_Y.potencia = sqrt(rtb_Product1 * rtb_Product1 + rtb_phi * rtb_phi);

    /* Outport: '<Root>/i3' incorporates:
     *  Integrator: '<Root>/Integrator8'
     */
    diesel_Y.i3 = diesel_X.Integrator8_CSTATE;

    /* Gain: '<Root>/Gain11' incorporates:
     *  Integrator: '<Root>/Integrator6'
     *  Integrator: '<Root>/Integrator8'
     *  Sum: '<Root>/Sum7'
     */
    diesel_B.Gain11 = (diesel_X.Integrator6_CSTATE - diesel_X.Integrator8_CSTATE)
      * 1639.344262295082;

    /* Sin: '<Root>/Sine Wave1' incorporates:
     *  Sin: '<S6>/cos(wt)'
     *  Sin: '<S6>/sin(wt)'
     */
    rtb_Product1 = 376.99111843077515 * diesel_M->Timing.t[0];
    rtb_phi = sin(rtb_Product1);
    diesel_B.refvoltage = rtb_phi * 170.0;

    /* Derivative: '<Root>/Derivative2' */
    if ((diesel_DW.TimeStampA >= diesel_M->Timing.t[0]) && (diesel_DW.TimeStampB
         >= diesel_M->Timing.t[0])) {
      rtb_Sum13 = 0.0;
    } else {
      rtb_Sum13 = diesel_DW.TimeStampA;
      lastU = &diesel_DW.LastUAtTimeA;
      if (diesel_DW.TimeStampA < diesel_DW.TimeStampB) {
        if (diesel_DW.TimeStampB < diesel_M->Timing.t[0]) {
          rtb_Sum13 = diesel_DW.TimeStampB;
          lastU = &diesel_DW.LastUAtTimeB;
        }
      } else {
        if (diesel_DW.TimeStampA >= diesel_M->Timing.t[0]) {
          rtb_Sum13 = diesel_DW.TimeStampB;
          lastU = &diesel_DW.LastUAtTimeB;
        }
      }

      rtb_Sum13 = (diesel_B.refvoltage - *lastU) / (diesel_M->Timing.t[0] -
        rtb_Sum13);
    }

    /* End of Derivative: '<Root>/Derivative2' */

    /* Sum: '<Root>/Sum11' incorporates:
     *  Gain: '<Root>/Gain19'
     *  Integrator: '<Root>/Integrator6'
     *  Integrator: '<Root>/Integrator8'
     *  Sum: '<Root>/Sum12'
     */
    diesel_B.Sum11 = (0.00061 * rtb_Sum13 + diesel_X.Integrator8_CSTATE) -
      diesel_X.Integrator6_CSTATE;

    /* Sum: '<S1>/Sum9' incorporates:
     *  Gain: '<S1>/Gain2'
     *  Sum: '<S1>/Sum5'
     *  TransferFcn: '<S1>/Transfer Fcn2'
     */
    diesel_Y.duty_cycle = (2.0 * diesel_X.TransferFcn2_CSTATE[0] + 0.0 *
      diesel_X.TransferFcn2_CSTATE[1]) + 0.002 * diesel_B.Sum11;

    /* Sum: '<Root>/Sum15' incorporates:
     *  Gain: '<Root>/Gain21'
     *  Gain: '<S2>/ Generador1'
     *  Gain: '<S2>/Gain1'
     *  TransferFcn: '<Root>/Transfer Fcn4'
     *  TransferFcn: '<S2>/Dinámica en el eje1'
     */
    diesel_B.OutputDCVoltage = 0.03 * diesel_X.Dinmicaeneleje1_CSTATE * 0.5 *
      12000.0 - 10000.0 * diesel_X.TransferFcn4_CSTATE * 0.5;

    /* Gain: '<Root>/Gain10' incorporates:
     *  Gain: '<Root>/Gain14'
     *  Gain: '<Root>/Gain17'
     *  Integrator: '<Root>/Integrator6'
     *  Integrator: '<Root>/Integrator7'
     *  Product: '<Root>/Product3'
     *  Sum: '<Root>/Sum9'
     */
    diesel_B.Gain10 = ((2.0 * diesel_Y.duty_cycle * diesel_B.OutputDCVoltage -
                        diesel_X.Integrator7_CSTATE) - 0.001 *
                       diesel_X.Integrator6_CSTATE) * 200.0;

    /* Sum: '<Root>/Sum13' incorporates:
     *  Inport: '<Root>/ref'
     */
    rtb_Sum13 = diesel_U.ref - diesel_B.OutputDCVoltage;

    /* Integrator: '<S4>/Filter' */
    rtb_Actuador1 = diesel_X.Filter_CSTATE;

    /* Gain: '<S4>/Filter Coefficient' incorporates:
     *  Gain: '<S4>/Derivative Gain'
     *  Sum: '<S4>/SumD'
     */
    diesel_B.FilterCoefficient = (0.00224356290205903 * rtb_Sum13 -
      rtb_Actuador1) * 0.155980576752107;

    /* Integrator: '<S4>/Integrator' */
    rtb_Actuador1 = diesel_X.Integrator_CSTATE;

    /* Sum: '<S4>/Sum' incorporates:
     *  Gain: '<S4>/Proportional Gain'
     */
    diesel_B.Sum = (0.000853612192208084 * rtb_Sum13 + rtb_Actuador1) +
      diesel_B.FilterCoefficient;

    /* Gain: '<S4>/Integral Gain' */
    diesel_B.IntegralGain = 3.94394231511782E-5 * rtb_Sum13;

    /* Sin: '<S6>/sin(wt)' incorporates:
     *  Sin: '<S7>/sin(wt)'
     */
    rtb_phi *= 2.0;
    rtb_Actuador1 = rtb_phi;

    /* Product: '<S6>/Product' incorporates:
     *  Integrator: '<Root>/Integrator7'
     */
    diesel_B.Product = diesel_X.Integrator7_CSTATE * rtb_Actuador1;

    /* Sin: '<S6>/cos(wt)' incorporates:
     *  Sin: '<S7>/cos(wt)'
     */
    rtb_Product1 = sin(rtb_Product1 + 1.5707963267948966) * 2.0;
    rtb_Actuador1 = rtb_Product1;

    /* Product: '<S6>/Product1' incorporates:
     *  Integrator: '<Root>/Integrator7'
     */
    diesel_B.Product1 = diesel_X.Integrator7_CSTATE * rtb_Actuador1;

    /* Gain: '<Root>/Gain12' incorporates:
     *  Gain: '<Root>/Gain13'
     *  Inport: '<Root>/Vload '
     *  Integrator: '<Root>/Integrator7'
     *  Integrator: '<Root>/Integrator8'
     *  Sum: '<Root>/Sum8'
     */
    diesel_B.Gain12 = ((diesel_X.Integrator7_CSTATE - diesel_U.Vload) - 0.001 *
                       diesel_X.Integrator8_CSTATE) * 99999.999999999985;

    /* Sin: '<S7>/sin(wt)' */
    rtb_Actuador1 = rtb_phi;

    /* Product: '<S7>/Product' incorporates:
     *  Integrator: '<Root>/Integrator8'
     */
    diesel_B.Product_a = diesel_X.Integrator8_CSTATE * rtb_Actuador1;

    /* Sin: '<S7>/cos(wt)' */
    rtb_Actuador1 = rtb_Product1;

    /* Product: '<S7>/Product1' incorporates:
     *  Integrator: '<Root>/Integrator8'
     */
    diesel_B.Product1_e = diesel_X.Integrator8_CSTATE * rtb_Actuador1;

    /* TransportDelay: '<S2>/Motor de Combustión1' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      real_T tMinusDelay = simTime - 0.5;
      rtb_Actuador1 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_DW.MotordeCombustin1_IWORK.CircularBufSize,
        &diesel_DW.MotordeCombustin1_IWORK.Last,
        diesel_DW.MotordeCombustin1_IWORK.Tail,
        diesel_DW.MotordeCombustin1_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* Sum: '<S2>/Sum2' incorporates:
     *  Constant: '<Root>/Constant30'
     */
    diesel_B.Sum2 = rtb_Actuador1 - 0.1;

    /* TransferFcn: '<S2>/Actuador1' */
    rtb_Actuador1 = 0.0;
    rtb_Actuador1 += 8.0 * diesel_X.Actuador1_CSTATE;

    /* Gain: '<S2>/ 1' */
    rtb_u = 1.15 * rtb_Actuador1;
  }

  if (rtmIsMajorTimeStep(diesel_M)) {
    real_T *lastU;

    /* Update for TransportDelay: '<S11>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&diesel_DW.TransportDelay_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&diesel_DW.TransportDelay_PWORK.TUbufferPtrs
        [1];
      real_T simTime = diesel_M->Timing.t[0];
      diesel_DW.TransportDelay_IWORK.Head =
        ((diesel_DW.TransportDelay_IWORK.Head <
          (diesel_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (diesel_DW.TransportDelay_IWORK.Head+1) : 0);
      if (diesel_DW.TransportDelay_IWORK.Head ==
          diesel_DW.TransportDelay_IWORK.Tail) {
        diesel_DW.TransportDelay_IWORK.Tail =
          ((diesel_DW.TransportDelay_IWORK.Tail <
            (diesel_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (diesel_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[diesel_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[diesel_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Update for Memory: '<S11>/Memory' */
      diesel_DW.Memory_PreviousInput = diesel_B.Switch;
    }

    /* Update for TransportDelay: '<S10>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      diesel_DW.TransportDelay_IWORK_e.Head =
        ((diesel_DW.TransportDelay_IWORK_e.Head <
          (diesel_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
         (diesel_DW.TransportDelay_IWORK_e.Head+1) : 0);
      if (diesel_DW.TransportDelay_IWORK_e.Head ==
          diesel_DW.TransportDelay_IWORK_e.Tail) {
        diesel_DW.TransportDelay_IWORK_e.Tail =
          ((diesel_DW.TransportDelay_IWORK_e.Tail <
            (diesel_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
           (diesel_DW.TransportDelay_IWORK_e.Tail+1) : 0);
      }

      (*tBuffer)[diesel_DW.TransportDelay_IWORK_e.Head] = simTime;
      (*uBuffer)[diesel_DW.TransportDelay_IWORK_e.Head] = rtb_integrator_l;
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Update for Memory: '<S10>/Memory' */
      diesel_DW.Memory_PreviousInput_n = diesel_B.Switch_m;
    }

    /* Update for TransportDelay: '<S15>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      diesel_DW.TransportDelay_IWORK_e4.Head =
        ((diesel_DW.TransportDelay_IWORK_e4.Head <
          (diesel_DW.TransportDelay_IWORK_e4.CircularBufSize-1)) ?
         (diesel_DW.TransportDelay_IWORK_e4.Head+1) : 0);
      if (diesel_DW.TransportDelay_IWORK_e4.Head ==
          diesel_DW.TransportDelay_IWORK_e4.Tail) {
        diesel_DW.TransportDelay_IWORK_e4.Tail =
          ((diesel_DW.TransportDelay_IWORK_e4.Tail <
            (diesel_DW.TransportDelay_IWORK_e4.CircularBufSize-1)) ?
           (diesel_DW.TransportDelay_IWORK_e4.Tail+1) : 0);
      }

      (*tBuffer)[diesel_DW.TransportDelay_IWORK_e4.Head] = simTime;
      (*uBuffer)[diesel_DW.TransportDelay_IWORK_e4.Head] = rtb_integrator_f;
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Update for Memory: '<S15>/Memory' */
      diesel_DW.Memory_PreviousInput_l = diesel_B.Switch_a;
    }

    /* Update for TransportDelay: '<S14>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      diesel_DW.TransportDelay_IWORK_h.Head =
        ((diesel_DW.TransportDelay_IWORK_h.Head <
          (diesel_DW.TransportDelay_IWORK_h.CircularBufSize-1)) ?
         (diesel_DW.TransportDelay_IWORK_h.Head+1) : 0);
      if (diesel_DW.TransportDelay_IWORK_h.Head ==
          diesel_DW.TransportDelay_IWORK_h.Tail) {
        diesel_DW.TransportDelay_IWORK_h.Tail =
          ((diesel_DW.TransportDelay_IWORK_h.Tail <
            (diesel_DW.TransportDelay_IWORK_h.CircularBufSize-1)) ?
           (diesel_DW.TransportDelay_IWORK_h.Tail+1) : 0);
      }

      (*tBuffer)[diesel_DW.TransportDelay_IWORK_h.Head] = simTime;
      (*uBuffer)[diesel_DW.TransportDelay_IWORK_h.Head] = rtb_integrator_d;
    }

    if (rtmIsMajorTimeStep(diesel_M)) {
      /* Update for Memory: '<S14>/Memory' */
      diesel_DW.Memory_PreviousInput_f = diesel_B.Switch_l;
    }

    /* Update for Derivative: '<Root>/Derivative2' */
    if (diesel_DW.TimeStampA == (rtInf)) {
      diesel_DW.TimeStampA = diesel_M->Timing.t[0];
      lastU = &diesel_DW.LastUAtTimeA;
    } else if (diesel_DW.TimeStampB == (rtInf)) {
      diesel_DW.TimeStampB = diesel_M->Timing.t[0];
      lastU = &diesel_DW.LastUAtTimeB;
    } else if (diesel_DW.TimeStampA < diesel_DW.TimeStampB) {
      diesel_DW.TimeStampA = diesel_M->Timing.t[0];
      lastU = &diesel_DW.LastUAtTimeA;
    } else {
      diesel_DW.TimeStampB = diesel_M->Timing.t[0];
      lastU = &diesel_DW.LastUAtTimeB;
    }

    *lastU = diesel_B.refvoltage;

    /* End of Update for Derivative: '<Root>/Derivative2' */

    /* Update for TransportDelay: '<S2>/Motor de Combustión1' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1];
      real_T simTime = diesel_M->Timing.t[0];
      diesel_DW.MotordeCombustin1_IWORK.Head =
        ((diesel_DW.MotordeCombustin1_IWORK.Head <
          (diesel_DW.MotordeCombustin1_IWORK.CircularBufSize-1)) ?
         (diesel_DW.MotordeCombustin1_IWORK.Head+1) : 0);
      if (diesel_DW.MotordeCombustin1_IWORK.Head ==
          diesel_DW.MotordeCombustin1_IWORK.Tail) {
        diesel_DW.MotordeCombustin1_IWORK.Tail =
          ((diesel_DW.MotordeCombustin1_IWORK.Tail <
            (diesel_DW.MotordeCombustin1_IWORK.CircularBufSize-1)) ?
           (diesel_DW.MotordeCombustin1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[diesel_DW.MotordeCombustin1_IWORK.Head] = simTime;
      (*uBuffer)[diesel_DW.MotordeCombustin1_IWORK.Head] = rtb_u;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(diesel_M)) {
    rt_ertODEUpdateContinuousStates(&diesel_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++diesel_M->Timing.clockTick0;
    diesel_M->Timing.t[0] = rtsiGetSolverStopTime(&diesel_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      diesel_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void diesel_derivatives(void)
{
  XDot_diesel_T *_rtXdot;
  _rtXdot = ((XDot_diesel_T *) diesel_M->derivs);

  /* Derivatives for Integrator: '<S11>/integrator' */
  _rtXdot->integrator_CSTATE = diesel_B.Product;

  /* Derivatives for Integrator: '<S10>/integrator' */
  _rtXdot->integrator_CSTATE_m = diesel_B.Product1;

  /* Derivatives for Integrator: '<S15>/integrator' */
  _rtXdot->integrator_CSTATE_g = diesel_B.Product_a;

  /* Derivatives for Integrator: '<S14>/integrator' */
  _rtXdot->integrator_CSTATE_j = diesel_B.Product1_e;

  /* Derivatives for Integrator: '<Root>/Integrator8' */
  _rtXdot->Integrator8_CSTATE = diesel_B.Gain12;

  /* Derivatives for Integrator: '<Root>/Integrator6' */
  _rtXdot->Integrator6_CSTATE = diesel_B.Gain10;

  /* Derivatives for Integrator: '<Root>/Integrator7' */
  _rtXdot->Integrator7_CSTATE = diesel_B.Gain11;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -2.0 * diesel_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -142122.30337568672 *
    diesel_X.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[1] += diesel_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[0] += diesel_B.Sum11;

  /* Derivatives for TransferFcn: '<S2>/Dinámica en el eje1' */
  _rtXdot->Dinmicaeneleje1_CSTATE = 0.0;
  _rtXdot->Dinmicaeneleje1_CSTATE += -0.03 * diesel_X.Dinmicaeneleje1_CSTATE;
  _rtXdot->Dinmicaeneleje1_CSTATE += diesel_B.Sum2;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn4' */
  _rtXdot->TransferFcn4_CSTATE = 0.0;
  _rtXdot->TransferFcn4_CSTATE += -10000.0 * diesel_X.TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += diesel_B.OutputDCVoltage;

  /* Derivatives for Integrator: '<S4>/Filter' */
  _rtXdot->Filter_CSTATE = diesel_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE = diesel_B.IntegralGain;

  /* Derivatives for TransferFcn: '<S2>/Actuador1' */
  _rtXdot->Actuador1_CSTATE = 0.0;
  _rtXdot->Actuador1_CSTATE += -8.0 * diesel_X.Actuador1_CSTATE;
  _rtXdot->Actuador1_CSTATE += diesel_B.Sum;
}

/* Model initialize function */
void diesel_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)diesel_M, 0,
                sizeof(RT_MODEL_diesel_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&diesel_M->solverInfo, &diesel_M->Timing.simTimeStep);
    rtsiSetTPtr(&diesel_M->solverInfo, &rtmGetTPtr(diesel_M));
    rtsiSetStepSizePtr(&diesel_M->solverInfo, &diesel_M->Timing.stepSize0);
    rtsiSetdXPtr(&diesel_M->solverInfo, &diesel_M->derivs);
    rtsiSetContStatesPtr(&diesel_M->solverInfo, (real_T **)
                         &diesel_M->contStates);
    rtsiSetNumContStatesPtr(&diesel_M->solverInfo,
      &diesel_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&diesel_M->solverInfo,
      &diesel_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&diesel_M->solverInfo,
      &diesel_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&diesel_M->solverInfo,
      &diesel_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&diesel_M->solverInfo, (&rtmGetErrorStatus(diesel_M)));
    rtsiSetRTModelPtr(&diesel_M->solverInfo, diesel_M);
  }

  rtsiSetSimTimeStep(&diesel_M->solverInfo, MAJOR_TIME_STEP);
  diesel_M->intgData.deltaY= diesel_M->OdeDeltaY;
  diesel_M->intgData.f[0] = diesel_M->odeF[0];
  diesel_M->intgData.f[1] = diesel_M->odeF[1];
  diesel_M->intgData.f[2] = diesel_M->odeF[2];
  diesel_M->intgData.f[3] = diesel_M->odeF[3];
  diesel_M->intgData.f[4] = diesel_M->odeF[4];
  diesel_M->intgData.f[5] = diesel_M->odeF[5];
  diesel_M->intgData.f[6] = diesel_M->odeF[6];
  diesel_M->intgData.f[7] = diesel_M->odeF[7];
  diesel_M->intgData.f[8] = diesel_M->odeF[8];
  diesel_M->intgData.f[9] = diesel_M->odeF[9];
  diesel_M->intgData.f[10] = diesel_M->odeF[10];
  diesel_M->intgData.f[11] = diesel_M->odeF[11];
  diesel_M->intgData.f[12] = diesel_M->odeF[12];
  diesel_M->intgData.x0 = diesel_M->odeX0;
  diesel_M->contStates = ((X_diesel_T *) &diesel_X);
  rtsiSetSolverData(&diesel_M->solverInfo, (void *)&diesel_M->intgData);
  rtsiSetSolverName(&diesel_M->solverInfo,"ode8");
  rtmSetTPtr(diesel_M, &diesel_M->Timing.tArray[0]);
  diesel_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &diesel_B), 0,
                sizeof(B_diesel_T));

  /* states (continuous) */
  {
    (void) memset((void *)&diesel_X, 0,
                  sizeof(X_diesel_T));
  }

  /* states (dwork) */
  (void) memset((void *)&diesel_DW, 0,
                sizeof(DW_diesel_T));

  /* external inputs */
  (void)memset((void *)&diesel_U, 0, sizeof(ExtU_diesel_T));

  /* external outputs */
  (void) memset((void *)&diesel_Y, 0,
                sizeof(ExtY_diesel_T));

  /* Start for TransportDelay: '<S11>/Transport Delay' */
  {
    real_T *pBuffer = &diesel_DW.TransportDelay_RWORK.TUbufferArea[0];
    diesel_DW.TransportDelay_IWORK.Tail = 0;
    diesel_DW.TransportDelay_IWORK.Head = 0;
    diesel_DW.TransportDelay_IWORK.Last = 0;
    diesel_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = diesel_M->Timing.t[0];
    diesel_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S10>/Transport Delay' */
  {
    real_T *pBuffer = &diesel_DW.TransportDelay_RWORK_g.TUbufferArea[0];
    diesel_DW.TransportDelay_IWORK_e.Tail = 0;
    diesel_DW.TransportDelay_IWORK_e.Head = 0;
    diesel_DW.TransportDelay_IWORK_e.Last = 0;
    diesel_DW.TransportDelay_IWORK_e.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = diesel_M->Timing.t[0];
    diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_DW.TransportDelay_PWORK_m.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S15>/Transport Delay' */
  {
    real_T *pBuffer = &diesel_DW.TransportDelay_RWORK_j.TUbufferArea[0];
    diesel_DW.TransportDelay_IWORK_e4.Tail = 0;
    diesel_DW.TransportDelay_IWORK_e4.Head = 0;
    diesel_DW.TransportDelay_IWORK_e4.Last = 0;
    diesel_DW.TransportDelay_IWORK_e4.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = diesel_M->Timing.t[0];
    diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_DW.TransportDelay_PWORK_o.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S14>/Transport Delay' */
  {
    real_T *pBuffer = &diesel_DW.TransportDelay_RWORK_h.TUbufferArea[0];
    diesel_DW.TransportDelay_IWORK_h.Tail = 0;
    diesel_DW.TransportDelay_IWORK_h.Head = 0;
    diesel_DW.TransportDelay_IWORK_h.Last = 0;
    diesel_DW.TransportDelay_IWORK_h.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = diesel_M->Timing.t[0];
    diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_DW.TransportDelay_PWORK_c.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S2>/Motor de Combustión1' */
  {
    real_T *pBuffer = &diesel_DW.MotordeCombustin1_RWORK.TUbufferArea[0];
    diesel_DW.MotordeCombustin1_IWORK.Tail = 0;
    diesel_DW.MotordeCombustin1_IWORK.Head = 0;
    diesel_DW.MotordeCombustin1_IWORK.Last = 0;
    diesel_DW.MotordeCombustin1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = diesel_M->Timing.t[0];
    diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
  }

  /* InitializeConditions for Integrator: '<S11>/integrator' */
  diesel_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S11>/Memory' */
  diesel_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S10>/integrator' */
  diesel_X.integrator_CSTATE_m = 0.0;

  /* InitializeConditions for Integrator: '<S15>/integrator' */
  diesel_X.integrator_CSTATE_g = 0.0;

  /* InitializeConditions for Memory: '<S15>/Memory' */
  diesel_DW.Memory_PreviousInput_l = 1.0;

  /* InitializeConditions for Integrator: '<S14>/integrator' */
  diesel_X.integrator_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator8' */
  diesel_X.Integrator8_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator6' */
  diesel_X.Integrator6_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator7' */
  diesel_X.Integrator7_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  diesel_DW.TimeStampA = (rtInf);
  diesel_DW.TimeStampB = (rtInf);

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  diesel_X.TransferFcn2_CSTATE[0] = 0.0;
  diesel_X.TransferFcn2_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Dinámica en el eje1' */
  diesel_X.Dinmicaeneleje1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn4' */
  diesel_X.TransferFcn4_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Filter' */
  diesel_X.Filter_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  diesel_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Actuador1' */
  diesel_X.Actuador1_CSTATE = 0.0;
}

/* Model terminate function */
void diesel_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

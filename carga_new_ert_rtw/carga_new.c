/*
 * File: carga_new.c
 *
 * Code generated for Simulink model 'carga_new'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:56:21 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "carga_new.h"
#include "carga_new_private.h"

/* Block signals (default storage) */
B_carga_new_T carga_new_B;

/* Continuous states */
X_carga_new_T carga_new_X;

/* Block states (default storage) */
DW_carga_new_T carga_new_DW;

/* External inputs (root inport signals with default storage) */
ExtU_carga_new_T carga_new_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_carga_new_T carga_new_Y;

/* Real-time model */
RT_MODEL_carga_new_T carga_new_M_;
RT_MODEL_carga_new_T *const carga_new_M = &carga_new_M_;

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
#define carga_new_NSTAGES              13

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
  real_T* f[carga_new_NSTAGES];
  int idx,stagesIdx,statesIdx;
  double deltaX;
  int_T nXc = 6;
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
  for (stagesIdx=0;stagesIdx<carga_new_NSTAGES;stagesIdx++) {
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
      carga_new_derivatives();
    } else {
      (stagesIdx==carga_new_NSTAGES-1)? rtsiSetT(si, tnew) : rtsiSetT(si, t + h*
        rt_ODE8_C[stagesIdx]);
      rtsiSetdX(si, f[stagesIdx]);
      carga_new_step();
      carga_new_derivatives();
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
void carga_new_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_m;
  real_T rtb_TransportDelay_o;
  real_T rtb_integrator_mm;
  real_T rtb_TransportDelay_j;
  real_T rtb_integrator_f;
  real_T rtb_TransportDelay_n;
  real_T rtb_coswt_d;
  real_T rtb_phi;
  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&carga_new_M->solverInfo,
                          ((carga_new_M->Timing.clockTick0+1)*
      carga_new_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(carga_new_M)) {
    carga_new_M->Timing.t[0] = rtsiGetT(&carga_new_M->solverInfo);
  }

  /* Integrator: '<S8>/integrator' */
  rtb_integrator = carga_new_X.integrator_CSTATE;

  /* TransportDelay: '<S8>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = carga_new_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_new_DW.TransportDelay_IWORK.CircularBufSize,
      &carga_new_DW.TransportDelay_IWORK.Last,
      carga_new_DW.TransportDelay_IWORK.Tail,
      carga_new_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* Memory: '<S8>/Memory' */
    carga_new_B.Memory = carga_new_DW.Memory_PreviousInput;
  }

  /* Switch: '<S8>/Switch' incorporates:
   *  Clock: '<S8>/Clock'
   *  Constant: '<S8>/K1'
   *  Gain: '<S8>/Gain'
   *  RelationalOperator: '<S8>/Relational Operator'
   *  Sum: '<S8>/Sum'
   */
  if (carga_new_M->Timing.t[0] >= 0.016666666666666666) {
    carga_new_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
  } else {
    carga_new_B.Switch = carga_new_B.Memory;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Integrator: '<S7>/integrator' */
  rtb_integrator_m = carga_new_X.integrator_CSTATE_k;

  /* TransportDelay: '<S7>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[1];
    real_T simTime = carga_new_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_o = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_new_DW.TransportDelay_IWORK_p.CircularBufSize,
      &carga_new_DW.TransportDelay_IWORK_p.Last,
      carga_new_DW.TransportDelay_IWORK_p.Tail,
      carga_new_DW.TransportDelay_IWORK_p.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* Memory: '<S7>/Memory' */
    carga_new_B.Memory_i = carga_new_DW.Memory_PreviousInput_f;
  }

  /* Switch: '<S7>/Switch' incorporates:
   *  Clock: '<S7>/Clock'
   *  Constant: '<S7>/K1'
   *  Gain: '<S7>/Gain'
   *  RelationalOperator: '<S7>/Relational Operator'
   *  Sum: '<S7>/Sum'
   */
  if (carga_new_M->Timing.t[0] >= 0.016666666666666666) {
    carga_new_B.Switch_a = (rtb_integrator_m - rtb_TransportDelay_o) * 60.0;
  } else {
    carga_new_B.Switch_a = carga_new_B.Memory_i;
  }

  /* End of Switch: '<S7>/Switch' */

  /* Integrator: '<S12>/integrator' */
  rtb_integrator_mm = carga_new_X.integrator_CSTATE_l;

  /* TransportDelay: '<S12>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[1];
    real_T simTime = carga_new_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_j = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_new_DW.TransportDelay_IWORK_l.CircularBufSize,
      &carga_new_DW.TransportDelay_IWORK_l.Last,
      carga_new_DW.TransportDelay_IWORK_l.Tail,
      carga_new_DW.TransportDelay_IWORK_l.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* Memory: '<S12>/Memory' */
    carga_new_B.Memory_g = carga_new_DW.Memory_PreviousInput_p;
  }

  /* Switch: '<S12>/Switch' incorporates:
   *  Clock: '<S12>/Clock'
   *  Constant: '<S12>/K1'
   *  Gain: '<S12>/Gain'
   *  RelationalOperator: '<S12>/Relational Operator'
   *  Sum: '<S12>/Sum'
   */
  if (carga_new_M->Timing.t[0] >= 0.016666666666666666) {
    carga_new_B.Switch_g = (rtb_integrator_mm - rtb_TransportDelay_j) * 60.0;
  } else {
    carga_new_B.Switch_g = carga_new_B.Memory_g;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Integrator: '<S11>/integrator' */
  rtb_integrator_f = carga_new_X.integrator_CSTATE_p;

  /* TransportDelay: '<S11>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[1];
    real_T simTime = carga_new_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_n = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      carga_new_DW.TransportDelay_IWORK_ph.CircularBufSize,
      &carga_new_DW.TransportDelay_IWORK_ph.Last,
      carga_new_DW.TransportDelay_IWORK_ph.Tail,
      carga_new_DW.TransportDelay_IWORK_ph.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* Memory: '<S11>/Memory' */
    carga_new_B.Memory_in = carga_new_DW.Memory_PreviousInput_m;
  }

  /* Switch: '<S11>/Switch' incorporates:
   *  Clock: '<S11>/Clock'
   *  Constant: '<S11>/K1'
   *  Gain: '<S11>/Gain'
   *  RelationalOperator: '<S11>/Relational Operator'
   *  Sum: '<S11>/Sum'
   */
  if (carga_new_M->Timing.t[0] >= 0.016666666666666666) {
    carga_new_B.Switch_j = (rtb_integrator_f - rtb_TransportDelay_n) * 60.0;
  } else {
    carga_new_B.Switch_j = carga_new_B.Memory_in;
  }

  /* End of Switch: '<S11>/Switch' */

  /* Gain: '<S2>/Gain1' incorporates:
   *  ComplexToMagnitudeAngle: '<S3>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S4>/Complex to Magnitude-Angle'
   *  Product: '<S2>/Product'
   *  RealImagToComplex: '<S3>/Real-Imag to Complex'
   *  RealImagToComplex: '<S4>/Real-Imag to Complex'
   */
  rtb_coswt_d = rt_hypotd_snf(carga_new_B.Switch, carga_new_B.Switch_a) *
    rt_hypotd_snf(carga_new_B.Switch_g, carga_new_B.Switch_j) * 0.5;

  /* Gain: '<S2>/Deg->Rad' incorporates:
   *  ComplexToMagnitudeAngle: '<S3>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S4>/Complex to Magnitude-Angle'
   *  Gain: '<S3>/Rad->Deg.'
   *  Gain: '<S4>/Rad->Deg.'
   *  RealImagToComplex: '<S3>/Real-Imag to Complex'
   *  RealImagToComplex: '<S4>/Real-Imag to Complex'
   *  Sum: '<S2>/Sum'
   */
  rtb_phi = (57.295779513082323 * rt_atan2d_snf(carga_new_B.Switch_a,
              carga_new_B.Switch) - 57.295779513082323 * rt_atan2d_snf
             (carga_new_B.Switch_j, carga_new_B.Switch_g)) *
    0.017453292519943295;

  /* Product: '<S2>/Product1' incorporates:
   *  Trigonometry: '<S2>/Trigonometric Function2'
   */
  carga_new_Y.Po = rtb_coswt_d * cos(rtb_phi);

  /* Product: '<S2>/Product3' incorporates:
   *  Trigonometry: '<S2>/Trigonometric Function2'
   */
  carga_new_Y.Qo = rtb_coswt_d * sin(rtb_phi);

  /* Outport: '<Root>/potencia' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  carga_new_Y.potencia = sqrt(carga_new_Y.Po * carga_new_Y.Po + carga_new_Y.Qo *
    carga_new_Y.Qo);

  /* TransferFcn: '<Root>/Transfer Fcn3' */
  carga_new_Y.Vload = 49.999999999999993 * carga_new_X.TransferFcn3_CSTATE[0] +
    96.153846153846146 * carga_new_X.TransferFcn3_CSTATE[1];

  /* Sin: '<S3>/sin(wt)' incorporates:
   *  Sin: '<S3>/cos(wt)'
   *  Sin: '<S4>/sin(wt)'
   */
  rtb_phi = 376.99111843077515 * carga_new_M->Timing.t[0];
  rtb_coswt_d = sin(rtb_phi) * 2.0;

  /* Product: '<S3>/Product' incorporates:
   *  Sin: '<S3>/sin(wt)'
   */
  carga_new_B.Product = rtb_coswt_d * carga_new_Y.Vload;

  /* Sin: '<S3>/cos(wt)' incorporates:
   *  Sin: '<S4>/cos(wt)'
   */
  rtb_phi = sin(rtb_phi + 1.5707963267948966) * 2.0;

  /* Product: '<S3>/Product1' incorporates:
   *  Sin: '<S3>/cos(wt)'
   */
  carga_new_B.Product1 = rtb_phi * carga_new_Y.Vload;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/i1'
   *  Inport: '<Root>/i2'
   *  Inport: '<Root>/i3'
   */
  carga_new_B.Sum2 = (carga_new_U.i1 + carga_new_U.i2) + carga_new_U.i3;

  /* Product: '<S4>/Product' */
  carga_new_B.Product_i = rtb_coswt_d * carga_new_B.Sum2;

  /* Product: '<S4>/Product1' */
  carga_new_B.Product1_h = rtb_phi * carga_new_B.Sum2;
  if (rtmIsMajorTimeStep(carga_new_M)) {
    /* Update for TransportDelay: '<S8>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = carga_new_M->Timing.t[0];
      carga_new_DW.TransportDelay_IWORK.Head =
        ((carga_new_DW.TransportDelay_IWORK.Head <
          (carga_new_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (carga_new_DW.TransportDelay_IWORK.Head+1) : 0);
      if (carga_new_DW.TransportDelay_IWORK.Head ==
          carga_new_DW.TransportDelay_IWORK.Tail) {
        carga_new_DW.TransportDelay_IWORK.Tail =
          ((carga_new_DW.TransportDelay_IWORK.Tail <
            (carga_new_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (carga_new_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[carga_new_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[carga_new_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(carga_new_M)) {
      /* Update for Memory: '<S8>/Memory' */
      carga_new_DW.Memory_PreviousInput = carga_new_B.Switch;
    }

    /* Update for TransportDelay: '<S7>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[1];
      real_T simTime = carga_new_M->Timing.t[0];
      carga_new_DW.TransportDelay_IWORK_p.Head =
        ((carga_new_DW.TransportDelay_IWORK_p.Head <
          (carga_new_DW.TransportDelay_IWORK_p.CircularBufSize-1)) ?
         (carga_new_DW.TransportDelay_IWORK_p.Head+1) : 0);
      if (carga_new_DW.TransportDelay_IWORK_p.Head ==
          carga_new_DW.TransportDelay_IWORK_p.Tail) {
        carga_new_DW.TransportDelay_IWORK_p.Tail =
          ((carga_new_DW.TransportDelay_IWORK_p.Tail <
            (carga_new_DW.TransportDelay_IWORK_p.CircularBufSize-1)) ?
           (carga_new_DW.TransportDelay_IWORK_p.Tail+1) : 0);
      }

      (*tBuffer)[carga_new_DW.TransportDelay_IWORK_p.Head] = simTime;
      (*uBuffer)[carga_new_DW.TransportDelay_IWORK_p.Head] = rtb_integrator_m;
    }

    if (rtmIsMajorTimeStep(carga_new_M)) {
      /* Update for Memory: '<S7>/Memory' */
      carga_new_DW.Memory_PreviousInput_f = carga_new_B.Switch_a;
    }

    /* Update for TransportDelay: '<S12>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[1];
      real_T simTime = carga_new_M->Timing.t[0];
      carga_new_DW.TransportDelay_IWORK_l.Head =
        ((carga_new_DW.TransportDelay_IWORK_l.Head <
          (carga_new_DW.TransportDelay_IWORK_l.CircularBufSize-1)) ?
         (carga_new_DW.TransportDelay_IWORK_l.Head+1) : 0);
      if (carga_new_DW.TransportDelay_IWORK_l.Head ==
          carga_new_DW.TransportDelay_IWORK_l.Tail) {
        carga_new_DW.TransportDelay_IWORK_l.Tail =
          ((carga_new_DW.TransportDelay_IWORK_l.Tail <
            (carga_new_DW.TransportDelay_IWORK_l.CircularBufSize-1)) ?
           (carga_new_DW.TransportDelay_IWORK_l.Tail+1) : 0);
      }

      (*tBuffer)[carga_new_DW.TransportDelay_IWORK_l.Head] = simTime;
      (*uBuffer)[carga_new_DW.TransportDelay_IWORK_l.Head] = rtb_integrator_mm;
    }

    if (rtmIsMajorTimeStep(carga_new_M)) {
      /* Update for Memory: '<S12>/Memory' */
      carga_new_DW.Memory_PreviousInput_p = carga_new_B.Switch_g;
    }

    /* Update for TransportDelay: '<S11>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[1];
      real_T simTime = carga_new_M->Timing.t[0];
      carga_new_DW.TransportDelay_IWORK_ph.Head =
        ((carga_new_DW.TransportDelay_IWORK_ph.Head <
          (carga_new_DW.TransportDelay_IWORK_ph.CircularBufSize-1)) ?
         (carga_new_DW.TransportDelay_IWORK_ph.Head+1) : 0);
      if (carga_new_DW.TransportDelay_IWORK_ph.Head ==
          carga_new_DW.TransportDelay_IWORK_ph.Tail) {
        carga_new_DW.TransportDelay_IWORK_ph.Tail =
          ((carga_new_DW.TransportDelay_IWORK_ph.Tail <
            (carga_new_DW.TransportDelay_IWORK_ph.CircularBufSize-1)) ?
           (carga_new_DW.TransportDelay_IWORK_ph.Tail+1) : 0);
      }

      (*tBuffer)[carga_new_DW.TransportDelay_IWORK_ph.Head] = simTime;
      (*uBuffer)[carga_new_DW.TransportDelay_IWORK_ph.Head] = rtb_integrator_f;
    }

    if (rtmIsMajorTimeStep(carga_new_M)) {
      /* Update for Memory: '<S11>/Memory' */
      carga_new_DW.Memory_PreviousInput_m = carga_new_B.Switch_j;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(carga_new_M)) {
    rt_ertODEUpdateContinuousStates(&carga_new_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++carga_new_M->Timing.clockTick0;
    carga_new_M->Timing.t[0] = rtsiGetSolverStopTime(&carga_new_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      carga_new_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void carga_new_derivatives(void)
{
  XDot_carga_new_T *_rtXdot;
  _rtXdot = ((XDot_carga_new_T *) carga_new_M->derivs);

  /* Derivatives for Integrator: '<S8>/integrator' */
  _rtXdot->integrator_CSTATE = carga_new_B.Product;

  /* Derivatives for Integrator: '<S7>/integrator' */
  _rtXdot->integrator_CSTATE_k = carga_new_B.Product1;

  /* Derivatives for Integrator: '<S12>/integrator' */
  _rtXdot->integrator_CSTATE_l = carga_new_B.Product_i;

  /* Derivatives for Integrator: '<S11>/integrator' */
  _rtXdot->integrator_CSTATE_p = carga_new_B.Product1_h;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -6.9230769230769225 *
    carga_new_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -19.23076923076923 *
    carga_new_X.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[1] += carga_new_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[0] += carga_new_B.Sum2;
}

/* Model initialize function */
void carga_new_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)carga_new_M, 0,
                sizeof(RT_MODEL_carga_new_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&carga_new_M->solverInfo,
                          &carga_new_M->Timing.simTimeStep);
    rtsiSetTPtr(&carga_new_M->solverInfo, &rtmGetTPtr(carga_new_M));
    rtsiSetStepSizePtr(&carga_new_M->solverInfo, &carga_new_M->Timing.stepSize0);
    rtsiSetdXPtr(&carga_new_M->solverInfo, &carga_new_M->derivs);
    rtsiSetContStatesPtr(&carga_new_M->solverInfo, (real_T **)
                         &carga_new_M->contStates);
    rtsiSetNumContStatesPtr(&carga_new_M->solverInfo,
      &carga_new_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&carga_new_M->solverInfo,
      &carga_new_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&carga_new_M->solverInfo,
      &carga_new_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&carga_new_M->solverInfo,
      &carga_new_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&carga_new_M->solverInfo, (&rtmGetErrorStatus
      (carga_new_M)));
    rtsiSetRTModelPtr(&carga_new_M->solverInfo, carga_new_M);
  }

  rtsiSetSimTimeStep(&carga_new_M->solverInfo, MAJOR_TIME_STEP);
  carga_new_M->intgData.deltaY= carga_new_M->OdeDeltaY;
  carga_new_M->intgData.f[0] = carga_new_M->odeF[0];
  carga_new_M->intgData.f[1] = carga_new_M->odeF[1];
  carga_new_M->intgData.f[2] = carga_new_M->odeF[2];
  carga_new_M->intgData.f[3] = carga_new_M->odeF[3];
  carga_new_M->intgData.f[4] = carga_new_M->odeF[4];
  carga_new_M->intgData.f[5] = carga_new_M->odeF[5];
  carga_new_M->intgData.f[6] = carga_new_M->odeF[6];
  carga_new_M->intgData.f[7] = carga_new_M->odeF[7];
  carga_new_M->intgData.f[8] = carga_new_M->odeF[8];
  carga_new_M->intgData.f[9] = carga_new_M->odeF[9];
  carga_new_M->intgData.f[10] = carga_new_M->odeF[10];
  carga_new_M->intgData.f[11] = carga_new_M->odeF[11];
  carga_new_M->intgData.f[12] = carga_new_M->odeF[12];
  carga_new_M->intgData.x0 = carga_new_M->odeX0;
  carga_new_M->contStates = ((X_carga_new_T *) &carga_new_X);
  rtsiSetSolverData(&carga_new_M->solverInfo, (void *)&carga_new_M->intgData);
  rtsiSetSolverName(&carga_new_M->solverInfo,"ode8");
  rtmSetTPtr(carga_new_M, &carga_new_M->Timing.tArray[0]);
  carga_new_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &carga_new_B), 0,
                sizeof(B_carga_new_T));

  /* states (continuous) */
  {
    (void) memset((void *)&carga_new_X, 0,
                  sizeof(X_carga_new_T));
  }

  /* states (dwork) */
  (void) memset((void *)&carga_new_DW, 0,
                sizeof(DW_carga_new_T));

  /* external inputs */
  (void)memset((void *)&carga_new_U, 0, sizeof(ExtU_carga_new_T));

  /* external outputs */
  (void) memset((void *)&carga_new_Y, 0,
                sizeof(ExtY_carga_new_T));

  /* Start for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T *pBuffer = &carga_new_DW.TransportDelay_RWORK.TUbufferArea[0];
    carga_new_DW.TransportDelay_IWORK.Tail = 0;
    carga_new_DW.TransportDelay_IWORK.Head = 0;
    carga_new_DW.TransportDelay_IWORK.Last = 0;
    carga_new_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_new_M->Timing.t[0];
    carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_new_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S7>/Transport Delay' */
  {
    real_T *pBuffer = &carga_new_DW.TransportDelay_RWORK_e.TUbufferArea[0];
    carga_new_DW.TransportDelay_IWORK_p.Tail = 0;
    carga_new_DW.TransportDelay_IWORK_p.Head = 0;
    carga_new_DW.TransportDelay_IWORK_p.Last = 0;
    carga_new_DW.TransportDelay_IWORK_p.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_new_M->Timing.t[0];
    carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_new_DW.TransportDelay_PWORK_k.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S12>/Transport Delay' */
  {
    real_T *pBuffer = &carga_new_DW.TransportDelay_RWORK_a.TUbufferArea[0];
    carga_new_DW.TransportDelay_IWORK_l.Tail = 0;
    carga_new_DW.TransportDelay_IWORK_l.Head = 0;
    carga_new_DW.TransportDelay_IWORK_l.Last = 0;
    carga_new_DW.TransportDelay_IWORK_l.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_new_M->Timing.t[0];
    carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_new_DW.TransportDelay_PWORK_i.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S11>/Transport Delay' */
  {
    real_T *pBuffer = &carga_new_DW.TransportDelay_RWORK_f.TUbufferArea[0];
    carga_new_DW.TransportDelay_IWORK_ph.Tail = 0;
    carga_new_DW.TransportDelay_IWORK_ph.Head = 0;
    carga_new_DW.TransportDelay_IWORK_ph.Last = 0;
    carga_new_DW.TransportDelay_IWORK_ph.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = carga_new_M->Timing.t[0];
    carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[0] = (void *) &pBuffer[0];
    carga_new_DW.TransportDelay_PWORK_h.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* InitializeConditions for Integrator: '<S8>/integrator' */
  carga_new_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S8>/Memory' */
  carga_new_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S7>/integrator' */
  carga_new_X.integrator_CSTATE_k = 0.0;

  /* InitializeConditions for Integrator: '<S12>/integrator' */
  carga_new_X.integrator_CSTATE_l = 0.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  carga_new_DW.Memory_PreviousInput_p = 1.0;

  /* InitializeConditions for Integrator: '<S11>/integrator' */
  carga_new_X.integrator_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  carga_new_X.TransferFcn3_CSTATE[0] = 0.0;
  carga_new_X.TransferFcn3_CSTATE[1] = 0.0;
}

/* Model terminate function */
void carga_new_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: renovables.c
 *
 * Code generated for Simulink model 'renovables'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:39:43 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "renovables.h"
#include "renovables_private.h"

/* Block signals (default storage) */
B_renovables_T renovables_B;

/* Continuous states */
X_renovables_T renovables_X;

/* Block states (default storage) */
DW_renovables_T renovables_DW;

/* External inputs (root inport signals with default storage) */
ExtU_renovables_T renovables_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_renovables_T renovables_Y;

/* Real-time model */
RT_MODEL_renovables_T renovables_M_;
RT_MODEL_renovables_T *const renovables_M = &renovables_M_;

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
     Interpolation method: 'Linear point-slope'
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
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

/* This function updates continuous states using the ODE8 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
#define renovables_NSTAGES             13

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
  real_T* f[renovables_NSTAGES];
  int idx,stagesIdx,statesIdx;
  double deltaX;
  int_T nXc = 16;
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
  for (stagesIdx=0;stagesIdx<renovables_NSTAGES;stagesIdx++) {
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
      renovables_derivatives();
    } else {
      (stagesIdx==renovables_NSTAGES-1)? rtsiSetT(si, tnew) : rtsiSetT(si, t + h*
        rt_ODE8_C[stagesIdx]);
      rtsiSetdX(si, f[stagesIdx]);
      renovables_step();
      renovables_derivatives();
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
void renovables_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_h;
  real_T rtb_TransportDelay_j;
  real_T rtb_integrator_c;
  real_T rtb_TransportDelay_m;
  real_T rtb_integrator_d;
  real_T rtb_TransportDelay_g;
  real_T paux;
  real_T rtb_Gain1;
  real_T rtb_phi;
  if (rtmIsMajorTimeStep(renovables_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&renovables_M->solverInfo,
                          ((renovables_M->Timing.clockTick0+1)*
      renovables_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(renovables_M)) {
    renovables_M->Timing.t[0] = rtsiGetT(&renovables_M->solverInfo);
  }

  /* Outport: '<Root>/Qoren' incorporates:
   *  StateSpace: '<S1>/Hw1'
   */
  renovables_Y.Qoren = 0.94444980822600488 * renovables_X.Hw1_CSTATE[3];

  /* Outport: '<Root>/Poren' incorporates:
   *  StateSpace: '<S1>/Hw6'
   */
  renovables_Y.Poren = 0.94444980822600488 * renovables_X.Hw6_CSTATE[3];

  /* Outport: '<Root>/i2' incorporates:
   *  Integrator: '<Root>/Integrator5'
   */
  renovables_Y.i2 = renovables_X.Integrator5_CSTATE;
  if (rtmIsMajorTimeStep(renovables_M)) {
    /* DiscreteTransferFcn: '<S1>/Delay90(z)I' incorporates:
     *  Integrator: '<Root>/Integrator5'
     */
    renovables_DW.Delay90zI_tmp = renovables_X.Integrator5_CSTATE - -0.96364 *
      renovables_DW.Delay90zI_states;
    renovables_B.Delay90zI = -1.0364 * renovables_DW.Delay90zI_states +
      renovables_DW.Delay90zI_tmp;

    /* DiscreteTransferFcn: '<S1>/Delay90(z)V' incorporates:
     *  Integrator: '<Root>/Integrator4'
     */
    renovables_DW.Delay90zV_tmp = renovables_X.Integrator4_CSTATE - -0.96364 *
      renovables_DW.Delay90zV_states;
    renovables_B.Delay90zV = -1.0364 * renovables_DW.Delay90zV_states +
      renovables_DW.Delay90zV_tmp;
  }

  /* MATLAB Function: '<S1>/PQ_singlePhase' incorporates:
   *  Integrator: '<Root>/Integrator4'
   *  Integrator: '<Root>/Integrator5'
   */
  paux = renovables_X.Integrator4_CSTATE * renovables_X.Integrator5_CSTATE +
    renovables_B.Delay90zV * renovables_B.Delay90zI;
  if (paux > 200000.0) {
    paux = 200000.0;
  }

  if (paux < -200000.0) {
    paux = -0.002;
  }

  renovables_B.p = paux / 2.0;
  paux = renovables_B.Delay90zV * renovables_X.Integrator5_CSTATE -
    renovables_X.Integrator4_CSTATE * renovables_B.Delay90zI;
  if (paux > 200000.0) {
    paux = 200000.0;
  }

  if (paux < -200000.0) {
    paux = -200000.0;
  }

  renovables_B.q = paux / 2.0;

  /* End of MATLAB Function: '<S1>/PQ_singlePhase' */

  /* MATLAB Function: '<S1>/PQ2Iab_PH1' incorporates:
   *  Inport: '<Root>/Piren'
   *  Inport: '<Root>/Qiren'
   *  Integrator: '<Root>/Integrator4'
   */
  paux = renovables_X.Integrator4_CSTATE * renovables_X.Integrator4_CSTATE +
    renovables_B.Delay90zV * renovables_B.Delay90zV;
  if (fabs(paux) <= 4.94065645841247E-321) {
    paux = (rtInf);
  } else {
    paux = 1.0 / paux;
  }

  paux = paux * renovables_X.Integrator4_CSTATE * (2.0 * renovables_U.Piren) +
    paux * renovables_B.Delay90zV * (2.0 * renovables_U.Qiren);
  if (paux > 1000.0) {
    paux = 1000.0;
  }

  if (paux < -1000.0) {
    paux = -1000.0;
  }

  if (rtIsNaN(paux)) {
    paux = 0.0;
  }

  if (rtmIsMajorTimeStep(renovables_M)) {
    /* DiscreteTransferFcn: '<S1>/PR(z)' incorporates:
     *  Integrator: '<Root>/Integrator5'
     *  MATLAB Function: '<S1>/PQ2Iab_PH1'
     *  Sum: '<S1>/Sum'
     */
    renovables_DW.PRz_tmp = ((paux - renovables_X.Integrator5_CSTATE) - -1.9966 *
      renovables_DW.PRz_states[0]) - 0.998 * renovables_DW.PRz_states[1];
    renovables_Y.duty_cycle = (0.0201 * renovables_DW.PRz_tmp + -0.039932 *
      renovables_DW.PRz_states[0]) + 0.01986 * renovables_DW.PRz_states[1];

    /* Gain: '<Root>/Gain16' incorporates:
     *  DiscreteTransferFcn: '<S1>/PR(z)'
     */
    renovables_B.Gain16 = 2.0 * renovables_Y.duty_cycle;
  }

  /* Integrator: '<Root>/Integrator9' */
  /* Limited  Integrator  */
  if (renovables_X.Integrator9_CSTATE >= 1.0) {
    renovables_X.Integrator9_CSTATE = 1.0;
  } else {
    if (renovables_X.Integrator9_CSTATE <= 0.0) {
      renovables_X.Integrator9_CSTATE = 0.0;
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function SOC ' incorporates:
   *  Integrator: '<Root>/Integrator9'
   */
  renovables_Y.soc = -0.03536 * renovables_X.Integrator9_CSTATE + 100.0;

  /* Gain: '<Root>/Gain5' incorporates:
   *  Gain: '<Root>/Gain18'
   *  Gain: '<Root>/Gain9'
   *  Integrator: '<Root>/Integrator3'
   *  Integrator: '<Root>/Integrator4'
   *  Lookup_n-D: '<Root>/1-D Lookup Table2'
   *  Product: '<Root>/Product1'
   *  Sum: '<Root>/Sum6'
   */
  renovables_B.Gain5 = ((2.0 * look1_binlxpw(renovables_Y.soc,
    renovables_ConstP.uDLookupTable2_bp01Data,
    renovables_ConstP.uDLookupTable2_tableData, 8U) * renovables_B.Gain16 -
    renovables_X.Integrator4_CSTATE) - 0.2 * renovables_X.Integrator3_CSTATE) *
    33.333333333333336;

  /* Gain: '<Root>/Gain6' incorporates:
   *  Integrator: '<Root>/Integrator3'
   *  Integrator: '<Root>/Integrator5'
   *  Sum: '<Root>/Sum4'
   */
  renovables_B.Gain6 = (renovables_X.Integrator3_CSTATE -
                        renovables_X.Integrator5_CSTATE) * 45454.545454545456;

  /* Sum: '<Root>/Sum14' incorporates:
   *  Inport: '<Root>/Ipv'
   *  Integrator: '<Root>/Integrator3'
   */
  renovables_B.Sum14 = renovables_X.Integrator3_CSTATE + renovables_U.Ipv;

  /* Sin: '<S9>/sin(wt)' incorporates:
   *  Sin: '<S10>/sin(wt)'
   *  Sin: '<S9>/cos(wt)'
   */
  rtb_Gain1 = 376.99111843077515 * renovables_M->Timing.t[0];
  paux = sin(rtb_Gain1) * 2.0;

  /* Product: '<S9>/Product' incorporates:
   *  Integrator: '<Root>/Integrator4'
   *  Sin: '<S9>/sin(wt)'
   */
  renovables_B.Product = paux * renovables_X.Integrator4_CSTATE;

  /* Sin: '<S9>/cos(wt)' incorporates:
   *  Sin: '<S10>/cos(wt)'
   */
  rtb_Gain1 = sin(rtb_Gain1 + 1.5707963267948966) * 2.0;

  /* Product: '<S9>/Product1' incorporates:
   *  Integrator: '<Root>/Integrator4'
   *  Sin: '<S9>/cos(wt)'
   */
  renovables_B.Product1 = rtb_Gain1 * renovables_X.Integrator4_CSTATE;

  /* Gain: '<Root>/Gain7' incorporates:
   *  Gain: '<Root>/Gain8'
   *  Inport: '<Root>/Vload'
   *  Integrator: '<Root>/Integrator4'
   *  Integrator: '<Root>/Integrator5'
   *  Sum: '<Root>/Sum5'
   */
  renovables_B.Gain7 = ((renovables_X.Integrator4_CSTATE - renovables_U.Vload) -
                        0.0012 * renovables_X.Integrator5_CSTATE) *
    45454.545454545456;

  /* Product: '<S10>/Product' incorporates:
   *  Integrator: '<Root>/Integrator5'
   */
  renovables_B.Product_d = paux * renovables_X.Integrator5_CSTATE;

  /* Product: '<S10>/Product1' incorporates:
   *  Integrator: '<Root>/Integrator5'
   */
  renovables_B.Product1_p = rtb_Gain1 * renovables_X.Integrator5_CSTATE;

  /* Integrator: '<S14>/integrator' */
  rtb_integrator = renovables_X.integrator_CSTATE;

  /* TransportDelay: '<S14>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = renovables_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      renovables_DW.TransportDelay_IWORK.CircularBufSize,
      &renovables_DW.TransportDelay_IWORK.Last,
      renovables_DW.TransportDelay_IWORK.Tail,
      renovables_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(renovables_M)) {
    /* Memory: '<S14>/Memory' */
    renovables_B.Memory = renovables_DW.Memory_PreviousInput;
  }

  /* Switch: '<S14>/Switch' incorporates:
   *  Clock: '<S14>/Clock'
   *  Constant: '<S14>/K1'
   *  Gain: '<S14>/Gain'
   *  RelationalOperator: '<S14>/Relational Operator'
   *  Sum: '<S14>/Sum'
   */
  if (renovables_M->Timing.t[0] >= 0.016666666666666666) {
    renovables_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
  } else {
    renovables_B.Switch = renovables_B.Memory;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Integrator: '<S13>/integrator' */
  rtb_integrator_h = renovables_X.integrator_CSTATE_n;

  /* TransportDelay: '<S13>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[1];
    real_T simTime = renovables_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_j = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      renovables_DW.TransportDelay_IWORK_f.CircularBufSize,
      &renovables_DW.TransportDelay_IWORK_f.Last,
      renovables_DW.TransportDelay_IWORK_f.Tail,
      renovables_DW.TransportDelay_IWORK_f.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(renovables_M)) {
    /* Memory: '<S13>/Memory' */
    renovables_B.Memory_e = renovables_DW.Memory_PreviousInput_b;
  }

  /* Switch: '<S13>/Switch' incorporates:
   *  Clock: '<S13>/Clock'
   *  Constant: '<S13>/K1'
   *  Gain: '<S13>/Gain'
   *  RelationalOperator: '<S13>/Relational Operator'
   *  Sum: '<S13>/Sum'
   */
  if (renovables_M->Timing.t[0] >= 0.016666666666666666) {
    renovables_B.Switch_i = (rtb_integrator_h - rtb_TransportDelay_j) * 60.0;
  } else {
    renovables_B.Switch_i = renovables_B.Memory_e;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Integrator: '<S18>/integrator' */
  rtb_integrator_c = renovables_X.integrator_CSTATE_d;

  /* TransportDelay: '<S18>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[1];
    real_T simTime = renovables_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_m = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      renovables_DW.TransportDelay_IWORK_n.CircularBufSize,
      &renovables_DW.TransportDelay_IWORK_n.Last,
      renovables_DW.TransportDelay_IWORK_n.Tail,
      renovables_DW.TransportDelay_IWORK_n.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(renovables_M)) {
    /* Memory: '<S18>/Memory' */
    renovables_B.Memory_e4 = renovables_DW.Memory_PreviousInput_m;
  }

  /* Switch: '<S18>/Switch' incorporates:
   *  Clock: '<S18>/Clock'
   *  Constant: '<S18>/K1'
   *  Gain: '<S18>/Gain'
   *  RelationalOperator: '<S18>/Relational Operator'
   *  Sum: '<S18>/Sum'
   */
  if (renovables_M->Timing.t[0] >= 0.016666666666666666) {
    renovables_B.Switch_f = (rtb_integrator_c - rtb_TransportDelay_m) * 60.0;
  } else {
    renovables_B.Switch_f = renovables_B.Memory_e4;
  }

  /* End of Switch: '<S18>/Switch' */

  /* Integrator: '<S17>/integrator' */
  rtb_integrator_d = renovables_X.integrator_CSTATE_j;

  /* TransportDelay: '<S17>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[1];
    real_T simTime = renovables_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_g = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      renovables_DW.TransportDelay_IWORK_g.CircularBufSize,
      &renovables_DW.TransportDelay_IWORK_g.Last,
      renovables_DW.TransportDelay_IWORK_g.Tail,
      renovables_DW.TransportDelay_IWORK_g.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(renovables_M)) {
    /* Memory: '<S17>/Memory' */
    renovables_B.Memory_g = renovables_DW.Memory_PreviousInput_i;
  }

  /* Switch: '<S17>/Switch' incorporates:
   *  Clock: '<S17>/Clock'
   *  Constant: '<S17>/K1'
   *  Gain: '<S17>/Gain'
   *  RelationalOperator: '<S17>/Relational Operator'
   *  Sum: '<S17>/Sum'
   */
  if (renovables_M->Timing.t[0] >= 0.016666666666666666) {
    renovables_B.Switch_n = (rtb_integrator_d - rtb_TransportDelay_g) * 60.0;
  } else {
    renovables_B.Switch_n = renovables_B.Memory_g;
  }

  /* End of Switch: '<S17>/Switch' */

  /* Gain: '<S4>/Gain1' incorporates:
   *  ComplexToMagnitudeAngle: '<S10>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S9>/Complex to Magnitude-Angle'
   *  Product: '<S4>/Product'
   *  RealImagToComplex: '<S10>/Real-Imag to Complex'
   *  RealImagToComplex: '<S9>/Real-Imag to Complex'
   */
  rtb_Gain1 = rt_hypotd_snf(renovables_B.Switch, renovables_B.Switch_i) *
    rt_hypotd_snf(renovables_B.Switch_f, renovables_B.Switch_n) * 0.5;

  /* Gain: '<S4>/Deg->Rad' incorporates:
   *  ComplexToMagnitudeAngle: '<S10>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S9>/Complex to Magnitude-Angle'
   *  Gain: '<S10>/Rad->Deg.'
   *  Gain: '<S9>/Rad->Deg.'
   *  RealImagToComplex: '<S10>/Real-Imag to Complex'
   *  RealImagToComplex: '<S9>/Real-Imag to Complex'
   *  Sum: '<S4>/Sum'
   */
  rtb_phi = (57.295779513082323 * rt_atan2d_snf(renovables_B.Switch_i,
              renovables_B.Switch) - 57.295779513082323 * rt_atan2d_snf
             (renovables_B.Switch_n, renovables_B.Switch_f)) *
    0.017453292519943295;

  /* Product: '<S4>/Product1' incorporates:
   *  Trigonometry: '<S4>/Trigonometric Function2'
   */
  paux = rtb_Gain1 * cos(rtb_phi);

  /* Product: '<S4>/Product3' incorporates:
   *  Trigonometry: '<S4>/Trigonometric Function2'
   */
  rtb_Gain1 *= sin(rtb_phi);

  /* Outport: '<Root>/Potencia_ren' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function6'
   */
  renovables_Y.Potencia_ren = sqrt(paux * paux + rtb_Gain1 * rtb_Gain1);
  if (rtmIsMajorTimeStep(renovables_M)) {
    if (rtmIsMajorTimeStep(renovables_M)) {
      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)I' */
      renovables_DW.Delay90zI_states = renovables_DW.Delay90zI_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)V' */
      renovables_DW.Delay90zV_states = renovables_DW.Delay90zV_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/PR(z)' */
      renovables_DW.PRz_states[1] = renovables_DW.PRz_states[0];
      renovables_DW.PRz_states[0] = renovables_DW.PRz_tmp;
    }

    /* Update for TransportDelay: '<S14>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = renovables_M->Timing.t[0];
      renovables_DW.TransportDelay_IWORK.Head =
        ((renovables_DW.TransportDelay_IWORK.Head <
          (renovables_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (renovables_DW.TransportDelay_IWORK.Head+1) : 0);
      if (renovables_DW.TransportDelay_IWORK.Head ==
          renovables_DW.TransportDelay_IWORK.Tail) {
        renovables_DW.TransportDelay_IWORK.Tail =
          ((renovables_DW.TransportDelay_IWORK.Tail <
            (renovables_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (renovables_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[renovables_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[renovables_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(renovables_M)) {
      /* Update for Memory: '<S14>/Memory' */
      renovables_DW.Memory_PreviousInput = renovables_B.Switch;
    }

    /* Update for TransportDelay: '<S13>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[1];
      real_T simTime = renovables_M->Timing.t[0];
      renovables_DW.TransportDelay_IWORK_f.Head =
        ((renovables_DW.TransportDelay_IWORK_f.Head <
          (renovables_DW.TransportDelay_IWORK_f.CircularBufSize-1)) ?
         (renovables_DW.TransportDelay_IWORK_f.Head+1) : 0);
      if (renovables_DW.TransportDelay_IWORK_f.Head ==
          renovables_DW.TransportDelay_IWORK_f.Tail) {
        renovables_DW.TransportDelay_IWORK_f.Tail =
          ((renovables_DW.TransportDelay_IWORK_f.Tail <
            (renovables_DW.TransportDelay_IWORK_f.CircularBufSize-1)) ?
           (renovables_DW.TransportDelay_IWORK_f.Tail+1) : 0);
      }

      (*tBuffer)[renovables_DW.TransportDelay_IWORK_f.Head] = simTime;
      (*uBuffer)[renovables_DW.TransportDelay_IWORK_f.Head] = rtb_integrator_h;
    }

    if (rtmIsMajorTimeStep(renovables_M)) {
      /* Update for Memory: '<S13>/Memory' */
      renovables_DW.Memory_PreviousInput_b = renovables_B.Switch_i;
    }

    /* Update for TransportDelay: '<S18>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[1];
      real_T simTime = renovables_M->Timing.t[0];
      renovables_DW.TransportDelay_IWORK_n.Head =
        ((renovables_DW.TransportDelay_IWORK_n.Head <
          (renovables_DW.TransportDelay_IWORK_n.CircularBufSize-1)) ?
         (renovables_DW.TransportDelay_IWORK_n.Head+1) : 0);
      if (renovables_DW.TransportDelay_IWORK_n.Head ==
          renovables_DW.TransportDelay_IWORK_n.Tail) {
        renovables_DW.TransportDelay_IWORK_n.Tail =
          ((renovables_DW.TransportDelay_IWORK_n.Tail <
            (renovables_DW.TransportDelay_IWORK_n.CircularBufSize-1)) ?
           (renovables_DW.TransportDelay_IWORK_n.Tail+1) : 0);
      }

      (*tBuffer)[renovables_DW.TransportDelay_IWORK_n.Head] = simTime;
      (*uBuffer)[renovables_DW.TransportDelay_IWORK_n.Head] = rtb_integrator_c;
    }

    if (rtmIsMajorTimeStep(renovables_M)) {
      /* Update for Memory: '<S18>/Memory' */
      renovables_DW.Memory_PreviousInput_m = renovables_B.Switch_f;
    }

    /* Update for TransportDelay: '<S17>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[1];
      real_T simTime = renovables_M->Timing.t[0];
      renovables_DW.TransportDelay_IWORK_g.Head =
        ((renovables_DW.TransportDelay_IWORK_g.Head <
          (renovables_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
         (renovables_DW.TransportDelay_IWORK_g.Head+1) : 0);
      if (renovables_DW.TransportDelay_IWORK_g.Head ==
          renovables_DW.TransportDelay_IWORK_g.Tail) {
        renovables_DW.TransportDelay_IWORK_g.Tail =
          ((renovables_DW.TransportDelay_IWORK_g.Tail <
            (renovables_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
           (renovables_DW.TransportDelay_IWORK_g.Tail+1) : 0);
      }

      (*tBuffer)[renovables_DW.TransportDelay_IWORK_g.Head] = simTime;
      (*uBuffer)[renovables_DW.TransportDelay_IWORK_g.Head] = rtb_integrator_d;
    }

    if (rtmIsMajorTimeStep(renovables_M)) {
      /* Update for Memory: '<S17>/Memory' */
      renovables_DW.Memory_PreviousInput_i = renovables_B.Switch_n;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(renovables_M)) {
    rt_ertODEUpdateContinuousStates(&renovables_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++renovables_M->Timing.clockTick0;
    renovables_M->Timing.t[0] = rtsiGetSolverStopTime(&renovables_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      renovables_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void renovables_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_renovables_T *_rtXdot;
  _rtXdot = ((XDot_renovables_T *) renovables_M->derivs);

  /* Derivatives for StateSpace: '<S1>/Hw1' */
  _rtXdot->Hw1_CSTATE[0] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw1' */
  _rtXdot->Hw1_CSTATE[1] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[1] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw1' */
  _rtXdot->Hw1_CSTATE[2] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[2] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw1' */
  _rtXdot->Hw1_CSTATE[3] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[3] = 0.0;

  /* Derivatives for StateSpace: '<S1>/Hw1' */
  _rtXdot->Hw1_CSTATE[0] += -341.08603071128289 * renovables_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[0] += -178.02459475242631 * renovables_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[1] += 178.0245947524264 * renovables_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[2] += 199.58239979893239 * renovables_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[2] += -247.76277465378331 * renovables_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[2] += -199.58239979893239 * renovables_X.Hw1_CSTATE[3];
  _rtXdot->Hw1_CSTATE[3] += 199.58239979893244 * renovables_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[0] += 188.49555921538757 * renovables_B.q;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] += -341.08603071128289 * renovables_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += -178.02459475242631 * renovables_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[1] += 178.0245947524264 * renovables_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[2] += 199.58239979893239 * renovables_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[2] += -247.76277465378331 * renovables_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[2] += -199.58239979893239 * renovables_X.Hw6_CSTATE[3];
  _rtXdot->Hw6_CSTATE[3] += 199.58239979893244 * renovables_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[0] += 188.49555921538757 * renovables_B.p;

  /* Derivatives for Integrator: '<Root>/Integrator5' */
  _rtXdot->Integrator5_CSTATE = renovables_B.Gain7;

  /* Derivatives for Integrator: '<Root>/Integrator4' */
  _rtXdot->Integrator4_CSTATE = renovables_B.Gain6;

  /* Derivatives for Integrator: '<Root>/Integrator9' */
  lsat = (renovables_X.Integrator9_CSTATE <= 0.0);
  usat = (renovables_X.Integrator9_CSTATE >= 1.0);
  if (((!lsat) && (!usat)) || (lsat && (renovables_B.Sum14 > 0.0)) || (usat &&
       (renovables_B.Sum14 < 0.0))) {
    _rtXdot->Integrator9_CSTATE = renovables_B.Sum14;
  } else {
    /* in saturation */
    _rtXdot->Integrator9_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<Root>/Integrator9' */

  /* Derivatives for Integrator: '<Root>/Integrator3' */
  _rtXdot->Integrator3_CSTATE = renovables_B.Gain5;

  /* Derivatives for Integrator: '<S14>/integrator' */
  _rtXdot->integrator_CSTATE = renovables_B.Product;

  /* Derivatives for Integrator: '<S13>/integrator' */
  _rtXdot->integrator_CSTATE_n = renovables_B.Product1;

  /* Derivatives for Integrator: '<S18>/integrator' */
  _rtXdot->integrator_CSTATE_d = renovables_B.Product_d;

  /* Derivatives for Integrator: '<S17>/integrator' */
  _rtXdot->integrator_CSTATE_j = renovables_B.Product1_p;
}

/* Model initialize function */
void renovables_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)renovables_M, 0,
                sizeof(RT_MODEL_renovables_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&renovables_M->solverInfo,
                          &renovables_M->Timing.simTimeStep);
    rtsiSetTPtr(&renovables_M->solverInfo, &rtmGetTPtr(renovables_M));
    rtsiSetStepSizePtr(&renovables_M->solverInfo,
                       &renovables_M->Timing.stepSize0);
    rtsiSetdXPtr(&renovables_M->solverInfo, &renovables_M->derivs);
    rtsiSetContStatesPtr(&renovables_M->solverInfo, (real_T **)
                         &renovables_M->contStates);
    rtsiSetNumContStatesPtr(&renovables_M->solverInfo,
      &renovables_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&renovables_M->solverInfo,
      &renovables_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&renovables_M->solverInfo,
      &renovables_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&renovables_M->solverInfo,
      &renovables_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&renovables_M->solverInfo, (&rtmGetErrorStatus
      (renovables_M)));
    rtsiSetRTModelPtr(&renovables_M->solverInfo, renovables_M);
  }

  rtsiSetSimTimeStep(&renovables_M->solverInfo, MAJOR_TIME_STEP);
  renovables_M->intgData.deltaY= renovables_M->OdeDeltaY;
  renovables_M->intgData.f[0] = renovables_M->odeF[0];
  renovables_M->intgData.f[1] = renovables_M->odeF[1];
  renovables_M->intgData.f[2] = renovables_M->odeF[2];
  renovables_M->intgData.f[3] = renovables_M->odeF[3];
  renovables_M->intgData.f[4] = renovables_M->odeF[4];
  renovables_M->intgData.f[5] = renovables_M->odeF[5];
  renovables_M->intgData.f[6] = renovables_M->odeF[6];
  renovables_M->intgData.f[7] = renovables_M->odeF[7];
  renovables_M->intgData.f[8] = renovables_M->odeF[8];
  renovables_M->intgData.f[9] = renovables_M->odeF[9];
  renovables_M->intgData.f[10] = renovables_M->odeF[10];
  renovables_M->intgData.f[11] = renovables_M->odeF[11];
  renovables_M->intgData.f[12] = renovables_M->odeF[12];
  renovables_M->intgData.x0 = renovables_M->odeX0;
  renovables_M->contStates = ((X_renovables_T *) &renovables_X);
  rtsiSetSolverData(&renovables_M->solverInfo, (void *)&renovables_M->intgData);
  rtsiSetSolverName(&renovables_M->solverInfo,"ode8");
  rtmSetTPtr(renovables_M, &renovables_M->Timing.tArray[0]);
  renovables_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &renovables_B), 0,
                sizeof(B_renovables_T));

  /* states (continuous) */
  {
    (void) memset((void *)&renovables_X, 0,
                  sizeof(X_renovables_T));
  }

  /* states (dwork) */
  (void) memset((void *)&renovables_DW, 0,
                sizeof(DW_renovables_T));

  /* external inputs */
  (void)memset((void *)&renovables_U, 0, sizeof(ExtU_renovables_T));

  /* external outputs */
  (void) memset((void *)&renovables_Y, 0,
                sizeof(ExtY_renovables_T));

  /* Start for TransportDelay: '<S14>/Transport Delay' */
  {
    real_T *pBuffer = &renovables_DW.TransportDelay_RWORK.TUbufferArea[0];
    renovables_DW.TransportDelay_IWORK.Tail = 0;
    renovables_DW.TransportDelay_IWORK.Head = 0;
    renovables_DW.TransportDelay_IWORK.Last = 0;
    renovables_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = renovables_M->Timing.t[0];
    renovables_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    renovables_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S13>/Transport Delay' */
  {
    real_T *pBuffer = &renovables_DW.TransportDelay_RWORK_d.TUbufferArea[0];
    renovables_DW.TransportDelay_IWORK_f.Tail = 0;
    renovables_DW.TransportDelay_IWORK_f.Head = 0;
    renovables_DW.TransportDelay_IWORK_f.Last = 0;
    renovables_DW.TransportDelay_IWORK_f.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = renovables_M->Timing.t[0];
    renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[0] = (void *) &pBuffer[0];
    renovables_DW.TransportDelay_PWORK_d.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* Start for TransportDelay: '<S18>/Transport Delay' */
  {
    real_T *pBuffer = &renovables_DW.TransportDelay_RWORK_n.TUbufferArea[0];
    renovables_DW.TransportDelay_IWORK_n.Tail = 0;
    renovables_DW.TransportDelay_IWORK_n.Head = 0;
    renovables_DW.TransportDelay_IWORK_n.Last = 0;
    renovables_DW.TransportDelay_IWORK_n.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = renovables_M->Timing.t[0];
    renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[0] = (void *) &pBuffer[0];
    renovables_DW.TransportDelay_PWORK_n.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* Start for TransportDelay: '<S17>/Transport Delay' */
  {
    real_T *pBuffer = &renovables_DW.TransportDelay_RWORK_nm.TUbufferArea[0];
    renovables_DW.TransportDelay_IWORK_g.Tail = 0;
    renovables_DW.TransportDelay_IWORK_g.Head = 0;
    renovables_DW.TransportDelay_IWORK_g.Last = 0;
    renovables_DW.TransportDelay_IWORK_g.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = renovables_M->Timing.t[0];
    renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[0] = (void *) &pBuffer[0];
    renovables_DW.TransportDelay_PWORK_o.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  renovables_X.Hw1_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  renovables_X.Hw6_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  renovables_X.Hw1_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  renovables_X.Hw6_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  renovables_X.Hw1_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  renovables_X.Hw6_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  renovables_X.Hw1_CSTATE[3] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  renovables_X.Hw6_CSTATE[3] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator5' */
  renovables_X.Integrator5_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator4' */
  renovables_X.Integrator4_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator9' */
  renovables_X.Integrator9_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator3' */
  renovables_X.Integrator3_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S14>/integrator' */
  renovables_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S14>/Memory' */
  renovables_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S13>/integrator' */
  renovables_X.integrator_CSTATE_n = 0.0;

  /* InitializeConditions for Integrator: '<S18>/integrator' */
  renovables_X.integrator_CSTATE_d = 0.0;

  /* InitializeConditions for Memory: '<S18>/Memory' */
  renovables_DW.Memory_PreviousInput_m = 1.0;

  /* InitializeConditions for Integrator: '<S17>/integrator' */
  renovables_X.integrator_CSTATE_j = 0.0;
}

/* Model terminate function */
void renovables_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: biomasa.c
 *
 * Code generated for Simulink model 'biomasa'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:25:24 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "biomasa.h"
#include "biomasa_private.h"

/* Block signals (default storage) */
B_biomasa_T biomasa_B;

/* Continuous states */
X_biomasa_T biomasa_X;

/* Block states (default storage) */
DW_biomasa_T biomasa_DW;

/* External inputs (root inport signals with default storage) */
ExtU_biomasa_T biomasa_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_biomasa_T biomasa_Y;

/* Real-time model */
RT_MODEL_biomasa_T biomasa_M_;
RT_MODEL_biomasa_T *const biomasa_M = &biomasa_M_;

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
#define biomasa_NSTAGES                13

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
  real_T* f[biomasa_NSTAGES];
  int idx,stagesIdx,statesIdx;
  double deltaX;
  int_T nXc = 26;
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
  for (stagesIdx=0;stagesIdx<biomasa_NSTAGES;stagesIdx++) {
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
      biomasa_derivatives();
    } else {
      (stagesIdx==biomasa_NSTAGES-1)? rtsiSetT(si, tnew) : rtsiSetT(si, t + h*
        rt_ODE8_C[stagesIdx]);
      rtsiSetdX(si, f[stagesIdx]);
      biomasa_step();
      biomasa_derivatives();
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
void biomasa_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_f;
  real_T rtb_TransportDelay_g;
  real_T rtb_integrator_g;
  real_T rtb_TransportDelay_d;
  real_T rtb_integrator_k;
  real_T rtb_TransportDelay_j;
  real_T rtb_Fuelsystemactuator;
  real_T rtb_ComplextoMagnitudeAngle_o1;
  real_T paux;
  real_T rtb_Add3;
  real_T rtb_phi;
  int32_T rtb_Step;
  real_T Svp_tmp;
  real_T Svp_tmp_0;
  real_T Xacidp_tmp;
  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&biomasa_M->solverInfo,((biomasa_M->Timing.clockTick0+
      1)*biomasa_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(biomasa_M)) {
    biomasa_M->Timing.t[0] = rtsiGetT(&biomasa_M->solverInfo);
  }

  /* Outport: '<Root>/Qobio' incorporates:
   *  StateSpace: '<S1>/Hw1'
   */
  biomasa_Y.Qobio = 0.94444980822600488 * biomasa_X.Hw1_CSTATE[3];

  /* Outport: '<Root>/Pobio' incorporates:
   *  StateSpace: '<S1>/Hw6'
   */
  biomasa_Y.Pobio = 0.94444980822600488 * biomasa_X.Hw6_CSTATE[3];

  /* Outport: '<Root>/i1' incorporates:
   *  Integrator: '<Root>/Integrator2'
   */
  biomasa_Y.i1 = biomasa_X.Integrator2_CSTATE;
  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* DiscreteTransferFcn: '<S1>/Delay90(z)I' incorporates:
     *  Integrator: '<Root>/Integrator2'
     */
    biomasa_DW.Delay90zI_tmp = biomasa_X.Integrator2_CSTATE - -0.96364 *
      biomasa_DW.Delay90zI_states;
    biomasa_B.Delay90zI = -1.0364 * biomasa_DW.Delay90zI_states +
      biomasa_DW.Delay90zI_tmp;

    /* DiscreteTransferFcn: '<S1>/Delay90(z)V' incorporates:
     *  Integrator: '<Root>/Integrator1'
     */
    biomasa_DW.Delay90zV_tmp = biomasa_X.Integrator1_CSTATE - -0.96364 *
      biomasa_DW.Delay90zV_states;
    biomasa_B.Delay90zV = -1.0364 * biomasa_DW.Delay90zV_states +
      biomasa_DW.Delay90zV_tmp;
  }

  /* MATLAB Function: '<S1>/PQ_singlePhase' incorporates:
   *  Integrator: '<Root>/Integrator1'
   *  Integrator: '<Root>/Integrator2'
   */
  paux = biomasa_X.Integrator1_CSTATE * biomasa_X.Integrator2_CSTATE +
    biomasa_B.Delay90zV * biomasa_B.Delay90zI;
  if (paux > 200000.0) {
    paux = 200000.0;
  }

  if (paux < -200000.0) {
    paux = -0.002;
  }

  biomasa_B.p = paux / 2.0;
  paux = biomasa_B.Delay90zV * biomasa_X.Integrator2_CSTATE -
    biomasa_X.Integrator1_CSTATE * biomasa_B.Delay90zI;
  if (paux > 200000.0) {
    paux = 200000.0;
  }

  if (paux < -200000.0) {
    paux = -200000.0;
  }

  biomasa_B.q = paux / 2.0;

  /* End of MATLAB Function: '<S1>/PQ_singlePhase' */

  /* MATLAB Function: '<S1>/PQ2Iab_PH1' incorporates:
   *  Inport: '<Root>/Pibio'
   *  Inport: '<Root>/Qibio'
   *  Integrator: '<Root>/Integrator1'
   */
  paux = biomasa_X.Integrator1_CSTATE * biomasa_X.Integrator1_CSTATE +
    biomasa_B.Delay90zV * biomasa_B.Delay90zV;
  if (fabs(paux) <= 4.94065645841247E-321) {
    paux = (rtInf);
  } else {
    paux = 1.0 / paux;
  }

  paux = paux * biomasa_X.Integrator1_CSTATE * (2.0 * biomasa_U.Pibio) + paux *
    biomasa_B.Delay90zV * (2.0 * biomasa_U.Qibio);
  if (paux > 1000.0) {
    paux = 1000.0;
  }

  if (paux < -1000.0) {
    paux = -1000.0;
  }

  if (rtIsNaN(paux)) {
    paux = 0.0;
  }

  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* DiscreteTransferFcn: '<S1>/PR(z)' incorporates:
     *  Integrator: '<Root>/Integrator2'
     *  MATLAB Function: '<S1>/PQ2Iab_PH1'
     *  Sum: '<S1>/Sum'
     */
    biomasa_DW.PRz_tmp = ((paux - biomasa_X.Integrator2_CSTATE) - -1.9966 *
                          biomasa_DW.PRz_states[0]) - 0.998 *
      biomasa_DW.PRz_states[1];
    biomasa_Y.duty_cycle = (0.0201 * biomasa_DW.PRz_tmp + -0.039932 *
      biomasa_DW.PRz_states[0]) + 0.01986 * biomasa_DW.PRz_states[1];

    /* Gain: '<Root>/Gain15' incorporates:
     *  DiscreteTransferFcn: '<S1>/PR(z)'
     */
    biomasa_B.Gain15 = 2.0 * biomasa_Y.duty_cycle;

    /* Sum: '<S4>/Add3' incorporates:
     *  Constant: '<S4>/Constant21'
     *  Delay: '<S4>/Delay'
     */
    rtb_Add3 = 1.0 - biomasa_DW.Delay_DSTATE;

    /* Product: '<S4>/Product2' incorporates:
     *  Constant: '<S4>/Constant22'
     */
    biomasa_B.Product2 = 0.5 * rtb_Add3;
  }

  /* Sum: '<S4>/Add2' incorporates:
   *  Constant: '<S4>/Constant19'
   *  Constant: '<S4>/Constant20'
   *  Product: '<S4>/Product1'
   *  Sum: '<S4>/Add1'
   *  TransferFcn: '<S4>/Compresor'
   */
  biomasa_B.Torquemecnico = (5.0 * biomasa_X.Compresor_CSTATE - 0.23) * 1.2 +
    biomasa_B.Product2;

  /* Gain: '<S4>/Gain1' */
  paux = 900.0 * biomasa_B.Torquemecnico;

  /* Saturate: '<S4>/Saturation' */
  if (paux > 1000.0) {
    paux = 1000.0;
  } else {
    if (paux < 0.0) {
      paux = 0.0;
    }
  }

  /* End of Saturate: '<S4>/Saturation' */

  /* Gain: '<Root>/Gain' incorporates:
   *  Gain: '<Root>/Gain4'
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator1'
   *  Product: '<Root>/Product'
   *  Sum: '<Root>/Sum3'
   */
  biomasa_B.Gain = ((paux * biomasa_B.Gain15 - biomasa_X.Integrator1_CSTATE) -
                    0.1 * biomasa_X.Integrator_CSTATE) * 25.0;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator2'
   *  Sum: '<Root>/Sum'
   */
  biomasa_B.Gain1 = (biomasa_X.Integrator_CSTATE - biomasa_X.Integrator2_CSTATE)
    * 45454.545454545456;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/wref'
   */
  biomasa_B.Sum1 = 70000.0 - biomasa_B.Torquemecnico;

  /* TransferFcn: '<S4>/thermo couple' */
  rtb_ComplextoMagnitudeAngle_o1 = 0.0;
  rtb_ComplextoMagnitudeAngle_o1 += 0.4 * biomasa_X.thermocouple_CSTATE;

  /* Sum: '<S4>/Sum3' incorporates:
   *  Constant: '<S4>/Constant26'
   */
  biomasa_B.Sum3 = 950.0 - rtb_ComplextoMagnitudeAngle_o1;

  /* TransferFcn: '<S4>/Temp Control' */
  rtb_ComplextoMagnitudeAngle_o1 = 0.0;
  rtb_ComplextoMagnitudeAngle_o1 += 0.0022222222222222222 *
    biomasa_X.TempControl_CSTATE;
  rtb_ComplextoMagnitudeAngle_o1 += 0.0073333333333333332 * biomasa_B.Sum3;

  /* MATLAB Function: '<S4>/MATLAB Function metano' incorporates:
   *  Constant: '<S4>/Constant18'
   *  Integrator: '<S4>/Integrator1'
   *  MATLAB Function: '<S4>/MATLAB Function metanogenesis'
   */
  rtb_phi = 3.0 / (biomasa_X.Integrator1_CSTATE_o + 1.0);

  /* Product: '<S4>/Divide' incorporates:
   *  Constant: '<S4>/Constant17'
   *  Constant: '<S4>/Constant27'
   *  Constant: '<S4>/Constant3'
   *  Integrator: '<S4>/Integrator3'
   *  MATLAB Function: '<S4>/MATLAB Function metano'
   */
  paux = 20.0 * biomasa_ConstB.Sum * 15.1 * biomasa_X.Integrator3_CSTATE /
    rtb_phi / 35.4;

  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  MinMax: '<S4>/Min'
   *  Product: '<S4>/Product'
   *  TransferFcn: '<S4>/Transfer Fcn'
   */
  biomasa_B.y = fmin(-5.0 * biomasa_X.TransferFcn_CSTATE + 10.0 * biomasa_B.Sum1,
                     rtb_ComplextoMagnitudeAngle_o1) * biomasa_B.Torquemecnico *
    (1.0 - paux);

  /* TransportDelay: '<S4>/Delay combustor1' */
  {
    /* Delay time is 0 and inline parameter is on */
    rtb_ComplextoMagnitudeAngle_o1 = biomasa_B.y;
  }

  /* Sum: '<S4>/Add' */
  biomasa_B.Add = paux + rtb_ComplextoMagnitudeAngle_o1;

  /* Step: '<Root>/Step' incorporates:
   *  Sin: '<S9>/sin(wt)'
   */
  paux = biomasa_M->Timing.t[0];
  if (paux < 0.0) {
    rtb_Step = 0;
  } else {
    rtb_Step = 28;
  }

  /* End of Step: '<Root>/Step' */

  /* MATLAB Function: '<S4>/MATLAB Function Acidogenesis' incorporates:
   *  Constant: '<S4>/Constant10'
   *  Constant: '<S4>/Constant3'
   *  Constant: '<S4>/Constant6'
   *  Constant: '<S4>/Constant7'
   *  Constant: '<S4>/Constant8'
   *  Constant: '<S4>/Constant9'
   *  Integrator: '<S4>/Integrator'
   *  Integrator: '<S4>/Integrator1'
   *  Integrator: '<S4>/Integrator2'
   *  Integrator: '<S4>/Integrator3'
   *  MATLAB Function: '<S4>/MATLAB Function Acetogenesis'
   *  MATLAB Function: '<S4>/MATLAB Function Hidrolisis'
   */
  Svp_tmp = 21.5 / (1.0 + biomasa_X.Integrator_CSTATE_i);
  Svp_tmp_0 = (real_T)rtb_Step / 20.0;
  biomasa_B.Svp = (biomasa_ConstB.Sum * 6.97 * biomasa_X.Integrator2_CSTATE_j /
                   Svp_tmp + (2.91 - biomasa_X.Integrator1_CSTATE_o) * Svp_tmp_0)
    - biomasa_ConstB.Sum * 31.8 * biomasa_X.Integrator3_CSTATE / (3.0 / (1.0 +
    biomasa_X.Integrator1_CSTATE_o));

  /* MATLAB Function: '<S4>/MATLAB Function Acetogenesis' incorporates:
   *  Constant: '<S4>/Constant12'
   *  Constant: '<S4>/Constant16'
   *  Constant: '<S4>/Constant3'
   *  Integrator: '<S4>/Integrator2'
   *  MATLAB Function: '<S4>/MATLAB Function metanogenesis'
   */
  Xacidp_tmp = (real_T)rtb_Step / 98.2;
  biomasa_B.Xacidp = ((biomasa_ConstB.Sum / Svp_tmp - 0.02) - Xacidp_tmp) *
    biomasa_X.Integrator2_CSTATE_j;

  /* MATLAB Function: '<S4>/MATLAB Function Hidrolisis' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Constant: '<S4>/Constant5'
   *  Integrator: '<S4>/Integrator'
   *  Integrator: '<S4>/Integrator2'
   */
  biomasa_B.Sbp = biomasa_ConstB.Sum * 9.66 * biomasa_X.Integrator2_CSTATE_j /
    Svp_tmp + (13.8 - biomasa_X.Integrator_CSTATE_i) * Svp_tmp_0;

  /* MATLAB Function: '<S4>/MATLAB Function metanogenesis' incorporates:
   *  Constant: '<S4>/Constant13'
   *  Integrator: '<S4>/Integrator3'
   */
  biomasa_B.Xmethp = ((biomasa_ConstB.Sum / rtb_phi - 0.02) - Xacidp_tmp) *
    biomasa_X.Integrator3_CSTATE;
  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* Product: '<S4>/Product3' incorporates:
     *  Constant: '<S4>/Constant23'
     */
    biomasa_B.Product3 = rtb_Add3 * 550.0;
  }

  /* TransportDelay: '<S4>/Turbine exhaust system delay' */
  {
    real_T **uBuffer = (real_T**)
      &biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.04;
    rtb_ComplextoMagnitudeAngle_o1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize,
      &biomasa_DW.Turbineexhaustsystemdelay_IWORK.Last,
      biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail,
      biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Sum: '<S4>/Add4' incorporates:
   *  Constant: '<S4>/Constant24'
   *  Constant: '<S4>/Constant25'
   *  Constant: '<S4>/Constant26'
   *  Product: '<S4>/Product4'
   *  Sum: '<S4>/Sum2'
   */
  biomasa_B.Add4 = (biomasa_B.Product3 - (1.0 - rtb_ComplextoMagnitudeAngle_o1) *
                    700.0) + 950.0;

  /* TransferFcn: '<S4>/Rotation Shield' */
  rtb_ComplextoMagnitudeAngle_o1 = 0.0;
  rtb_ComplextoMagnitudeAngle_o1 += 0.013333333333333334 *
    biomasa_X.RotationShield_CSTATE;

  /* Sum: '<S4>/Add5' incorporates:
   *  Gain: '<S4>/Gain2'
   */
  biomasa_B.Add5 = 0.8 * biomasa_B.Add4 + rtb_ComplextoMagnitudeAngle_o1;

  /* Sin: '<S9>/sin(wt)' incorporates:
   *  Sin: '<S10>/sin(wt)'
   *  Sin: '<S9>/cos(wt)'
   */
  rtb_Add3 = 376.99111843077515 * paux;
  paux = sin(rtb_Add3) * 2.0;
  rtb_ComplextoMagnitudeAngle_o1 = paux;

  /* Product: '<S9>/Product' incorporates:
   *  Integrator: '<Root>/Integrator1'
   */
  biomasa_B.Product = biomasa_X.Integrator1_CSTATE *
    rtb_ComplextoMagnitudeAngle_o1;

  /* Sin: '<S9>/cos(wt)' incorporates:
   *  Sin: '<S10>/cos(wt)'
   */
  rtb_Add3 = sin(rtb_Add3 + 1.5707963267948966) * 2.0;
  rtb_ComplextoMagnitudeAngle_o1 = rtb_Add3;

  /* Product: '<S9>/Product1' incorporates:
   *  Integrator: '<Root>/Integrator1'
   */
  biomasa_B.Product1 = biomasa_X.Integrator1_CSTATE *
    rtb_ComplextoMagnitudeAngle_o1;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Gain: '<Root>/Gain3'
   *  Inport: '<Root>/Vload'
   *  Integrator: '<Root>/Integrator1'
   *  Integrator: '<Root>/Integrator2'
   *  Sum: '<Root>/Sum1'
   */
  biomasa_B.Gain2 = ((biomasa_X.Integrator1_CSTATE - biomasa_U.Vload) - 0.005 *
                     biomasa_X.Integrator2_CSTATE) * 28571.428571428572;

  /* Sin: '<S10>/sin(wt)' */
  rtb_ComplextoMagnitudeAngle_o1 = paux;

  /* Product: '<S10>/Product' incorporates:
   *  Integrator: '<Root>/Integrator2'
   */
  biomasa_B.Product_b = biomasa_X.Integrator2_CSTATE *
    rtb_ComplextoMagnitudeAngle_o1;

  /* Sin: '<S10>/cos(wt)' */
  rtb_ComplextoMagnitudeAngle_o1 = rtb_Add3;

  /* Product: '<S10>/Product1' incorporates:
   *  Integrator: '<Root>/Integrator2'
   */
  biomasa_B.Product1_n = biomasa_X.Integrator2_CSTATE *
    rtb_ComplextoMagnitudeAngle_o1;

  /* Integrator: '<S14>/integrator' */
  rtb_integrator = biomasa_X.integrator_CSTATE;

  /* TransportDelay: '<S14>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.TransportDelay_IWORK.CircularBufSize,
      &biomasa_DW.TransportDelay_IWORK.Last,
      biomasa_DW.TransportDelay_IWORK.Tail,
      biomasa_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Clock: '<S14>/Clock' */
  rtb_ComplextoMagnitudeAngle_o1 = biomasa_M->Timing.t[0];
  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* Memory: '<S14>/Memory' */
    biomasa_B.Memory = biomasa_DW.Memory_PreviousInput;
  }

  /* Switch: '<S14>/Switch' incorporates:
   *  Constant: '<S14>/K1'
   *  Gain: '<S14>/Gain'
   *  RelationalOperator: '<S14>/Relational Operator'
   *  Sum: '<S14>/Sum'
   */
  if (rtb_ComplextoMagnitudeAngle_o1 >= 0.016666666666666666) {
    biomasa_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
  } else {
    biomasa_B.Switch = biomasa_B.Memory;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Integrator: '<S13>/integrator' */
  rtb_integrator_f = biomasa_X.integrator_CSTATE_d;

  /* TransportDelay: '<S13>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_g = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.TransportDelay_IWORK_g.CircularBufSize,
      &biomasa_DW.TransportDelay_IWORK_g.Last,
      biomasa_DW.TransportDelay_IWORK_g.Tail,
      biomasa_DW.TransportDelay_IWORK_g.Head,
      0.0,
      0,
      0);
  }

  /* Clock: '<S13>/Clock' */
  rtb_ComplextoMagnitudeAngle_o1 = biomasa_M->Timing.t[0];
  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* Memory: '<S13>/Memory' */
    biomasa_B.Memory_h = biomasa_DW.Memory_PreviousInput_p;
  }

  /* Switch: '<S13>/Switch' incorporates:
   *  Constant: '<S13>/K1'
   *  Gain: '<S13>/Gain'
   *  RelationalOperator: '<S13>/Relational Operator'
   *  Sum: '<S13>/Sum'
   */
  if (rtb_ComplextoMagnitudeAngle_o1 >= 0.016666666666666666) {
    biomasa_B.Switch_l = (rtb_integrator_f - rtb_TransportDelay_g) * 60.0;
  } else {
    biomasa_B.Switch_l = biomasa_B.Memory_h;
  }

  /* End of Switch: '<S13>/Switch' */

  /* ComplexToMagnitudeAngle: '<S9>/Complex to Magnitude-Angle' incorporates:
   *  RealImagToComplex: '<S9>/Real-Imag to Complex'
   */
  rtb_ComplextoMagnitudeAngle_o1 = rt_hypotd_snf(biomasa_B.Switch,
    biomasa_B.Switch_l);

  /* Integrator: '<S18>/integrator' */
  rtb_integrator_g = biomasa_X.integrator_CSTATE_p;

  /* TransportDelay: '<S18>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_d = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.TransportDelay_IWORK_e.CircularBufSize,
      &biomasa_DW.TransportDelay_IWORK_e.Last,
      biomasa_DW.TransportDelay_IWORK_e.Tail,
      biomasa_DW.TransportDelay_IWORK_e.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* Memory: '<S18>/Memory' */
    biomasa_B.Memory_l = biomasa_DW.Memory_PreviousInput_a;
  }

  /* Switch: '<S18>/Switch' incorporates:
   *  Clock: '<S18>/Clock'
   *  Constant: '<S18>/K1'
   *  Gain: '<S18>/Gain'
   *  RelationalOperator: '<S18>/Relational Operator'
   *  Sum: '<S18>/Sum'
   */
  if (biomasa_M->Timing.t[0] >= 0.016666666666666666) {
    biomasa_B.Switch_n = (rtb_integrator_g - rtb_TransportDelay_d) * 60.0;
  } else {
    biomasa_B.Switch_n = biomasa_B.Memory_l;
  }

  /* End of Switch: '<S18>/Switch' */

  /* Integrator: '<S17>/integrator' */
  rtb_integrator_k = biomasa_X.integrator_CSTATE_e;

  /* TransportDelay: '<S17>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_j = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.TransportDelay_IWORK_c.CircularBufSize,
      &biomasa_DW.TransportDelay_IWORK_c.Last,
      biomasa_DW.TransportDelay_IWORK_c.Tail,
      biomasa_DW.TransportDelay_IWORK_c.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(biomasa_M)) {
    /* Memory: '<S17>/Memory' */
    biomasa_B.Memory_m = biomasa_DW.Memory_PreviousInput_f;
  }

  /* Switch: '<S17>/Switch' incorporates:
   *  Clock: '<S17>/Clock'
   *  Constant: '<S17>/K1'
   *  Gain: '<S17>/Gain'
   *  RelationalOperator: '<S17>/Relational Operator'
   *  Sum: '<S17>/Sum'
   */
  if (biomasa_M->Timing.t[0] >= 0.016666666666666666) {
    biomasa_B.Switch_d = (rtb_integrator_k - rtb_TransportDelay_j) * 60.0;
  } else {
    biomasa_B.Switch_d = biomasa_B.Memory_m;
  }

  /* End of Switch: '<S17>/Switch' */

  /* Gain: '<S3>/Gain1' incorporates:
   *  ComplexToMagnitudeAngle: '<S10>/Complex to Magnitude-Angle'
   *  Product: '<S3>/Product'
   *  RealImagToComplex: '<S10>/Real-Imag to Complex'
   */
  paux = rtb_ComplextoMagnitudeAngle_o1 * rt_hypotd_snf(biomasa_B.Switch_n,
    biomasa_B.Switch_d) * 0.5;

  /* Gain: '<S3>/Deg->Rad' incorporates:
   *  ComplexToMagnitudeAngle: '<S10>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S9>/Complex to Magnitude-Angle'
   *  Gain: '<S10>/Rad->Deg.'
   *  Gain: '<S9>/Rad->Deg.'
   *  RealImagToComplex: '<S10>/Real-Imag to Complex'
   *  RealImagToComplex: '<S9>/Real-Imag to Complex'
   *  Sum: '<S3>/Sum'
   */
  rtb_phi = (57.295779513082323 * rt_atan2d_snf(biomasa_B.Switch_l,
              biomasa_B.Switch) - 57.295779513082323 * rt_atan2d_snf
             (biomasa_B.Switch_d, biomasa_B.Switch_n)) * 0.017453292519943295;

  /* Product: '<S3>/Product1' incorporates:
   *  Trigonometry: '<S3>/Trigonometric Function2'
   */
  rtb_Add3 = paux * cos(rtb_phi);

  /* Product: '<S3>/Product3' incorporates:
   *  Trigonometry: '<S3>/Trigonometric Function2'
   */
  paux *= sin(rtb_phi);

  /* Outport: '<Root>/Potencia_bio' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function5'
   */
  biomasa_Y.Potencia_bio = sqrt(rtb_Add3 * rtb_Add3 + paux * paux);

  /* TransportDelay: '<S4>/Delay combustor' */
  {
    real_T **uBuffer = (real_T**)&biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[1];
    real_T simTime = biomasa_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.01;
    biomasa_B.Delaycombustor = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      biomasa_DW.Delaycombustor_IWORK.CircularBufSize,
      &biomasa_DW.Delaycombustor_IWORK.Last,
      biomasa_DW.Delaycombustor_IWORK.Tail,
      biomasa_DW.Delaycombustor_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* TransferFcn: '<S4>/Fuel system actuator' */
  rtb_Fuelsystemactuator = 0.0;
  rtb_Fuelsystemactuator += 25.0 * biomasa_X.Fuelsystemactuator_CSTATE;

  /* TransferFcn: '<S4>/Valve Positioner' */
  biomasa_B.ValvePositioner = 0.0;
  biomasa_B.ValvePositioner += 20.0 * biomasa_X.ValvePositioner_CSTATE;
  if (rtmIsMajorTimeStep(biomasa_M)) {
    if (rtmIsMajorTimeStep(biomasa_M)) {
      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)I' */
      biomasa_DW.Delay90zI_states = biomasa_DW.Delay90zI_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)V' */
      biomasa_DW.Delay90zV_states = biomasa_DW.Delay90zV_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/PR(z)' */
      biomasa_DW.PRz_states[1] = biomasa_DW.PRz_states[0];
      biomasa_DW.PRz_states[0] = biomasa_DW.PRz_tmp;

      /* Update for Delay: '<S4>/Delay' */
      biomasa_DW.Delay_DSTATE = biomasa_B.Torquemecnico;
    }

    /* Update for TransportDelay: '<S4>/Delay combustor1' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.Delaycombustor1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.Delaycombustor1_PWORK.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.Delaycombustor1_IWORK.Head =
        ((biomasa_DW.Delaycombustor1_IWORK.Head <
          (biomasa_DW.Delaycombustor1_IWORK.CircularBufSize-1)) ?
         (biomasa_DW.Delaycombustor1_IWORK.Head+1) : 0);
      if (biomasa_DW.Delaycombustor1_IWORK.Head ==
          biomasa_DW.Delaycombustor1_IWORK.Tail) {
        biomasa_DW.Delaycombustor1_IWORK.Tail =
          ((biomasa_DW.Delaycombustor1_IWORK.Tail <
            (biomasa_DW.Delaycombustor1_IWORK.CircularBufSize-1)) ?
           (biomasa_DW.Delaycombustor1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.Delaycombustor1_IWORK.Head] = simTime;
      (*uBuffer)[biomasa_DW.Delaycombustor1_IWORK.Head] = biomasa_B.y;
    }

    /* Update for TransportDelay: '<S4>/Turbine exhaust system delay' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head =
        ((biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head <
          (biomasa_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize-1)) ?
         (biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head+1) : 0);
      if (biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head ==
          biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail) {
        biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail =
          ((biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail <
            (biomasa_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize-1)) ?
           (biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head] = simTime;
      (*uBuffer)[biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head] =
        biomasa_B.Delaycombustor;
    }

    /* Update for TransportDelay: '<S14>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.TransportDelay_IWORK.Head =
        ((biomasa_DW.TransportDelay_IWORK.Head <
          (biomasa_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (biomasa_DW.TransportDelay_IWORK.Head+1) : 0);
      if (biomasa_DW.TransportDelay_IWORK.Head ==
          biomasa_DW.TransportDelay_IWORK.Tail) {
        biomasa_DW.TransportDelay_IWORK.Tail =
          ((biomasa_DW.TransportDelay_IWORK.Tail <
            (biomasa_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (biomasa_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[biomasa_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(biomasa_M)) {
      /* Update for Memory: '<S14>/Memory' */
      biomasa_DW.Memory_PreviousInput = biomasa_B.Switch;
    }

    /* Update for TransportDelay: '<S13>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.TransportDelay_IWORK_g.Head =
        ((biomasa_DW.TransportDelay_IWORK_g.Head <
          (biomasa_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
         (biomasa_DW.TransportDelay_IWORK_g.Head+1) : 0);
      if (biomasa_DW.TransportDelay_IWORK_g.Head ==
          biomasa_DW.TransportDelay_IWORK_g.Tail) {
        biomasa_DW.TransportDelay_IWORK_g.Tail =
          ((biomasa_DW.TransportDelay_IWORK_g.Tail <
            (biomasa_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
           (biomasa_DW.TransportDelay_IWORK_g.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.TransportDelay_IWORK_g.Head] = simTime;
      (*uBuffer)[biomasa_DW.TransportDelay_IWORK_g.Head] = rtb_integrator_f;
    }

    if (rtmIsMajorTimeStep(biomasa_M)) {
      /* Update for Memory: '<S13>/Memory' */
      biomasa_DW.Memory_PreviousInput_p = biomasa_B.Switch_l;
    }

    /* Update for TransportDelay: '<S18>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.TransportDelay_IWORK_e.Head =
        ((biomasa_DW.TransportDelay_IWORK_e.Head <
          (biomasa_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
         (biomasa_DW.TransportDelay_IWORK_e.Head+1) : 0);
      if (biomasa_DW.TransportDelay_IWORK_e.Head ==
          biomasa_DW.TransportDelay_IWORK_e.Tail) {
        biomasa_DW.TransportDelay_IWORK_e.Tail =
          ((biomasa_DW.TransportDelay_IWORK_e.Tail <
            (biomasa_DW.TransportDelay_IWORK_e.CircularBufSize-1)) ?
           (biomasa_DW.TransportDelay_IWORK_e.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.TransportDelay_IWORK_e.Head] = simTime;
      (*uBuffer)[biomasa_DW.TransportDelay_IWORK_e.Head] = rtb_integrator_g;
    }

    if (rtmIsMajorTimeStep(biomasa_M)) {
      /* Update for Memory: '<S18>/Memory' */
      biomasa_DW.Memory_PreviousInput_a = biomasa_B.Switch_n;
    }

    /* Update for TransportDelay: '<S17>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.TransportDelay_IWORK_c.Head =
        ((biomasa_DW.TransportDelay_IWORK_c.Head <
          (biomasa_DW.TransportDelay_IWORK_c.CircularBufSize-1)) ?
         (biomasa_DW.TransportDelay_IWORK_c.Head+1) : 0);
      if (biomasa_DW.TransportDelay_IWORK_c.Head ==
          biomasa_DW.TransportDelay_IWORK_c.Tail) {
        biomasa_DW.TransportDelay_IWORK_c.Tail =
          ((biomasa_DW.TransportDelay_IWORK_c.Tail <
            (biomasa_DW.TransportDelay_IWORK_c.CircularBufSize-1)) ?
           (biomasa_DW.TransportDelay_IWORK_c.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.TransportDelay_IWORK_c.Head] = simTime;
      (*uBuffer)[biomasa_DW.TransportDelay_IWORK_c.Head] = rtb_integrator_k;
    }

    if (rtmIsMajorTimeStep(biomasa_M)) {
      /* Update for Memory: '<S17>/Memory' */
      biomasa_DW.Memory_PreviousInput_f = biomasa_B.Switch_d;
    }

    /* Update for TransportDelay: '<S4>/Delay combustor' */
    {
      real_T **uBuffer = (real_T**)
        &biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[1];
      real_T simTime = biomasa_M->Timing.t[0];
      biomasa_DW.Delaycombustor_IWORK.Head =
        ((biomasa_DW.Delaycombustor_IWORK.Head <
          (biomasa_DW.Delaycombustor_IWORK.CircularBufSize-1)) ?
         (biomasa_DW.Delaycombustor_IWORK.Head+1) : 0);
      if (biomasa_DW.Delaycombustor_IWORK.Head ==
          biomasa_DW.Delaycombustor_IWORK.Tail) {
        biomasa_DW.Delaycombustor_IWORK.Tail =
          ((biomasa_DW.Delaycombustor_IWORK.Tail <
            (biomasa_DW.Delaycombustor_IWORK.CircularBufSize-1)) ?
           (biomasa_DW.Delaycombustor_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[biomasa_DW.Delaycombustor_IWORK.Head] = simTime;
      (*uBuffer)[biomasa_DW.Delaycombustor_IWORK.Head] = rtb_Fuelsystemactuator;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(biomasa_M)) {
    rt_ertODEUpdateContinuousStates(&biomasa_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++biomasa_M->Timing.clockTick0;
    biomasa_M->Timing.t[0] = rtsiGetSolverStopTime(&biomasa_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      biomasa_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void biomasa_derivatives(void)
{
  XDot_biomasa_T *_rtXdot;
  _rtXdot = ((XDot_biomasa_T *) biomasa_M->derivs);

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
  _rtXdot->Hw1_CSTATE[0] += -341.08603071128289 * biomasa_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[0] += -178.02459475242631 * biomasa_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[1] += 178.0245947524264 * biomasa_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[2] += 199.58239979893239 * biomasa_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[2] += -247.76277465378331 * biomasa_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[2] += -199.58239979893239 * biomasa_X.Hw1_CSTATE[3];
  _rtXdot->Hw1_CSTATE[3] += 199.58239979893244 * biomasa_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[0] += 188.49555921538757 * biomasa_B.q;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] += -341.08603071128289 * biomasa_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += -178.02459475242631 * biomasa_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[1] += 178.0245947524264 * biomasa_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[2] += 199.58239979893239 * biomasa_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[2] += -247.76277465378331 * biomasa_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[2] += -199.58239979893239 * biomasa_X.Hw6_CSTATE[3];
  _rtXdot->Hw6_CSTATE[3] += 199.58239979893244 * biomasa_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[0] += 188.49555921538757 * biomasa_B.p;

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = biomasa_B.Gain2;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = biomasa_B.Gain1;

  /* Derivatives for TransferFcn: '<S4>/Compresor' */
  _rtXdot->Compresor_CSTATE = 0.0;
  _rtXdot->Compresor_CSTATE += -5.0 * biomasa_X.Compresor_CSTATE;
  _rtXdot->Compresor_CSTATE += biomasa_B.Delaycombustor;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = biomasa_B.Gain;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -3.0 * biomasa_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += biomasa_B.Sum1;

  /* Derivatives for TransferFcn: '<S4>/thermo couple' */
  _rtXdot->thermocouple_CSTATE = 0.0;
  _rtXdot->thermocouple_CSTATE += -0.4 * biomasa_X.thermocouple_CSTATE;
  _rtXdot->thermocouple_CSTATE += biomasa_B.Add5;

  /* Derivatives for TransferFcn: '<S4>/Temp Control' */
  _rtXdot->TempControl_CSTATE = 0.0;
  _rtXdot->TempControl_CSTATE += -0.0 * biomasa_X.TempControl_CSTATE;
  _rtXdot->TempControl_CSTATE += biomasa_B.Sum3;

  /* Derivatives for Integrator: '<S4>/Integrator3' */
  _rtXdot->Integrator3_CSTATE = biomasa_B.Xmethp;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_o = biomasa_B.Svp;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_i = biomasa_B.Sbp;

  /* Derivatives for Integrator: '<S4>/Integrator2' */
  _rtXdot->Integrator2_CSTATE_j = biomasa_B.Xacidp;

  /* Derivatives for TransferFcn: '<S4>/Rotation Shield' */
  _rtXdot->RotationShield_CSTATE = 0.0;
  _rtXdot->RotationShield_CSTATE += -0.066666666666666666 *
    biomasa_X.RotationShield_CSTATE;
  _rtXdot->RotationShield_CSTATE += biomasa_B.Add4;

  /* Derivatives for Integrator: '<S14>/integrator' */
  _rtXdot->integrator_CSTATE = biomasa_B.Product;

  /* Derivatives for Integrator: '<S13>/integrator' */
  _rtXdot->integrator_CSTATE_d = biomasa_B.Product1;

  /* Derivatives for Integrator: '<S18>/integrator' */
  _rtXdot->integrator_CSTATE_p = biomasa_B.Product_b;

  /* Derivatives for Integrator: '<S17>/integrator' */
  _rtXdot->integrator_CSTATE_e = biomasa_B.Product1_n;

  /* Derivatives for TransferFcn: '<S4>/Fuel system actuator' */
  _rtXdot->Fuelsystemactuator_CSTATE = 0.0;
  _rtXdot->Fuelsystemactuator_CSTATE += -25.0 *
    biomasa_X.Fuelsystemactuator_CSTATE;
  _rtXdot->Fuelsystemactuator_CSTATE += biomasa_B.ValvePositioner;

  /* Derivatives for TransferFcn: '<S4>/Valve Positioner' */
  _rtXdot->ValvePositioner_CSTATE = 0.0;
  _rtXdot->ValvePositioner_CSTATE += -20.0 * biomasa_X.ValvePositioner_CSTATE;
  _rtXdot->ValvePositioner_CSTATE += biomasa_B.Add;
}

/* Model initialize function */
void biomasa_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)biomasa_M, 0,
                sizeof(RT_MODEL_biomasa_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&biomasa_M->solverInfo, &biomasa_M->Timing.simTimeStep);
    rtsiSetTPtr(&biomasa_M->solverInfo, &rtmGetTPtr(biomasa_M));
    rtsiSetStepSizePtr(&biomasa_M->solverInfo, &biomasa_M->Timing.stepSize0);
    rtsiSetdXPtr(&biomasa_M->solverInfo, &biomasa_M->derivs);
    rtsiSetContStatesPtr(&biomasa_M->solverInfo, (real_T **)
                         &biomasa_M->contStates);
    rtsiSetNumContStatesPtr(&biomasa_M->solverInfo,
      &biomasa_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&biomasa_M->solverInfo,
      &biomasa_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&biomasa_M->solverInfo,
      &biomasa_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&biomasa_M->solverInfo,
      &biomasa_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&biomasa_M->solverInfo, (&rtmGetErrorStatus(biomasa_M)));
    rtsiSetRTModelPtr(&biomasa_M->solverInfo, biomasa_M);
  }

  rtsiSetSimTimeStep(&biomasa_M->solverInfo, MAJOR_TIME_STEP);
  biomasa_M->intgData.deltaY= biomasa_M->OdeDeltaY;
  biomasa_M->intgData.f[0] = biomasa_M->odeF[0];
  biomasa_M->intgData.f[1] = biomasa_M->odeF[1];
  biomasa_M->intgData.f[2] = biomasa_M->odeF[2];
  biomasa_M->intgData.f[3] = biomasa_M->odeF[3];
  biomasa_M->intgData.f[4] = biomasa_M->odeF[4];
  biomasa_M->intgData.f[5] = biomasa_M->odeF[5];
  biomasa_M->intgData.f[6] = biomasa_M->odeF[6];
  biomasa_M->intgData.f[7] = biomasa_M->odeF[7];
  biomasa_M->intgData.f[8] = biomasa_M->odeF[8];
  biomasa_M->intgData.f[9] = biomasa_M->odeF[9];
  biomasa_M->intgData.f[10] = biomasa_M->odeF[10];
  biomasa_M->intgData.f[11] = biomasa_M->odeF[11];
  biomasa_M->intgData.f[12] = biomasa_M->odeF[12];
  biomasa_M->intgData.x0 = biomasa_M->odeX0;
  biomasa_M->contStates = ((X_biomasa_T *) &biomasa_X);
  rtsiSetSolverData(&biomasa_M->solverInfo, (void *)&biomasa_M->intgData);
  rtsiSetSolverName(&biomasa_M->solverInfo,"ode8");
  rtmSetTPtr(biomasa_M, &biomasa_M->Timing.tArray[0]);
  biomasa_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &biomasa_B), 0,
                sizeof(B_biomasa_T));

  /* states (continuous) */
  {
    (void) memset((void *)&biomasa_X, 0,
                  sizeof(X_biomasa_T));
  }

  /* states (dwork) */
  (void) memset((void *)&biomasa_DW, 0,
                sizeof(DW_biomasa_T));

  /* external inputs */
  (void)memset((void *)&biomasa_U, 0, sizeof(ExtU_biomasa_T));

  /* external outputs */
  (void) memset((void *)&biomasa_Y, 0,
                sizeof(ExtY_biomasa_T));

  /* Start for TransportDelay: '<S4>/Delay combustor1' */
  {
    real_T *pBuffer = &biomasa_DW.Delaycombustor1_RWORK.TUbufferArea[0];
    biomasa_DW.Delaycombustor1_IWORK.Tail = 0;
    biomasa_DW.Delaycombustor1_IWORK.Head = 0;
    biomasa_DW.Delaycombustor1_IWORK.Last = 0;
    biomasa_DW.Delaycombustor1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = biomasa_M->Timing.t[0];
    biomasa_DW.Delaycombustor1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.Delaycombustor1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S4>/Turbine exhaust system delay' */
  {
    real_T *pBuffer = &biomasa_DW.Turbineexhaustsystemdelay_RWORK.TUbufferArea[0];
    biomasa_DW.Turbineexhaustsystemdelay_IWORK.Tail = 0;
    biomasa_DW.Turbineexhaustsystemdelay_IWORK.Head = 0;
    biomasa_DW.Turbineexhaustsystemdelay_IWORK.Last = 0;
    biomasa_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = biomasa_M->Timing.t[0];
    biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    biomasa_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S14>/Transport Delay' */
  {
    real_T *pBuffer = &biomasa_DW.TransportDelay_RWORK.TUbufferArea[0];
    biomasa_DW.TransportDelay_IWORK.Tail = 0;
    biomasa_DW.TransportDelay_IWORK.Head = 0;
    biomasa_DW.TransportDelay_IWORK.Last = 0;
    biomasa_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = biomasa_M->Timing.t[0];
    biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S13>/Transport Delay' */
  {
    real_T *pBuffer = &biomasa_DW.TransportDelay_RWORK_k.TUbufferArea[0];
    biomasa_DW.TransportDelay_IWORK_g.Tail = 0;
    biomasa_DW.TransportDelay_IWORK_g.Head = 0;
    biomasa_DW.TransportDelay_IWORK_g.Last = 0;
    biomasa_DW.TransportDelay_IWORK_g.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = biomasa_M->Timing.t[0];
    biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.TransportDelay_PWORK_p.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S18>/Transport Delay' */
  {
    real_T *pBuffer = &biomasa_DW.TransportDelay_RWORK_o.TUbufferArea[0];
    biomasa_DW.TransportDelay_IWORK_e.Tail = 0;
    biomasa_DW.TransportDelay_IWORK_e.Head = 0;
    biomasa_DW.TransportDelay_IWORK_e.Last = 0;
    biomasa_DW.TransportDelay_IWORK_e.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = biomasa_M->Timing.t[0];
    biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.TransportDelay_PWORK_f.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S17>/Transport Delay' */
  {
    real_T *pBuffer = &biomasa_DW.TransportDelay_RWORK_g.TUbufferArea[0];
    biomasa_DW.TransportDelay_IWORK_c.Tail = 0;
    biomasa_DW.TransportDelay_IWORK_c.Head = 0;
    biomasa_DW.TransportDelay_IWORK_c.Last = 0;
    biomasa_DW.TransportDelay_IWORK_c.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = biomasa_M->Timing.t[0];
    biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.TransportDelay_PWORK_j.TUbufferPtrs[1] = (void *) &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S4>/Delay combustor' */
  {
    real_T *pBuffer = &biomasa_DW.Delaycombustor_RWORK.TUbufferArea[0];
    biomasa_DW.Delaycombustor_IWORK.Tail = 0;
    biomasa_DW.Delaycombustor_IWORK.Head = 0;
    biomasa_DW.Delaycombustor_IWORK.Last = 0;
    biomasa_DW.Delaycombustor_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = biomasa_M->Timing.t[0];
    biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    biomasa_DW.Delaycombustor_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
  }

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  biomasa_X.Hw1_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  biomasa_X.Hw6_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  biomasa_X.Hw1_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  biomasa_X.Hw6_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  biomasa_X.Hw1_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  biomasa_X.Hw6_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  biomasa_X.Hw1_CSTATE[3] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  biomasa_X.Hw6_CSTATE[3] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator2' */
  biomasa_X.Integrator2_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  biomasa_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Compresor' */
  biomasa_X.Compresor_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  biomasa_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn' */
  biomasa_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/thermo couple' */
  biomasa_X.thermocouple_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Temp Control' */
  biomasa_X.TempControl_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator3' */
  biomasa_X.Integrator3_CSTATE = 0.35;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' */
  biomasa_X.Integrator1_CSTATE_o = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  biomasa_X.Integrator_CSTATE_i = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator2' */
  biomasa_X.Integrator2_CSTATE_j = 1.2;

  /* InitializeConditions for TransferFcn: '<S4>/Rotation Shield' */
  biomasa_X.RotationShield_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S14>/integrator' */
  biomasa_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S14>/Memory' */
  biomasa_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S13>/integrator' */
  biomasa_X.integrator_CSTATE_d = 0.0;

  /* InitializeConditions for Integrator: '<S18>/integrator' */
  biomasa_X.integrator_CSTATE_p = 0.0;

  /* InitializeConditions for Memory: '<S18>/Memory' */
  biomasa_DW.Memory_PreviousInput_a = 1.0;

  /* InitializeConditions for Integrator: '<S17>/integrator' */
  biomasa_X.integrator_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Fuel system actuator' */
  biomasa_X.Fuelsystemactuator_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Valve Positioner' */
  biomasa_X.ValvePositioner_CSTATE = 0.0;
}

/* Model terminate function */
void biomasa_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: cargaRLC_variable.c
 *
 * Code generated for Simulink model 'cargaRLC_variable'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Wed Feb  6 16:17:24 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "cargaRLC_variable.h"
#include "cargaRLC_variable_private.h"

/* Block signals (default storage) */
B_cargaRLC_variable_T cargaRLC_variable_B;

/* Continuous states */
X_cargaRLC_variable_T cargaRLC_variable_X;

/* Block states (default storage) */
DW_cargaRLC_variable_T cargaRLC_variable_DW;

/* External inputs (root inport signals with default storage) */
ExtU_cargaRLC_variable_T cargaRLC_variable_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_cargaRLC_variable_T cargaRLC_variable_Y;

//-------Funciones para asignar entradas-------------
void set_i1(double i1){
	cargaRLC_variable_U.i1=i1;
}	
void set_i2(double i2){
	cargaRLC_variable_U.i2=i2;
}
void set_i3(double i3){
	cargaRLC_variable_U.i3=i3;
}

void set_P(double P){
    cargaRLC_variable_U.P=P;
}

void set_Q(double Q){
    cargaRLC_variable_U.Q=Q;
}

//-----Funciones para obtener valores de las salidas-------
double get_Pm(void){
	//printf("La potencia P medida es: %3.2f \n",carga_sf_Y.Pm);
	return cargaRLC_variable_Y.Pm;
}

double get_Qm(void){
	return cargaRLC_variable_Y.Qm;
}

double get_Vload(void){
	return cargaRLC_variable_Y.Vload;
}

/* Real-time model */
RT_MODEL_cargaRLC_variable_T cargaRLC_variable_M_;
RT_MODEL_cargaRLC_variable_T *const cargaRLC_variable_M = &cargaRLC_variable_M_;

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
  cargaRLC_variable_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  cargaRLC_variable_step();
  cargaRLC_variable_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  cargaRLC_variable_step();
  cargaRLC_variable_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  cargaRLC_variable_step();
  cargaRLC_variable_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
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
void cargaRLC_variable_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_i;
  real_T rtb_TransportDelay_p;
  real_T rtb_integrator_o;
  real_T rtb_TransportDelay_b;
  real_T rtb_integrator_d;
  real_T rtb_TransportDelay_e;
  real_T L;
  real_T rtb_Gain1;
  real_T rtb_phi;
  real_T L_tmp;
  real_T dv_tmp;
  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&cargaRLC_variable_M->solverInfo,
                          ((cargaRLC_variable_M->Timing.clockTick0+1)*
      cargaRLC_variable_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(cargaRLC_variable_M)) {
    cargaRLC_variable_M->Timing.t[0] = rtsiGetT(&cargaRLC_variable_M->solverInfo);
  }

  /* Integrator: '<S10>/integrator' */
  rtb_integrator = cargaRLC_variable_X.integrator_CSTATE;

  /* TransportDelay: '<S10>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = cargaRLC_variable_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      cargaRLC_variable_DW.TransportDelay_IWORK.CircularBufSize,
      &cargaRLC_variable_DW.TransportDelay_IWORK.Last,
      cargaRLC_variable_DW.TransportDelay_IWORK.Tail,
      cargaRLC_variable_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* Memory: '<S10>/Memory' */
    cargaRLC_variable_B.Memory = cargaRLC_variable_DW.Memory_PreviousInput;
  }

  /* Switch: '<S10>/Switch' incorporates:
   *  Clock: '<S10>/Clock'
   *  Constant: '<S10>/K1'
   *  Gain: '<S10>/Gain'
   *  RelationalOperator: '<S10>/Relational Operator'
   *  Sum: '<S10>/Sum'
   */
  if (cargaRLC_variable_M->Timing.t[0] >= 0.016666666666666666) {
    cargaRLC_variable_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
  } else {
    cargaRLC_variable_B.Switch = cargaRLC_variable_B.Memory;
  }

  /* End of Switch: '<S10>/Switch' */

  /* Integrator: '<S9>/integrator' */
  rtb_integrator_i = cargaRLC_variable_X.integrator_CSTATE_a;

  /* TransportDelay: '<S9>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[1];
    real_T simTime = cargaRLC_variable_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_p = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      cargaRLC_variable_DW.TransportDelay_IWORK_h.CircularBufSize,
      &cargaRLC_variable_DW.TransportDelay_IWORK_h.Last,
      cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail,
      cargaRLC_variable_DW.TransportDelay_IWORK_h.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* Memory: '<S9>/Memory' */
    cargaRLC_variable_B.Memory_j = cargaRLC_variable_DW.Memory_PreviousInput_n;
  }

  /* Switch: '<S9>/Switch' incorporates:
   *  Clock: '<S9>/Clock'
   *  Constant: '<S9>/K1'
   *  Gain: '<S9>/Gain'
   *  RelationalOperator: '<S9>/Relational Operator'
   *  Sum: '<S9>/Sum'
   */
  if (cargaRLC_variable_M->Timing.t[0] >= 0.016666666666666666) {
    cargaRLC_variable_B.Switch_e = (rtb_integrator_i - rtb_TransportDelay_p) *
      60.0;
  } else {
    cargaRLC_variable_B.Switch_e = cargaRLC_variable_B.Memory_j;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Integrator: '<S14>/integrator' */
  rtb_integrator_o = cargaRLC_variable_X.integrator_CSTATE_g;

  /* TransportDelay: '<S14>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
    real_T simTime = cargaRLC_variable_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_b = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      cargaRLC_variable_DW.TransportDelay_IWORK_p.CircularBufSize,
      &cargaRLC_variable_DW.TransportDelay_IWORK_p.Last,
      cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail,
      cargaRLC_variable_DW.TransportDelay_IWORK_p.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* Memory: '<S14>/Memory' */
    cargaRLC_variable_B.Memory_c = cargaRLC_variable_DW.Memory_PreviousInput_i;
  }

  /* Switch: '<S14>/Switch' incorporates:
   *  Clock: '<S14>/Clock'
   *  Constant: '<S14>/K1'
   *  Gain: '<S14>/Gain'
   *  RelationalOperator: '<S14>/Relational Operator'
   *  Sum: '<S14>/Sum'
   */
  if (cargaRLC_variable_M->Timing.t[0] >= 0.016666666666666666) {
    cargaRLC_variable_B.Switch_ey = (rtb_integrator_o - rtb_TransportDelay_b) *
      60.0;
  } else {
    cargaRLC_variable_B.Switch_ey = cargaRLC_variable_B.Memory_c;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Integrator: '<S13>/integrator' */
  rtb_integrator_d = cargaRLC_variable_X.integrator_CSTATE_gj;

  /* TransportDelay: '<S13>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[1];
    real_T simTime = cargaRLC_variable_M->Timing.t[0];
    real_T tMinusDelay = simTime - (0.016666666666666666);
    rtb_TransportDelay_e = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      cargaRLC_variable_DW.TransportDelay_IWORK_g.CircularBufSize,
      &cargaRLC_variable_DW.TransportDelay_IWORK_g.Last,
      cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail,
      cargaRLC_variable_DW.TransportDelay_IWORK_g.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* Memory: '<S13>/Memory' */
    cargaRLC_variable_B.Memory_i = cargaRLC_variable_DW.Memory_PreviousInput_np;
  }

  /* Switch: '<S13>/Switch' incorporates:
   *  Clock: '<S13>/Clock'
   *  Constant: '<S13>/K1'
   *  Gain: '<S13>/Gain'
   *  RelationalOperator: '<S13>/Relational Operator'
   *  Sum: '<S13>/Sum'
   */
  if (cargaRLC_variable_M->Timing.t[0] >= 0.016666666666666666) {
    cargaRLC_variable_B.Switch_o = (rtb_integrator_d - rtb_TransportDelay_e) *
      60.0;
  } else {
    cargaRLC_variable_B.Switch_o = cargaRLC_variable_B.Memory_i;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Gain: '<S2>/Gain1' incorporates:
   *  ComplexToMagnitudeAngle: '<S5>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S6>/Complex to Magnitude-Angle'
   *  Product: '<S2>/Product'
   *  RealImagToComplex: '<S5>/Real-Imag to Complex'
   *  RealImagToComplex: '<S6>/Real-Imag to Complex'
   */
  rtb_Gain1 = rt_hypotd_snf(cargaRLC_variable_B.Switch,
    cargaRLC_variable_B.Switch_e) * rt_hypotd_snf(cargaRLC_variable_B.Switch_ey,
    cargaRLC_variable_B.Switch_o) * 0.5;

  /* Gain: '<S2>/Deg->Rad' incorporates:
   *  ComplexToMagnitudeAngle: '<S5>/Complex to Magnitude-Angle'
   *  ComplexToMagnitudeAngle: '<S6>/Complex to Magnitude-Angle'
   *  Gain: '<S5>/Rad->Deg.'
   *  Gain: '<S6>/Rad->Deg.'
   *  RealImagToComplex: '<S5>/Real-Imag to Complex'
   *  RealImagToComplex: '<S6>/Real-Imag to Complex'
   *  Sum: '<S2>/Sum'
   */
  rtb_phi = (57.295779513082323 * rt_atan2d_snf(cargaRLC_variable_B.Switch_e,
              cargaRLC_variable_B.Switch) - 57.295779513082323 * rt_atan2d_snf
             (cargaRLC_variable_B.Switch_o, cargaRLC_variable_B.Switch_ey)) *
    0.017453292519943295;

  /* Outport: '<Root>/Pm' incorporates:
   *  Product: '<S2>/Product1'
   *  Trigonometry: '<S2>/Trigonometric Function2'
   */
  cargaRLC_variable_Y.Pm = rtb_Gain1 * cos(rtb_phi);

  /* Outport: '<Root>/Qm' incorporates:
   *  Product: '<S2>/Product3'
   *  Trigonometry: '<S2>/Trigonometric Function2'
   */
  cargaRLC_variable_Y.Qm = rtb_Gain1 * sin(rtb_phi);

  /* Integrator: '<Root>/Integrator1' */
  cargaRLC_variable_B.Integrator1 = cargaRLC_variable_X.Integrator1_CSTATE;

  /* Outport: '<Root>/Vload' */
  cargaRLC_variable_Y.Vload = cargaRLC_variable_B.Integrator1;

  /* Sum: '<Root>/Sum6' incorporates:
   *  Inport: '<Root>/i1'
   *  Inport: '<Root>/i2'
   *  Inport: '<Root>/i3'
   */
  rtb_Gain1 = (cargaRLC_variable_U.i1 + cargaRLC_variable_U.i2) +
    cargaRLC_variable_U.i3;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/P'
   *  Inport: '<Root>/Q'
   *  Integrator: '<Root>/Integrator2'
   */
  rtb_phi = 14449.999999999998 / cargaRLC_variable_U.P;
  if (cargaRLC_variable_U.Q >= 0.0) {
    L = 14449.999999999998 / (490.08845396000771 * cargaRLC_variable_U.Q);
    L_tmp = 0.3 * cargaRLC_variable_U.Q / 5.4475216613247E+6;
  } else {
    L_tmp = fabs(cargaRLC_variable_U.Q);
    L = 14449.999999999998 / (113.09733552923254 * L_tmp);
    L_tmp = 1.3 * L_tmp / 5.4475216613247E+6;
  }

  dv_tmp = rtb_phi * L;
  cargaRLC_variable_B.dv = ((dv_tmp * rtb_Gain1 - L *
    cargaRLC_variable_B.Integrator1) - rtb_phi *
    cargaRLC_variable_X.Integrator2_CSTATE) / (dv_tmp * L_tmp);

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* Sin: '<S6>/sin(wt)' incorporates:
   *  Sin: '<S5>/sin(wt)'
   *  Sin: '<S6>/cos(wt)'
   */
  L = 376.99111843077515 * cargaRLC_variable_M->Timing.t[0];
  rtb_phi = sin(L) * 2.0;

  /* Product: '<S6>/Product' incorporates:
   *  Sin: '<S6>/sin(wt)'
   */
  cargaRLC_variable_B.Product = rtb_phi * rtb_Gain1;

  /* Sin: '<S6>/cos(wt)' incorporates:
   *  Sin: '<S5>/cos(wt)'
   */
  L = sin(L + 1.5707963267948966) * 2.0;

  /* Product: '<S6>/Product1' incorporates:
   *  Sin: '<S6>/cos(wt)'
   */
  cargaRLC_variable_B.Product1 = L * rtb_Gain1;

  /* Product: '<S5>/Product' */
  cargaRLC_variable_B.Product_f = rtb_phi * cargaRLC_variable_B.Integrator1;

  /* Product: '<S5>/Product1' */
  cargaRLC_variable_B.Product1_f = L * cargaRLC_variable_B.Integrator1;
  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    /* Update for TransportDelay: '<S10>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = cargaRLC_variable_M->Timing.t[0];
      cargaRLC_variable_DW.TransportDelay_IWORK.Head =
        ((cargaRLC_variable_DW.TransportDelay_IWORK.Head <
          (cargaRLC_variable_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (cargaRLC_variable_DW.TransportDelay_IWORK.Head+1) : 0);
      if (cargaRLC_variable_DW.TransportDelay_IWORK.Head ==
          cargaRLC_variable_DW.TransportDelay_IWORK.Tail) {
        cargaRLC_variable_DW.TransportDelay_IWORK.Tail =
          ((cargaRLC_variable_DW.TransportDelay_IWORK.Tail <
            (cargaRLC_variable_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (cargaRLC_variable_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK.Head] =
        rtb_integrator;
    }

    if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
      /* Update for Memory: '<S10>/Memory' */
      cargaRLC_variable_DW.Memory_PreviousInput = cargaRLC_variable_B.Switch;
    }

    /* Update for TransportDelay: '<S9>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[1];
      real_T simTime = cargaRLC_variable_M->Timing.t[0];
      cargaRLC_variable_DW.TransportDelay_IWORK_h.Head =
        ((cargaRLC_variable_DW.TransportDelay_IWORK_h.Head <
          (cargaRLC_variable_DW.TransportDelay_IWORK_h.CircularBufSize-1)) ?
         (cargaRLC_variable_DW.TransportDelay_IWORK_h.Head+1) : 0);
      if (cargaRLC_variable_DW.TransportDelay_IWORK_h.Head ==
          cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail) {
        cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail =
          ((cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail <
            (cargaRLC_variable_DW.TransportDelay_IWORK_h.CircularBufSize-1)) ?
           (cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail+1) : 0);
      }

      (*tBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_h.Head] = simTime;
      (*uBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_h.Head] =
        rtb_integrator_i;
    }

    if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
      /* Update for Memory: '<S9>/Memory' */
      cargaRLC_variable_DW.Memory_PreviousInput_n = cargaRLC_variable_B.Switch_e;
    }

    /* Update for TransportDelay: '<S14>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
      real_T simTime = cargaRLC_variable_M->Timing.t[0];
      cargaRLC_variable_DW.TransportDelay_IWORK_p.Head =
        ((cargaRLC_variable_DW.TransportDelay_IWORK_p.Head <
          (cargaRLC_variable_DW.TransportDelay_IWORK_p.CircularBufSize-1)) ?
         (cargaRLC_variable_DW.TransportDelay_IWORK_p.Head+1) : 0);
      if (cargaRLC_variable_DW.TransportDelay_IWORK_p.Head ==
          cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail) {
        cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail =
          ((cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail <
            (cargaRLC_variable_DW.TransportDelay_IWORK_p.CircularBufSize-1)) ?
           (cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail+1) : 0);
      }

      (*tBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_p.Head] = simTime;
      (*uBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_p.Head] =
        rtb_integrator_o;
    }

    if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
      /* Update for Memory: '<S14>/Memory' */
      cargaRLC_variable_DW.Memory_PreviousInput_i =
        cargaRLC_variable_B.Switch_ey;
    }

    /* Update for TransportDelay: '<S13>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[1];
      real_T simTime = cargaRLC_variable_M->Timing.t[0];
      cargaRLC_variable_DW.TransportDelay_IWORK_g.Head =
        ((cargaRLC_variable_DW.TransportDelay_IWORK_g.Head <
          (cargaRLC_variable_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
         (cargaRLC_variable_DW.TransportDelay_IWORK_g.Head+1) : 0);
      if (cargaRLC_variable_DW.TransportDelay_IWORK_g.Head ==
          cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail) {
        cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail =
          ((cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail <
            (cargaRLC_variable_DW.TransportDelay_IWORK_g.CircularBufSize-1)) ?
           (cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail+1) : 0);
      }

      (*tBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_g.Head] = simTime;
      (*uBuffer)[cargaRLC_variable_DW.TransportDelay_IWORK_g.Head] =
        rtb_integrator_d;
    }

    if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
      /* Update for Memory: '<S13>/Memory' */
      cargaRLC_variable_DW.Memory_PreviousInput_np =
        cargaRLC_variable_B.Switch_o;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(cargaRLC_variable_M)) {
    rt_ertODEUpdateContinuousStates(&cargaRLC_variable_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++cargaRLC_variable_M->Timing.clockTick0;
    cargaRLC_variable_M->Timing.t[0] = rtsiGetSolverStopTime
      (&cargaRLC_variable_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      cargaRLC_variable_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void cargaRLC_variable_derivatives(void)
{
  XDot_cargaRLC_variable_T *_rtXdot;
  _rtXdot = ((XDot_cargaRLC_variable_T *) cargaRLC_variable_M->derivs);

  /* Derivatives for Integrator: '<S10>/integrator' */
  _rtXdot->integrator_CSTATE = cargaRLC_variable_B.Product_f;

  /* Derivatives for Integrator: '<S9>/integrator' */
  _rtXdot->integrator_CSTATE_a = cargaRLC_variable_B.Product1_f;

  /* Derivatives for Integrator: '<S14>/integrator' */
  _rtXdot->integrator_CSTATE_g = cargaRLC_variable_B.Product;

  /* Derivatives for Integrator: '<S13>/integrator' */
  _rtXdot->integrator_CSTATE_gj = cargaRLC_variable_B.Product1;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = cargaRLC_variable_B.dv;

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = cargaRLC_variable_B.Integrator1;
}

/* Model initialize function */
void cargaRLC_variable_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)cargaRLC_variable_M, 0,
                sizeof(RT_MODEL_cargaRLC_variable_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&cargaRLC_variable_M->solverInfo,
                          &cargaRLC_variable_M->Timing.simTimeStep);
    rtsiSetTPtr(&cargaRLC_variable_M->solverInfo, &rtmGetTPtr
                (cargaRLC_variable_M));
    rtsiSetStepSizePtr(&cargaRLC_variable_M->solverInfo,
                       &cargaRLC_variable_M->Timing.stepSize0);
    rtsiSetdXPtr(&cargaRLC_variable_M->solverInfo, &cargaRLC_variable_M->derivs);
    rtsiSetContStatesPtr(&cargaRLC_variable_M->solverInfo, (real_T **)
                         &cargaRLC_variable_M->contStates);
    rtsiSetNumContStatesPtr(&cargaRLC_variable_M->solverInfo,
      &cargaRLC_variable_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&cargaRLC_variable_M->solverInfo,
      &cargaRLC_variable_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&cargaRLC_variable_M->solverInfo,
      &cargaRLC_variable_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&cargaRLC_variable_M->solverInfo,
      &cargaRLC_variable_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&cargaRLC_variable_M->solverInfo, (&rtmGetErrorStatus
      (cargaRLC_variable_M)));
    rtsiSetRTModelPtr(&cargaRLC_variable_M->solverInfo, cargaRLC_variable_M);
  }

  rtsiSetSimTimeStep(&cargaRLC_variable_M->solverInfo, MAJOR_TIME_STEP);
  cargaRLC_variable_M->intgData.y = cargaRLC_variable_M->odeY;
  cargaRLC_variable_M->intgData.f[0] = cargaRLC_variable_M->odeF[0];
  cargaRLC_variable_M->intgData.f[1] = cargaRLC_variable_M->odeF[1];
  cargaRLC_variable_M->intgData.f[2] = cargaRLC_variable_M->odeF[2];
  cargaRLC_variable_M->intgData.f[3] = cargaRLC_variable_M->odeF[3];
  cargaRLC_variable_M->contStates = ((X_cargaRLC_variable_T *)
    &cargaRLC_variable_X);
  rtsiSetSolverData(&cargaRLC_variable_M->solverInfo, (void *)
                    &cargaRLC_variable_M->intgData);
  rtsiSetSolverName(&cargaRLC_variable_M->solverInfo,"ode4");
  rtmSetTPtr(cargaRLC_variable_M, &cargaRLC_variable_M->Timing.tArray[0]);
  cargaRLC_variable_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &cargaRLC_variable_B), 0,
                sizeof(B_cargaRLC_variable_T));

  /* states (continuous) */
  {
    (void) memset((void *)&cargaRLC_variable_X, 0,
                  sizeof(X_cargaRLC_variable_T));
  }

  /* states (dwork) */
  (void) memset((void *)&cargaRLC_variable_DW, 0,
                sizeof(DW_cargaRLC_variable_T));

  /* external inputs */
  (void)memset((void *)&cargaRLC_variable_U, 0, sizeof(ExtU_cargaRLC_variable_T));

  /* external outputs */
  (void) memset((void *)&cargaRLC_variable_Y, 0,
                sizeof(ExtY_cargaRLC_variable_T));

  /* Start for TransportDelay: '<S10>/Transport Delay' */
  {
    real_T *pBuffer = &cargaRLC_variable_DW.TransportDelay_RWORK.TUbufferArea[0];
    cargaRLC_variable_DW.TransportDelay_IWORK.Tail = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK.Head = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK.Last = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = cargaRLC_variable_M->Timing.t[0];
    cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    cargaRLC_variable_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S9>/Transport Delay' */
  {
    real_T *pBuffer = &cargaRLC_variable_DW.TransportDelay_RWORK_n.TUbufferArea
      [0];
    cargaRLC_variable_DW.TransportDelay_IWORK_h.Tail = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_h.Head = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_h.Last = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_h.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = cargaRLC_variable_M->Timing.t[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_k.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S14>/Transport Delay' */
  {
    real_T *pBuffer = &cargaRLC_variable_DW.TransportDelay_RWORK_f.TUbufferArea
      [0];
    cargaRLC_variable_DW.TransportDelay_IWORK_p.Tail = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_p.Head = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_p.Last = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_p.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = cargaRLC_variable_M->Timing.t[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_f.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S13>/Transport Delay' */
  {
    real_T *pBuffer = &cargaRLC_variable_DW.TransportDelay_RWORK_h.TUbufferArea
      [0];
    cargaRLC_variable_DW.TransportDelay_IWORK_g.Tail = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_g.Head = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_g.Last = 0;
    cargaRLC_variable_DW.TransportDelay_IWORK_g.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = cargaRLC_variable_M->Timing.t[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    cargaRLC_variable_DW.TransportDelay_PWORK_b.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* InitializeConditions for Integrator: '<S10>/integrator' */
  cargaRLC_variable_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S10>/Memory' */
  cargaRLC_variable_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S9>/integrator' */
  cargaRLC_variable_X.integrator_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S14>/integrator' */
  cargaRLC_variable_X.integrator_CSTATE_g = 0.0;

  /* InitializeConditions for Memory: '<S14>/Memory' */
  cargaRLC_variable_DW.Memory_PreviousInput_i = 1.0;

  /* InitializeConditions for Integrator: '<S13>/integrator' */
  cargaRLC_variable_X.integrator_CSTATE_gj = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  cargaRLC_variable_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator2' */
  cargaRLC_variable_X.Integrator2_CSTATE = 0.0;
}

/* Model terminate function */
void cargaRLC_variable_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

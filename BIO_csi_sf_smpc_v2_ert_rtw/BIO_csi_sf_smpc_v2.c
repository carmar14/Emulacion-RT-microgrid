/*
 * File: BIO_csi_sf_smpc_v2.c
 *
 * Code generated for Simulink model 'BIO_csi_sf_smpc_v2'.
 *
 * Model version                  : 1.79
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Mon Sep 16 14:30:34 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BIO_csi_sf_smpc_v2.h"
#include "BIO_csi_sf_smpc_v2_private.h"

/* Block signals (default storage) */
B_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_B;

/* Continuous states */
X_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_X;

/* Block states (default storage) */
DW_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_DW;

/* External inputs (root inport signals with default storage) */
ExtU_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_Y;

/* Real-time model */
RT_MODEL_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_M_;
RT_MODEL_BIO_csi_sf_smpc_v2_T *const BIO_csi_sf_smpc_v2_M =
  &BIO_csi_sf_smpc_v2_M_;

//Funciones creadas por el programador set y get
//-------Funciones para asignar entradas-------------
/*
void set_Vdc_bio(double Vdc_bio){
	//printf("La accion 1 es: %3.2f \n",V_bio);
	BIO_csi_sf_smpc_U.Vdc=Vdc_bio;
	//printf("El voltaje es: %3.2f \n",BIO_csi_U.V_bio);
	}

*/
	
void set_Vload(double Vload){
	BIO_csi_sf_smpc_v2_U.Vload=Vload;
}

void set_Qref_bio(double Qref_bio){
	BIO_csi_sf_smpc_v2_U.Qrefb=Qref_bio;
	}
	
void set_Pref_bio(double Pref_bio){
	BIO_csi_sf_smpc_v2_U.Prefb=Pref_bio;
	}
	
//-----Funciones para obtener valores de las salidas-------
	
double get_I_bio(void){
	return BIO_csi_sf_smpc_v2_Y.i1;
	 
	}
	
double get_Pm(void){
	return BIO_csi_sf_smpc_v2_Y.pbio_meas;
	
}

double get_Qm(void){
	return BIO_csi_sf_smpc_v2_Y.qbio_meas;
	
}

double get_duty_cycle(void) {
    return BIO_csi_sf_smpc_v2_Y.duty_cycle; 
}

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
  int_T nXc = 20;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  BIO_csi_sf_smpc_v2_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  BIO_csi_sf_smpc_v2_step();
  BIO_csi_sf_smpc_v2_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  BIO_csi_sf_smpc_v2_step();
  BIO_csi_sf_smpc_v2_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  BIO_csi_sf_smpc_v2_step();
  BIO_csi_sf_smpc_v2_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void BIO_csi_sf_smpc_v2_step(void)
{
  /* local block i/o variables */
  real_T rtb_Torquemecnico;
  real_T rtb_Fuelsystemactuator;
  real_T rtb_Delaycombustor2;
  real_T rtb_RotationShield;
  real_T det;
  real_T rtb_PRz;
  real_T rtb_Divide;
  real_T TransferFcn;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&BIO_csi_sf_smpc_v2_M->solverInfo,
                          ((BIO_csi_sf_smpc_v2_M->Timing.clockTick0+1)*
      BIO_csi_sf_smpc_v2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    BIO_csi_sf_smpc_v2_M->Timing.t[0] = rtsiGetT
      (&BIO_csi_sf_smpc_v2_M->solverInfo);
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  TransferFcn = 25.0 * BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE;

  /* Outport: '<Root>/i1' */
  BIO_csi_sf_smpc_v2_Y.i1 = TransferFcn;

  /* StateSpace: '<S1>/Hw1' */
  rtb_Delaycombustor2 = 0.0;
  rtb_Delaycombustor2 += 0.94444980822600488 * BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[3];

  /* Outport: '<Root>/qbio_meas' */
  BIO_csi_sf_smpc_v2_Y.qbio_meas = rtb_Delaycombustor2;

  /* StateSpace: '<S1>/Hw6' */
  rtb_Delaycombustor2 = 0.0;
  rtb_Delaycombustor2 += 0.94444980822600488 * BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[3];

  /* Outport: '<Root>/pbio_meas' */
  BIO_csi_sf_smpc_v2_Y.pbio_meas = rtb_Delaycombustor2;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    /* DiscreteTransferFcn: '<S1>/Delay90(z)V' incorporates:
     *  Inport: '<Root>/Vload'
     */
    BIO_csi_sf_smpc_v2_DW.Delay90zV_tmp = BIO_csi_sf_smpc_v2_U.Vload - -0.96364 *
      BIO_csi_sf_smpc_v2_DW.Delay90zV_states;
    BIO_csi_sf_smpc_v2_B.Delay90zV = -1.0364 *
      BIO_csi_sf_smpc_v2_DW.Delay90zV_states +
      BIO_csi_sf_smpc_v2_DW.Delay90zV_tmp;
  }

  /* MATLAB Function: '<S1>/PQ2Iab_PH1' incorporates:
   *  Inport: '<Root>/Prefb'
   *  Inport: '<Root>/Qrefb'
   *  Inport: '<Root>/Vload'
   */
  /*  divide by zero protection */
  /* MATLAB Function 'CSI_Control_BIO/PQ2Iab_PH1': '<S3>:1' */
  /* '<S3>:1:5' if(abs((Va^2+Vb^2))<=1000*eps(0)) */
  det = BIO_csi_sf_smpc_v2_U.Vload * BIO_csi_sf_smpc_v2_U.Vload +
    BIO_csi_sf_smpc_v2_B.Delay90zV * BIO_csi_sf_smpc_v2_B.Delay90zV;
  if (fabs(det) <= 4.94065645841247E-321) {
    /* '<S3>:1:6' det = 1/eps(0); */
    det = (rtInf);
  } else {
    /* '<S3>:1:7' else */
    /* '<S3>:1:8' det = 1/(Va^2+Vb^2); */
    det = 1.0 / det;

    /*  constante auxiliar */
  }

  /* det = 1/(Va^2+Vb^2); */
  /* '<S3>:1:12' Mat = det*[Va Vb; Vb -Va]; */
  /* '<S3>:1:13' Iab = Mat*[2*p;2*q]; */
  det = det * BIO_csi_sf_smpc_v2_U.Vload * (2.0 * BIO_csi_sf_smpc_v2_U.Prefb) +
    det * BIO_csi_sf_smpc_v2_B.Delay90zV * (2.0 * BIO_csi_sf_smpc_v2_U.Qrefb);

  /* '<S3>:1:15' Iaaux = Iab(1); */
  /* '<S3>:1:16' Ibaux = Iab(2); */
  /* '<S3>:1:18' ilim=1e3; */
  /* '<S3>:1:20' if(Iaaux>ilim) */
  if (det > 1000.0) {
    /* '<S3>:1:21' Iaaux=ilim; */
    det = 1000.0;
  }

  /* '<S3>:1:23' if(Iaaux<-ilim) */
  if (det < -1000.0) {
    /* '<S3>:1:24' Iaaux =-ilim; */
    det = -1000.0;
  }

  /* '<S3>:1:27' if(isnan(Iaaux)) */
  if (rtIsNaN(det)) {
    /* '<S3>:1:28' Iaaux=0; */
    det = 0.0;
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  MATLAB Function: '<S1>/PQ2Iab_PH1'
   */
  /* ----------------- */
  /* '<S3>:1:33' if(Ibaux>ilim) */
  /* '<S3>:1:36' if(Ibaux<-ilim) */
  /* '<S3>:1:40' if(isnan(Ibaux)) */
  /* ----------------- */
  /* '<S3>:1:46' Ia = Iaaux; */
  /* '<S3>:1:47' Ib = Ibaux; */
  det -= TransferFcn;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    /* DiscreteTransferFcn: '<S1>/PR(z)' */
    BIO_csi_sf_smpc_v2_DW.PRz_tmp = (det - -1.9966 *
      BIO_csi_sf_smpc_v2_DW.PRz_states[0]) - 0.998 *
      BIO_csi_sf_smpc_v2_DW.PRz_states[1];
    rtb_PRz = (0.0201 * BIO_csi_sf_smpc_v2_DW.PRz_tmp + -0.039932 *
               BIO_csi_sf_smpc_v2_DW.PRz_states[0]) + 0.01986 *
      BIO_csi_sf_smpc_v2_DW.PRz_states[1];

    /* Outport: '<Root>/duty_cycle' */
    BIO_csi_sf_smpc_v2_Y.duty_cycle = rtb_PRz;

    /* DiscreteTransferFcn: '<S1>/Delay90(z)I' */
    BIO_csi_sf_smpc_v2_DW.Delay90zI_tmp = TransferFcn - -0.96364 *
      BIO_csi_sf_smpc_v2_DW.Delay90zI_states;
    BIO_csi_sf_smpc_v2_B.Delay90zI = -1.0364 *
      BIO_csi_sf_smpc_v2_DW.Delay90zI_states +
      BIO_csi_sf_smpc_v2_DW.Delay90zI_tmp;
  }

  /* MATLAB Function: '<S1>/PQ_singlePhase' incorporates:
   *  Inport: '<Root>/Vload'
   */
  /*  Esta funcion calcula la potencia activa y reactiva instantanea */
  /*  para el caso mnosofasico. En la revision de 2 papers he observado */
  /*  que una manera de extender la teoria de potencia al caso monofasico */
  /*  es asumiendo la tension o corriente de una fase como la componente */
  /*  alpha y hacer un desfase de 90 grados para obtener una version */
  /*  artificial de beta. */
  /* MATLAB Function 'CSI_Control_BIO/PQ_singlePhase': '<S4>:1' */
  /* '<S4>:1:9' paux=va*ia+vb*ib; */
  det = BIO_csi_sf_smpc_v2_U.Vload * TransferFcn +
    BIO_csi_sf_smpc_v2_B.Delay90zV * BIO_csi_sf_smpc_v2_B.Delay90zI;

  /* '<S4>:1:10' if(paux > 20e4) */
  if (det > 200000.0) {
    /* '<S4>:1:11' paux = 20e4; */
    det = 200000.0;
  }

  /* '<S4>:1:13' if(paux < -20e4) */
  if (det < -200000.0) {
    /* '<S4>:1:14' paux = -20e-4; */
    det = -0.002;
  }

  /* '<S4>:1:17' p = paux/2; */
  BIO_csi_sf_smpc_v2_B.p = det / 2.0;

  /*  potencia activa instantanea */
  /* '<S4>:1:19' qaux = vb*ia-va*ib; */
  TransferFcn = BIO_csi_sf_smpc_v2_B.Delay90zV * TransferFcn -
    BIO_csi_sf_smpc_v2_U.Vload * BIO_csi_sf_smpc_v2_B.Delay90zI;

  /* '<S4>:1:21' if(qaux>20e4) */
  if (TransferFcn > 200000.0) {
    /* '<S4>:1:22' qaux=20e4; */
    TransferFcn = 200000.0;
  }

  /* '<S4>:1:24' if(qaux<-20e4) */
  if (TransferFcn < -200000.0) {
    /* '<S4>:1:25' qaux=-20e4; */
    TransferFcn = -200000.0;
  }

  /* '<S4>:1:28' q = qaux/2; */
  BIO_csi_sf_smpc_v2_B.q = TransferFcn / 2.0;

  /* End of MATLAB Function: '<S1>/PQ_singlePhase' */
  /*  potencia reactiva instantanea */
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    /* Gain: '<Root>/Gain3' */
    BIO_csi_sf_smpc_v2_B.Gain3 = 2.0 * rtb_PRz;
  }

  /* TransferFcn: '<S2>/Compresor' */
  rtb_Delaycombustor2 = 0.0;
  rtb_Delaycombustor2 += 5.0 * BIO_csi_sf_smpc_v2_X.Compresor_CSTATE;

  /* Sum: '<S2>/Add1' incorporates:
   *  Constant: '<S2>/Constant19'
   */
  TransferFcn = rtb_Delaycombustor2 - 0.23;

  /* TransportDelay: '<S2>/Delay combustor2' */
  {
    real_T **uBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[1];
    real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.001;
    rtb_Delaycombustor2 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.CircularBufSize,
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Last,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Sum: '<S2>/Add2' incorporates:
   *  Constant: '<S2>/Constant20'
   *  Constant: '<S2>/Constant21'
   *  Constant: '<S2>/Constant22'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Sum: '<S2>/Add3'
   */
  rtb_Torquemecnico = (1.0 - rtb_Delaycombustor2) * 0.5 + TransferFcn * 1.2;

  /* Gain: '<S2>/Gain1' */
  TransferFcn = 900.0 * rtb_Torquemecnico;

  /* Step: '<Root>/Step' */
  if (BIO_csi_sf_smpc_v2_M->Timing.t[0] < 0.0) {
    rtb_PRz = 0.0;
  } else {
    rtb_PRz = 28.0;
  }

  /* End of Step: '<Root>/Step' */

  /* MATLAB Function: '<S2>/MATLAB Function metano' incorporates:
   *  Constant: '<S2>/Constant18'
   *  Integrator: '<S2>/Integrator1'
   *  MATLAB Function: '<S2>/MATLAB Function metanogenesis'
   */
  /*  Fmeth=V*umc*K4*Xmeth/(Ksc/Sv+1); */
  /* MATLAB Function 'Subsystem/MATLAB Function metano': '<S11>:1' */
  /* '<S11>:1:5' Fmeth=V*umc*K4*Xmeth/(Ksc/(Sv+1)); */
  det = 3.0 / (BIO_csi_sf_smpc_v2_X.Integrator1_CSTATE + 1.0);

  /* Product: '<S2>/Divide' incorporates:
   *  Constant: '<S2>/Constant17'
   *  Constant: '<S2>/Constant27'
   *  Constant: '<S2>/Constant3'
   *  Integrator: '<S2>/Integrator3'
   *  MATLAB Function: '<S2>/MATLAB Function metano'
   */
  rtb_Divide = 20.0 * BIO_csi_sf_smpc_v2_ConstB.Sum * 15.1 *
    BIO_csi_sf_smpc_v2_X.Integrator3_CSTATE / det / 35.4;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/wref'
   */
  BIO_csi_sf_smpc_v2_B.Sum1 = 70000.0 - rtb_Delaycombustor2;

  /* TransferFcn: '<S2>/thermo couple' */
  rtb_RotationShield = 0.0;
  rtb_RotationShield += 0.4 * BIO_csi_sf_smpc_v2_X.thermocouple_CSTATE;

  /* Sum: '<S2>/Sum3' incorporates:
   *  Constant: '<S2>/Constant26'
   */
  BIO_csi_sf_smpc_v2_B.Sum3 = 950.0 - rtb_RotationShield;

  /* TransferFcn: '<S2>/Temp Control' */
  rtb_RotationShield = 0.0;
  rtb_RotationShield += 0.0022222222222222222 *
    BIO_csi_sf_smpc_v2_X.TempControl_CSTATE;
  rtb_RotationShield += 0.0073333333333333332 * BIO_csi_sf_smpc_v2_B.Sum3;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  MinMax: '<S2>/Min'
   *  Product: '<S2>/Product'
   *  TransferFcn: '<S2>/Transfer Fcn'
   */
  /* MATLAB Function 'Subsystem/MATLAB Function': '<S7>:1' */
  /* '<S7>:1:3' y = u2*(1-u1); */
  BIO_csi_sf_smpc_v2_B.y = fmin(-5.0 * BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE_i
    + 10.0 * BIO_csi_sf_smpc_v2_B.Sum1, rtb_RotationShield) *
    rtb_Delaycombustor2 * (1.0 - rtb_Divide);

  /* TransportDelay: '<S2>/Delay combustor1' */
  {
    /* Delay time is 0 and inline parameter is on */
    rtb_RotationShield = BIO_csi_sf_smpc_v2_B.y;
  }

  /* Sum: '<S2>/Add' */
  BIO_csi_sf_smpc_v2_B.Add = rtb_Divide + rtb_RotationShield;

  /* TransportDelay: '<S2>/Turbine exhaust system delay' */
  {
    real_T **uBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1];
    real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.04;
    rtb_RotationShield = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize,
      &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Last,
      BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail,
      BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Sum: '<S2>/Add4' incorporates:
   *  Constant: '<S2>/Constant21'
   *  Constant: '<S2>/Constant23'
   *  Constant: '<S2>/Constant24'
   *  Constant: '<S2>/Constant25'
   *  Constant: '<S2>/Constant26'
   *  Product: '<S2>/Product3'
   *  Product: '<S2>/Product4'
   *  Sum: '<S2>/Add3'
   *  Sum: '<S2>/Sum2'
   */
  BIO_csi_sf_smpc_v2_B.Add4 = ((1.0 - rtb_Delaycombustor2) * 550.0 - (1.0 -
    rtb_RotationShield) * 700.0) + 950.0;

  /* TransferFcn: '<S2>/Rotation Shield' */
  rtb_RotationShield = 0.0;
  rtb_RotationShield += 0.013333333333333334 *
    BIO_csi_sf_smpc_v2_X.RotationShield_CSTATE;

  /* Sum: '<S2>/Add5' incorporates:
   *  Gain: '<S2>/Gain2'
   */
  BIO_csi_sf_smpc_v2_B.Add5 = 0.8 * BIO_csi_sf_smpc_v2_B.Add4 +
    rtb_RotationShield;

  /* TransportDelay: '<S2>/Delay combustor' */
  {
    real_T **uBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[1];
    real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.01;
    BIO_csi_sf_smpc_v2_B.Delaycombustor = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.CircularBufSize,
      &BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Last,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail,
      BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* TransferFcn: '<S2>/Fuel system actuator' */
  rtb_Fuelsystemactuator = 0.0;
  rtb_Fuelsystemactuator += 25.0 *
    BIO_csi_sf_smpc_v2_X.Fuelsystemactuator_CSTATE;

  /* MATLAB Function: '<S2>/MATLAB Function Acetogenesis' incorporates:
   *  Constant: '<S2>/Constant12'
   *  Constant: '<S2>/Constant15'
   *  Constant: '<S2>/Constant16'
   *  Constant: '<S2>/Constant3'
   *  Integrator: '<S2>/Integrator'
   *  Integrator: '<S2>/Integrator2'
   *  MATLAB Function: '<S2>/MATLAB Function Acidogenesis'
   *  MATLAB Function: '<S2>/MATLAB Function Hidrolisis'
   */
  /*  Xacidp=(um/(1+Ks/Sb)-Kd-Ffeed/(b*V))*Xacid; */
  /* MATLAB Function 'Subsystem/MATLAB Function Acetogenesis': '<S8>:1' */
  /* '<S8>:1:4' Xacidp=(um/(Ks/(1+Sb))-Kd-Ffeed/(b*V))*Xacid; */
  rtb_Divide = 21.5 / (1.0 + BIO_csi_sf_smpc_v2_X.Integrator_CSTATE);
  BIO_csi_sf_smpc_v2_B.Xacidp = ((BIO_csi_sf_smpc_v2_ConstB.Sum / rtb_Divide -
    0.02) - rtb_PRz / 98.2) * BIO_csi_sf_smpc_v2_X.Integrator2_CSTATE;

  /* MATLAB Function: '<S2>/MATLAB Function Acidogenesis' incorporates:
   *  Constant: '<S2>/Constant10'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant6'
   *  Constant: '<S2>/Constant7'
   *  Constant: '<S2>/Constant8'
   *  Integrator: '<S2>/Integrator1'
   *  Integrator: '<S2>/Integrator2'
   *  Integrator: '<S2>/Integrator3'
   */
  /*  Svp=(Svin-Sv)*(Ffeed/V)+um*K2*Xacid/(1+Ks/Sb)-umc*K3*Xmeth/(1+Ksc/Sv); */
  /* MATLAB Function 'Subsystem/MATLAB Function Acidogenesis': '<S9>:1' */
  /* '<S9>:1:4' Svp=(Svin-Sv)*(Ffeed/V)+um*K2*Xacid/(Ks/(1+Sb))-umc*K3*Xmeth/(Ksc/(1+Sv)); */
  BIO_csi_sf_smpc_v2_B.Svp = (BIO_csi_sf_smpc_v2_ConstB.Sum * 6.97 *
    BIO_csi_sf_smpc_v2_X.Integrator2_CSTATE / rtb_Divide + (2.91 -
    BIO_csi_sf_smpc_v2_X.Integrator1_CSTATE) * (rtb_PRz / 20.0)) -
    BIO_csi_sf_smpc_v2_ConstB.Sum * 31.8 *
    BIO_csi_sf_smpc_v2_X.Integrator3_CSTATE / (3.0 / (1.0 +
    BIO_csi_sf_smpc_v2_X.Integrator1_CSTATE));

  /* MATLAB Function: '<S2>/MATLAB Function Hidrolisis' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   *  Constant: '<S2>/Constant5'
   *  Integrator: '<S2>/Integrator'
   *  Integrator: '<S2>/Integrator2'
   */
  /*  Sbp=(Sbin-Sb)*(Ffeed/V)+um*K1*Xacid/(1+Ks/Sb); */
  /* MATLAB Function 'Subsystem/MATLAB Function Hidrolisis': '<S10>:1' */
  /* '<S10>:1:4' Sbp=(Sbin-Sb)*(Ffeed/V)+um*K1*Xacid/(Ks/(1+Sb)); */
  BIO_csi_sf_smpc_v2_B.Sbp = BIO_csi_sf_smpc_v2_ConstB.Sum * 9.66 *
    BIO_csi_sf_smpc_v2_X.Integrator2_CSTATE / rtb_Divide + (13.8 -
    BIO_csi_sf_smpc_v2_X.Integrator_CSTATE) * (rtb_PRz / 20.0);

  /* MATLAB Function: '<S2>/MATLAB Function metanogenesis' incorporates:
   *  Constant: '<S2>/Constant11'
   *  Constant: '<S2>/Constant13'
   *  Constant: '<S2>/Constant3'
   *  Integrator: '<S2>/Integrator3'
   */
  /*  Xmethp=(umc/(Ksc/Sv+1)-Kdc-Ffeed/(b*V))*Xmeth; */
  /* MATLAB Function 'Subsystem/MATLAB Function metanogenesis': '<S12>:1' */
  /* '<S12>:1:4' Xmethp=(umc/(Ksc/(Sv+1))-Kdc-Ffeed/(b*V))*Xmeth; */
  BIO_csi_sf_smpc_v2_B.Xmethp = ((BIO_csi_sf_smpc_v2_ConstB.Sum / det - 0.02) -
    rtb_PRz / 98.2) * BIO_csi_sf_smpc_v2_X.Integrator3_CSTATE;

  /* TransferFcn: '<S2>/Valve Positioner' */
  BIO_csi_sf_smpc_v2_B.ValvePositioner = 0.0;
  BIO_csi_sf_smpc_v2_B.ValvePositioner += 20.0 *
    BIO_csi_sf_smpc_v2_X.ValvePositioner_CSTATE;

  /* Saturate: '<S2>/Saturation' */
  if (TransferFcn > 1000.0) {
    TransferFcn = 1000.0;
  } else {
    if (TransferFcn < 0.0) {
      TransferFcn = 0.0;
    }
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Vload'
   *  Product: '<Root>/Product'
   */
  BIO_csi_sf_smpc_v2_B.Sum_n = TransferFcn * BIO_csi_sf_smpc_v2_B.Gain3 -
    BIO_csi_sf_smpc_v2_U.Vload;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)V' */
      BIO_csi_sf_smpc_v2_DW.Delay90zV_states =
        BIO_csi_sf_smpc_v2_DW.Delay90zV_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/PR(z)' */
      BIO_csi_sf_smpc_v2_DW.PRz_states[1] = BIO_csi_sf_smpc_v2_DW.PRz_states[0];
      BIO_csi_sf_smpc_v2_DW.PRz_states[0] = BIO_csi_sf_smpc_v2_DW.PRz_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)I' */
      BIO_csi_sf_smpc_v2_DW.Delay90zI_states =
        BIO_csi_sf_smpc_v2_DW.Delay90zI_tmp;
    }

    /* Update for TransportDelay: '<S2>/Delay combustor2' */
    {
      real_T **uBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[1];
      real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
      BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head =
        ((BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head <
          (BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.CircularBufSize-1)) ?
         (BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head+1) : 0);
      if (BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head ==
          BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail) {
        BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail =
          ((BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail <
            (BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.CircularBufSize-1)) ?
           (BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head] = simTime;
      (*uBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head] =
        rtb_Torquemecnico;
    }

    /* Update for TransportDelay: '<S2>/Delay combustor1' */
    {
      real_T **uBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor1_PWORK.TUbufferPtrs[1];
      real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
      BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head =
        ((BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head <
          (BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.CircularBufSize-1)) ?
         (BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head+1) : 0);
      if (BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head ==
          BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Tail) {
        BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Tail =
          ((BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Tail <
            (BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.CircularBufSize-1)) ?
           (BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head] = simTime;
      (*uBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head] =
        BIO_csi_sf_smpc_v2_B.y;
    }

    /* Update for TransportDelay: '<S2>/Turbine exhaust system delay' */
    {
      real_T **uBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1];
      real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
      BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head =
        ((BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head <
          (BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize
           -1)) ? (BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head+1)
         : 0);
      if (BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head ==
          BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail) {
        BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail =
          ((BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail <
            (BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize
             -1)) ? (BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail+
                     1) : 0);
      }

      (*tBuffer)[BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head] =
        simTime;
      (*uBuffer)[BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head] =
        BIO_csi_sf_smpc_v2_B.Delaycombustor;
    }

    /* Update for TransportDelay: '<S2>/Delay combustor' */
    {
      real_T **uBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[1];
      real_T simTime = BIO_csi_sf_smpc_v2_M->Timing.t[0];
      BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head =
        ((BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head <
          (BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.CircularBufSize-1)) ?
         (BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head+1) : 0);
      if (BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head ==
          BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail) {
        BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail =
          ((BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail <
            (BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.CircularBufSize-1)) ?
           (BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head] = simTime;
      (*uBuffer)[BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head] =
        rtb_Fuelsystemactuator;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_v2_M)) {
    rt_ertODEUpdateContinuousStates(&BIO_csi_sf_smpc_v2_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++BIO_csi_sf_smpc_v2_M->Timing.clockTick0;
    BIO_csi_sf_smpc_v2_M->Timing.t[0] = rtsiGetSolverStopTime
      (&BIO_csi_sf_smpc_v2_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      BIO_csi_sf_smpc_v2_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void BIO_csi_sf_smpc_v2_derivatives(void)
{
  XDot_BIO_csi_sf_smpc_v2_T *_rtXdot;
  _rtXdot = ((XDot_BIO_csi_sf_smpc_v2_T *) BIO_csi_sf_smpc_v2_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -2.5 * BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += BIO_csi_sf_smpc_v2_B.Sum_n;

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
  _rtXdot->Hw1_CSTATE[0] += -341.08603071128289 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[0] += -178.02459475242631 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[1] += 178.0245947524264 * BIO_csi_sf_smpc_v2_X.Hw1_CSTATE
    [0];
  _rtXdot->Hw1_CSTATE[2] += 199.58239979893239 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[2] += -247.76277465378331 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[2] += -199.58239979893239 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[3];
  _rtXdot->Hw1_CSTATE[3] += 199.58239979893244 *
    BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[0] += 188.49555921538757 * BIO_csi_sf_smpc_v2_B.q;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] += -341.08603071128289 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += -178.02459475242631 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[1] += 178.0245947524264 * BIO_csi_sf_smpc_v2_X.Hw6_CSTATE
    [0];
  _rtXdot->Hw6_CSTATE[2] += 199.58239979893239 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[2] += -247.76277465378331 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[2] += -199.58239979893239 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[3];
  _rtXdot->Hw6_CSTATE[3] += 199.58239979893244 *
    BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[0] += 188.49555921538757 * BIO_csi_sf_smpc_v2_B.p;

  /* Derivatives for TransferFcn: '<S2>/Compresor' */
  _rtXdot->Compresor_CSTATE = 0.0;
  _rtXdot->Compresor_CSTATE += -5.0 * BIO_csi_sf_smpc_v2_X.Compresor_CSTATE;
  _rtXdot->Compresor_CSTATE += BIO_csi_sf_smpc_v2_B.Delaycombustor;

  /* Derivatives for Integrator: '<S2>/Integrator3' */
  _rtXdot->Integrator3_CSTATE = BIO_csi_sf_smpc_v2_B.Xmethp;

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = BIO_csi_sf_smpc_v2_B.Svp;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_i = 0.0;
  _rtXdot->TransferFcn_CSTATE_i += -3.0 *
    BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE_i;
  _rtXdot->TransferFcn_CSTATE_i += BIO_csi_sf_smpc_v2_B.Sum1;

  /* Derivatives for TransferFcn: '<S2>/thermo couple' */
  _rtXdot->thermocouple_CSTATE = 0.0;
  _rtXdot->thermocouple_CSTATE += -0.4 *
    BIO_csi_sf_smpc_v2_X.thermocouple_CSTATE;
  _rtXdot->thermocouple_CSTATE += BIO_csi_sf_smpc_v2_B.Add5;

  /* Derivatives for TransferFcn: '<S2>/Temp Control' */
  _rtXdot->TempControl_CSTATE = 0.0;
  _rtXdot->TempControl_CSTATE += -0.0 * BIO_csi_sf_smpc_v2_X.TempControl_CSTATE;
  _rtXdot->TempControl_CSTATE += BIO_csi_sf_smpc_v2_B.Sum3;

  /* Derivatives for TransferFcn: '<S2>/Rotation Shield' */
  _rtXdot->RotationShield_CSTATE = 0.0;
  _rtXdot->RotationShield_CSTATE += -0.066666666666666666 *
    BIO_csi_sf_smpc_v2_X.RotationShield_CSTATE;
  _rtXdot->RotationShield_CSTATE += BIO_csi_sf_smpc_v2_B.Add4;

  /* Derivatives for TransferFcn: '<S2>/Fuel system actuator' */
  _rtXdot->Fuelsystemactuator_CSTATE = 0.0;
  _rtXdot->Fuelsystemactuator_CSTATE += -25.0 *
    BIO_csi_sf_smpc_v2_X.Fuelsystemactuator_CSTATE;
  _rtXdot->Fuelsystemactuator_CSTATE += BIO_csi_sf_smpc_v2_B.ValvePositioner;

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE = BIO_csi_sf_smpc_v2_B.Sbp;

  /* Derivatives for Integrator: '<S2>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = BIO_csi_sf_smpc_v2_B.Xacidp;

  /* Derivatives for TransferFcn: '<S2>/Valve Positioner' */
  _rtXdot->ValvePositioner_CSTATE = 0.0;
  _rtXdot->ValvePositioner_CSTATE += -20.0 *
    BIO_csi_sf_smpc_v2_X.ValvePositioner_CSTATE;
  _rtXdot->ValvePositioner_CSTATE += BIO_csi_sf_smpc_v2_B.Add;
}

/* Model initialize function */
void BIO_csi_sf_smpc_v2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)BIO_csi_sf_smpc_v2_M, 0,
                sizeof(RT_MODEL_BIO_csi_sf_smpc_v2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
                          &BIO_csi_sf_smpc_v2_M->Timing.simTimeStep);
    rtsiSetTPtr(&BIO_csi_sf_smpc_v2_M->solverInfo, &rtmGetTPtr
                (BIO_csi_sf_smpc_v2_M));
    rtsiSetStepSizePtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
                       &BIO_csi_sf_smpc_v2_M->Timing.stepSize0);
    rtsiSetdXPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
                 &BIO_csi_sf_smpc_v2_M->derivs);
    rtsiSetContStatesPtr(&BIO_csi_sf_smpc_v2_M->solverInfo, (real_T **)
                         &BIO_csi_sf_smpc_v2_M->contStates);
    rtsiSetNumContStatesPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
      &BIO_csi_sf_smpc_v2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
      &BIO_csi_sf_smpc_v2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
      &BIO_csi_sf_smpc_v2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&BIO_csi_sf_smpc_v2_M->solverInfo,
      &BIO_csi_sf_smpc_v2_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&BIO_csi_sf_smpc_v2_M->solverInfo, (&rtmGetErrorStatus
      (BIO_csi_sf_smpc_v2_M)));
    rtsiSetRTModelPtr(&BIO_csi_sf_smpc_v2_M->solverInfo, BIO_csi_sf_smpc_v2_M);
  }

  rtsiSetSimTimeStep(&BIO_csi_sf_smpc_v2_M->solverInfo, MAJOR_TIME_STEP);
  BIO_csi_sf_smpc_v2_M->intgData.y = BIO_csi_sf_smpc_v2_M->odeY;
  BIO_csi_sf_smpc_v2_M->intgData.f[0] = BIO_csi_sf_smpc_v2_M->odeF[0];
  BIO_csi_sf_smpc_v2_M->intgData.f[1] = BIO_csi_sf_smpc_v2_M->odeF[1];
  BIO_csi_sf_smpc_v2_M->intgData.f[2] = BIO_csi_sf_smpc_v2_M->odeF[2];
  BIO_csi_sf_smpc_v2_M->intgData.f[3] = BIO_csi_sf_smpc_v2_M->odeF[3];
  BIO_csi_sf_smpc_v2_M->contStates = ((X_BIO_csi_sf_smpc_v2_T *)
    &BIO_csi_sf_smpc_v2_X);
  rtsiSetSolverData(&BIO_csi_sf_smpc_v2_M->solverInfo, (void *)
                    &BIO_csi_sf_smpc_v2_M->intgData);
  rtsiSetSolverName(&BIO_csi_sf_smpc_v2_M->solverInfo,"ode4");
  rtmSetTPtr(BIO_csi_sf_smpc_v2_M, &BIO_csi_sf_smpc_v2_M->Timing.tArray[0]);
  BIO_csi_sf_smpc_v2_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &BIO_csi_sf_smpc_v2_B), 0,
                sizeof(B_BIO_csi_sf_smpc_v2_T));

  /* states (continuous) */
  {
    (void) memset((void *)&BIO_csi_sf_smpc_v2_X, 0,
                  sizeof(X_BIO_csi_sf_smpc_v2_T));
  }

  /* states (dwork) */
  (void) memset((void *)&BIO_csi_sf_smpc_v2_DW, 0,
                sizeof(DW_BIO_csi_sf_smpc_v2_T));

  /* external inputs */
  (void)memset((void *)&BIO_csi_sf_smpc_v2_U, 0, sizeof
               (ExtU_BIO_csi_sf_smpc_v2_T));

  /* external outputs */
  (void) memset((void *)&BIO_csi_sf_smpc_v2_Y, 0,
                sizeof(ExtY_BIO_csi_sf_smpc_v2_T));

  /* Start for TransportDelay: '<S2>/Delay combustor2' */
  {
    real_T *pBuffer = &BIO_csi_sf_smpc_v2_DW.Delaycombustor2_RWORK.TUbufferArea
      [0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Tail = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Head = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.Last = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor2_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S2>/Delay combustor1' */
  {
    real_T *pBuffer = &BIO_csi_sf_smpc_v2_DW.Delaycombustor1_RWORK.TUbufferArea
      [0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Tail = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Head = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.Last = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor1_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S2>/Turbine exhaust system delay' */
  {
    real_T *pBuffer =
      &BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_RWORK.TUbufferArea[0];
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Tail = 0;
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Head = 0;
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.Last = 0;
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[0] =
      (void *) &pBuffer[0];
    BIO_csi_sf_smpc_v2_DW.Turbineexhaustsystemdelay_PWORK.TUbufferPtrs[1] =
      (void *) &pBuffer[1024];
  }

  /* Start for TransportDelay: '<S2>/Delay combustor' */
  {
    real_T *pBuffer = &BIO_csi_sf_smpc_v2_DW.Delaycombustor_RWORK.TUbufferArea[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Tail = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Head = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.Last = 0;
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = BIO_csi_sf_smpc_v2_M->Timing.t[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    BIO_csi_sf_smpc_v2_DW.Delaycombustor_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[1024];
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_v2_X.Hw1_CSTATE[3] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_v2_X.Hw6_CSTATE[3] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Compresor' */
  BIO_csi_sf_smpc_v2_X.Compresor_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator3' */
  BIO_csi_sf_smpc_v2_X.Integrator3_CSTATE = 0.35;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  BIO_csi_sf_smpc_v2_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn' */
  BIO_csi_sf_smpc_v2_X.TransferFcn_CSTATE_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/thermo couple' */
  BIO_csi_sf_smpc_v2_X.thermocouple_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Temp Control' */
  BIO_csi_sf_smpc_v2_X.TempControl_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Rotation Shield' */
  BIO_csi_sf_smpc_v2_X.RotationShield_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Fuel system actuator' */
  BIO_csi_sf_smpc_v2_X.Fuelsystemactuator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  BIO_csi_sf_smpc_v2_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator2' */
  BIO_csi_sf_smpc_v2_X.Integrator2_CSTATE = 1.2;

  /* InitializeConditions for TransferFcn: '<S2>/Valve Positioner' */
  BIO_csi_sf_smpc_v2_X.ValvePositioner_CSTATE = 0.0;
}

/* Model terminate function */
void BIO_csi_sf_smpc_v2_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

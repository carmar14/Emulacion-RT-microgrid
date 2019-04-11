/*
 * File: BIO_csi_sf_smpc.c
 *
 * Code generated for Simulink model 'BIO_csi_sf_smpc'.
 *
 * Model version                  : 1.73
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 11 08:30:10 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BIO_csi_sf_smpc.h"
#include "BIO_csi_sf_smpc_private.h"

/* Block signals (default storage) */
B_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_B;

/* Continuous states */
X_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_X;

/* Block states (default storage) */
DW_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_DW;

/* External inputs (root inport signals with default storage) */
ExtU_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_Y;

/* Real-time model */
RT_MODEL_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_M_;
RT_MODEL_BIO_csi_sf_smpc_T *const BIO_csi_sf_smpc_M = &BIO_csi_sf_smpc_M_;

//Funciones creadas por el programador set y get
//-------Funciones para asignar entradas-------------
void set_Vdc_bio(double Vdc_bio){
	//printf("La accion 1 es: %3.2f \n",V_bio);
	BIO_csi_sf_smpc_U.Vdc=Vdc_bio;
	//printf("El voltaje es: %3.2f \n",BIO_csi_U.V_bio);
	}
	
void set_Vload(double Vload){
	BIO_csi_sf_smpc_U.Vload=Vload;
}

void set_Qref_bio(double Qref_bio){
	BIO_csi_sf_smpc_U.Qrefb=Qref_bio;
	}
	
void set_Pref_bio(double Pref_bio){
	BIO_csi_sf_smpc_U.Prefb=Pref_bio;
	}
	
//-----Funciones para obtener valores de las salidas-------
	
double get_I_bio(void){
	return BIO_csi_sf_smpc_Y.i1;
	 
	}
	
double get_Pm(void){
	return BIO_csi_sf_smpc_Y.pbio_meas;
	
}

double get_Qm(void){
	return BIO_csi_sf_smpc_Y.qbio_meas;
	
}

double get_duty_cycle(void) {
    return BIO_csi_sf_smpc_Y.duty_cycle; 
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
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  BIO_csi_sf_smpc_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  BIO_csi_sf_smpc_step();
  BIO_csi_sf_smpc_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  BIO_csi_sf_smpc_step();
  BIO_csi_sf_smpc_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  BIO_csi_sf_smpc_step();
  BIO_csi_sf_smpc_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void BIO_csi_sf_smpc_step(void)
{
  real_T rtb_Hw6;
  real_T rtb_PRz;
  real_T TransferFcn;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&BIO_csi_sf_smpc_M->solverInfo,
                          ((BIO_csi_sf_smpc_M->Timing.clockTick0+1)*
      BIO_csi_sf_smpc_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(BIO_csi_sf_smpc_M)) {
    BIO_csi_sf_smpc_M->Timing.t[0] = rtsiGetT(&BIO_csi_sf_smpc_M->solverInfo);
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  TransferFcn = 25.0 * BIO_csi_sf_smpc_X.TransferFcn_CSTATE;

  /* Outport: '<Root>/i1' */
  BIO_csi_sf_smpc_Y.i1 = TransferFcn;

  /* Outport: '<Root>/qbio_meas' incorporates:
   *  StateSpace: '<S1>/Hw1'
   */
  BIO_csi_sf_smpc_Y.qbio_meas = 0.94444980822600488 *
    BIO_csi_sf_smpc_X.Hw1_CSTATE[3];

  /* Outport: '<Root>/pbio_meas' incorporates:
   *  StateSpace: '<S1>/Hw6'
   */
  BIO_csi_sf_smpc_Y.pbio_meas = 0.94444980822600488 *
    BIO_csi_sf_smpc_X.Hw6_CSTATE[3];
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    /* DiscreteTransferFcn: '<S1>/Delay90(z)V' incorporates:
     *  Inport: '<Root>/Vload'
     */
    BIO_csi_sf_smpc_DW.Delay90zV_tmp = BIO_csi_sf_smpc_U.Vload - -0.96364 *
      BIO_csi_sf_smpc_DW.Delay90zV_states;
    BIO_csi_sf_smpc_B.Delay90zV = -1.0364 * BIO_csi_sf_smpc_DW.Delay90zV_states
      + BIO_csi_sf_smpc_DW.Delay90zV_tmp;
  }

  /* MATLAB Function: '<S1>/PQ2Iab_PH1' incorporates:
   *  Inport: '<Root>/Prefb'
   *  Inport: '<Root>/Qrefb'
   *  Inport: '<Root>/Vload'
   */
  /*  divide by zero protection */
  /* MATLAB Function 'CSI_Control_BIO/PQ2Iab_PH1': '<S2>:1' */
  /* '<S2>:1:5' if(abs((Va^2+Vb^2))<=1000*eps(0)) */
  rtb_Hw6 = BIO_csi_sf_smpc_U.Vload * BIO_csi_sf_smpc_U.Vload +
    BIO_csi_sf_smpc_B.Delay90zV * BIO_csi_sf_smpc_B.Delay90zV;
  if (fabs(rtb_Hw6) <= 4.94065645841247E-321) {
    /* '<S2>:1:6' det = 1/eps(0); */
    rtb_Hw6 = (rtInf);
  } else {
    /* '<S2>:1:7' else */
    /* '<S2>:1:8' det = 1/(Va^2+Vb^2); */
    rtb_Hw6 = 1.0 / rtb_Hw6;

    /*  constante auxiliar */
  }

  /* det = 1/(Va^2+Vb^2); */
  /* '<S2>:1:12' Mat = det*[Va Vb; Vb -Va]; */
  /* '<S2>:1:13' Iab = Mat*[2*p;2*q]; */
  rtb_Hw6 = rtb_Hw6 * BIO_csi_sf_smpc_U.Vload * (2.0 * BIO_csi_sf_smpc_U.Prefb)
    + rtb_Hw6 * BIO_csi_sf_smpc_B.Delay90zV * (2.0 * BIO_csi_sf_smpc_U.Qrefb);

  /* '<S2>:1:15' Iaaux = Iab(1); */
  /* '<S2>:1:16' Ibaux = Iab(2); */
  /* '<S2>:1:18' ilim=1e3; */
  /* '<S2>:1:20' if(Iaaux>ilim) */
  if (rtb_Hw6 > 1000.0) {
    /* '<S2>:1:21' Iaaux=ilim; */
    rtb_Hw6 = 1000.0;
  }

  /* '<S2>:1:23' if(Iaaux<-ilim) */
  if (rtb_Hw6 < -1000.0) {
    /* '<S2>:1:24' Iaaux =-ilim; */
    rtb_Hw6 = -1000.0;
  }

  /* '<S2>:1:27' if(isnan(Iaaux)) */
  if (rtIsNaN(rtb_Hw6)) {
    /* '<S2>:1:28' Iaaux=0; */
    rtb_Hw6 = 0.0;
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  MATLAB Function: '<S1>/PQ2Iab_PH1'
   */
  /* ----------------- */
  /* '<S2>:1:33' if(Ibaux>ilim) */
  /* '<S2>:1:36' if(Ibaux<-ilim) */
  /* '<S2>:1:40' if(isnan(Ibaux)) */
  /* ----------------- */
  /* '<S2>:1:46' Ia = Iaaux; */
  /* '<S2>:1:47' Ib = Ibaux; */
  rtb_Hw6 -= TransferFcn;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    /* DiscreteTransferFcn: '<S1>/PR(z)' */
    BIO_csi_sf_smpc_DW.PRz_tmp = (rtb_Hw6 - -1.9966 *
      BIO_csi_sf_smpc_DW.PRz_states[0]) - 0.998 * BIO_csi_sf_smpc_DW.PRz_states
      [1];
    rtb_PRz = (0.0201 * BIO_csi_sf_smpc_DW.PRz_tmp + -0.039932 *
               BIO_csi_sf_smpc_DW.PRz_states[0]) + 0.01986 *
      BIO_csi_sf_smpc_DW.PRz_states[1];

    /* Outport: '<Root>/duty_cycle' */
    BIO_csi_sf_smpc_Y.duty_cycle = rtb_PRz;

    /* DiscreteTransferFcn: '<S1>/Delay90(z)I' */
    BIO_csi_sf_smpc_DW.Delay90zI_tmp = TransferFcn - -0.96364 *
      BIO_csi_sf_smpc_DW.Delay90zI_states;
    BIO_csi_sf_smpc_B.Delay90zI = -1.0364 * BIO_csi_sf_smpc_DW.Delay90zI_states
      + BIO_csi_sf_smpc_DW.Delay90zI_tmp;
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
  /* MATLAB Function 'CSI_Control_BIO/PQ_singlePhase': '<S3>:1' */
  /* '<S3>:1:9' paux=va*ia+vb*ib; */
  rtb_Hw6 = BIO_csi_sf_smpc_U.Vload * TransferFcn + BIO_csi_sf_smpc_B.Delay90zV *
    BIO_csi_sf_smpc_B.Delay90zI;

  /* '<S3>:1:10' if(paux > 20e4) */
  if (rtb_Hw6 > 200000.0) {
    /* '<S3>:1:11' paux = 20e4; */
    rtb_Hw6 = 200000.0;
  }

  /* '<S3>:1:13' if(paux < -20e4) */
  if (rtb_Hw6 < -200000.0) {
    /* '<S3>:1:14' paux = -20e-4; */
    rtb_Hw6 = -0.002;
  }

  /* '<S3>:1:17' p = paux/2; */
  BIO_csi_sf_smpc_B.p = rtb_Hw6 / 2.0;

  /*  potencia activa instantanea */
  /* '<S3>:1:19' qaux = vb*ia-va*ib; */
  TransferFcn = BIO_csi_sf_smpc_B.Delay90zV * TransferFcn -
    BIO_csi_sf_smpc_U.Vload * BIO_csi_sf_smpc_B.Delay90zI;

  /* '<S3>:1:21' if(qaux>20e4) */
  if (TransferFcn > 200000.0) {
    /* '<S3>:1:22' qaux=20e4; */
    TransferFcn = 200000.0;
  }

  /* '<S3>:1:24' if(qaux<-20e4) */
  if (TransferFcn < -200000.0) {
    /* '<S3>:1:25' qaux=-20e4; */
    TransferFcn = -200000.0;
  }

  /* '<S3>:1:28' q = qaux/2; */
  BIO_csi_sf_smpc_B.q = TransferFcn / 2.0;

  /* End of MATLAB Function: '<S1>/PQ_singlePhase' */
  /*  potencia reactiva instantanea */
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    /* Gain: '<Root>/Gain3' */
    BIO_csi_sf_smpc_B.Gain3 = 2.0 * rtb_PRz;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/Vdc'
   *  Inport: '<Root>/Vload'
   *  Product: '<Root>/Product'
   */
  BIO_csi_sf_smpc_B.Sum_n = BIO_csi_sf_smpc_U.Vdc * BIO_csi_sf_smpc_B.Gain3 -
    BIO_csi_sf_smpc_U.Vload;
  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)V' */
      BIO_csi_sf_smpc_DW.Delay90zV_states = BIO_csi_sf_smpc_DW.Delay90zV_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/PR(z)' */
      BIO_csi_sf_smpc_DW.PRz_states[1] = BIO_csi_sf_smpc_DW.PRz_states[0];
      BIO_csi_sf_smpc_DW.PRz_states[0] = BIO_csi_sf_smpc_DW.PRz_tmp;

      /* Update for DiscreteTransferFcn: '<S1>/Delay90(z)I' */
      BIO_csi_sf_smpc_DW.Delay90zI_states = BIO_csi_sf_smpc_DW.Delay90zI_tmp;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(BIO_csi_sf_smpc_M)) {
    rt_ertODEUpdateContinuousStates(&BIO_csi_sf_smpc_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++BIO_csi_sf_smpc_M->Timing.clockTick0;
    BIO_csi_sf_smpc_M->Timing.t[0] = rtsiGetSolverStopTime
      (&BIO_csi_sf_smpc_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      BIO_csi_sf_smpc_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void BIO_csi_sf_smpc_derivatives(void)
{
  XDot_BIO_csi_sf_smpc_T *_rtXdot;
  _rtXdot = ((XDot_BIO_csi_sf_smpc_T *) BIO_csi_sf_smpc_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -2.5 * BIO_csi_sf_smpc_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += BIO_csi_sf_smpc_B.Sum_n;

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
  _rtXdot->Hw1_CSTATE[0] += -341.08603071128289 * BIO_csi_sf_smpc_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[0] += -178.02459475242631 * BIO_csi_sf_smpc_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[1] += 178.0245947524264 * BIO_csi_sf_smpc_X.Hw1_CSTATE[0];
  _rtXdot->Hw1_CSTATE[2] += 199.58239979893239 * BIO_csi_sf_smpc_X.Hw1_CSTATE[1];
  _rtXdot->Hw1_CSTATE[2] += -247.76277465378331 * BIO_csi_sf_smpc_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[2] += -199.58239979893239 * BIO_csi_sf_smpc_X.Hw1_CSTATE[3];
  _rtXdot->Hw1_CSTATE[3] += 199.58239979893244 * BIO_csi_sf_smpc_X.Hw1_CSTATE[2];
  _rtXdot->Hw1_CSTATE[0] += 188.49555921538757 * BIO_csi_sf_smpc_B.q;

  /* Derivatives for StateSpace: '<S1>/Hw6' */
  _rtXdot->Hw6_CSTATE[0] += -341.08603071128289 * BIO_csi_sf_smpc_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[0] += -178.02459475242631 * BIO_csi_sf_smpc_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[1] += 178.0245947524264 * BIO_csi_sf_smpc_X.Hw6_CSTATE[0];
  _rtXdot->Hw6_CSTATE[2] += 199.58239979893239 * BIO_csi_sf_smpc_X.Hw6_CSTATE[1];
  _rtXdot->Hw6_CSTATE[2] += -247.76277465378331 * BIO_csi_sf_smpc_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[2] += -199.58239979893239 * BIO_csi_sf_smpc_X.Hw6_CSTATE[3];
  _rtXdot->Hw6_CSTATE[3] += 199.58239979893244 * BIO_csi_sf_smpc_X.Hw6_CSTATE[2];
  _rtXdot->Hw6_CSTATE[0] += 188.49555921538757 * BIO_csi_sf_smpc_B.p;
}

/* Model initialize function */
void BIO_csi_sf_smpc_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)BIO_csi_sf_smpc_M, 0,
                sizeof(RT_MODEL_BIO_csi_sf_smpc_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&BIO_csi_sf_smpc_M->solverInfo,
                          &BIO_csi_sf_smpc_M->Timing.simTimeStep);
    rtsiSetTPtr(&BIO_csi_sf_smpc_M->solverInfo, &rtmGetTPtr(BIO_csi_sf_smpc_M));
    rtsiSetStepSizePtr(&BIO_csi_sf_smpc_M->solverInfo,
                       &BIO_csi_sf_smpc_M->Timing.stepSize0);
    rtsiSetdXPtr(&BIO_csi_sf_smpc_M->solverInfo, &BIO_csi_sf_smpc_M->derivs);
    rtsiSetContStatesPtr(&BIO_csi_sf_smpc_M->solverInfo, (real_T **)
                         &BIO_csi_sf_smpc_M->contStates);
    rtsiSetNumContStatesPtr(&BIO_csi_sf_smpc_M->solverInfo,
      &BIO_csi_sf_smpc_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&BIO_csi_sf_smpc_M->solverInfo,
      &BIO_csi_sf_smpc_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&BIO_csi_sf_smpc_M->solverInfo,
      &BIO_csi_sf_smpc_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&BIO_csi_sf_smpc_M->solverInfo,
      &BIO_csi_sf_smpc_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&BIO_csi_sf_smpc_M->solverInfo, (&rtmGetErrorStatus
      (BIO_csi_sf_smpc_M)));
    rtsiSetRTModelPtr(&BIO_csi_sf_smpc_M->solverInfo, BIO_csi_sf_smpc_M);
  }

  rtsiSetSimTimeStep(&BIO_csi_sf_smpc_M->solverInfo, MAJOR_TIME_STEP);
  BIO_csi_sf_smpc_M->intgData.y = BIO_csi_sf_smpc_M->odeY;
  BIO_csi_sf_smpc_M->intgData.f[0] = BIO_csi_sf_smpc_M->odeF[0];
  BIO_csi_sf_smpc_M->intgData.f[1] = BIO_csi_sf_smpc_M->odeF[1];
  BIO_csi_sf_smpc_M->intgData.f[2] = BIO_csi_sf_smpc_M->odeF[2];
  BIO_csi_sf_smpc_M->intgData.f[3] = BIO_csi_sf_smpc_M->odeF[3];
  BIO_csi_sf_smpc_M->contStates = ((X_BIO_csi_sf_smpc_T *) &BIO_csi_sf_smpc_X);
  rtsiSetSolverData(&BIO_csi_sf_smpc_M->solverInfo, (void *)
                    &BIO_csi_sf_smpc_M->intgData);
  rtsiSetSolverName(&BIO_csi_sf_smpc_M->solverInfo,"ode4");
  rtmSetTPtr(BIO_csi_sf_smpc_M, &BIO_csi_sf_smpc_M->Timing.tArray[0]);
  BIO_csi_sf_smpc_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &BIO_csi_sf_smpc_B), 0,
                sizeof(B_BIO_csi_sf_smpc_T));

  /* states (continuous) */
  {
    (void) memset((void *)&BIO_csi_sf_smpc_X, 0,
                  sizeof(X_BIO_csi_sf_smpc_T));
  }

  /* states (dwork) */
  (void) memset((void *)&BIO_csi_sf_smpc_DW, 0,
                sizeof(DW_BIO_csi_sf_smpc_T));

  /* external inputs */
  (void)memset((void *)&BIO_csi_sf_smpc_U, 0, sizeof(ExtU_BIO_csi_sf_smpc_T));

  /* external outputs */
  (void) memset((void *)&BIO_csi_sf_smpc_Y, 0,
                sizeof(ExtY_BIO_csi_sf_smpc_T));

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  BIO_csi_sf_smpc_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_X.Hw1_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_X.Hw6_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_X.Hw1_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_X.Hw6_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_X.Hw1_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_X.Hw6_CSTATE[2] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw1' */
  BIO_csi_sf_smpc_X.Hw1_CSTATE[3] = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/Hw6' */
  BIO_csi_sf_smpc_X.Hw6_CSTATE[3] = 0.0;
}

/* Model terminate function */
void BIO_csi_sf_smpc_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

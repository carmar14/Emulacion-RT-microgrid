/*
 * File: carga_reno.h
 *
 * Code generated for Simulink model 'carga_reno'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Dec 13 10:39:26 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_carga_reno_h_
#define RTW_HEADER_carga_reno_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef carga_reno_COMMON_INCLUDES_
# define carga_reno_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* carga_reno_COMMON_INCLUDES_ */

#include "carga_reno_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Memory;                       /* '<S14>/Memory' */
  real_T Switch;                       /* '<S14>/Switch' */
  real_T Memory_i;                     /* '<S13>/Memory' */
  real_T Switch_a;                     /* '<S13>/Switch' */
  real_T Memory_g;                     /* '<S18>/Memory' */
  real_T Switch_g;                     /* '<S18>/Switch' */
  real_T Memory_in;                    /* '<S17>/Memory' */
  real_T Switch_j;                     /* '<S17>/Switch' */
  real_T Product;                      /* '<S9>/Product' */
  real_T Product1;                     /* '<S9>/Product1' */
  real_T Gain7;                        /* '<Root>/Gain7' */
  real_T Delay90zI;                    /* '<S1>/Delay90(z)I' */
  real_T Delay90zV;                    /* '<S1>/Delay90(z)V' */
  real_T Gain16;                       /* '<Root>/Gain16' */
  real_T Gain5;                        /* '<Root>/Gain5' */
  real_T Gain6;                        /* '<Root>/Gain6' */
  real_T Sum14;                        /* '<Root>/Sum14' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T Product_i;                    /* '<S10>/Product' */
  real_T Product1_h;                   /* '<S10>/Product1' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
} B_carga_reno_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Memory_PreviousInput;         /* '<S14>/Memory' */
  real_T Memory_PreviousInput_f;       /* '<S13>/Memory' */
  real_T Memory_PreviousInput_p;       /* '<S18>/Memory' */
  real_T Memory_PreviousInput_m;       /* '<S17>/Memory' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S14>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_e;            /* '<S13>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_a;            /* '<S18>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_f;            /* '<S17>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S14>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_k;            /* '<S13>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_i;            /* '<S18>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_h;            /* '<S17>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S14>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_p;            /* '<S13>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_l;            /* '<S18>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_ph;           /* '<S17>/Transport Delay' */
} DW_carga_reno_T;

/* Continuous states (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_k;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_l;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S17>/integrator' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
  real_T Integrator4_CSTATE;           /* '<Root>/Integrator4' */
  real_T Integrator5_CSTATE;           /* '<Root>/Integrator5' */
  real_T Integrator9_CSTATE;           /* '<Root>/Integrator9' */
  real_T Integrator3_CSTATE;           /* '<Root>/Integrator3' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} X_carga_reno_T;

/* State derivatives (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_k;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_l;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S17>/integrator' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
  real_T Integrator4_CSTATE;           /* '<Root>/Integrator4' */
  real_T Integrator5_CSTATE;           /* '<Root>/Integrator5' */
  real_T Integrator9_CSTATE;           /* '<Root>/Integrator9' */
  real_T Integrator3_CSTATE;           /* '<Root>/Integrator3' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} XDot_carga_reno_T;

/* State disabled  */
typedef struct {
  boolean_T integrator_CSTATE;         /* '<S14>/integrator' */
  boolean_T integrator_CSTATE_k;       /* '<S13>/integrator' */
  boolean_T integrator_CSTATE_l;       /* '<S18>/integrator' */
  boolean_T integrator_CSTATE_p;       /* '<S17>/integrator' */
  boolean_T TransferFcn3_CSTATE[2];    /* '<Root>/Transfer Fcn3' */
  boolean_T Integrator4_CSTATE;        /* '<Root>/Integrator4' */
  boolean_T Integrator5_CSTATE;        /* '<Root>/Integrator5' */
  boolean_T Integrator9_CSTATE;        /* '<Root>/Integrator9' */
  boolean_T Integrator3_CSTATE;        /* '<Root>/Integrator3' */
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
} XDis_carga_reno_T;

#ifndef ODE8_INTG
#define ODE8_INTG

/* ODE8 Integration Data */
typedef struct {
  real_T *deltaY;                      /* output diff */
  real_T *f[13];                       /* derivatives */
  real_T *x0;                          /* Initial State */
} ODE8_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [0 10 200 500 800 1000 1140 1150 1200]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_tableData[9];

  /* Expression: [0 10 20 30 40 50 70 80 100]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_bp01Data[9];
} ConstP_carga_reno_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T i1;                           /* '<Root>/i1' */
  real_T i3;                           /* '<Root>/i3' */
  real_T Piren;                        /* '<Root>/Piren' */
  real_T Qiren;                        /* '<Root>/Qiren' */
  real_T Ipv;                          /* '<Root>/Ipv' */
} ExtU_carga_reno_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T potencia;                     /* '<Root>/potencia' */
  real_T Po;                           /* '<Root>/Po' */
  real_T Qo;                           /* '<Root>/Qo' */
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Qoren;                        /* '<Root>/Qoren' */
  real_T Poren;                        /* '<Root>/Poren' */
  real_T soc;                          /* '<Root>/soc' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
  real_T i2;                           /* '<Root>/i2' */
} ExtY_carga_reno_T;

/* Real-time Model Data Structure */
struct tag_RTM_carga_reno_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_carga_reno_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T OdeDeltaY[18];
  real_T odeF[13][18];
  real_T odeX0[18];
  ODE8_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_carga_reno_T carga_reno_B;

/* Continuous states (default storage) */
extern X_carga_reno_T carga_reno_X;

/* Block states (default storage) */
extern DW_carga_reno_T carga_reno_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_carga_reno_T carga_reno_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_carga_reno_T carga_reno_Y;

/* Constant parameters (default storage) */
extern const ConstP_carga_reno_T carga_reno_ConstP;

/* Model entry point functions */
extern void carga_reno_initialize(void);
extern void carga_reno_step(void);
extern void carga_reno_terminate(void);

//Funciones creadas por el programador set y get
//-------Funciones para asignar entradas-------------
extern void set_Idc_PV(double);
extern void set_Pref(double);	
extern void set_Qref(double);
extern void set_i1(double);
extern void set_i3(double);

//-----Funciones para obtener valores de las salidas-------
	
extern double get_I_pv(void);
extern double get_SOC(void);
extern double get_duty_cycle(void);
extern double get_Pm2(void);
extern double get_Qm2(void);
extern double get_Potencia(void);
extern double get_Pm(void);
extern double get_Qm(void);
extern double get_Vload(void);


/* Real-time Model object */
extern RT_MODEL_carga_reno_T *const carga_reno_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'carga_reno'
 * '<S1>'   : 'carga_reno/CSI_Control_BIO1'
 * '<S2>'   : 'carga_reno/MATLAB Function'
 * '<S3>'   : 'carga_reno/MATLAB Function SOC '
 * '<S4>'   : 'carga_reno/Power'
 * '<S5>'   : 'carga_reno/CSI_Control_BIO1/PQ2Iab_PH1'
 * '<S6>'   : 'carga_reno/CSI_Control_BIO1/PQ_singlePhase'
 * '<S7>'   : 'carga_reno/CSI_Control_BIO1/PR Controller_0_ref 1'
 * '<S8>'   : 'carga_reno/CSI_Control_BIO1/PR Controller_0_ref 1/Steper6'
 * '<S9>'   : 'carga_reno/Power/Fourier'
 * '<S10>'  : 'carga_reno/Power/Fourier1'
 * '<S11>'  : 'carga_reno/Power/Fourier/Mean'
 * '<S12>'  : 'carga_reno/Power/Fourier/Mean value1'
 * '<S13>'  : 'carga_reno/Power/Fourier/Mean/Model'
 * '<S14>'  : 'carga_reno/Power/Fourier/Mean value1/Model'
 * '<S15>'  : 'carga_reno/Power/Fourier1/Mean'
 * '<S16>'  : 'carga_reno/Power/Fourier1/Mean value1'
 * '<S17>'  : 'carga_reno/Power/Fourier1/Mean/Model'
 * '<S18>'  : 'carga_reno/Power/Fourier1/Mean value1/Model'
 */
#endif                                 /* RTW_HEADER_carga_reno_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

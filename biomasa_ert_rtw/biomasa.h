/*
 * File: biomasa.h
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

#ifndef RTW_HEADER_biomasa_h_
#define RTW_HEADER_biomasa_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef biomasa_COMMON_INCLUDES_
# define biomasa_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* biomasa_COMMON_INCLUDES_ */

#include "biomasa_types.h"
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
  real_T Delay90zI;                    /* '<S1>/Delay90(z)I' */
  real_T Delay90zV;                    /* '<S1>/Delay90(z)V' */
  real_T Gain15;                       /* '<Root>/Gain15' */
  real_T Product2;                     /* '<S4>/Product2' */
  real_T Torquemecnico;                /* '<S4>/Add2' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T Gain1;                        /* '<Root>/Gain1' */
  real_T Sum1;                         /* '<S4>/Sum1' */
  real_T Sum3;                         /* '<S4>/Sum3' */
  real_T Add;                          /* '<S4>/Add' */
  real_T Product3;                     /* '<S4>/Product3' */
  real_T Add4;                         /* '<S4>/Add4' */
  real_T Add5;                         /* '<S4>/Add5' */
  real_T Product;                      /* '<S9>/Product' */
  real_T Product1;                     /* '<S9>/Product1' */
  real_T Gain2;                        /* '<Root>/Gain2' */
  real_T Product_b;                    /* '<S10>/Product' */
  real_T Product1_n;                   /* '<S10>/Product1' */
  real_T Memory;                       /* '<S14>/Memory' */
  real_T Switch;                       /* '<S14>/Switch' */
  real_T Memory_h;                     /* '<S13>/Memory' */
  real_T Switch_l;                     /* '<S13>/Switch' */
  real_T Memory_l;                     /* '<S18>/Memory' */
  real_T Switch_n;                     /* '<S18>/Switch' */
  real_T Memory_m;                     /* '<S17>/Memory' */
  real_T Switch_d;                     /* '<S17>/Switch' */
  real_T Delaycombustor;               /* '<S4>/Delay combustor' */
  real_T ValvePositioner;              /* '<S4>/Valve Positioner' */
  real_T Xmethp;                       /* '<S4>/MATLAB Function metanogenesis' */
  real_T Sbp;                          /* '<S4>/MATLAB Function Hidrolisis' */
  real_T Svp;                          /* '<S4>/MATLAB Function Acidogenesis' */
  real_T Xacidp;                       /* '<S4>/MATLAB Function Acetogenesis' */
  real_T y;                            /* '<S4>/MATLAB Function' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
} B_biomasa_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay_DSTATE;                 /* '<S4>/Delay' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  real_T Memory_PreviousInput;         /* '<S14>/Memory' */
  real_T Memory_PreviousInput_p;       /* '<S13>/Memory' */
  real_T Memory_PreviousInput_a;       /* '<S18>/Memory' */
  real_T Memory_PreviousInput_f;       /* '<S17>/Memory' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Delaycombustor1_RWORK;             /* '<S4>/Delay combustor1' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Turbineexhaustsystemdelay_RWORK;   /* '<S4>/Turbine exhaust system delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S14>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_k;            /* '<S13>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_o;            /* '<S18>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_g;            /* '<S17>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Delaycombustor_RWORK;              /* '<S4>/Delay combustor' */

  struct {
    void *TUbufferPtrs[2];
  } Delaycombustor1_PWORK;             /* '<S4>/Delay combustor1' */

  struct {
    void *TUbufferPtrs[2];
  } Turbineexhaustsystemdelay_PWORK;   /* '<S4>/Turbine exhaust system delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S14>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_p;            /* '<S13>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_f;            /* '<S18>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_j;            /* '<S17>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } Delaycombustor_PWORK;              /* '<S4>/Delay combustor' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Delaycombustor1_IWORK;             /* '<S4>/Delay combustor1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Turbineexhaustsystemdelay_IWORK;   /* '<S4>/Turbine exhaust system delay' */

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
  } TransportDelay_IWORK_g;            /* '<S13>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_e;            /* '<S18>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_c;            /* '<S17>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Delaycombustor_IWORK;              /* '<S4>/Delay combustor' */
} DW_biomasa_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator2' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T Compresor_CSTATE;             /* '<S4>/Compresor' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S4>/Transfer Fcn' */
  real_T thermocouple_CSTATE;          /* '<S4>/thermo couple' */
  real_T TempControl_CSTATE;           /* '<S4>/Temp Control' */
  real_T Integrator3_CSTATE;           /* '<S4>/Integrator3' */
  real_T Integrator1_CSTATE_o;         /* '<S4>/Integrator1' */
  real_T Integrator_CSTATE_i;          /* '<S4>/Integrator' */
  real_T Integrator2_CSTATE_j;         /* '<S4>/Integrator2' */
  real_T RotationShield_CSTATE;        /* '<S4>/Rotation Shield' */
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_d;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_e;          /* '<S17>/integrator' */
  real_T Fuelsystemactuator_CSTATE;    /* '<S4>/Fuel system actuator' */
  real_T ValvePositioner_CSTATE;       /* '<S4>/Valve Positioner' */
} X_biomasa_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator2' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T Compresor_CSTATE;             /* '<S4>/Compresor' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S4>/Transfer Fcn' */
  real_T thermocouple_CSTATE;          /* '<S4>/thermo couple' */
  real_T TempControl_CSTATE;           /* '<S4>/Temp Control' */
  real_T Integrator3_CSTATE;           /* '<S4>/Integrator3' */
  real_T Integrator1_CSTATE_o;         /* '<S4>/Integrator1' */
  real_T Integrator_CSTATE_i;          /* '<S4>/Integrator' */
  real_T Integrator2_CSTATE_j;         /* '<S4>/Integrator2' */
  real_T RotationShield_CSTATE;        /* '<S4>/Rotation Shield' */
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_d;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_e;          /* '<S17>/integrator' */
  real_T Fuelsystemactuator_CSTATE;    /* '<S4>/Fuel system actuator' */
  real_T ValvePositioner_CSTATE;       /* '<S4>/Valve Positioner' */
} XDot_biomasa_T;

/* State disabled  */
typedef struct {
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
  boolean_T Integrator2_CSTATE;        /* '<Root>/Integrator2' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
  boolean_T Compresor_CSTATE;          /* '<S4>/Compresor' */
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T TransferFcn_CSTATE;        /* '<S4>/Transfer Fcn' */
  boolean_T thermocouple_CSTATE;       /* '<S4>/thermo couple' */
  boolean_T TempControl_CSTATE;        /* '<S4>/Temp Control' */
  boolean_T Integrator3_CSTATE;        /* '<S4>/Integrator3' */
  boolean_T Integrator1_CSTATE_o;      /* '<S4>/Integrator1' */
  boolean_T Integrator_CSTATE_i;       /* '<S4>/Integrator' */
  boolean_T Integrator2_CSTATE_j;      /* '<S4>/Integrator2' */
  boolean_T RotationShield_CSTATE;     /* '<S4>/Rotation Shield' */
  boolean_T integrator_CSTATE;         /* '<S14>/integrator' */
  boolean_T integrator_CSTATE_d;       /* '<S13>/integrator' */
  boolean_T integrator_CSTATE_p;       /* '<S18>/integrator' */
  boolean_T integrator_CSTATE_e;       /* '<S17>/integrator' */
  boolean_T Fuelsystemactuator_CSTATE; /* '<S4>/Fuel system actuator' */
  boolean_T ValvePositioner_CSTATE;    /* '<S4>/Valve Positioner' */
} XDis_biomasa_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S4>/Gain' */
  const real_T Sum;                    /* '<S4>/Sum' */
} ConstB_biomasa_T;

#ifndef ODE8_INTG
#define ODE8_INTG

/* ODE8 Integration Data */
typedef struct {
  real_T *deltaY;                      /* output diff */
  real_T *f[13];                       /* derivatives */
  real_T *x0;                          /* Initial State */
} ODE8_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Pibio;                        /* '<Root>/Pibio' */
  real_T Qibio;                        /* '<Root>/Qibio' */
} ExtU_biomasa_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Qobio;                        /* '<Root>/Qobio' */
  real_T Pobio;                        /* '<Root>/Pobio' */
  real_T i1;                           /* '<Root>/i1' */
  real_T Potencia_bio;                 /* '<Root>/Potencia_bio' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
} ExtY_biomasa_T;

/* Real-time Model Data Structure */
struct tag_RTM_biomasa_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_biomasa_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T OdeDeltaY[26];
  real_T odeF[13][26];
  real_T odeX0[26];
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
extern B_biomasa_T biomasa_B;

/* Continuous states (default storage) */
extern X_biomasa_T biomasa_X;

/* Block states (default storage) */
extern DW_biomasa_T biomasa_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_biomasa_T biomasa_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_biomasa_T biomasa_Y;
extern const ConstB_biomasa_T biomasa_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void biomasa_initialize(void);
extern void biomasa_step(void);
extern void biomasa_terminate(void);

/* Real-time Model object */
extern RT_MODEL_biomasa_T *const biomasa_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope2' : Unused code path elimination
 * Block '<S4>/Scope3' : Unused code path elimination
 * Block '<S4>/Scope4' : Unused code path elimination
 * Block '<S4>/Scope5' : Unused code path elimination
 * Block '<S4>/Scope6' : Unused code path elimination
 * Block '<S4>/Scope7' : Unused code path elimination
 * Block '<S4>/Scope8' : Unused code path elimination
 * Block '<S4>/Scope9' : Unused code path elimination
 * Block '<S4>/Gain3' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'biomasa'
 * '<S1>'   : 'biomasa/CSI_Control_BIO'
 * '<S2>'   : 'biomasa/MATLAB Function5'
 * '<S3>'   : 'biomasa/Power3'
 * '<S4>'   : 'biomasa/generador biomasa'
 * '<S5>'   : 'biomasa/CSI_Control_BIO/PQ2Iab_PH1'
 * '<S6>'   : 'biomasa/CSI_Control_BIO/PQ_singlePhase'
 * '<S7>'   : 'biomasa/CSI_Control_BIO/PR Controller_0_ref 1'
 * '<S8>'   : 'biomasa/CSI_Control_BIO/PR Controller_0_ref 1/Steper6'
 * '<S9>'   : 'biomasa/Power3/Fourier'
 * '<S10>'  : 'biomasa/Power3/Fourier1'
 * '<S11>'  : 'biomasa/Power3/Fourier/Mean'
 * '<S12>'  : 'biomasa/Power3/Fourier/Mean value1'
 * '<S13>'  : 'biomasa/Power3/Fourier/Mean/Model'
 * '<S14>'  : 'biomasa/Power3/Fourier/Mean value1/Model'
 * '<S15>'  : 'biomasa/Power3/Fourier1/Mean'
 * '<S16>'  : 'biomasa/Power3/Fourier1/Mean value1'
 * '<S17>'  : 'biomasa/Power3/Fourier1/Mean/Model'
 * '<S18>'  : 'biomasa/Power3/Fourier1/Mean value1/Model'
 * '<S19>'  : 'biomasa/generador biomasa/MATLAB Function'
 * '<S20>'  : 'biomasa/generador biomasa/MATLAB Function Acetogenesis'
 * '<S21>'  : 'biomasa/generador biomasa/MATLAB Function Acidogenesis'
 * '<S22>'  : 'biomasa/generador biomasa/MATLAB Function Hidrolisis'
 * '<S23>'  : 'biomasa/generador biomasa/MATLAB Function metano'
 * '<S24>'  : 'biomasa/generador biomasa/MATLAB Function metanogenesis'
 */
#endif                                 /* RTW_HEADER_biomasa_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

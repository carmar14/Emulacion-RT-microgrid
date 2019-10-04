/*
 * File: renovables.h
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

#ifndef RTW_HEADER_renovables_h_
#define RTW_HEADER_renovables_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef renovables_COMMON_INCLUDES_
# define renovables_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* renovables_COMMON_INCLUDES_ */

#include "renovables_types.h"
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
  real_T Gain16;                       /* '<Root>/Gain16' */
  real_T Gain5;                        /* '<Root>/Gain5' */
  real_T Gain6;                        /* '<Root>/Gain6' */
  real_T Sum14;                        /* '<Root>/Sum14' */
  real_T Product;                      /* '<S9>/Product' */
  real_T Product1;                     /* '<S9>/Product1' */
  real_T Gain7;                        /* '<Root>/Gain7' */
  real_T Product_d;                    /* '<S10>/Product' */
  real_T Product1_p;                   /* '<S10>/Product1' */
  real_T Memory;                       /* '<S14>/Memory' */
  real_T Switch;                       /* '<S14>/Switch' */
  real_T Memory_e;                     /* '<S13>/Memory' */
  real_T Switch_i;                     /* '<S13>/Switch' */
  real_T Memory_e4;                    /* '<S18>/Memory' */
  real_T Switch_f;                     /* '<S18>/Switch' */
  real_T Memory_g;                     /* '<S17>/Memory' */
  real_T Switch_n;                     /* '<S17>/Switch' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
} B_renovables_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  real_T Memory_PreviousInput;         /* '<S14>/Memory' */
  real_T Memory_PreviousInput_b;       /* '<S13>/Memory' */
  real_T Memory_PreviousInput_m;       /* '<S18>/Memory' */
  real_T Memory_PreviousInput_i;       /* '<S17>/Memory' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S14>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_d;            /* '<S13>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_n;            /* '<S18>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_nm;           /* '<S17>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S14>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_d;            /* '<S13>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_n;            /* '<S18>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_o;            /* '<S17>/Transport Delay' */

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
  } TransportDelay_IWORK_f;            /* '<S13>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_n;            /* '<S18>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_g;            /* '<S17>/Transport Delay' */
} DW_renovables_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Integrator5_CSTATE;           /* '<Root>/Integrator5' */
  real_T Integrator4_CSTATE;           /* '<Root>/Integrator4' */
  real_T Integrator9_CSTATE;           /* '<Root>/Integrator9' */
  real_T Integrator3_CSTATE;           /* '<Root>/Integrator3' */
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_n;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_d;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_j;          /* '<S17>/integrator' */
} X_renovables_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Integrator5_CSTATE;           /* '<Root>/Integrator5' */
  real_T Integrator4_CSTATE;           /* '<Root>/Integrator4' */
  real_T Integrator9_CSTATE;           /* '<Root>/Integrator9' */
  real_T Integrator3_CSTATE;           /* '<Root>/Integrator3' */
  real_T integrator_CSTATE;            /* '<S14>/integrator' */
  real_T integrator_CSTATE_n;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_d;          /* '<S18>/integrator' */
  real_T integrator_CSTATE_j;          /* '<S17>/integrator' */
} XDot_renovables_T;

/* State disabled  */
typedef struct {
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
  boolean_T Integrator5_CSTATE;        /* '<Root>/Integrator5' */
  boolean_T Integrator4_CSTATE;        /* '<Root>/Integrator4' */
  boolean_T Integrator9_CSTATE;        /* '<Root>/Integrator9' */
  boolean_T Integrator3_CSTATE;        /* '<Root>/Integrator3' */
  boolean_T integrator_CSTATE;         /* '<S14>/integrator' */
  boolean_T integrator_CSTATE_n;       /* '<S13>/integrator' */
  boolean_T integrator_CSTATE_d;       /* '<S18>/integrator' */
  boolean_T integrator_CSTATE_j;       /* '<S17>/integrator' */
} XDis_renovables_T;

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
} ConstP_renovables_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Piren;                        /* '<Root>/Piren' */
  real_T Qiren;                        /* '<Root>/Qiren' */
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Ipv;                          /* '<Root>/Ipv' */
} ExtU_renovables_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Qoren;                        /* '<Root>/Qoren' */
  real_T Poren;                        /* '<Root>/Poren' */
  real_T i2;                           /* '<Root>/i2' */
  real_T Potencia_ren;                 /* '<Root>/Potencia_ren' */
  real_T soc;                          /* '<Root>/soc' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
} ExtY_renovables_T;

/* Real-time Model Data Structure */
struct tag_RTM_renovables_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_renovables_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T OdeDeltaY[16];
  real_T odeF[13][16];
  real_T odeX0[16];
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
extern B_renovables_T renovables_B;

/* Continuous states (default storage) */
extern X_renovables_T renovables_X;

/* Block states (default storage) */
extern DW_renovables_T renovables_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_renovables_T renovables_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_renovables_T renovables_Y;

/* Constant parameters (default storage) */
extern const ConstP_renovables_T renovables_ConstP;

/* Model entry point functions */
extern void renovables_initialize(void);
extern void renovables_step(void);
extern void renovables_terminate(void);

/* Real-time Model object */
extern RT_MODEL_renovables_T *const renovables_M;

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
 * '<Root>' : 'renovables'
 * '<S1>'   : 'renovables/CSI_Control_BIO1'
 * '<S2>'   : 'renovables/MATLAB Function SOC '
 * '<S3>'   : 'renovables/MATLAB Function6'
 * '<S4>'   : 'renovables/Power4'
 * '<S5>'   : 'renovables/CSI_Control_BIO1/PQ2Iab_PH1'
 * '<S6>'   : 'renovables/CSI_Control_BIO1/PQ_singlePhase'
 * '<S7>'   : 'renovables/CSI_Control_BIO1/PR Controller_0_ref 1'
 * '<S8>'   : 'renovables/CSI_Control_BIO1/PR Controller_0_ref 1/Steper6'
 * '<S9>'   : 'renovables/Power4/Fourier'
 * '<S10>'  : 'renovables/Power4/Fourier1'
 * '<S11>'  : 'renovables/Power4/Fourier/Mean'
 * '<S12>'  : 'renovables/Power4/Fourier/Mean value1'
 * '<S13>'  : 'renovables/Power4/Fourier/Mean/Model'
 * '<S14>'  : 'renovables/Power4/Fourier/Mean value1/Model'
 * '<S15>'  : 'renovables/Power4/Fourier1/Mean'
 * '<S16>'  : 'renovables/Power4/Fourier1/Mean value1'
 * '<S17>'  : 'renovables/Power4/Fourier1/Mean/Model'
 * '<S18>'  : 'renovables/Power4/Fourier1/Mean value1/Model'
 */
#endif                                 /* RTW_HEADER_renovables_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

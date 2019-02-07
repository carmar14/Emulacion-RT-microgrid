/*
 * File: cargaRLC_variable.h
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

#ifndef RTW_HEADER_cargaRLC_variable_h_
#define RTW_HEADER_cargaRLC_variable_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef cargaRLC_variable_COMMON_INCLUDES_
# define cargaRLC_variable_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* cargaRLC_variable_COMMON_INCLUDES_ */

#include "cargaRLC_variable_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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
  real_T Memory;                       /* '<S10>/Memory' */
  real_T Switch;                       /* '<S10>/Switch' */
  real_T Memory_j;                     /* '<S9>/Memory' */
  real_T Switch_e;                     /* '<S9>/Switch' */
  real_T Memory_c;                     /* '<S14>/Memory' */
  real_T Switch_ey;                    /* '<S14>/Switch' */
  real_T Memory_i;                     /* '<S13>/Memory' */
  real_T Switch_o;                     /* '<S13>/Switch' */
  real_T Integrator1;                  /* '<Root>/Integrator1' */
  real_T Product;                      /* '<S6>/Product' */
  real_T Product1;                     /* '<S6>/Product1' */
  real_T Product_f;                    /* '<S5>/Product' */
  real_T Product1_f;                   /* '<S5>/Product1' */
  real_T dv;                           /* '<Root>/MATLAB Function' */
} B_cargaRLC_variable_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<S10>/Memory' */
  real_T Memory_PreviousInput_n;       /* '<S9>/Memory' */
  real_T Memory_PreviousInput_i;       /* '<S14>/Memory' */
  real_T Memory_PreviousInput_np;      /* '<S13>/Memory' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S10>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_n;            /* '<S9>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_f;            /* '<S14>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_h;            /* '<S13>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S10>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_k;            /* '<S9>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_f;            /* '<S14>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_b;            /* '<S13>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S10>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_h;            /* '<S9>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_p;            /* '<S14>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_g;            /* '<S13>/Transport Delay' */
} DW_cargaRLC_variable_T;

/* Continuous states (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S10>/integrator' */
  real_T integrator_CSTATE_a;          /* '<S9>/integrator' */
  real_T integrator_CSTATE_g;          /* '<S14>/integrator' */
  real_T integrator_CSTATE_gj;         /* '<S13>/integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator2' */
} X_cargaRLC_variable_T;

/* State derivatives (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S10>/integrator' */
  real_T integrator_CSTATE_a;          /* '<S9>/integrator' */
  real_T integrator_CSTATE_g;          /* '<S14>/integrator' */
  real_T integrator_CSTATE_gj;         /* '<S13>/integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<Root>/Integrator2' */
} XDot_cargaRLC_variable_T;

/* State disabled  */
typedef struct {
  boolean_T integrator_CSTATE;         /* '<S10>/integrator' */
  boolean_T integrator_CSTATE_a;       /* '<S9>/integrator' */
  boolean_T integrator_CSTATE_g;       /* '<S14>/integrator' */
  boolean_T integrator_CSTATE_gj;      /* '<S13>/integrator' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
  boolean_T Integrator2_CSTATE;        /* '<Root>/Integrator2' */
} XDis_cargaRLC_variable_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T i1;                           /* '<Root>/i1' */
  real_T i2;                           /* '<Root>/i2' */
  real_T i3;                           /* '<Root>/i3' */
  real_T P;                            /* '<Root>/P' */
  real_T Q;                            /* '<Root>/Q' */
} ExtU_cargaRLC_variable_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Pm;                           /* '<Root>/Pm' */
  real_T Qm;                           /* '<Root>/Qm' */
  real_T Vload;                        /* '<Root>/Vload' */
} ExtY_cargaRLC_variable_T;

/* Real-time Model Data Structure */
struct tag_RTM_cargaRLC_variable_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_cargaRLC_variable_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[4][6];
  ODE4_IntgData intgData;

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
extern B_cargaRLC_variable_T cargaRLC_variable_B;

/* Continuous states (default storage) */
extern X_cargaRLC_variable_T cargaRLC_variable_X;

/* Block states (default storage) */
extern DW_cargaRLC_variable_T cargaRLC_variable_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_cargaRLC_variable_T cargaRLC_variable_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_cargaRLC_variable_T cargaRLC_variable_Y;

/* Model entry point functions */
extern void cargaRLC_variable_initialize(void);
extern void cargaRLC_variable_step(void);
extern void cargaRLC_variable_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_i1(double);
extern void set_i2(double);
extern void set_i3(double);
extern void set_P(double);
extern void set_Q(double);
//-----Funciones para obtener valores de las salidas-------
extern double get_Pm(void);
extern double get_Qm(void);
extern double get_Vload(void);

/* Real-time Model object */
extern RT_MODEL_cargaRLC_variable_T *const cargaRLC_variable_M;

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
 * '<Root>' : 'cargaRLC_variable'
 * '<S1>'   : 'cargaRLC_variable/MATLAB Function'
 * '<S2>'   : 'cargaRLC_variable/Power'
 * '<S3>'   : 'cargaRLC_variable/Repeating Sequence Stair2'
 * '<S4>'   : 'cargaRLC_variable/Repeating Sequence Stair3'
 * '<S5>'   : 'cargaRLC_variable/Power/Fourier'
 * '<S6>'   : 'cargaRLC_variable/Power/Fourier1'
 * '<S7>'   : 'cargaRLC_variable/Power/Fourier/Mean'
 * '<S8>'   : 'cargaRLC_variable/Power/Fourier/Mean value1'
 * '<S9>'   : 'cargaRLC_variable/Power/Fourier/Mean/Model'
 * '<S10>'  : 'cargaRLC_variable/Power/Fourier/Mean value1/Model'
 * '<S11>'  : 'cargaRLC_variable/Power/Fourier1/Mean'
 * '<S12>'  : 'cargaRLC_variable/Power/Fourier1/Mean value1'
 * '<S13>'  : 'cargaRLC_variable/Power/Fourier1/Mean/Model'
 * '<S14>'  : 'cargaRLC_variable/Power/Fourier1/Mean value1/Model'
 * '<S15>'  : 'cargaRLC_variable/Repeating Sequence Stair2/LimitedCounter'
 * '<S16>'  : 'cargaRLC_variable/Repeating Sequence Stair2/LimitedCounter/Increment Real World'
 * '<S17>'  : 'cargaRLC_variable/Repeating Sequence Stair2/LimitedCounter/Wrap To Zero'
 * '<S18>'  : 'cargaRLC_variable/Repeating Sequence Stair3/LimitedCounter'
 * '<S19>'  : 'cargaRLC_variable/Repeating Sequence Stair3/LimitedCounter/Increment Real World'
 * '<S20>'  : 'cargaRLC_variable/Repeating Sequence Stair3/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_cargaRLC_variable_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: carga_new.h
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

#ifndef RTW_HEADER_carga_new_h_
#define RTW_HEADER_carga_new_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef carga_new_COMMON_INCLUDES_
# define carga_new_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* carga_new_COMMON_INCLUDES_ */

#include "carga_new_types.h"
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
  real_T Memory;                       /* '<S8>/Memory' */
  real_T Switch;                       /* '<S8>/Switch' */
  real_T Memory_i;                     /* '<S7>/Memory' */
  real_T Switch_a;                     /* '<S7>/Switch' */
  real_T Memory_g;                     /* '<S12>/Memory' */
  real_T Switch_g;                     /* '<S12>/Switch' */
  real_T Memory_in;                    /* '<S11>/Memory' */
  real_T Switch_j;                     /* '<S11>/Switch' */
  real_T Product;                      /* '<S3>/Product' */
  real_T Product1;                     /* '<S3>/Product1' */
  real_T Sum2;                         /* '<Root>/Sum2' */
  real_T Product_i;                    /* '<S4>/Product' */
  real_T Product1_h;                   /* '<S4>/Product1' */
} B_carga_new_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<S8>/Memory' */
  real_T Memory_PreviousInput_f;       /* '<S7>/Memory' */
  real_T Memory_PreviousInput_p;       /* '<S12>/Memory' */
  real_T Memory_PreviousInput_m;       /* '<S11>/Memory' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S8>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_e;            /* '<S7>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_a;            /* '<S12>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_f;            /* '<S11>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S8>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_k;            /* '<S7>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_i;            /* '<S12>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_h;            /* '<S11>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S8>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_p;            /* '<S7>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_l;            /* '<S12>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_ph;           /* '<S11>/Transport Delay' */
} DW_carga_new_T;

/* Continuous states (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S8>/integrator' */
  real_T integrator_CSTATE_k;          /* '<S7>/integrator' */
  real_T integrator_CSTATE_l;          /* '<S12>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S11>/integrator' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
} X_carga_new_T;

/* State derivatives (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S8>/integrator' */
  real_T integrator_CSTATE_k;          /* '<S7>/integrator' */
  real_T integrator_CSTATE_l;          /* '<S12>/integrator' */
  real_T integrator_CSTATE_p;          /* '<S11>/integrator' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
} XDot_carga_new_T;

/* State disabled  */
typedef struct {
  boolean_T integrator_CSTATE;         /* '<S8>/integrator' */
  boolean_T integrator_CSTATE_k;       /* '<S7>/integrator' */
  boolean_T integrator_CSTATE_l;       /* '<S12>/integrator' */
  boolean_T integrator_CSTATE_p;       /* '<S11>/integrator' */
  boolean_T TransferFcn3_CSTATE[2];    /* '<Root>/Transfer Fcn3' */
} XDis_carga_new_T;

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
  real_T i1;                           /* '<Root>/i1' */
  real_T i2;                           /* '<Root>/i2' */
  real_T i3;                           /* '<Root>/i3' */
} ExtU_carga_new_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T potencia;                     /* '<Root>/potencia' */
  real_T Po;                           /* '<Root>/Po' */
  real_T Qo;                           /* '<Root>/Qo' */
  real_T Vload;                        /* '<Root>/Vload' */
} ExtY_carga_new_T;

/* Real-time Model Data Structure */
struct tag_RTM_carga_new_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_carga_new_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T OdeDeltaY[6];
  real_T odeF[13][6];
  real_T odeX0[6];
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
extern B_carga_new_T carga_new_B;

/* Continuous states (default storage) */
extern X_carga_new_T carga_new_X;

/* Block states (default storage) */
extern DW_carga_new_T carga_new_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_carga_new_T carga_new_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_carga_new_T carga_new_Y;

/* Model entry point functions */
extern void carga_new_initialize(void);
extern void carga_new_step(void);
extern void carga_new_terminate(void);

/* Real-time Model object */
extern RT_MODEL_carga_new_T *const carga_new_M;

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
 * '<Root>' : 'carga_new'
 * '<S1>'   : 'carga_new/MATLAB Function'
 * '<S2>'   : 'carga_new/Power'
 * '<S3>'   : 'carga_new/Power/Fourier'
 * '<S4>'   : 'carga_new/Power/Fourier1'
 * '<S5>'   : 'carga_new/Power/Fourier/Mean'
 * '<S6>'   : 'carga_new/Power/Fourier/Mean value1'
 * '<S7>'   : 'carga_new/Power/Fourier/Mean/Model'
 * '<S8>'   : 'carga_new/Power/Fourier/Mean value1/Model'
 * '<S9>'   : 'carga_new/Power/Fourier1/Mean'
 * '<S10>'  : 'carga_new/Power/Fourier1/Mean value1'
 * '<S11>'  : 'carga_new/Power/Fourier1/Mean/Model'
 * '<S12>'  : 'carga_new/Power/Fourier1/Mean value1/Model'
 */
#endif                                 /* RTW_HEADER_carga_new_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: pruebaj2.h
 *
 * Code generated for Simulink model 'pruebaj2'.
 *
 * Model version                  : 1.72
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Sep 17 15:20:04 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pruebaj2_h_
#define RTW_HEADER_pruebaj2_h_
#include <string.h>
#ifndef pruebaj2_COMMON_INCLUDES_
# define pruebaj2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* pruebaj2_COMMON_INCLUDES_ */

#include "pruebaj2_types.h"

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

/* Block signals (auto storage) */
typedef struct {
  real_T Step;                         /* '<Root>/Step' */
  real_T VSIlineZ1;                    /* '<Root>/VSI  line Z1' */
} B_pruebaj2_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T VSIlineZ2_CSTATE;             /* '<Root>/VSI  line Z2' */
  real_T VSIlineZ1_CSTATE;             /* '<Root>/VSI  line Z1' */
} X_pruebaj2_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T VSIlineZ2_CSTATE;             /* '<Root>/VSI  line Z2' */
  real_T VSIlineZ1_CSTATE;             /* '<Root>/VSI  line Z1' */
} XDot_pruebaj2_T;

/* State disabled  */
typedef struct {
  boolean_T VSIlineZ2_CSTATE;          /* '<Root>/VSI  line Z2' */
  boolean_T VSIlineZ1_CSTATE;          /* '<Root>/VSI  line Z1' */
} XDis_pruebaj2_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
} ExtY_pruebaj2_T;

/* Real-time Model Data Structure */
struct tag_RTM_pruebaj2_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_pruebaj2_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[2];
  real_T odeF[4][2];
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

/* Block signals (auto storage) */
extern B_pruebaj2_T pruebaj2_B;

/* Continuous states (auto storage) */
extern X_pruebaj2_T pruebaj2_X;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_pruebaj2_T pruebaj2_Y;

/* Model entry point functions */
extern void pruebaj2_initialize(void);
extern void pruebaj2_step(void);
extern void pruebaj2_terminate(void);



extern double get_1(void);

/* Real-time Model object */
extern RT_MODEL_pruebaj2_T *const pruebaj2_M;

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
 * '<Root>' : 'pruebaj2'
 */
#endif                                 /* RTW_HEADER_pruebaj2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

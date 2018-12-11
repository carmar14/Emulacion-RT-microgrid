/*
 * File: PV_vsi_sf.h
 *
 * Code generated for Simulink model 'PV_vsi_sf'.
 *
 * Model version                  : 1.64
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 13:48:18 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PV_vsi_sf_h_
#define RTW_HEADER_PV_vsi_sf_h_
#include <math.h>
#include <string.h>
#ifndef PV_vsi_sf_COMMON_INCLUDES_
# define PV_vsi_sf_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* PV_vsi_sf_COMMON_INCLUDES_ */

#include "PV_vsi_sf_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

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
  real_T refvoltage;                   /* '<Root>/Sine Wave' */
  real_T Sum3;                         /* '<Root>/Sum3' */
  real_T Sum4;                         /* '<Root>/Sum4' */
  real_T Sum7;                         /* '<Root>/Sum7' */
} B_PV_vsi_sf_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T TimeStampA_e;                 /* '<Root>/Derivative' */
  real_T LastUAtTimeA_n;               /* '<Root>/Derivative' */
  real_T TimeStampB_a;                 /* '<Root>/Derivative' */
  real_T LastUAtTimeB_c;               /* '<Root>/Derivative' */
} DW_PV_vsi_sf_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T VSIlineZ_CSTATE;              /* '<Root>/VSI  line Z' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
} X_PV_vsi_sf_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T VSIlineZ_CSTATE;              /* '<Root>/VSI  line Z' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
} XDot_PV_vsi_sf_T;

/* State disabled  */
typedef struct {
  boolean_T VSIlineZ_CSTATE;           /* '<Root>/VSI  line Z' */
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T TransferFcn2_CSTATE[2];    /* '<S1>/Transfer Fcn2' */
} XDis_PV_vsi_sf_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: [0 10 200 500 800 1000 1140 1150 1200]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_tableData[9];

  /* Expression: [0 10 20 30 40 50 70 80 100]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_bp01Data[9];
} ConstP_PV_vsi_sf_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Ipv;                          /* '<Root>/Ipv' */
} ExtU_PV_vsi_sf_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T i3;                           /* '<Root>/i3' */
  real_T SOC;                          /* '<Root>/SOC' */
} ExtY_PV_vsi_sf_T;

/* Real-time Model Data Structure */
struct tag_RTM_PV_vsi_sf_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_PV_vsi_sf_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[4];
  real_T odeF[4][4];
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
extern B_PV_vsi_sf_T PV_vsi_sf_B;

/* Continuous states (auto storage) */
extern X_PV_vsi_sf_T PV_vsi_sf_X;

/* Block states (auto storage) */
extern DW_PV_vsi_sf_T PV_vsi_sf_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_PV_vsi_sf_T PV_vsi_sf_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_PV_vsi_sf_T PV_vsi_sf_Y;

/* Constant parameters (auto storage) */
extern const ConstP_PV_vsi_sf_T PV_vsi_sf_ConstP;

/* Model entry point functions */
extern void PV_vsi_sf_initialize(void);
extern void PV_vsi_sf_step(void);
extern void PV_vsi_sf_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_Idc_PV(double);
extern void set_Vload(double);
//-----Funciones para obtener valores de las salidas-------
extern double get_I_pv(void);
extern double get_SOC(void);

/* Real-time Model object */
extern RT_MODEL_PV_vsi_sf_T *const PV_vsi_sf_M;

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
 * '<Root>' : 'PV_vsi_sf'
 * '<S1>'   : 'PV_vsi_sf/Control PR VSI'
 * '<S2>'   : 'PV_vsi_sf/MATLAB Function SOC '
 */
#endif                                 /* RTW_HEADER_PV_vsi_sf_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

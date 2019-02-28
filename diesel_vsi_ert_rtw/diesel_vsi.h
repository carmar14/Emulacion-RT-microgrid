/*
 * File: diesel_vsi.h
 *
 * Code generated for Simulink model 'diesel_vsi'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Mon Jan 21 15:38:20 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_diesel_vsi_h_
#define RTW_HEADER_diesel_vsi_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef diesel_vsi_COMMON_INCLUDES_
# define diesel_vsi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* diesel_vsi_COMMON_INCLUDES_ */

#include "diesel_vsi_types.h"
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

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T refvoltage;                   /* '<Root>/Sine Wave1' */
  real_T Sum11;                        /* '<Root>/Sum11' */
  real_T Sum12;                        /* '<Root>/Sum12' */
  real_T OutputDCVoltage;              /* '<Root>/Sum8' */
  real_T FilterCoefficient;            /* '<S3>/Filter Coefficient' */
  real_T Sum;                          /* '<S3>/Sum' */
  real_T IntegralGain;                 /* '<S3>/Integral Gain' */
  real_T Sum2;                         /* '<S2>/Sum2' */
} B_diesel_vsi_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T TimeStampA;                   /* '<Root>/Derivative3' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative3' */
  real_T TimeStampB;                   /* '<Root>/Derivative3' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative3' */
  real_T TimeStampA_f;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeA_b;               /* '<Root>/Derivative2' */
  real_T TimeStampB_g;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeB_l;               /* '<Root>/Derivative2' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } MotordeCombustin1_RWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    void *TUbufferPtrs[2];
  } MotordeCombustin1_PWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } MotordeCombustin1_IWORK;           /* '<S2>/Motor de Combustión1' */
} DW_diesel_vsi_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
  real_T VSIlineZ1_CSTATE;             /* '<Root>/VSI  line Z1' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T Filter_CSTATE;                /* '<S3>/Filter' */
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
} X_diesel_vsi_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
  real_T VSIlineZ1_CSTATE;             /* '<Root>/VSI  line Z1' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE;          /* '<Root>/Transfer Fcn5' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T Filter_CSTATE;                /* '<S3>/Filter' */
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
} XDot_diesel_vsi_T;

/* State disabled  */
typedef struct {
  boolean_T Actuador1_CSTATE;          /* '<S2>/Actuador1' */
  boolean_T VSIlineZ1_CSTATE;          /* '<Root>/VSI  line Z1' */
  boolean_T TransferFcn2_CSTATE[2];    /* '<S1>/Transfer Fcn2' */
  boolean_T TransferFcn5_CSTATE;       /* '<Root>/Transfer Fcn5' */
  boolean_T Dinmicaeneleje1_CSTATE;    /* '<S2>/Dinámica en el eje1' */
  boolean_T Filter_CSTATE;             /* '<S3>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
} XDis_diesel_vsi_T;

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
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Vref;                         /* '<Root>/Vref' */
  real_T par;                          /* '<Root>/par' */
} ExtU_diesel_vsi_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T flujo;                        /* '<Root>/flujo' */
  real_T i2;                           /* '<Root>/i2' */
  real_T vdc;                          /* '<Root>/vdc' */
  real_T duty;
} ExtY_diesel_vsi_T;

/* Real-time Model Data Structure */
struct tag_RTM_diesel_vsi_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_diesel_vsi_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[8];
  real_T odeF[4][8];
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
extern B_diesel_vsi_T diesel_vsi_B;

/* Continuous states (default storage) */
extern X_diesel_vsi_T diesel_vsi_X;

/* Block states (default storage) */
extern DW_diesel_vsi_T diesel_vsi_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_diesel_vsi_T diesel_vsi_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_diesel_vsi_T diesel_vsi_Y;

/* Model entry point functions */
extern void diesel_vsi_initialize(void);
extern void diesel_vsi_step(void);
extern void diesel_vsi_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_Vload(double);
extern void set_par(double);
extern void set_flujo(double);

//-----Funciones para obtener valores de las salidas-------
extern double get_I_die(void);
extern double get_flujo(void);
extern double get_vdc(void);
extern double get_duty(void);

/* Real-time Model object */
extern RT_MODEL_diesel_vsi_T *const diesel_vsi_M;

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
 * '<Root>' : 'diesel_vsi'
 * '<S1>'   : 'diesel_vsi/Control PR VSI1'
 * '<S2>'   : 'diesel_vsi/Diesel Generator3'
 * '<S3>'   : 'diesel_vsi/PID Controller3'
 */
#endif                                 /* RTW_HEADER_diesel_vsi_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

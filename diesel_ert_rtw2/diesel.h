/*
 * File: diesel.h
 *
 * Code generated for Simulink model 'diesel'.
 *
 * Model version                  : 1.25
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Nov 28 09:59:44 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_diesel_h_
#define RTW_HEADER_diesel_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef diesel_COMMON_INCLUDES_
# define diesel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* diesel_COMMON_INCLUDES_ */

#include "diesel_types.h"
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
  real_T Memory;                       /* '<S11>/Memory' */
  real_T Switch;                       /* '<S11>/Switch' */
  real_T Memory_d;                     /* '<S10>/Memory' */
  real_T Switch_m;                     /* '<S10>/Switch' */
  real_T Memory_dw;                    /* '<S15>/Memory' */
  real_T Switch_a;                     /* '<S15>/Switch' */
  real_T Memory_l;                     /* '<S14>/Memory' */
  real_T Switch_l;                     /* '<S14>/Switch' */
  real_T Gain11;                       /* '<Root>/Gain11' */
  real_T OutputDCVoltage;              /* '<Root>/Sum15' */
  real_T refvoltage;                   /* '<Root>/Sine Wave1' */
  real_T Sum11;                        /* '<Root>/Sum11' */
  real_T Gain10;                       /* '<Root>/Gain10' */
  real_T FilterCoefficient;            /* '<S4>/Filter Coefficient' */
  real_T Sum;                          /* '<S4>/Sum' */
  real_T IntegralGain;                 /* '<S4>/Integral Gain' */
  real_T Product;                      /* '<S6>/Product' */
  real_T Product1;                     /* '<S6>/Product1' */
  real_T Gain12;                       /* '<Root>/Gain12' */
  real_T Product_a;                    /* '<S7>/Product' */
  real_T Product1_e;                   /* '<S7>/Product1' */
  real_T Sum2;                         /* '<S2>/Sum2' */
} B_diesel_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<S11>/Memory' */
  real_T Memory_PreviousInput_n;       /* '<S10>/Memory' */
  real_T Memory_PreviousInput_l;       /* '<S15>/Memory' */
  real_T Memory_PreviousInput_f;       /* '<S14>/Memory' */
  real_T TimeStampA;                   /* '<Root>/Derivative2' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative2' */
  real_T TimeStampB;                   /* '<Root>/Derivative2' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative2' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S11>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_g;            /* '<S10>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_j;            /* '<S15>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_h;            /* '<S14>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } MotordeCombustin1_RWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S11>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_m;            /* '<S10>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_o;            /* '<S15>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_c;            /* '<S14>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } MotordeCombustin1_PWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S11>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_e;            /* '<S10>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_e4;           /* '<S15>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_h;            /* '<S14>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } MotordeCombustin1_IWORK;           /* '<S2>/Motor de Combustión1' */
} DW_diesel_T;

/* Continuous states (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S11>/integrator' */
  real_T integrator_CSTATE_m;          /* '<S10>/integrator' */
  real_T integrator_CSTATE_g;          /* '<S15>/integrator' */
  real_T integrator_CSTATE_j;          /* '<S14>/integrator' */
  real_T Integrator8_CSTATE;           /* '<Root>/Integrator8' */
  real_T Integrator6_CSTATE;           /* '<Root>/Integrator6' */
  real_T Integrator7_CSTATE;           /* '<Root>/Integrator7' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
  real_T Filter_CSTATE;                /* '<S4>/Filter' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
} X_diesel_T;

/* State derivatives (default storage) */
typedef struct {
  real_T integrator_CSTATE;            /* '<S11>/integrator' */
  real_T integrator_CSTATE_m;          /* '<S10>/integrator' */
  real_T integrator_CSTATE_g;          /* '<S15>/integrator' */
  real_T integrator_CSTATE_j;          /* '<S14>/integrator' */
  real_T Integrator8_CSTATE;           /* '<Root>/Integrator8' */
  real_T Integrator6_CSTATE;           /* '<Root>/Integrator6' */
  real_T Integrator7_CSTATE;           /* '<Root>/Integrator7' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T TransferFcn4_CSTATE;          /* '<Root>/Transfer Fcn4' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
  real_T Filter_CSTATE;                /* '<S4>/Filter' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
} XDot_diesel_T;

/* State disabled  */
typedef struct {
  boolean_T integrator_CSTATE;         /* '<S11>/integrator' */
  boolean_T integrator_CSTATE_m;       /* '<S10>/integrator' */
  boolean_T integrator_CSTATE_g;       /* '<S15>/integrator' */
  boolean_T integrator_CSTATE_j;       /* '<S14>/integrator' */
  boolean_T Integrator8_CSTATE;        /* '<Root>/Integrator8' */
  boolean_T Integrator6_CSTATE;        /* '<Root>/Integrator6' */
  boolean_T Integrator7_CSTATE;        /* '<Root>/Integrator7' */
  boolean_T Dinmicaeneleje1_CSTATE;    /* '<S2>/Dinámica en el eje1' */
  boolean_T TransferFcn4_CSTATE;       /* '<Root>/Transfer Fcn4' */
  boolean_T TransferFcn2_CSTATE[2];    /* '<S1>/Transfer Fcn2' */
  boolean_T Filter_CSTATE;             /* '<S4>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S4>/Integrator' */
  boolean_T Actuador1_CSTATE;          /* '<S2>/Actuador1' */
} XDis_diesel_T;

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
  real_T Vload;                        /* '<Root>/Vload ' */
  real_T ref;                          /* '<Root>/ref' */
} ExtU_diesel_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T potencia;                     /* '<Root>/potencia' */
  real_T i3;                           /* '<Root>/i3' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
  real_T bus_dc;                       /* '<Root>/bus_dc' */
} ExtY_diesel_T;

/* Real-time Model Data Structure */
struct tag_RTM_diesel_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_diesel_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T OdeDeltaY[14];
  real_T odeF[13][14];
  real_T odeX0[14];
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
extern B_diesel_T diesel_B;

/* Continuous states (default storage) */
extern X_diesel_T diesel_X;

/* Block states (default storage) */
extern DW_diesel_T diesel_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_diesel_T diesel_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_diesel_T diesel_Y;

/* Model entry point functions */
extern void diesel_initialize(void);
extern void diesel_step(void);
extern void diesel_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_Vload(double);
extern void set_flujo(double);

//-----Funciones para obtener valores de las salidas-------
extern double get_I_die(void);
extern double get_Potencia(void);
extern double get_duty(void);
extern double get_dc(void);



/* Real-time Model object */
extern RT_MODEL_diesel_T *const diesel_M;

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
 * '<Root>' : 'diesel'
 * '<S1>'   : 'diesel/Control PR VSI1'
 * '<S2>'   : 'diesel/Diesel Generator2'
 * '<S3>'   : 'diesel/MATLAB Function'
 * '<S4>'   : 'diesel/PID Controller2'
 * '<S5>'   : 'diesel/Power1'
 * '<S6>'   : 'diesel/Power1/Fourier'
 * '<S7>'   : 'diesel/Power1/Fourier1'
 * '<S8>'   : 'diesel/Power1/Fourier/Mean'
 * '<S9>'   : 'diesel/Power1/Fourier/Mean value1'
 * '<S10>'  : 'diesel/Power1/Fourier/Mean/Model'
 * '<S11>'  : 'diesel/Power1/Fourier/Mean value1/Model'
 * '<S12>'  : 'diesel/Power1/Fourier1/Mean'
 * '<S13>'  : 'diesel/Power1/Fourier1/Mean value1'
 * '<S14>'  : 'diesel/Power1/Fourier1/Mean/Model'
 * '<S15>'  : 'diesel/Power1/Fourier1/Mean value1/Model'
 */
#endif                                 /* RTW_HEADER_diesel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

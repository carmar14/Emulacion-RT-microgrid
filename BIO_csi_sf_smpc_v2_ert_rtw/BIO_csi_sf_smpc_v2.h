/*
 * File: BIO_csi_sf_smpc_v2.h
 *
 * Code generated for Simulink model 'BIO_csi_sf_smpc_v2'.
 *
 * Model version                  : 1.79
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Mon Sep 16 14:30:34 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_sf_smpc_v2_h_
#define RTW_HEADER_BIO_csi_sf_smpc_v2_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef BIO_csi_sf_smpc_v2_COMMON_INCLUDES_
# define BIO_csi_sf_smpc_v2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* BIO_csi_sf_smpc_v2_COMMON_INCLUDES_ */

#include "BIO_csi_sf_smpc_v2_types.h"
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
  real_T Delay90zV;                    /* '<S1>/Delay90(z)V' */
  real_T Delay90zI;                    /* '<S1>/Delay90(z)I' */
  real_T Gain3;                        /* '<Root>/Gain3' */
  real_T Sum1;                         /* '<S2>/Sum1' */
  real_T Sum3;                         /* '<S2>/Sum3' */
  real_T Add;                          /* '<S2>/Add' */
  real_T Add4;                         /* '<S2>/Add4' */
  real_T Add5;                         /* '<S2>/Add5' */
  real_T Delaycombustor;               /* '<S2>/Delay combustor' */
  real_T ValvePositioner;              /* '<S2>/Valve Positioner' */
  real_T Sum_n;                        /* '<Root>/Sum' */
  real_T Xmethp;                       /* '<S2>/MATLAB Function metanogenesis' */
  real_T Sbp;                          /* '<S2>/MATLAB Function Hidrolisis' */
  real_T Svp;                          /* '<S2>/MATLAB Function Acidogenesis' */
  real_T Xacidp;                       /* '<S2>/MATLAB Function Acetogenesis' */
  real_T y;                            /* '<S2>/MATLAB Function' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
} B_BIO_csi_sf_smpc_v2_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Delaycombustor2_RWORK;             /* '<S2>/Delay combustor2' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Delaycombustor1_RWORK;             /* '<S2>/Delay combustor1' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Turbineexhaustsystemdelay_RWORK;   /* '<S2>/Turbine exhaust system delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } Delaycombustor_RWORK;              /* '<S2>/Delay combustor' */

  struct {
    void *TUbufferPtrs[2];
  } Delaycombustor2_PWORK;             /* '<S2>/Delay combustor2' */

  struct {
    void *TUbufferPtrs[2];
  } Delaycombustor1_PWORK;             /* '<S2>/Delay combustor1' */

  struct {
    void *TUbufferPtrs[2];
  } Turbineexhaustsystemdelay_PWORK;   /* '<S2>/Turbine exhaust system delay' */

  struct {
    void *TUbufferPtrs[2];
  } Delaycombustor_PWORK;              /* '<S2>/Delay combustor' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Delaycombustor2_IWORK;             /* '<S2>/Delay combustor2' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Delaycombustor1_IWORK;             /* '<S2>/Delay combustor1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Turbineexhaustsystemdelay_IWORK;   /* '<S2>/Turbine exhaust system delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } Delaycombustor_IWORK;              /* '<S2>/Delay combustor' */
} DW_BIO_csi_sf_smpc_v2_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Compresor_CSTATE;             /* '<S2>/Compresor' */
  real_T Integrator3_CSTATE;           /* '<S2>/Integrator3' */
  real_T Integrator1_CSTATE;           /* '<S2>/Integrator1' */
  real_T TransferFcn_CSTATE_i;         /* '<S2>/Transfer Fcn' */
  real_T thermocouple_CSTATE;          /* '<S2>/thermo couple' */
  real_T TempControl_CSTATE;           /* '<S2>/Temp Control' */
  real_T RotationShield_CSTATE;        /* '<S2>/Rotation Shield' */
  real_T Fuelsystemactuator_CSTATE;    /* '<S2>/Fuel system actuator' */
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
  real_T Integrator2_CSTATE;           /* '<S2>/Integrator2' */
  real_T ValvePositioner_CSTATE;       /* '<S2>/Valve Positioner' */
} X_BIO_csi_sf_smpc_v2_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Compresor_CSTATE;             /* '<S2>/Compresor' */
  real_T Integrator3_CSTATE;           /* '<S2>/Integrator3' */
  real_T Integrator1_CSTATE;           /* '<S2>/Integrator1' */
  real_T TransferFcn_CSTATE_i;         /* '<S2>/Transfer Fcn' */
  real_T thermocouple_CSTATE;          /* '<S2>/thermo couple' */
  real_T TempControl_CSTATE;           /* '<S2>/Temp Control' */
  real_T RotationShield_CSTATE;        /* '<S2>/Rotation Shield' */
  real_T Fuelsystemactuator_CSTATE;    /* '<S2>/Fuel system actuator' */
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
  real_T Integrator2_CSTATE;           /* '<S2>/Integrator2' */
  real_T ValvePositioner_CSTATE;       /* '<S2>/Valve Positioner' */
} XDot_BIO_csi_sf_smpc_v2_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
  boolean_T Compresor_CSTATE;          /* '<S2>/Compresor' */
  boolean_T Integrator3_CSTATE;        /* '<S2>/Integrator3' */
  boolean_T Integrator1_CSTATE;        /* '<S2>/Integrator1' */
  boolean_T TransferFcn_CSTATE_i;      /* '<S2>/Transfer Fcn' */
  boolean_T thermocouple_CSTATE;       /* '<S2>/thermo couple' */
  boolean_T TempControl_CSTATE;        /* '<S2>/Temp Control' */
  boolean_T RotationShield_CSTATE;     /* '<S2>/Rotation Shield' */
  boolean_T Fuelsystemactuator_CSTATE; /* '<S2>/Fuel system actuator' */
  boolean_T Integrator_CSTATE;         /* '<S2>/Integrator' */
  boolean_T Integrator2_CSTATE;        /* '<S2>/Integrator2' */
  boolean_T ValvePositioner_CSTATE;    /* '<S2>/Valve Positioner' */
} XDis_BIO_csi_sf_smpc_v2_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S2>/Gain' */
  const real_T Sum;                    /* '<S2>/Sum' */
} ConstB_BIO_csi_sf_smpc_v2_T;

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
  real_T Prefb;                        /* '<Root>/Prefb' */
  real_T Qrefb;                        /* '<Root>/Qrefb' */
} ExtU_BIO_csi_sf_smpc_v2_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T i1;                           /* '<Root>/i1' */
  real_T qbio_meas;                    /* '<Root>/qbio_meas' */
  real_T pbio_meas;                    /* '<Root>/pbio_meas' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
} ExtY_BIO_csi_sf_smpc_v2_T;

/* Real-time Model Data Structure */
struct tag_RTM_BIO_csi_sf_smpc_v2_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_BIO_csi_sf_smpc_v2_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[20];
  real_T odeF[4][20];
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
extern B_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_B;

/* Continuous states (default storage) */
extern X_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_X;

/* Block states (default storage) */
extern DW_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_Y;
extern const ConstB_BIO_csi_sf_smpc_v2_T BIO_csi_sf_smpc_v2_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void BIO_csi_sf_smpc_v2_initialize(void);
extern void BIO_csi_sf_smpc_v2_step(void);
extern void BIO_csi_sf_smpc_v2_terminate(void);

//-------Funciones para asignar entradas-------------
//extern void set_Vdc_bio(double);
extern void set_Vload(double);
extern void set_Qref_bio(double);
extern void set_Pref_bio(double);
//-----Funciones para obtener valores de las salidas-------
	
extern double get_I_bio(void);
extern double get_Pm(void);
extern double get_Qm(void);
extern double get_duty_cycle(void);	

/* Real-time Model object */
extern RT_MODEL_BIO_csi_sf_smpc_v2_T *const BIO_csi_sf_smpc_v2_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope10' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S2>/Scope5' : Unused code path elimination
 * Block '<S2>/Scope6' : Unused code path elimination
 * Block '<S2>/Scope7' : Unused code path elimination
 * Block '<S2>/Scope8' : Unused code path elimination
 * Block '<S2>/Scope9' : Unused code path elimination
 * Block '<S14>/do not delete this gain' : Unused code path elimination
 * Block '<S17>/Gain' : Unused code path elimination
 * Block '<S2>/Gain3' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'BIO_csi_sf_smpc_v2'
 * '<S1>'   : 'BIO_csi_sf_smpc_v2/CSI_Control_BIO'
 * '<S2>'   : 'BIO_csi_sf_smpc_v2/Subsystem'
 * '<S3>'   : 'BIO_csi_sf_smpc_v2/CSI_Control_BIO/PQ2Iab_PH1'
 * '<S4>'   : 'BIO_csi_sf_smpc_v2/CSI_Control_BIO/PQ_singlePhase'
 * '<S5>'   : 'BIO_csi_sf_smpc_v2/CSI_Control_BIO/PR Controller_0_ref 1'
 * '<S6>'   : 'BIO_csi_sf_smpc_v2/CSI_Control_BIO/PR Controller_0_ref 1/Steper6'
 * '<S7>'   : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function'
 * '<S8>'   : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function Acetogenesis'
 * '<S9>'   : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function Acidogenesis'
 * '<S10>'  : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function Hidrolisis'
 * '<S11>'  : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function metano'
 * '<S12>'  : 'BIO_csi_sf_smpc_v2/Subsystem/MATLAB Function metanogenesis'
 * '<S13>'  : 'BIO_csi_sf_smpc_v2/Subsystem/V_diesel'
 * '<S14>'  : 'BIO_csi_sf_smpc_v2/Subsystem/Vsensa1'
 * '<S15>'  : 'BIO_csi_sf_smpc_v2/Subsystem/powergui'
 * '<S16>'  : 'BIO_csi_sf_smpc_v2/Subsystem/Vsensa1/Model'
 * '<S17>'  : 'BIO_csi_sf_smpc_v2/Subsystem/powergui/EquivalentModel1'
 * '<S18>'  : 'BIO_csi_sf_smpc_v2/Subsystem/powergui/EquivalentModel1/Sources'
 * '<S19>'  : 'BIO_csi_sf_smpc_v2/Subsystem/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_BIO_csi_sf_smpc_v2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

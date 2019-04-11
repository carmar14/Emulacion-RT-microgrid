/*
 * File: BIO_csi_sf_smpc.h
 *
 * Code generated for Simulink model 'BIO_csi_sf_smpc'.
 *
 * Model version                  : 1.73
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 11 08:30:10 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_sf_smpc_h_
#define RTW_HEADER_BIO_csi_sf_smpc_h_
#include <math.h>
#include <string.h>
#ifndef BIO_csi_sf_smpc_COMMON_INCLUDES_
# define BIO_csi_sf_smpc_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* BIO_csi_sf_smpc_COMMON_INCLUDES_ */

#include "BIO_csi_sf_smpc_types.h"
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
  real_T Sum_n;                        /* '<Root>/Sum' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
} B_BIO_csi_sf_smpc_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
} DW_BIO_csi_sf_smpc_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} X_BIO_csi_sf_smpc_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} XDot_BIO_csi_sf_smpc_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
} XDis_BIO_csi_sf_smpc_T;

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
  real_T Vdc;                          /* '<Root>/Vdc' */
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Prefb;                        /* '<Root>/Prefb' */
  real_T Qrefb;                        /* '<Root>/Qrefb' */
} ExtU_BIO_csi_sf_smpc_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T i1;                           /* '<Root>/i1' */
  real_T qbio_meas;                    /* '<Root>/qbio_meas' */
  real_T pbio_meas;                    /* '<Root>/pbio_meas' */
  real_T duty_cycle;                   /* '<Root>/duty_cycle' */
} ExtY_BIO_csi_sf_smpc_T;

/* Real-time Model Data Structure */
struct tag_RTM_BIO_csi_sf_smpc_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_BIO_csi_sf_smpc_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[9];
  real_T odeF[4][9];
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
extern B_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_B;

/* Continuous states (default storage) */
extern X_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_X;

/* Block states (default storage) */
extern DW_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_BIO_csi_sf_smpc_T BIO_csi_sf_smpc_Y;

/* Model entry point functions */
extern void BIO_csi_sf_smpc_initialize(void);
extern void BIO_csi_sf_smpc_step(void);
extern void BIO_csi_sf_smpc_terminate(void);

//-------Funciones para asignar entradas-------------
extern void set_Vdc_bio(double);
extern void set_Vload(double);
extern void set_Qref_bio(double);
extern void set_Pref_bio(double);
//-----Funciones para obtener valores de las salidas-------
	
extern double get_I_bio(void);
extern double get_Pm(void);
extern double get_Qm(void);
extern double get_duty_cycle(void);	 


/* Real-time Model object */
extern RT_MODEL_BIO_csi_sf_smpc_T *const BIO_csi_sf_smpc_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
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
 * '<Root>' : 'BIO_csi_sf_smpc'
 * '<S1>'   : 'BIO_csi_sf_smpc/CSI_Control_BIO'
 * '<S2>'   : 'BIO_csi_sf_smpc/CSI_Control_BIO/PQ2Iab_PH1'
 * '<S3>'   : 'BIO_csi_sf_smpc/CSI_Control_BIO/PQ_singlePhase'
 * '<S4>'   : 'BIO_csi_sf_smpc/CSI_Control_BIO/PR Controller_0_ref 1'
 * '<S5>'   : 'BIO_csi_sf_smpc/CSI_Control_BIO/PR Controller_0_ref 1/Steper6'
 */
#endif                                 /* RTW_HEADER_BIO_csi_sf_smpc_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

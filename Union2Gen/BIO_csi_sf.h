/*
 * File: BIO_csi_sf.h
 *
 * Code generated for Simulink model 'BIO_csi_sf'.
 *
 * Model version                  : 1.63
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Aug 14 16:25:22 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BIO_csi_sf_h_
#define RTW_HEADER_BIO_csi_sf_h_
#include <math.h>
#include <string.h>
#ifndef BIO_csi_sf_COMMON_INCLUDES_
# define BIO_csi_sf_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* BIO_csi_sf_COMMON_INCLUDES_ */

#include "BIO_csi_sf_types.h"
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
  real_T dv0[40000];
  real_T dv1[20200];
  real_T Delay90zI;                    /* '<S1>/Delay90(z)I' */
  real_T Delay90zV;                    /* '<S1>/Delay90(z)V' */
  real_T Gain3;                        /* '<Root>/Gain3' */
  real_T Sum_n;                        /* '<Root>/Sum' */
  real_T xk1[14];                      /* '<S7>/optimizer' */
  real_T u[2];                         /* '<S7>/optimizer' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
  boolean_T iAout;                     /* '<S7>/optimizer' */
} B_BIO_csi_sf_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T last_mv_DSTATE[2];            /* '<S7>/last_mv' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T last_x_PreviousInput[14];     /* '<S7>/last_x' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  boolean_T Memory_PreviousInput;      /* '<S7>/Memory' */
} DW_BIO_csi_sf_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} X_BIO_csi_sf_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
} XDot_BIO_csi_sf_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
} XDis_BIO_csi_sf_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vdc;                          /* '<Root>/Vdc' */
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Prefb;                        /* '<Root>/Prefb' */
  real_T Qrefb;                        /* '<Root>/Qrefb' */
} ExtU_BIO_csi_sf_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T i1;                           /* '<Root>/i1' */
} ExtY_BIO_csi_sf_T;

/* Real-time Model Data Structure */
struct tag_RTM_BIO_csi_sf_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_BIO_csi_sf_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
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
    struct {
      uint16_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block signals (auto storage) */
extern B_BIO_csi_sf_T BIO_csi_sf_B;

/* Continuous states (auto storage) */
extern X_BIO_csi_sf_T BIO_csi_sf_X;

/* Block states (auto storage) */
extern DW_BIO_csi_sf_T BIO_csi_sf_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_BIO_csi_sf_T BIO_csi_sf_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_BIO_csi_sf_T BIO_csi_sf_Y;

/* Model entry point functions */
extern void BIO_csi_sf_initialize(void);
extern void BIO_csi_sf_step(void);
extern void BIO_csi_sf_terminate(void);
//-------Funciones para asignar entradas-------------
extern void set_Vdc_bio(double);
extern void set_Vload2(double);
extern void set_Qref_bio(double);
extern void set_Pref_bio(double);
//-----Funciones para obtener valores de las salidas-------
	
extern double get_I_bio(void);
extern double get_MPC1(void);
	 

/* Real-time Model object */
extern RT_MODEL_BIO_csi_sf_T *const BIO_csi_sf_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S8>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S9>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S10>/Vector Dimension Check' : Unused code path elimination
 * Block '<S11>/Vector Dimension Check' : Unused code path elimination
 * Block '<S12>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Vector Dimension Check' : Unused code path elimination
 * Block '<S14>/Vector Dimension Check' : Unused code path elimination
 * Block '<S15>/Vector Dimension Check' : Unused code path elimination
 * Block '<S16>/Vector Dimension Check' : Unused code path elimination
 * Block '<S17>/Vector Dimension Check' : Unused code path elimination
 * Block '<S18>/Vector Dimension Check' : Unused code path elimination
 * Block '<S19>/Vector Dimension Check' : Unused code path elimination
 * Block '<S20>/Vector Dimension Check' : Unused code path elimination
 * Block '<S21>/Vector Dimension Check' : Unused code path elimination
 * Block '<S7>/constant' : Unused code path elimination
 * Block '<S7>/umin_scale2' : Unused code path elimination
 * Block '<S7>/umin_scale3' : Unused code path elimination
 * Block '<S7>/ym_zero' : Unused code path elimination
 * Block '<S7>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S7>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S7>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S7>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S7>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/ymin_scale' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'BIO_csi_sf'
 * '<S1>'   : 'BIO_csi_sf/CSI_Control_BIO'
 * '<S2>'   : 'BIO_csi_sf/MPC Controller'
 * '<S3>'   : 'BIO_csi_sf/CSI_Control_BIO/PQ2Iab_PH1'
 * '<S4>'   : 'BIO_csi_sf/CSI_Control_BIO/PQ_singlePhase'
 * '<S5>'   : 'BIO_csi_sf/CSI_Control_BIO/PR Controller_0_ref 1'
 * '<S6>'   : 'BIO_csi_sf/CSI_Control_BIO/PR Controller_0_ref 1/Steper6'
 * '<S7>'   : 'BIO_csi_sf/MPC Controller/MPC'
 * '<S8>'   : 'BIO_csi_sf/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S9>'   : 'BIO_csi_sf/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S10>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S11>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S12>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S13>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S14>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S15>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S16>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S17>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S18>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S19>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S20>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S21>'  : 'BIO_csi_sf/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S22>'  : 'BIO_csi_sf/MPC Controller/MPC/optimizer'
 */
#endif                                 /* RTW_HEADER_BIO_csi_sf_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

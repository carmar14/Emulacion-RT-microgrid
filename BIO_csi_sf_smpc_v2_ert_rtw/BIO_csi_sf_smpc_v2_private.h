/*
 * File: BIO_csi_sf_smpc_v2_private.h
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

#ifndef RTW_HEADER_BIO_csi_sf_smpc_v2_private_h_
#define RTW_HEADER_BIO_csi_sf_smpc_v2_private_h_
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;

/* private model entry point functions */
extern void BIO_csi_sf_smpc_v2_derivatives(void);

#endif                                 /* RTW_HEADER_BIO_csi_sf_smpc_v2_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

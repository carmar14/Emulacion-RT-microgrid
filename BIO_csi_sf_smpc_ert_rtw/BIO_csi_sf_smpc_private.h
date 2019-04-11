/*
 * File: BIO_csi_sf_smpc_private.h
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

#ifndef RTW_HEADER_BIO_csi_sf_smpc_private_h_
#define RTW_HEADER_BIO_csi_sf_smpc_private_h_
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

/* private model entry point functions */
extern void BIO_csi_sf_smpc_derivatives(void);

#endif                                 /* RTW_HEADER_BIO_csi_sf_smpc_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

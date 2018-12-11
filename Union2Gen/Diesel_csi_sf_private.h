/*
 * File: Diesel_csi_sf_private.h
 *
 * Code generated for Simulink model 'Diesel_csi_sf'.
 *
 * Model version                  : 1.75
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Dec  6 15:06:29 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Diesel_csi_sf_private_h_
#define RTW_HEADER_Diesel_csi_sf_private_h_
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
extern void Diesel_csi_sf_derivatives(void);

#endif                                 /* RTW_HEADER_Diesel_csi_sf_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: TailRotor.h
 *
 * Code generated for Simulink model 'TailRotor'.
 *
 * Model version                  : 2.125
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Apr  6 15:50:48 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef TailRotor_h_
#define TailRotor_h_
#ifndef TailRotor_COMMON_INCLUDES_
#define TailRotor_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* TailRotor_COMMON_INCLUDES_ */

#include "TailRotor_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rtw_modelmap.h"
#include <string.h>
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Rotor6_o3;                    /* '<S1>/Rotor6' */
  real_T Rotor6_o4;                    /* '<S1>/Rotor6' */
  real_T UnitConversion;               /* '<S2>/Unit Conversion' */
  real_T RotationAnglestoDirectionCosine[9];
                         /* '<S1>/Rotation Angles to Direction Cosine Matrix' */
  real_T Rotor6_o1[3];                 /* '<S1>/Rotor6' */
  real_T Rotor6_o2[3];                 /* '<S1>/Rotor6' */
  real_T Transformmomentsaboutxaxisby90d[3];
                           /* '<S1>/Transform moments about x-axis by 90 deg' */
  real_T Sum_f[6];                     /* '<S3>/Sum' */
} B_TailRotor_T;

/* Parameters (default storage) */
struct P_TailRotor_T_ {
  real_T Constant3_Value;              /* Expression: 90
                                        * Referenced by: '<S1>/Constant3'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Rotor6_radius;                /* Expression: 1.29
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_Nb;                    /* Expression: 2
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_chord;                 /* Expression: 0.2133
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_hingeOffset;           /* Expression: 0
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_clalpha;               /* Expression: 5.5
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_cd0;                   /* Expression: 0.002
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_thetaRoot;             /* Expression: 0.015
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Rotor6_thetaTwist;            /* Expression: 0
                                        * Referenced by: '<S1>/Rotor6'
                                        */
  real_T Constant7_Value[3];           /* Expression: [-8.53 0 -2.10]
                                        * Referenced by: '<S1>/Constant7'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_TailRotor_T {
  const char_T * volatile errorStatus;
  B_TailRotor_T *blockIO;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[12];
    int32_T* vardimsAddress[12];
    RTWLoggingFcnPtr loggingPtrs[12];
  } DataMapInfo;
};

/* Block parameters (default storage) */
extern P_TailRotor_T TailRotor_P;

/* Model entry point functions */
extern void TailRotor_initialize(RT_MODEL_TailRotor_T *const TailRotor_M, real_T
  *TailRotor_U_SpeedT, real_T *TailRotor_U_CollectiveT, real_T *TailRotor_U_rho,
  real_T TailRotor_Y_Ft[3], real_T TailRotor_Y_Mt[3]);
extern void TailRotor_step(RT_MODEL_TailRotor_T *const TailRotor_M, real_T
  TailRotor_U_SpeedT, real_T TailRotor_U_CollectiveT, real_T TailRotor_U_rho,
  real_T TailRotor_Y_Ft[3], real_T TailRotor_Y_Mt[3]);
extern void TailRotor_terminate(RT_MODEL_TailRotor_T *const TailRotor_M);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  TailRotor_GetCAPIStaticMap(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor')    - opens subsystem test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor
 * hilite_system('test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment'
 * '<S1>'   : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor'
 * '<S2>'   : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor/Angle Conversion'
 * '<S3>'   : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/TailRotor/Cross Product'
 */
#endif                                 /* TailRotor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

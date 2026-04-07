/*
 * File: MainRotor.h
 *
 * Code generated for Simulink model 'MainRotor'.
 *
 * Model version                  : 2.125
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Apr  6 15:48:13 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef MainRotor_h_
#define MainRotor_h_
#ifndef MainRotor_COMMON_INCLUDES_
#define MainRotor_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* MainRotor_COMMON_INCLUDES_ */

#include "MainRotor_types.h"
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
  real_T Rotor1_o3;                    /* '<S1>/Rotor1' */
  real_T Rotor1_o4;                    /* '<S1>/Rotor1' */
  real_T Rotor1_o2[3];                 /* '<S1>/Rotor1' */
  real_T Sum[6];                       /* '<S2>/Sum' */
} B_MainRotor_T;

/* Parameters (default storage) */
struct P_MainRotor_T_ {
  real_T Rotor1_radius;                /* Expression: 7.35
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_Nb;                    /* Expression: 2
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_chord;                 /* Expression: 0.53
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_hingeOffset;           /* Expression: 0
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_clalpha;               /* Expression: 5.5
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_cd0;                   /* Expression: 0.009
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_gamma;                 /* Expression: 10
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_thetaRoot;             /* Expression: 0.1493
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Rotor1_thetaTwist;            /* Expression: -0.1745
                                        * Referenced by: '<S1>/Rotor1'
                                        */
  real_T Constant8_Value[3];           /* Expression: [-0.165 0 -2.07]
                                        * Referenced by: '<S1>/Constant8'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_MainRotor_T {
  const char_T * volatile errorStatus;
  B_MainRotor_T *blockIO;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[10];
    int32_T* vardimsAddress[10];
    RTWLoggingFcnPtr loggingPtrs[10];
  } DataMapInfo;
};

/* Block parameters (default storage) */
extern P_MainRotor_T MainRotor_P;

/* Model entry point functions */
extern void MainRotor_initialize(RT_MODEL_MainRotor_T *const MainRotor_M, real_T
  *MainRotor_U_SpeedM, real_T *MainRotor_U_CollectiveM, real_T
  *MainRotor_U_CyclicLat, real_T *MainRotor_U_CyclicLon, real_T *MainRotor_U_rho,
  real_T MainRotor_U_wb[3], real_T MainRotor_U_Vb[3], real_T MainRotor_Y_Fm[3],
  real_T MainRotor_Y_Mm[3]);
extern void MainRotor_step(RT_MODEL_MainRotor_T *const MainRotor_M, real_T
  MainRotor_U_SpeedM, real_T MainRotor_U_CollectiveM, real_T
  MainRotor_U_CyclicLat, real_T MainRotor_U_CyclicLon, real_T MainRotor_U_rho,
  real_T MainRotor_U_wb[3], real_T MainRotor_U_Vb[3], real_T MainRotor_Y_Fm[3],
  real_T MainRotor_Y_Mm[3]);
extern void MainRotor_terminate(RT_MODEL_MainRotor_T *const MainRotor_M);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  MainRotor_GetCAPIStaticMap(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
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
 * hilite_system('test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/MainRotor')    - opens subsystem test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/MainRotor
 * hilite_system('test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/MainRotor/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment'
 * '<S1>'   : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/MainRotor'
 * '<S2>'   : 'test_HelicopterModelingSimulation_disc_copy/Force Moment Computation  and Modeling/Helicopter Force Moment Computation/ComputeForceandMoment/MainRotor/Cross Product1'
 */
#endif                                 /* MainRotor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

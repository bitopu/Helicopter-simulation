/*
 * File: TailRotor.c
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

#include "TailRotor.h"
#include <math.h>
#include "TailRotor_private.h"
#include <emmintrin.h>
#include "rtwtypes.h"
#include <string.h>
#include "TailRotor_capi.h"
#include "rt_nonfinite.h"

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void TailRotor_step(RT_MODEL_TailRotor_T *const TailRotor_M, real_T
                    TailRotor_U_SpeedT, real_T TailRotor_U_CollectiveT, real_T
                    TailRotor_U_rho, real_T TailRotor_Y_Ft[3], real_T
                    TailRotor_Y_Mt[3])
{
  B_TailRotor_T *TailRotor_B = TailRotor_M->blockIO;
  __m128d tmp_0;
  real_T xnodes[101];
  real_T tmp[2];
  real_T pData_idx_0;
  real_T pData_idx_0_tmp;
  real_T pData_idx_0_tmp_0;
  real_T pData_idx_1;
  real_T pData_idx_3;
  real_T pData_idx_3_tmp;
  real_T pData_idx_6_tmp;
  real_T pData_tmp;
  real_T pData_tmp_0;
  real_T pData_tmp_1;
  real_T pData_tmp_2;
  int32_T j;
  int_T i;

  /* UnitConversion: '<S2>/Unit Conversion' incorporates:
   *  Constant: '<S1>/Constant3'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  TailRotor_B->UnitConversion = 0.017453292519943295 *
    TailRotor_P.Constant3_Value;

  /* Outport: '<Root>/Ft' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant2'
   *  SignalConversion generated from: '<S1>/Rotation Angles to Direction Cosine Matrix'
   */
  TailRotor_Y_Ft[0] = TailRotor_B->UnitConversion;
  TailRotor_Y_Ft[1] = TailRotor_P.Constant1_Value;
  TailRotor_Y_Ft[2] = TailRotor_P.Constant2_Value;

  /* Angle2Dcm: '<S1>/Rotation Angles to Direction Cosine Matrix' incorporates:
   *  Outport: '<Root>/Ft'
   */
  pData_tmp_0 = cos(TailRotor_Y_Ft[2]);
  pData_tmp = sin(TailRotor_Y_Ft[2]);
  pData_tmp_2 = cos(TailRotor_Y_Ft[1]);
  pData_tmp_1 = sin(TailRotor_Y_Ft[1]);
  pData_idx_0_tmp = pData_tmp * 0.0;
  pData_idx_0_tmp_0 = 0.0 * pData_tmp_1;
  pData_idx_0 = (pData_tmp_0 * pData_tmp_2 + pData_idx_0_tmp) +
    pData_idx_0_tmp_0;
  pData_idx_3_tmp = pData_tmp_0 * 0.0;
  pData_idx_3 = pData_idx_3_tmp + pData_tmp;
  pData_idx_6_tmp = 0.0 * pData_tmp_2;
  pData_idx_0_tmp = (pData_tmp_0 * -pData_tmp_1 + pData_idx_0_tmp) +
    pData_idx_6_tmp;
  pData_idx_1 = (pData_tmp_2 * -pData_tmp + pData_idx_3_tmp) + pData_idx_0_tmp_0;
  pData_idx_0_tmp_0 = -pData_tmp * 0.0 + pData_tmp_0;
  pData_idx_3_tmp = (-pData_tmp_1 * -pData_tmp + pData_idx_3_tmp) +
    pData_idx_6_tmp;
  pData_idx_6_tmp += pData_tmp_1;
  pData_tmp_2 += 0.0 * -pData_tmp_1;
  pData_tmp_0 = cos(TailRotor_Y_Ft[0]);
  pData_tmp = sin(TailRotor_Y_Ft[0]);
  TailRotor_B->RotationAnglestoDirectionCosine[0] = (pData_idx_3 * 0.0 +
    pData_idx_0) + pData_idx_0_tmp * 0.0;
  TailRotor_B->RotationAnglestoDirectionCosine[1] = (pData_idx_0_tmp_0 * 0.0 +
    pData_idx_1) + pData_idx_3_tmp * 0.0;
  TailRotor_B->RotationAnglestoDirectionCosine[2] = pData_tmp_2 * 0.0 +
    pData_idx_6_tmp;
  pData_idx_0 *= 0.0;
  TailRotor_B->RotationAnglestoDirectionCosine[3] = (pData_idx_3 * pData_tmp_0 +
    pData_idx_0) + pData_idx_0_tmp * -pData_tmp;
  pData_tmp_1 = pData_idx_1 * 0.0;
  TailRotor_B->RotationAnglestoDirectionCosine[4] = (pData_idx_0_tmp_0 *
    pData_tmp_0 + pData_tmp_1) + pData_idx_3_tmp * -pData_tmp;
  pData_idx_1 = pData_idx_6_tmp * 0.0;
  TailRotor_B->RotationAnglestoDirectionCosine[5] = (pData_tmp_0 * 0.0 +
    pData_idx_1) + -pData_tmp * pData_tmp_2;
  TailRotor_B->RotationAnglestoDirectionCosine[6] = (pData_idx_3 * pData_tmp +
    pData_idx_0) + pData_idx_0_tmp * pData_tmp_0;
  TailRotor_B->RotationAnglestoDirectionCosine[7] = (pData_idx_0_tmp_0 *
    pData_tmp + pData_tmp_1) + pData_idx_3_tmp * pData_tmp_0;
  TailRotor_B->RotationAnglestoDirectionCosine[8] = (pData_tmp * 0.0 +
    pData_idx_1) + pData_tmp_2 * pData_tmp_0;

  /* Rotor: '<S1>/Rotor6' incorporates:
   *  Inport: '<Root>/CollectiveT'
   *  Inport: '<Root>/SpeedT'
   *  Inport: '<Root>/rho'
   */
  pData_tmp_0 = (TailRotor_P.Rotor6_thetaRoot + TailRotor_U_CollectiveT) *
    0.66666666666666663 + TailRotor_P.Rotor6_thetaTwist / 2.0;
  pData_tmp = TailRotor_P.Rotor6_Nb * TailRotor_P.Rotor6_chord /
    3.1415926535897931 / TailRotor_P.Rotor6_radius;
  TailRotor_B->Rotor6_o3 = 0.0;
  pData_idx_3 = 0.0;
  pData_idx_0_tmp = TailRotor_P.Rotor6_hingeOffset / TailRotor_P.Rotor6_radius;
  xnodes[0] = pData_idx_0_tmp;
  for (i = 0; i < 100; i++) {
    pData_idx_0 = xnodes[i];
    pData_idx_0_tmp_0 = (1.0 - pData_idx_0_tmp) / 100.0;
    xnodes[i + 1] = pData_idx_0_tmp_0 + pData_idx_0;
    pData_idx_0 += pData_idx_0_tmp_0 / 2.0;
    pData_idx_3_tmp = 0.001;
    j = 0;
    do {
      pData_tmp_2 = (pData_idx_0 - 1.0) * TailRotor_P.Rotor6_Nb;
      pData_tmp_1 = exp(pData_tmp_2 / (2.0 * pData_idx_3_tmp));
      pData_idx_1 = -(TailRotor_P.Rotor6_Nb / 2.0);
      pData_idx_3_tmp -= (acos(exp((1.0 - pData_idx_0) / (pData_idx_3_tmp /
        pData_idx_0 * pData_idx_0) * pData_idx_1)) * 0.63661977236758138 * 4.0 *
                          rt_powd_snf(pData_idx_3_tmp, 2.0) - (pData_tmp_0 /
        pData_idx_0 * pData_idx_0 - pData_idx_3_tmp) * (0.5 * pData_tmp *
        TailRotor_P.Rotor6_clalpha)) / (1.2732 * TailRotor_P.Rotor6_Nb *
        pData_tmp_1 * (pData_idx_0 - 1.0) / rt_powd_snf(1.0 - exp(pData_tmp_2 /
        pData_idx_3_tmp), 0.5) + (TailRotor_P.Rotor6_clalpha * pData_tmp / 2.0 +
        5.093 * pData_idx_3_tmp * acos(pData_tmp_1)));
      j++;
    } while ((j < (int32_T)(int8_T)100) || (fabs(pData_idx_3_tmp -
               pData_idx_3_tmp) >= 1.0E-6));

    pData_tmp_2 = acos(exp((1.0 - pData_idx_0) / (pData_idx_3_tmp / pData_idx_0 *
      pData_idx_0) * pData_idx_1)) * 0.63661977236758138 * 4.0;
    TailRotor_B->Rotor6_o3 += pData_tmp_2 * rt_powd_snf(pData_idx_3_tmp, 2.0) *
      pData_idx_0 * pData_idx_0_tmp_0;
    pData_idx_3 += pData_tmp_2 * rt_powd_snf(pData_idx_3_tmp, 3.0) * pData_idx_0
      * pData_idx_0_tmp_0;
  }

  TailRotor_B->Rotor6_o4 = pData_tmp * TailRotor_P.Rotor6_cd0 / 8.0 +
    pData_idx_3;
  TailRotor_B->Rotor6_o1[0] = 0.0;
  TailRotor_B->Rotor6_o1[1] = 0.0;
  pData_tmp_0 = rt_powd_snf(TailRotor_P.Rotor6_radius, 2.0);
  TailRotor_B->Rotor6_o1[2] = -(TailRotor_B->Rotor6_o3 * TailRotor_U_rho *
    3.1415926535897931 * pData_tmp_0 * rt_powd_snf(TailRotor_U_SpeedT *
    TailRotor_P.Rotor6_radius, 2.0));
  TailRotor_B->Rotor6_o2[0] = 0.0;
  TailRotor_B->Rotor6_o2[1] = 0.0;
  TailRotor_B->Rotor6_o2[2] = -TailRotor_B->Rotor6_o4 * TailRotor_U_rho *
    3.1415926535897931 * pData_tmp_0 * TailRotor_U_SpeedT * fabs
    (TailRotor_U_SpeedT) * rt_powd_snf(TailRotor_P.Rotor6_radius, 3.0);

  /* End of Rotor: '<S1>/Rotor6' */

  /* Product: '<S1>/Transform forces about  x-axis by 90 deg ' incorporates:
   *  Outport: '<Root>/Ft'
   */
  pData_tmp_0 = 0.0;
  pData_tmp = 0.0;
  pData_idx_3 = 0.0;

  /* Product: '<S1>/Transform moments about x-axis by 90 deg' */
  pData_idx_0_tmp = 0.0;
  pData_idx_0_tmp_0 = 0.0;
  pData_idx_0 = 0.0;
  for (i = 0; i < 3; i++) {
    /* Product: '<S1>/Transform forces about  x-axis by 90 deg ' incorporates:
     *  Angle2Dcm: '<S1>/Rotation Angles to Direction Cosine Matrix'
     *  Outport: '<Root>/Ft'
     */
    tmp_0 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&TailRotor_B->RotationAnglestoDirectionCosine[3 * i]), _mm_set1_pd
      (TailRotor_B->Rotor6_o1[i])), _mm_set_pd(pData_tmp, pData_tmp_0));
    _mm_storeu_pd(&tmp[0], tmp_0);

    /* Product: '<S1>/Transform forces about  x-axis by 90 deg ' incorporates:
     *  Angle2Dcm: '<S1>/Rotation Angles to Direction Cosine Matrix'
     *  Outport: '<Root>/Ft'
     *  Product: '<S1>/Transform moments about x-axis by 90 deg'
     */
    pData_tmp_0 = tmp[0];
    pData_tmp = tmp[1];
    _mm_storeu_pd(&tmp[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd
      (TailRotor_B->RotationAnglestoDirectionCosine[3 * i],
       TailRotor_B->RotationAnglestoDirectionCosine[3 * i + 2]), _mm_set_pd
      (TailRotor_B->Rotor6_o2[i], TailRotor_B->Rotor6_o1[i])), _mm_set_pd
      (pData_idx_0_tmp, pData_idx_3)));
    pData_idx_3 = tmp[0];

    /* Product: '<S1>/Transform moments about x-axis by 90 deg' */
    pData_idx_0_tmp = tmp[1];

    /* Product: '<S1>/Transform forces about  x-axis by 90 deg ' incorporates:
     *  Angle2Dcm: '<S1>/Rotation Angles to Direction Cosine Matrix'
     *  Product: '<S1>/Transform moments about x-axis by 90 deg'
     */
    tmp_0 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&TailRotor_B->RotationAnglestoDirectionCosine[3 * i + 1]), _mm_set1_pd
      (TailRotor_B->Rotor6_o2[i])), _mm_set_pd(pData_idx_0, pData_idx_0_tmp_0));
    _mm_storeu_pd(&tmp[0], tmp_0);

    /* Product: '<S1>/Transform moments about x-axis by 90 deg' */
    pData_idx_0_tmp_0 = tmp[0];
    pData_idx_0 = tmp[1];
  }

  /* Product: '<S1>/Transform moments about x-axis by 90 deg' */
  TailRotor_B->Transformmomentsaboutxaxisby90d[2] = pData_idx_0;
  TailRotor_B->Transformmomentsaboutxaxisby90d[1] = pData_idx_0_tmp_0;
  TailRotor_B->Transformmomentsaboutxaxisby90d[0] = pData_idx_0_tmp;

  /* Product: '<S1>/Transform forces about  x-axis by 90 deg ' incorporates:
   *  Outport: '<Root>/Ft'
   */
  TailRotor_Y_Ft[2] = pData_idx_3;
  TailRotor_Y_Ft[1] = pData_tmp;
  TailRotor_Y_Ft[0] = pData_tmp_0;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S1>/Constant7'
   *  Outport: '<Root>/Ft'
   *  Product: '<S3>/Element Product'
   */
  _mm_storeu_pd(&TailRotor_B->Sum_f[0], _mm_mul_pd(_mm_set_pd(TailRotor_Y_Ft[0],
    TailRotor_P.Constant7_Value[1]), _mm_set_pd(TailRotor_P.Constant7_Value[2],
    TailRotor_Y_Ft[2])));
  _mm_storeu_pd(&TailRotor_B->Sum_f[2], _mm_mul_pd(_mm_set_pd(TailRotor_Y_Ft[1],
    TailRotor_P.Constant7_Value[0]), _mm_set_pd(TailRotor_P.Constant7_Value[2],
    TailRotor_Y_Ft[1])));
  _mm_storeu_pd(&TailRotor_B->Sum_f[4], _mm_mul_pd(_mm_set_pd(TailRotor_Y_Ft[0],
    TailRotor_P.Constant7_Value[0]), _mm_set_pd(TailRotor_P.Constant7_Value[1],
    TailRotor_Y_Ft[2])));

  /* Sum: '<S3>/Sum' */
  tmp_0 = _mm_sub_pd(_mm_loadu_pd(&TailRotor_B->Sum_f[0]), _mm_loadu_pd
                     (&TailRotor_B->Sum_f[3]));

  /* Sum: '<S3>/Sum' */
  _mm_storeu_pd(&TailRotor_B->Sum_f[0], tmp_0);

  /* Sum: '<S1>/Sum' incorporates:
   *  Sum: '<S3>/Sum'
   */
  _mm_storeu_pd(&tmp[0], _mm_add_pd(_mm_set_pd(TailRotor_B->Sum_f[0],
    TailRotor_B->Sum_f[2]), _mm_mul_pd(_mm_set_pd
    (TailRotor_B->Transformmomentsaboutxaxisby90d[0], TailRotor_B->Sum_f[5]),
    _mm_set_pd(1.0, -1.0))));

  /* Sum: '<S3>/Sum' */
  TailRotor_B->Sum_f[2] = tmp[0];

  /* Outport: '<Root>/Mt' */
  TailRotor_Y_Mt[0] = tmp[1];

  /* Sum: '<S1>/Sum' */
  tmp_0 = _mm_add_pd(_mm_loadu_pd(&TailRotor_B->Sum_f[1]), _mm_loadu_pd
                     (&TailRotor_B->Transformmomentsaboutxaxisby90d[1]));

  /* Outport: '<Root>/Mt' */
  _mm_storeu_pd(&TailRotor_Y_Mt[1], tmp_0);
}

/* Model initialize function */
void TailRotor_initialize(RT_MODEL_TailRotor_T *const TailRotor_M, real_T
  *TailRotor_U_SpeedT, real_T *TailRotor_U_CollectiveT, real_T *TailRotor_U_rho,
  real_T TailRotor_Y_Ft[3], real_T TailRotor_Y_Mt[3])
{
  B_TailRotor_T *TailRotor_B = TailRotor_M->blockIO;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) TailRotor_B), 0,
                sizeof(B_TailRotor_T));

  /* external inputs */
  *TailRotor_U_SpeedT = 0.0;
  *TailRotor_U_CollectiveT = 0.0;
  *TailRotor_U_rho = 0.0;

  /* external outputs */
  (void)memset(&TailRotor_Y_Ft[0], 0, 3U * sizeof(real_T));
  (void)memset(&TailRotor_Y_Mt[0], 0, 3U * sizeof(real_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  TailRotor_InitializeDataMapInfo(TailRotor_M);
}

/* Model terminate function */
void TailRotor_terminate(RT_MODEL_TailRotor_T *const TailRotor_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(TailRotor_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

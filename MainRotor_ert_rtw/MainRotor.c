/*
 * File: MainRotor.c
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

#include "MainRotor.h"
#include "MainRotor_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include "rtwtypes.h"
#include <string.h>
#include "MainRotor_capi.h"
#include "rt_defines.h"

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

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2((real_T)tmp, (real_T)tmp_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void MainRotor_step(RT_MODEL_MainRotor_T *const MainRotor_M, real_T
                    MainRotor_U_SpeedM, real_T MainRotor_U_CollectiveM, real_T
                    MainRotor_U_CyclicLat, real_T MainRotor_U_CyclicLon, real_T
                    MainRotor_U_rho, real_T MainRotor_U_wb[3], real_T
                    MainRotor_U_Vb[3], real_T MainRotor_Y_Fm[3], real_T
                    MainRotor_Y_Mm[3])
{
  B_MainRotor_T *MainRotor_B = MainRotor_M->blockIO;
  __m128d tmp_0;
  __m128d tmp_1;
  __m128d tmp_2;
  __m128d tmp_3;
  __m128d tmp_4;
  __m128d tmp_5;
  __m128d tmp_6;
  __m128d tmp_7;
  __m128d tmp_8;
  __m128d tmp_9;
  __m128d tmp_a;
  __m128d tmp_b;
  __m128d tmp_c;
  __m128d tmp_d;
  __m128d tmp_e;
  __m128d tmp_f;
  __m128d tmp_g;
  __m128d tmp_h;
  __m128d tmp_i;
  real_T xnodes[101];
  real_T tmp[2];
  real_T CQ;
  real_T sigma;
  real_T thetaVal;
  real_T x1;
  real_T x1_tmp;
  real_T x1_tmp_0;
  real_T x1_tmp_tmp;
  real_T xnodes_0;
  real_T xnodes_tmp;
  real_T xnodes_tmp_0;
  int32_T j;
  int_T i;

  /* Rotor: '<S1>/Rotor1' incorporates:
   *  Inport: '<Root>/CollectiveM'
   *  Inport: '<Root>/SpeedM'
   *  Inport: '<Root>/Vb'
   */
  thetaVal = (MainRotor_P.Rotor1_thetaRoot + MainRotor_U_CollectiveM) *
    0.66666666666666663 + MainRotor_P.Rotor1_thetaTwist / 2.0;
  sigma = MainRotor_P.Rotor1_Nb * MainRotor_P.Rotor1_chord / 3.1415926535897931 /
    MainRotor_P.Rotor1_radius;
  MainRotor_B->Rotor1_o3 = 0.0;
  CQ = 0.0;
  xnodes_tmp = MainRotor_P.Rotor1_hingeOffset / MainRotor_P.Rotor1_radius;
  xnodes[0] = xnodes_tmp;
  for (i = 0; i < 100; i++) {
    xnodes_0 = xnodes[i];
    xnodes_tmp_0 = (1.0 - xnodes_tmp) / 100.0;
    xnodes[i + 1] = xnodes_tmp_0 + xnodes_0;
    xnodes_0 += xnodes_tmp_0 / 2.0;
    x1 = 0.001;
    j = 0;
    do {
      x1_tmp_tmp = (xnodes_0 - 1.0) * MainRotor_P.Rotor1_Nb;
      x1_tmp = exp(x1_tmp_tmp / (2.0 * x1));
      x1_tmp_0 = -(MainRotor_P.Rotor1_Nb / 2.0);
      x1 -= (acos(exp((1.0 - xnodes_0) / (x1 / xnodes_0 * xnodes_0) * x1_tmp_0))
             * 0.63661977236758138 * 4.0 * rt_powd_snf(x1, 2.0) - (thetaVal /
              xnodes_0 * xnodes_0 - x1) * (0.5 * sigma *
              MainRotor_P.Rotor1_clalpha)) / (1.2732 * MainRotor_P.Rotor1_Nb *
        x1_tmp * (xnodes_0 - 1.0) / rt_powd_snf(1.0 - exp(x1_tmp_tmp / x1), 0.5)
        + (MainRotor_P.Rotor1_clalpha * sigma / 2.0 + 5.093 * x1 * acos(x1_tmp)));
      j++;
    } while ((j < (int32_T)(int8_T)100) || (fabs(x1 - x1) >= 1.0E-6));

    x1_tmp_tmp = acos(exp((1.0 - xnodes_0) / (x1 / xnodes_0 * xnodes_0) *
                          x1_tmp_0)) * 0.63661977236758138 * 4.0;
    MainRotor_B->Rotor1_o3 += x1_tmp_tmp * rt_powd_snf(x1, 2.0) * xnodes_0 *
      xnodes_tmp_0;
    CQ += x1_tmp_tmp * rt_powd_snf(x1, 3.0) * xnodes_0 * xnodes_tmp_0;
  }

  MainRotor_B->Rotor1_o4 = sigma * MainRotor_P.Rotor1_cd0 / 8.0 + CQ;
  if (MainRotor_U_SpeedM == 0.0) {
    CQ = 2.2204460492503131E-16;
  } else {
    CQ = MainRotor_U_SpeedM;
  }

  xnodes_tmp_0 = sqrt(rt_powd_snf(MainRotor_U_Vb[0], 2.0) + rt_powd_snf
                      (MainRotor_U_Vb[1], 2.0));
  xnodes_0 = fabs(CQ * MainRotor_P.Rotor1_radius);
  x1 = xnodes_tmp_0 / xnodes_0;
  x1_tmp_tmp = rt_atan2d_snf(MainRotor_U_Vb[1], MainRotor_U_Vb[0]);
  x1_tmp = sin(x1_tmp_tmp);
  x1_tmp_tmp = cos(x1_tmp_tmp);
  if (rtIsNaN(MainRotor_U_SpeedM)) {
    x1_tmp_0 = (rtNaN);
  } else if (MainRotor_U_SpeedM < 0.0) {
    x1_tmp_0 = -1.0;
  } else {
    x1_tmp_0 = MainRotor_U_SpeedM > 0.0 ? 1.0 : 0.0;
  }

  tmp_0 = _mm_set1_pd(xnodes_0);

  /* Rotor: '<S1>/Rotor1' */
  tmp_1 = _mm_set1_pd(1.0);
  tmp_2 = _mm_div_pd(_mm_set1_pd(xnodes_tmp_0), tmp_0);

  /* Rotor: '<S1>/Rotor1' incorporates:
   *  Inport: '<Root>/Vb'
   */
  tmp_3 = _mm_set1_pd(1.5);
  tmp_4 = _mm_set1_pd(rt_powd_snf(x1, 2.0));
  tmp_5 = _mm_set1_pd(2.0);
  tmp_0 = _mm_div_pd(_mm_set1_pd(sqrt(rt_powd_snf(MainRotor_U_Vb[2], 2.0))),
                     tmp_0);

  /* Rotor: '<S1>/Rotor1' */
  tmp_6 = _mm_div_pd(_mm_set1_pd(MainRotor_P.Rotor1_hingeOffset), _mm_set1_pd
                     (MainRotor_P.Rotor1_radius));

  /* Rotor: '<S1>/Rotor1' */
  tmp_7 = _mm_set1_pd(4.0);

  /* Rotor: '<S1>/Rotor1' */
  tmp_8 = _mm_set1_pd(MainRotor_P.Rotor1_gamma);
  tmp_9 = _mm_mul_pd(_mm_add_pd(_mm_mul_pd(_mm_div_pd(_mm_mul_pd(_mm_div_pd
    (_mm_mul_pd(tmp_2, tmp_8), _mm_set1_pd(MainRotor_P.Rotor1_clalpha)),
    _mm_set1_pd(0.66666666666666663)), _mm_add_pd(_mm_mul_pd(tmp_6, tmp_3),
    tmp_1)), _mm_div_pd(_mm_set1_pd(MainRotor_B->Rotor1_o3), _mm_set1_pd(sigma))),
    tmp_0), _mm_set1_pd(1.3333333333333333));
  tmp_f = _mm_div_pd(tmp_4, tmp_5);
  tmp_a = _mm_add_pd(tmp_f, tmp_1);

  /* Inport: '<Root>/CyclicLat' */
  tmp_b = _mm_set1_pd(MainRotor_U_CyclicLat);

  /* Rotor: '<S1>/Rotor1' */
  tmp_g = _mm_set1_pd(12.0);
  tmp_c = _mm_mul_pd(tmp_6, tmp_g);

  /* Rotor: '<S1>/Rotor1' */
  tmp_d = _mm_div_pd(_mm_set1_pd(rt_powd_snf(x1, 4.0)), tmp_7);
  tmp_h = _mm_set1_pd(rt_powd_snf(1.0 - xnodes_tmp, 3.0));
  tmp_e = _mm_mul_pd(tmp_8, tmp_h);

  /* Rotor: '<S1>/Rotor1' incorporates:
   *  Inport: '<Root>/CyclicLon'
   *  Inport: '<Root>/wb'
   */
  tmp_0 = _mm_sub_pd(_mm_sub_pd(_mm_mul_pd(_mm_mul_pd(tmp_7, _mm_set1_pd
    (thetaVal)), tmp_2), _mm_mul_pd(_mm_add_pd(_mm_mul_pd(tmp_3, tmp_4), tmp_1),
    _mm_set1_pd(MainRotor_U_CyclicLon))), _mm_mul_pd(_mm_mul_pd(tmp_2, tmp_5),
    tmp_0));
  tmp_2 = _mm_set1_pd(fabs(CQ));
  tmp_3 = _mm_div_pd(_mm_set1_pd(-16.0), tmp_8);
  tmp_5 = _mm_div_pd(_mm_set_pd(MainRotor_U_wb[0], MainRotor_U_wb[1]), tmp_2);
  tmp_i = _mm_set1_pd(rt_powd_snf(1.0 - xnodes_tmp, 2.0));
  tmp_f = _mm_sub_pd(tmp_1, tmp_f);

  /* Rotor: '<S1>/Rotor1' incorporates:
   *  Inport: '<Root>/SpeedM'
   *  Inport: '<Root>/rho'
   *  Inport: '<Root>/wb'
   *  Outport: '<Root>/Fm'
   */
  _mm_storeu_pd(&tmp[0], _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_mul_pd(_mm_add_pd
    (_mm_add_pd(_mm_div_pd(tmp_9, tmp_a), tmp_b), _mm_mul_pd(tmp_0, _mm_div_pd
    (tmp_c, _mm_mul_pd(_mm_sub_pd(tmp_1, tmp_d), tmp_e)))), _mm_set1_pd(x1_tmp_0)),
    _mm_set_pd(x1_tmp_tmp, x1_tmp)), _mm_mul_pd(_mm_add_pd(_mm_mul_pd(_mm_add_pd
    (tmp_9, _mm_mul_pd(tmp_a, tmp_b)), _mm_div_pd(tmp_c, _mm_mul_pd(_mm_add_pd
    (tmp_d, tmp_1), tmp_e))), _mm_div_pd(tmp_0, tmp_f)), _mm_set_pd(-x1_tmp,
    x1_tmp_tmp))), _mm_add_pd(_mm_div_pd(_mm_mul_pd(_mm_sub_pd(_mm_div_pd
    (_mm_mul_pd(tmp_3, _mm_div_pd(_mm_loadu_pd(&MainRotor_U_wb[0]), tmp_2)),
     tmp_i), tmp_5), _mm_div_pd(_mm_mul_pd(_mm_div_pd(tmp_g, tmp_8), tmp_6),
    tmp_h)), _mm_sub_pd(tmp_1, _mm_div_pd(tmp_4, tmp_7))), _mm_div_pd(_mm_add_pd
    (_mm_div_pd(_mm_mul_pd(tmp_3, tmp_5), tmp_i), _mm_div_pd(_mm_loadu_pd
    (&MainRotor_U_wb[0]), tmp_2)), tmp_f))));
  thetaVal = rt_powd_snf(MainRotor_P.Rotor1_radius, 2.0);
  sigma = cos(tmp[1]);
  xnodes_tmp = MainRotor_B->Rotor1_o3 * MainRotor_U_rho * 3.1415926535897931 *
    thetaVal * rt_powd_snf(MainRotor_U_SpeedM * MainRotor_P.Rotor1_radius, 2.0);
  MainRotor_Y_Fm[0] = sin(tmp[0]) * -sigma * xnodes_tmp;
  MainRotor_Y_Fm[1] = xnodes_tmp * sin(tmp[1]);
  MainRotor_Y_Fm[2] = sigma * -cos(tmp[0]) * xnodes_tmp;
  MainRotor_B->Rotor1_o2[0] = 0.0;
  MainRotor_B->Rotor1_o2[1] = 0.0;
  MainRotor_B->Rotor1_o2[2] = -MainRotor_B->Rotor1_o4 * MainRotor_U_rho *
    3.1415926535897931 * thetaVal * MainRotor_U_SpeedM * fabs(MainRotor_U_SpeedM)
    * rt_powd_snf(MainRotor_P.Rotor1_radius, 3.0);

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S1>/Constant8'
   *  Outport: '<Root>/Fm'
   *  Product: '<S2>/Element Product'
   */
  _mm_storeu_pd(&MainRotor_B->Sum[0], _mm_mul_pd(_mm_set_pd(MainRotor_Y_Fm[0],
    MainRotor_P.Constant8_Value[1]), _mm_set_pd(MainRotor_P.Constant8_Value[2],
    MainRotor_Y_Fm[2])));
  _mm_storeu_pd(&MainRotor_B->Sum[2], _mm_mul_pd(_mm_set_pd(MainRotor_Y_Fm[1],
    MainRotor_P.Constant8_Value[0]), _mm_set_pd(MainRotor_P.Constant8_Value[2],
    MainRotor_Y_Fm[1])));
  _mm_storeu_pd(&MainRotor_B->Sum[4], _mm_mul_pd(_mm_set_pd(MainRotor_Y_Fm[0],
    MainRotor_P.Constant8_Value[0]), _mm_set_pd(MainRotor_P.Constant8_Value[1],
    MainRotor_Y_Fm[2])));

  /* Sum: '<S2>/Sum' */
  thetaVal = MainRotor_B->Sum[0] - MainRotor_B->Sum[3];

  /* Sum: '<S2>/Sum' */
  MainRotor_B->Sum[0] = thetaVal;

  /* Outport: '<Root>/Mm' incorporates:
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S2>/Sum'
   */
  MainRotor_Y_Mm[0] = thetaVal;

  /* Sum: '<S2>/Sum' */
  thetaVal = MainRotor_B->Sum[1] - MainRotor_B->Sum[4];

  /* Sum: '<S2>/Sum' */
  MainRotor_B->Sum[1] = thetaVal;

  /* Outport: '<Root>/Mm' incorporates:
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S2>/Sum'
   */
  MainRotor_Y_Mm[1] = thetaVal;

  /* Sum: '<S2>/Sum' */
  thetaVal = MainRotor_B->Sum[2] - MainRotor_B->Sum[5];

  /* Sum: '<S2>/Sum' */
  MainRotor_B->Sum[2] = thetaVal;

  /* Outport: '<Root>/Mm' incorporates:
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S2>/Sum'
   */
  MainRotor_Y_Mm[2] = thetaVal + MainRotor_B->Rotor1_o2[2];
}

/* Model initialize function */
void MainRotor_initialize(RT_MODEL_MainRotor_T *const MainRotor_M, real_T
  *MainRotor_U_SpeedM, real_T *MainRotor_U_CollectiveM, real_T
  *MainRotor_U_CyclicLat, real_T *MainRotor_U_CyclicLon, real_T *MainRotor_U_rho,
  real_T MainRotor_U_wb[3], real_T MainRotor_U_Vb[3], real_T MainRotor_Y_Fm[3],
  real_T MainRotor_Y_Mm[3])
{
  B_MainRotor_T *MainRotor_B = MainRotor_M->blockIO;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) MainRotor_B), 0,
                sizeof(B_MainRotor_T));

  /* external inputs */
  (void)memset(&MainRotor_U_wb[0], 0, 3U * sizeof(real_T));
  (void)memset(&MainRotor_U_Vb[0], 0, 3U * sizeof(real_T));
  *MainRotor_U_SpeedM = 0.0;
  *MainRotor_U_CollectiveM = 0.0;
  *MainRotor_U_CyclicLat = 0.0;
  *MainRotor_U_CyclicLon = 0.0;
  *MainRotor_U_rho = 0.0;

  /* external outputs */
  (void)memset(&MainRotor_Y_Fm[0], 0, 3U * sizeof(real_T));
  (void)memset(&MainRotor_Y_Mm[0], 0, 3U * sizeof(real_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  MainRotor_InitializeDataMapInfo(MainRotor_M);
}

/* Model terminate function */
void MainRotor_terminate(RT_MODEL_MainRotor_T *const MainRotor_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(MainRotor_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

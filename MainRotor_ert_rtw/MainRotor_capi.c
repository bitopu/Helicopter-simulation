/*
 * File: MainRotor_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "MainRotor_capi_host.h"
#define sizeof(...)                    ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "MainRotor.h"
#include "MainRotor_capi.h"
#include "MainRotor_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

static rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 0, TARGET_STRING("MainRotor/MainRotor/Constant8"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 1, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("radius"), 0, 1, 0 },

  { 2, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("Nb"), 0, 1, 0 },

  { 3, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("chord"), 0, 1, 0 },

  { 4, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("hingeOffset"), 0, 1, 0 },

  { 5, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("clalpha"), 0, 1, 0 },

  { 6, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("cd0"), 0, 1, 0 },

  { 7, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("gamma"), 0, 1, 0 },

  { 8, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("thetaRoot"), 0, 1, 0 },

  { 9, TARGET_STRING("MainRotor/MainRotor/Rotor1"),
    TARGET_STRING("thetaTwist"), 0, 1, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void MainRotor_InitializeDataAddr(void* dataAddr[])
{
  dataAddr[0] = (void*) (&MainRotor_P.Constant8_Value[0]);
  dataAddr[1] = (void*) (&MainRotor_P.Rotor1_radius);
  dataAddr[2] = (void*) (&MainRotor_P.Rotor1_Nb);
  dataAddr[3] = (void*) (&MainRotor_P.Rotor1_chord);
  dataAddr[4] = (void*) (&MainRotor_P.Rotor1_hingeOffset);
  dataAddr[5] = (void*) (&MainRotor_P.Rotor1_clalpha);
  dataAddr[6] = (void*) (&MainRotor_P.Rotor1_cd0);
  dataAddr[7] = (void*) (&MainRotor_P.Rotor1_gamma);
  dataAddr[8] = (void*) (&MainRotor_P.Rotor1_thetaRoot);
  dataAddr[9] = (void*) (&MainRotor_P.Rotor1_thetaTwist);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void MainRotor_InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void MainRotor_InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
  loggingPtrs[1] = (NULL);
  loggingPtrs[2] = (NULL);
  loggingPtrs[3] = (NULL);
  loggingPtrs[4] = (NULL);
  loggingPtrs[5] = (NULL);
  loggingPtrs[6] = (NULL);
  loggingPtrs[7] = (NULL);
  loggingPtrs[8] = (NULL);
  loggingPtrs[9] = (NULL);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_VECTOR, 0, 2, 0 },

  { rtwCAPI_SCALAR, 2, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  3,                                   /* 1 */
  1,                                   /* 2 */
  1                                    /* 3 */
};

/* Fixed Point Map */
static rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  {
    (NULL), (NULL), 0, 0
  }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { (NULL), 0,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 10,
    rtModelParameters, 0 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 1892467883U,
    2796462281U,
    4076606562U,
    760611353U },
  (NULL), 0,
  (boolean_T)0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  MainRotor_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void MainRotor_InitializeDataMapInfo(RT_MODEL_MainRotor_T *const MainRotor_M)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(MainRotor_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(MainRotor_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(MainRotor_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  MainRotor_InitializeDataAddr(MainRotor_M->DataMapInfo.dataAddress);
  rtwCAPI_SetDataAddressMap(MainRotor_M->DataMapInfo.mmi,
    MainRotor_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  MainRotor_InitializeVarDimsAddr(MainRotor_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(MainRotor_M->DataMapInfo.mmi,
    MainRotor_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(MainRotor_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(MainRotor_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  MainRotor_InitializeLoggingFunctions(MainRotor_M->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(MainRotor_M->DataMapInfo.mmi,
    MainRotor_M->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(MainRotor_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(MainRotor_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(MainRotor_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void MainRotor_host_InitializeDataMapInfo(MainRotor_host_DataMapInfo_T
    *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (NULL));

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (NULL));

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (NULL));

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

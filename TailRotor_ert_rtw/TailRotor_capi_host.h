#ifndef TailRotor_cap_host_h__
#define TailRotor_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} TailRotor_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C"
{

#endif

  void TailRotor_host_InitializeDataMapInfo(TailRotor_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* TailRotor_cap_host_h__ */

/* EOF: TailRotor_capi_host.h */

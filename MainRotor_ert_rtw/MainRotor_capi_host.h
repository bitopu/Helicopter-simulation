#ifndef MainRotor_cap_host_h__
#define MainRotor_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} MainRotor_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C"
{

#endif

  void MainRotor_host_InitializeDataMapInfo(MainRotor_host_DataMapInfo_T
    *dataMap, const char *path);

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* MainRotor_cap_host_h__ */

/* EOF: MainRotor_capi_host.h */

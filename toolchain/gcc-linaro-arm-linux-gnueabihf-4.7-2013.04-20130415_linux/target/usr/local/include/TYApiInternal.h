#ifndef TY_API_INTERNAL_H_
#define TY_API_INTERNAL_H_

#include <exception>
#include "TYApi.h"

#ifdef EXPORT_TY_INTERNAL_API
#    define TY_INTERNAL_API TY_EXPORT
#    define TY_INTERNAL_CAPI TY_CAPI
#else
#    define TY_INTERNAL_API 
#    define TY_INTERNAL_CAPI TY_EXTC TY_STATUS TY_STDC
#endif

#define PERCIPIO_DEV_PORT   7001    // internal port, 7000 is for APP

//---------------------------------------------------
// Used internal
//---------------------------------------------------

typedef enum TY_FEATURE_ID_LIST_ext{
    TY_STRING_SN          = 0xf00 | TY_FEATURE_STRING, // 0x5f00
    TY_STRING_VENDOR      = 0xf01 | TY_FEATURE_STRING,
    TY_STRING_MODEL       = 0xf02 | TY_FEATURE_STRING,
    TY_STRING_HW_VER      = 0xf03 | TY_FEATURE_STRING,
    TY_STRING_FW_VER      = 0xf04 | TY_FEATURE_STRING,
    TY_STRING_FW_BUILD    = 0xf05 | TY_FEATURE_STRING,
    TY_STRING_SENSOR_NAME = 0xf06 | TY_FEATURE_STRING,
    TY_STRING_BUILD_HASH  = 0xf07 | TY_FEATURE_STRING,
    TY_STRING_USER        = 0xf08 | TY_FEATURE_STRING,

    TY_STRING_CONFIG_XML  = 0xf10 | TY_FEATURE_STRING,
    TY_STRING_CONFIG_VER  = 0xf11 | TY_FEATURE_STRING,

    TY_INT_INTRINSIC_W    = 0x003 | TY_FEATURE_INT,
    TY_INT_INTRINSIC_H    = 0x004 | TY_FEATURE_INT,

    TY_INT_RGB_ANALOG_GAIN = 0x525 | TY_FEATURE_INT, // for compatible with old device
}TY_FEATURE_ID_LIST_ext;


//---------------------------------------------------
// Utils
//---------------------------------------------------

extern void debug_set_flag();
extern void debug();
extern void debug_core();

typedef enum TY_LOG_LEVEL_LIST{
  TY_LOG_LEVEL_DEBUG    = 2,
  TY_LOG_LEVEL_INFO     = 3,
  TY_LOG_LEVEL_WARNING  = 4,
  TY_LOG_LEVEL_ERROR    = 5,
  TY_LOG_LEVEL_NEVER    = 9,
}TY_LOG_LEVEL_LIST;
typedef int32_t TY_LOG_LEVEL;


TY_INTERNAL_CAPI TYSetLogLevel             (TY_LOG_LEVEL level);


/// @brief Get device descriptor.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  string        String buffer to be filled.
/// @param  [in]  bufferSize    Size of string buffer.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      string is NULL.
/// @retval TY_STATUS_WRONG_SIZE        bufferSize is not large enough.
TY_INTERNAL_CAPI TYGetDeviceDescriptor     (TY_DEV_HANDLE hDevice, char* string, int32_t bufferSize);


/// @brief Override device descriptor.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  xml_desc      New xml descriptor.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NULL_POINTER      xml_desc is NULL.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_PARAMETER Invalid new descrptor.
TY_INTERNAL_CAPI TYOverrideDeviceDescriptor(TY_DEV_HANDLE hDevice, const char* xml_desc);


TY_INTERNAL_CAPI TYLicFullCheck(TY_DEV_HANDLE hDevice, const void* buffer, int32_t length);
TY_INTERNAL_CAPI TYLicRandomCheck(TY_DEV_HANDLE hDevice);
TY_INTERNAL_CAPI TYReadRegister(TY_DEV_HANDLE hDevice, uint32_t addr, void * buf, int32_t len);
TY_INTERNAL_CAPI TYWriteRegister(TY_DEV_HANDLE hDevice, uint32_t addr, void * buf, int32_t len);


#endif

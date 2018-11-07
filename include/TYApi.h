/**@file      TYApi.h
 * @brief     TYApi.h includes camera control and data receiving interface, 
 *            which supports configuration for image resolution,  frame rate, exposure  
 *            time, gain, working mode,etc.
 *
 */

/**@mainpage 
*  @section Changes compare to V2:
*  1. New Interface Layer
*       Add this layer to specify local network interface to open network camera,
*       solving the problem that someone wants to connect to a network camera with
*       ethernet rather than WIFI. Users have to call interface APIs before openning
*       devices.
*  2. New Image Processing Library
*       The new library which has header file TYImageProc.h collects all image
*       processing functions we provided.
*  3. New Coordinate Mapper
*       New TYCoordinateMapper.h handles various convertions, including
*       depth <-> point3D, point3D <-> point3D.
*  4. Components:
*       Removed Point3D component(TY_COMPONENT_POINT3D). Point3D is a virtual component
*       in V2, and the points are calculated from depth image. We put the calculation
*       outside tycam library to increase flexibility.
*  5. Features:
*       Removed   TY_BOOL_TRIGGER_MODE        , covered by TY_STRUCT_TRIGGER_PARAM
*       Added     TY_STRUCT_CAM_CALIB_DATA    , for easy use in image processing library
*                 TY_INT_IMAGE_MODE           , covered by new added TY_ENUM_IMAGE_MODE
*       Modified  TY_ENUM_IMAGE_MODE          , means resolution mode in V2, combind
*                                               resolution and pixel format in V3
*       Added some network camera's feature, such as TY_INT_PERSISTENT_IP,
*       TY_INT_PERSISTENT_SUBMASK, TY_INT_PACKET_DELAY, etc.
* 
* Copyright(C)2016-2018 Percipio All Rights Reserved
*
*
*
* @section Note
*   Depth camera, called "device", consists of several components. Each component
*   is a hardware module or virtual module, such as RGB sensor, depth sensor.
*   Each component has its own features, such as image width, exposure time, etc..
* 
*   NOTE: The component TY_COMPONENT_DEVICE is a virtual component that contains
*         all features related to the whole device, such as trigger mode, device IP.
* 
*   Each frame consists of several images. Normally, all the images have identical
*   timestamp, means they are captured at the same time.
* 
* */

#ifndef TY_API_H_
#define TY_API_H_

#include <stddef.h>
#include <stdlib.h>

#ifdef WIN32
#  ifndef _WIN32
#    define _WIN32
#  endif
#endif

#ifdef _WIN32
# ifndef _STDINT_H
#  if defined(_MSC_VER) && _MSC_VER < 1600
    typedef __int8            int8_t;
    typedef __int16           int16_t;
    typedef __int32           int32_t;
    typedef __int64           int64_t;
    typedef unsigned __int8   uint8_t;
    typedef unsigned __int16  uint16_t;
    typedef unsigned __int32  uint32_t;
    typedef unsigned __int64  uint64_t;
#  else
#   include <stdint.h>
#  endif
# endif
#else
# include <stdint.h>
#endif

// copy stdbool.h here in case bool not defined or <stdbool.h> cant be found
#ifndef _STDBOOL_H
# define _STDBOOL_H
# define __bool_true_false_are_defined	1
# ifndef __cplusplus
#  define bool  _Bool
#  define true  1
#  define false 0
# endif
#endif

#ifdef _WIN32
#  include <WinSock2.h>
#  include <Windows.h>
#  ifdef TY_STATIC_LIB
#    define TY_DLLIMPORT
#    define TY_DLLEXPORT
#  else
#    define TY_DLLIMPORT    __declspec(dllimport)
#    define TY_DLLEXPORT    __declspec(dllexport)
#  endif
#  define TY_STDC           __stdcall
#  define TY_CDEC           __cdecl
#else
#  ifdef TY_STATIC_LIB
#    define TY_DLLIMPORT
#    define TY_DLLEXPORT
#  else
#    define TY_DLLIMPORT    __attribute__((visibility("default")))
#    define TY_DLLEXPORT    __attribute__((visibility("default")))
#  endif
#  if defined(__i386__)
#    define TY_STDC         __attribute__((stdcall))
#    define TY_CDEC         __attribute__((cdecl))
#  else
#    define TY_STDC
#    define TY_CDEC
#  endif
#endif

#ifdef TY_BUILDING_LIB
#  define TY_EXPORT     TY_DLLEXPORT
#else
#  define TY_EXPORT     TY_DLLIMPORT
#endif

#if defined(__cplusplus)
#  define TY_EXTC extern "C"
#else
#  define TY_EXTC
#endif


#define TY_LIB_VERSION_MAJOR       3
#define TY_LIB_VERSION_MINOR       1 
#define TY_LIB_VERSION_PATCH       0 


//------------------------------------------------------------------------------
///@brief API call return status
typedef enum TY_STATUS_LIST
{
    TY_STATUS_OK                = 0,
    TY_STATUS_ERROR             = -1001,
    TY_STATUS_NOT_INITED        = -1002,
    TY_STATUS_NOT_IMPLEMENTED   = -1003,
    TY_STATUS_NOT_PERMITTED     = -1004,
    TY_STATUS_DEVICE_ERROR      = -1005,
    TY_STATUS_INVALID_PARAMETER = -1006,
    TY_STATUS_INVALID_HANDLE    = -1007,
    TY_STATUS_INVALID_COMPONENT = -1008,
    TY_STATUS_INVALID_FEATURE   = -1009,
    TY_STATUS_WRONG_TYPE        = -1010,
    TY_STATUS_WRONG_SIZE        = -1011,
    TY_STATUS_OUT_OF_MEMORY     = -1012,
    TY_STATUS_OUT_OF_RANGE      = -1013,
    TY_STATUS_TIMEOUT           = -1014,
    TY_STATUS_WRONG_MODE        = -1015,
    TY_STATUS_BUSY              = -1016,
    TY_STATUS_IDLE              = -1017,
    TY_STATUS_NO_DATA           = -1018,
    TY_STATUS_NO_BUFFER         = -1019,
    TY_STATUS_NULL_POINTER      = -1020,
    TY_STATUS_READONLY_FEATURE  = -1021,
    TY_STATUS_INVALID_DESCRIPTOR= -1022,
    TY_STATUS_INVALID_INTERFACE = -1023,
    TY_STATUS_FIRMWARE_ERROR    = -1024,
}TY_STATUS_LIST;
typedef int32_t TY_STATUS;

typedef enum TY_EVENT_LIST
{
    TY_EVENT_DEVICE_OFFLINE     = -2001,
    TY_EVENT_LICENSE_ERROR      = -2002,
    TY_EVENT_FW_INIT_ERROR      = -2003,
}TY_ENENT_LIST;
typedef int32_t TY_EVENT;


typedef void* TY_INTERFACE_HANDLE; ///<Interface handle 
typedef void* TY_DEV_HANDLE;///<Device Handle


///@breif  Device Component list
/// A device contains several component. 
/// Each component can be controlled by its own features, such as image width, exposure time, etc..
///@see To Know how to get feature information please refer to sample code DumpAllFeatures
typedef enum TY_DEVICE_COMPONENT_LIST
{
    TY_COMPONENT_DEVICE         = 0x80000000, ///< Abstract component stands for whole device, always enabled
    TY_COMPONENT_DEPTH_CAM      = 0x00010000, ///< Depth camera
    TY_COMPONENT_IR_CAM_LEFT    = 0x00040000, ///< Left IR camera
    TY_COMPONENT_IR_CAM_RIGHT   = 0x00080000, ///< Right IR camera
    TY_COMPONENT_RGB_CAM_LEFT   = 0x00100000, ///< Left RGB camera
    TY_COMPONENT_RGB_CAM_RIGHT  = 0x00200000, ///< Right RGB camera
    TY_COMPONENT_LASER          = 0x00400000, ///< Laser
    TY_COMPONENT_IMU            = 0x00800000, ///< Inertial Measurement Unit
    TY_COMPONENT_BRIGHT_HISTO   = 0x01000000, ///< virtual component for brightness histogram of ir

    TY_COMPONENT_RGB_CAM        = TY_COMPONENT_RGB_CAM_LEFT ///< Some device has only one RGB camera, map it to left
}TY_DEVICE_COMPONENT_LIST;
typedef int32_t TY_COMPONENT_ID;///< component unique  id @see TY_DEVICE_COMPONENT_LIST


//------------------------------------------------------------------------------
///Feature Format Type definitions
typedef enum TY_FEATURE_TYPE_LIST
{
    TY_FEATURE_INT              = 0x1000,
    TY_FEATURE_FLOAT            = 0X2000,
    TY_FEATURE_ENUM             = 0x3000,
    TY_FEATURE_BOOL             = 0x4000,
    TY_FEATURE_STRING           = 0x5000,
    TY_FEATURE_BYTEARRAY        = 0x6000,
    TY_FEATURE_STRUCT           = 0x7000,
}TY_FEATURE_TYPE_LIST;
typedef int32_t TY_FEATURE_TYPE;


///feature for component definitions 
typedef enum TY_FEATURE_ID_LIST
{
    TY_STRUCT_CAM_INTRINSIC         = 0x0000 | TY_FEATURE_STRUCT, ///< see TY_CAMERA_INTRINSIC
    TY_STRUCT_EXTRINSIC_TO_LEFT_IR  = 0x0001 | TY_FEATURE_STRUCT, ///< extrinsic from current component to left IR, see TY_CAMERA_EXTRINSIC
    TY_STRUCT_CAM_DISTORTION        = 0x0006 | TY_FEATURE_STRUCT, ///< see TY_CAMERA_DISTORTION
    TY_STRUCT_CAM_CALIB_DATA        = 0x0007 | TY_FEATURE_STRUCT, ///< see TY_CAMERA_CALIB_INFO

    TY_INT_PERSISTENT_IP            = 0x0010 | TY_FEATURE_INT,
    TY_INT_PERSISTENT_SUBMASK       = 0x0011 | TY_FEATURE_INT,
    TY_INT_PERSISTENT_GATEWAY       = 0x0012 | TY_FEATURE_INT,
    TY_BOOL_GVSP_RESEND             = 0x0013 | TY_FEATURE_BOOL,
    TY_INT_PACKET_DELAY             = 0x0014 | TY_FEATURE_INT,    ///< microseconds
    TY_INT_ACCEPTABLE_PERCENT       = 0x0015 | TY_FEATURE_INT,
    TY_STRUCT_CAM_STATISTICS        = 0x00ff | TY_FEATURE_STRUCT, ///< statistical information, see TY_CAMERA_STATISTICS

    TY_INT_WIDTH_MAX                = 0x0100 | TY_FEATURE_INT,
    TY_INT_HEIGHT_MAX               = 0x0101 | TY_FEATURE_INT,
    TY_INT_OFFSET_X                 = 0x0102 | TY_FEATURE_INT,
    TY_INT_OFFSET_Y                 = 0x0103 | TY_FEATURE_INT,
    TY_INT_WIDTH                    = 0x0104 | TY_FEATURE_INT,  ///< Image width
    TY_INT_HEIGHT                   = 0x0105 | TY_FEATURE_INT,  ///< Image height
    TY_ENUM_IMAGE_MODE              = 0x0109 | TY_FEATURE_ENUM, ///< Resolution-PixelFromat mode, see TY_IMAGE_MODE_LIST

    //@breif scale unit
    //depth image is uint16 pixel format with default millimeter unit ,for some device  can output Sub-millimeter accuracy data
    //the acutal depth (mm)= PxielValue * ScaleUnit 
    TY_FLOAT_SCALE_UNIT             = 0x010a | TY_FEATURE_FLOAT, 

    TY_ENUM_TRIGGER_ACTIVATION      = 0x0201 | TY_FEATURE_ENUM, ///< Trigger activation, see TY_TRIGGER_ACTIVATION_LIST
    TY_INT_FRAME_PER_TRIGGER        = 0x0202 | TY_FEATURE_INT,  ///< Number of frames captured per trigger
    TY_STRUCT_TRIGGER_PARAM         = 0x0523 | TY_FEATURE_STRUCT,  ///< param of trigger, see TY_TRIGGER_PARAM
    TY_BOOL_KEEP_ALIVE_ONOFF        = 0x0203 | TY_FEATURE_BOOL, ///< Keep Alive switch
    TY_INT_KEEP_ALIVE_TIMEOUT       = 0x0204 | TY_FEATURE_INT,  ///< Keep Alive timeout
    TY_BOOL_CMOS_SYNC               = 0x0205 | TY_FEATURE_BOOL, ///< Cmos sync switch
    TY_INT_TRIGGER_DELAY_US         = 0x0206 | TY_FEATURE_INT,  ///< Trigger delay time, in microseconds
    TY_BOOL_TRIGGER_OUT_IO          = 0x0207 | TY_FEATURE_BOOL, ///< Trigger out IO

    TY_BOOL_AUTO_EXPOSURE           = 0x0300 | TY_FEATURE_BOOL, ///< Auto exposure switch
    TY_INT_EXPOSURE_TIME            = 0x0301 | TY_FEATURE_INT,  ///< Exposure time in percentage
    TY_BOOL_AUTO_GAIN               = 0x0302 | TY_FEATURE_BOOL, ///< Auto gain switch
    TY_INT_GAIN                     = 0x0303 | TY_FEATURE_INT,  ///< Sensor Gain
    TY_BOOL_AUTO_AWB                = 0x0304 | TY_FEATURE_BOOL, ///< Auto white balance

    TY_INT_LASER_POWER              = 0x0500 | TY_FEATURE_INT,  ///< Laser power level
    TY_BOOL_LASER_AUTO_CTRL         = 0x0501 | TY_FEATURE_BOOL, ///< Laser auto ctrl

    TY_BOOL_UNDISTORTION            = 0x0510 | TY_FEATURE_BOOL, ///< Output undistorted image
    TY_BOOL_BRIGHTNESS_HISTOGRAM    = 0x0511 | TY_FEATURE_BOOL, ///< Output bright histogram
    TY_BOOL_DEPTH_POSTPROC          = 0x0512 | TY_FEATURE_BOOL, ///< Do depth image postproc

    TY_INT_R_GAIN                   = 0x0520 | TY_FEATURE_INT,  ///< Gain of R channel
    TY_INT_G_GAIN                   = 0x0521 | TY_FEATURE_INT,  ///< Gain of G channel
    TY_INT_B_GAIN                   = 0x0522 | TY_FEATURE_INT,  ///< Gain of B channel

    TY_INT_ANALOG_GAIN              = 0x0524 | TY_FEATURE_INT,  ///< Analog gain
}TY_FEATURE_ID_LIST;
typedef int32_t TY_FEATURE_ID;///< feature unique id @see TY_FEATURE_ID_LIST


///@brief set external trigger signal edge
///@see refer to sample SimpleView_TriggerMode for detail usage
typedef enum TY_TRIGGER_ACTIVATION_LIST
{
    TY_TRIGGER_ACTIVATION_FALLINGEDGE = 0,
    TY_TRIGGER_ACTIVATION_RISINGEDGE  = 1,
}TY_TRIGGER_ACTIVATION_LIST;
typedef int32_t TY_TRIGGER_ACTIVATION;


///interface type definition
typedef enum TY_INTERFACE_TYPE_LIST
{
    TY_INTERFACE_UNKNOWN        = 0,
    TY_INTERFACE_RAW            = 1,
    TY_INTERFACE_USB            = 2,
    TY_INTERFACE_ETHERNET       = 4,
    TY_INTERFACE_IEEE80211      = 8,
    TY_INTERFACE_ALL            = 0xffff,
}TY_INTERFACE_TYPE_LIST;
typedef int32_t TY_INTERFACE_TYPE;

///a feature is readable or writable
typedef enum TY_ACCESS_MODE_LIST
{
    TY_ACCESS_READABLE          = 0x1,
    TY_ACCESS_WRITABLE          = 0x2,
}TY_ACCESS_MODE_LIST;
typedef int8_t TY_ACCESS_MODE;


//------------------------------------------------------------------------------
///Pixel size type definitions 
typedef enum TY_PIXEL_BITS_LIST{
    TY_PIXEL_8BIT               = 0x1 << 28,
    TY_PIXEL_16BIT              = 0x2 << 28,
    TY_PIXEL_24BIT              = 0x3 << 28,
    TY_PIXEL_32BIT              = 0x4 << 28,
}TY_PIXEL_BITS_LIST;


///pixel format definitions
typedef enum TY_PIXEL_FORMAT_LIST{
    TY_PIXEL_FORMAT_UNDEFINED   = 0,
    TY_PIXEL_FORMAT_MONO        = (TY_PIXEL_8BIT  | (0x0 << 24)), ///< 0x10000000
    TY_PIXEL_FORMAT_BAYER8GB    = (TY_PIXEL_8BIT  | (0x1 << 24)), ///< 0x11000000
    TY_PIXEL_FORMAT_DEPTH16     = (TY_PIXEL_16BIT | (0x0 << 24)), ///< 0x20000000
    TY_PIXEL_FORMAT_YVYU        = (TY_PIXEL_16BIT | (0x1 << 24)), ///< 0x21000000, yvyu422
    TY_PIXEL_FORMAT_YUYV        = (TY_PIXEL_16BIT | (0x2 << 24)), ///< 0x22000000, yuyv422
    TY_PIXEL_FORMAT_RGB         = (TY_PIXEL_24BIT | (0x0 << 24)), ///< 0x30000000
    TY_PIXEL_FORMAT_BGR         = (TY_PIXEL_24BIT | (0x1 << 24)), ///< 0x31000000
    TY_PIXEL_FORMAT_JPEG        = (TY_PIXEL_24BIT | (0x2 << 24)), ///< 0x32000000
    TY_PIXEL_FORMAT_MJPG        = (TY_PIXEL_24BIT | (0x3 << 24)), ///< 0x33000000
}TY_PIXEL_FORMAT_LIST;
typedef int32_t TY_PIXEL_FORMAT;


///predefined resolution list
typedef enum TY_RESOLUTION_MODE_LIST
{
    TY_RESOLUTION_MODE_160x120      = (160<<12)+120,    ///< 0x000a0078 
    TY_RESOLUTION_MODE_240x320      = (240<<12)+320,    ///< 0x000f0140 
    TY_RESOLUTION_MODE_320x180      = (320<<12)+180,    ///< 0x001400b4
    TY_RESOLUTION_MODE_320x200      = (320<<12)+200,    ///< 0x001400c8
    TY_RESOLUTION_MODE_320x240      = (320<<12)+240,    ///< 0x001400f0
    TY_RESOLUTION_MODE_480x640      = (480<<12)+640,    ///< 0x001e0280
    TY_RESOLUTION_MODE_640x360      = (640<<12)+360,    ///< 0x00280168
    TY_RESOLUTION_MODE_640x400      = (640<<12)+400,    ///< 0x00280190
    TY_RESOLUTION_MODE_640x480      = (640<<12)+480,    ///< 0x002801e0
    TY_RESOLUTION_MODE_960x1280      = (960<<12)+1280,    ///< 0x003c0500
    TY_RESOLUTION_MODE_1280x720     = (1280<<12)+720,   ///< 0x005002d0
    TY_RESOLUTION_MODE_1280x800     = (1280<<12)+800,   ///< 0x00500320
    TY_RESOLUTION_MODE_1280x960     = (1280<<12)+960,   ///< 0x005003c0
    TY_RESOLUTION_MODE_2592x1944    = (2592<<12)+1944,  ///< 0x00a20798
}TY_RESOLUTION_MODE_LIST;
typedef int32_t TY_RESOLUTION_MODE;


#define TY_DECLARE_IMAGE_MODE0(pix, res) \
            TY_IMAGE_MODE_##pix##_##res = TY_PIXEL_FORMAT_##pix | TY_RESOLUTION_MODE_##res
#define TY_DECLARE_IMAGE_MODE1(pix) \
            TY_DECLARE_IMAGE_MODE0(pix, 160x120), \
            TY_DECLARE_IMAGE_MODE0(pix, 320x180), \
            TY_DECLARE_IMAGE_MODE0(pix, 320x200), \
            TY_DECLARE_IMAGE_MODE0(pix, 320x240), \
            TY_DECLARE_IMAGE_MODE0(pix, 480x640), \
            TY_DECLARE_IMAGE_MODE0(pix, 640x360), \
            TY_DECLARE_IMAGE_MODE0(pix, 640x400), \
            TY_DECLARE_IMAGE_MODE0(pix, 640x480), \
            TY_DECLARE_IMAGE_MODE0(pix, 960x1280), \
            TY_DECLARE_IMAGE_MODE0(pix, 1280x720), \
            TY_DECLARE_IMAGE_MODE0(pix, 1280x960), \
            TY_DECLARE_IMAGE_MODE0(pix, 1280x800), \
            TY_DECLARE_IMAGE_MODE0(pix, 2592x1944)


///@brief Predefined Image Mode List
/// image mode controls image resolution & format
/// named like TY_IMAGE_MODE_MONO_160x120
typedef enum TY_IMAGE_MODE_LIST
{
    TY_DECLARE_IMAGE_MODE1(MONO),
    TY_DECLARE_IMAGE_MODE1(DEPTH16),
    TY_DECLARE_IMAGE_MODE1(YVYU),
    TY_DECLARE_IMAGE_MODE1(YUYV),
    TY_DECLARE_IMAGE_MODE1(RGB),
    TY_DECLARE_IMAGE_MODE1(JPEG),
    TY_DECLARE_IMAGE_MODE1(BAYER8GB)
}TY_IMAGE_MODE_LIST;
typedef int32_t TY_IMAGE_MODE;
#undef TY_DECLARE_IMAGE_MODE0
#undef TY_DECLARE_IMAGE_MODE1

///@see refer to sample SimpleView_TriggerMode for detail usage
typedef enum TY_TRIGGER_MODE_LIST
{
    TY_TRIGGER_MODE_OFF         = 0, ///<not trigger mode, continuous mode
    TY_TRIGGER_MODE_SLAVE       = 1, ///<slave mode, receive soft/hardware triggers
    TY_TRIGGER_MODE_M_SIG       = 2, ///<master mode 1, sending one trigger signal once received a soft/hardware trigger
    TY_TRIGGER_MODE_M_PER       = 3, ///<master mode 2, periodic sending one trigger signals, 'fps' param should be set
}TY_TRIGGER_MODE_LIST;
typedef int16_t TY_TRIGGER_MODE;

//------------------------------------------------------------------------------
//  Struct
//------------------------------------------------------------------------------
typedef struct TY_VERSION_INFO
{
    int32_t major;
    int32_t minor;
    int32_t patch;
    int32_t reserved;
}TY_VERSION_INFO;

typedef struct TY_DEVICE_NET_INFO
{
    char    mac[32];
    char    ip[32];
    char    netmask[32];
    char    gateway[32];
    char    broadcast[32];
    char    reserved[96];
}TY_DEVICE_NET_INFO;

typedef struct TY_DEVICE_USB_INFO
{
    int     bus;
    int     addr;
    char    reserved[248];
}TY_DEVICE_USB_INFO;

///@see TYGetInterfaceList
typedef struct TY_INTERFACE_INFO
{
    char                name[32];
    char                id[32];
    TY_INTERFACE_TYPE   type;
    char                reserved[4];
    TY_DEVICE_NET_INFO  netInfo; // only meaningful when TYIsNetworkInterface(type)
}TY_INTERFACE_INFO;

///@see TYGetDeviceList
typedef struct TY_DEVICE_BASE_INFO
{
    TY_INTERFACE_INFO   iface;
    char                id[32];///<device serial number
    char                vendorName[32];     
    char                modelName[32];///<device model name
    TY_VERSION_INFO     hardwareVersion; ///<deprecated
    TY_VERSION_INFO     firmwareVersion;///<deprecated
    union {
      TY_DEVICE_NET_INFO netInfo;
      TY_DEVICE_USB_INFO usbInfo;
    };
    char                reserved[256];
}TY_DEVICE_BASE_INFO;

typedef struct TY_FEATURE_INFO
{
    bool            isValid;            ///< true if feature exists, false otherwise
    TY_ACCESS_MODE  accessMode;         ///< feature access privilege
    bool            writableAtRun;      ///< feature can be written while capturing
    char            reserved0[1];
    TY_COMPONENT_ID componentID;        ///< owner of this feature
    TY_FEATURE_ID   featureID;          ///< feature unique id
    char            name[32];           ///< describe string
    int32_t         bindComponentID;    ///< component ID current feature bind to
    int32_t         bindFeatureID;      ///< feature ID current feature bind to
    char            reserved[252];
}TY_FEATURE_INFO;

typedef struct TY_INT_RANGE
{
    int32_t min;
    int32_t max;
    int32_t inc;   ///<increaing step
    int32_t reserved[1];
}TY_INT_RANGE;

typedef struct TY_FLOAT_RANGE
{
    float   min;
    float   max;
    float   inc;   ///<increaing step
    float   reserved[1];
}TY_FLOAT_RANGE;

///enum feature entry information
///@see TYGetEnumEntryInfo
typedef struct TY_ENUM_ENTRY
{
    char    description[64];
    int32_t value;
    int32_t reserved[3];
}TY_ENUM_ENTRY;

typedef struct TY_VECT_3F
{
    float   x;
    float   y;
    float   z;
}TY_VECT_3F;

///  a 3x3 matrix  
/// |.|.|.|
/// | --|---|---|
/// | fx|  0| cx|
/// |  0| fy| cy|
/// |  0|  0|  1|
typedef struct TY_CAMERA_INTRINSIC
{
    float data[3*3];
}TY_CAMERA_INTRINSIC;

/// a 4x4 matrix
///  |.|.|.|.|
///  |---|----|----|---|
///  |r11| r12| r13| t1|
///  |r21| r22| r23| t2|
///  |r31| r32| r33| t3|
///  | 0 |   0|   0|  1|
typedef struct TY_CAMERA_EXTRINSIC
{
    float data[4*4];
}TY_CAMERA_EXTRINSIC;

///camera distortion parameters
typedef struct TY_CAMERA_DISTORTION
{
    float data[12];///<Definition is compatible with opencv3.0+ :k1,k2,p1,p2,k3,k4,k5,k6,s1,s2,s3,s4
}TY_CAMERA_DISTORTION;


///camera 's cailbration data
///@see TYGetStruct
typedef struct TY_CAMERA_CALIB_INFO
{
  int32_t intrinsicWidth;
  int32_t intrinsicHeight;
  TY_CAMERA_INTRINSIC   intrinsic;  // TY_STRUCT_CAM_INTRINSIC
  TY_CAMERA_EXTRINSIC   extrinsic;  // TY_STRUCT_EXTRINSIC_TO_LEFT_IR
  TY_CAMERA_DISTORTION  distortion; // TY_STRUCT_CAM_DISTORTION
}TY_CAMERA_CALIB_INFO;


//@see sample SimpleView_TriggerMode  
typedef struct TY_TRIGGER_PARAM
{
    TY_TRIGGER_MODE   mode;
    int8_t    fps;
    int8_t    rsvd;
}TY_TRIGGER_PARAM;


typedef struct TY_CAMERA_STATISTICS
{
    int32_t   packetReceived;
    int32_t   packetLost;
    int32_t   imageOutputed;
    int32_t   imageDropped;
    uint8_t   rsvd[1024];
}TY_CAMERA_STATISTICS;


//------------------------------------------------------------------------------
//  Buffer & Callback
//------------------------------------------------------------------------------
typedef struct TY_IMAGE_DATA
{
    uint64_t        timestamp;      ///< Timestamp in microseconds
    int32_t         imageIndex;     ///< image index used in trigger mode
    int32_t         status;         ///< Status of this buffer
    int32_t         componentID;    ///< Where current data come from
    int32_t         size;           ///< Buffer size
    void*           buffer;         ///< Pointer to data buffer
    int32_t         width;          ///< Image width in pixels
    int32_t         height;         ///< Image height in pixels
    int32_t         pixelFormat;    ///< Pixel format, see TY_PIXEL_FORMAT_LIST
    int32_t         reserved[9];    ///< Reserved
}TY_IMAGE_DATA;


typedef struct TY_FRAME_DATA
{
    void*           userBuffer;     ///< Pointer to user enqueued buffer, user should enqueue this buffer in the end of callback
    int32_t         bufferSize;     ///< Size of userBuffer
    int32_t         validCount;     ///< Number of valid data
    int32_t         reserved[6];    ///< Reserved
    TY_IMAGE_DATA   image[10];      ///< Buffer data, max to 10 images per frame, each buffer data could be an image or something else.
}TY_FRAME_DATA;


typedef struct TY_EVENT_INFO
{
    TY_EVENT        eventId;
    char            message[124];
}TY_EVENT_INFO;


typedef void (*TY_EVENT_CALLBACK) (TY_EVENT_INFO*, void* userdata);


//------------------------------------------------------------------------------
// inlines
//------------------------------------------------------------------------------
static inline bool TYIsNetworkInterface(int32_t interfaceType)
{
  return (interfaceType == TY_INTERFACE_ETHERNET) || 
         (interfaceType == TY_INTERFACE_IEEE80211);
}

static inline void TYIntToIPv4(uint32_t addr, uint8_t out[4])
{
  out[0] = (addr>>24) & 0xff;
  out[1] = (addr>>16) & 0xff;
  out[2] = (addr>>8) & 0xff;
  out[3] = (addr>>0) & 0xff;
}

static inline uint32_t TYIPv4ToInt(uint8_t ip[4])
{
  return (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
}

///init a TY_IMAGE_DATA struct
static inline TY_IMAGE_DATA TYInitImageData(size_t size, void* buffer
    , size_t width, size_t height)
{
  TY_IMAGE_DATA out;
  out.timestamp = 0;
  out.imageIndex = 0;
  out.status = 0;
  out.componentID = 0;
  out.size = size;
  out.buffer = buffer;
  out.width = width;
  out.height = height;
  out.pixelFormat = 0;
  return out;
}

///get feature format type from feature id
static inline TY_FEATURE_TYPE TYFeatureType(TY_FEATURE_ID id)
{
    return id & 0xf000;
}

///get pixel size in byte 
static inline int32_t TYPixelSize(TY_IMAGE_MODE imageMode)
{
    return ((imageMode >> 28) & 0xf);
}

///make a image mode from pixel format & resolution mode
static inline TY_IMAGE_MODE TYImageMode(TY_PIXEL_FORMAT pix, TY_RESOLUTION_MODE res)
{
    return pix | res;
}

///get a resoltuion mode from width & height
static inline TY_RESOLUTION_MODE TYResolutionMode2(int width, int height){
    return (TY_RESOLUTION_MODE)((width << 12) + height);
}

///create a image mode from pixel format , width & height  
static inline TY_IMAGE_MODE TYImageMode2(TY_PIXEL_FORMAT pix, int width,int height)
{
    return pix | TYResolutionMode2(width, height);
}

///get pixel format from image mode
static inline TY_PIXEL_FORMAT TYPixelFormat(TY_IMAGE_MODE imageMode)
{
    return imageMode & 0xff000000;
}

///get a resoltuion mode from image mode 
static inline TY_RESOLUTION_MODE TYResolutionMode(TY_IMAGE_MODE imageMode)
{
    return imageMode & 0x00ffffff;
}

///get image width from image mode
static inline int32_t TYImageWidth(TY_IMAGE_MODE imageMode)
{
    return TYResolutionMode(imageMode) >> 12;
}

///get image height from image mode
static inline int32_t TYImageHeight(TY_IMAGE_MODE imageMode)
{
    return TYResolutionMode(imageMode) & 0x0fff;
}

//------------------------------------------------------------------------------
//  C API
//------------------------------------------------------------------------------
#define TY_CAPI TY_EXTC TY_EXPORT TY_STATUS TY_STDC


/// @brief Get error information.
/// @param  [in]  errorID       Error id.
/// @return Error string.
TY_EXTC TY_EXPORT const char* TY_STDC TYErrorString (TY_STATUS errorID);


/// @brief Init this library.
///
///   We make this function to be static inline, because we do a version check here.
///   Some user may use the mismatched header file and dynamic library, and
///   that's quite difficult to locate the error.
///
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_ERROR     Has been inited.
static inline TY_STATUS TYInitLib (void);

/// @brief Deinit this library.
/// @retval TY_STATUS_OK        Succeed.
TY_CAPI TYDeinitLib               (void);

/// @brief Get current library version.
/// @param  [out] version       Version infomation to be filled.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NULL_POINTER      buffer is NULL.
TY_CAPI TYLibVersion              (TY_VERSION_INFO* version);


/// @brief Update current interfaces.
/// call before TYGetInterfaceList
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
TY_CAPI TYUpdateInterfaceList     ();

/// @brief Get number of current interfaces.
/// @param  [out] pNumIfaces    Number of interfaces.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_NULL_POINTER      deviceNumber is NULL.
TY_CAPI TYGetInterfaceNumber      (uint32_t* pNumIfaces);

/// @brief Get interface info list.
/// @param  [out] pIfaceInfos   Array of interface infos to be filled.
/// @param  [in]  bufferCount   Array size of interface infos.
/// @param  [out] filledCount   Number of filled TY_INTERFACE_INFO.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_NULL_POINTER      pIfaceInfos or filledCount is NULL.
TY_CAPI TYGetInterfaceList        (TY_INTERFACE_INFO* pIfaceInfos, uint32_t bufferCount, uint32_t* filledCount);

/// @brief Check if has interface.
/// @param  [in]  ifaceID       Interface ID string, can be get from TY_INTERFACE_INFO.
/// @param  [out] value         True if the interface exists.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_NULL_POINTER      ifaceID or outHandle is NULL.
/// @see TYGetInterfaceList
TY_CAPI TYHasInterface            (const char* ifaceID, bool* value);

/// @brief Open specified interface.
/// @param  [in]  ifaceID       Interface ID string, can be get from TY_INTERFACE_INFO.
/// @param  [out] outHandle     Handle of opened interface.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_NULL_POINTER      ifaceID or outHandle is NULL.
/// @retval TY_STATUS_INVALID_INTERFACE Interface not found.
/// @see TYGetInterfaceList
TY_CAPI TYOpenInterface           (const char* ifaceID, TY_INTERFACE_HANDLE* outHandle);

/// @brief Close interface.
/// @param  [in]  ifaceHandle   Interface to be closed.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Interface not found.
TY_CAPI TYCloseInterface          (TY_INTERFACE_HANDLE ifaceHandle);


/// @brief Update current connected devices.
/// @param  [in]  ifaceHandle   Interface handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
TY_CAPI TYUpdateDeviceList        (TY_INTERFACE_HANDLE ifaceHandle);

/// @brief Get number of current connected devices.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [out] deviceNumber  Number of connected devices.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_NULL_POINTER      deviceNumber is NULL.
TY_CAPI TYGetDeviceNumber         (TY_INTERFACE_HANDLE ifaceHandle, uint32_t* deviceNumber);

/// @brief Get device info list.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [out] deviceInfos   Device info array to be filled.
/// @param  [in]  bufferCount   Array size of deviceInfos.
/// @param  [out] filledDeviceCount     Number of filled TY_DEVICE_BASE_INFO.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_NULL_POINTER      deviceInfos or filledDeviceCount is NULL.
TY_CAPI TYGetDeviceList           (TY_INTERFACE_HANDLE ifaceHandle, TY_DEVICE_BASE_INFO* deviceInfos, uint32_t bufferCount, uint32_t* filledDeviceCount);

/// @brief Check whether the interface has the specified device.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [in]  deviceID      Device ID string, can be get from TY_DEVICE_BASE_INFO.
/// @param  [out] value         True if the device exists.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_NULL_POINTER      deviceID or value is NULL.
TY_CAPI TYHasDevice               (TY_INTERFACE_HANDLE ifaceHandle, const char* deviceID, bool* value);

/// @brief Open device by device ID.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [in]  deviceID      Device ID string, can be get from TY_DEVICE_BASE_INFO.
/// @param  [out] deviceHandle  Handle of opened device.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_NULL_POINTER      deviceID or deviceHandle is NULL.
/// @retval TY_STATUS_INVALID_PARAMETER Device not found.
/// @retval TY_STATUS_BUSY              Device has been opened.
/// @retval TY_STATUS_DEVICE_ERROR      Open device failed.
TY_CAPI TYOpenDevice              (TY_INTERFACE_HANDLE ifaceHandle, const char* deviceID, TY_DEV_HANDLE* outDeviceHandle);

/// @brief Open device by device IP, useful when a device is not listed.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [in]  IP            Device IP.
/// @param  [out] deviceHandle  Handle of opened device.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_NULL_POINTER      IP or deviceHandle is NULL.
/// @retval TY_STATUS_INVALID_PARAMETER Device not found.
/// @retval TY_STATUS_BUSY              Device has been opened, may occupied somewhere else.
/// @retval TY_STATUS_DEVICE_ERROR      Open device failed.
TY_CAPI TYOpenDeviceWithIP        (TY_INTERFACE_HANDLE ifaceHandle, const char* IP, TY_DEV_HANDLE* deviceHandle);

/// @brief Get interface handle by device handle.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] pIface        Interface handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      pIface is NULL.
TY_CAPI TYGetDeviceInterface      (TY_DEV_HANDLE hDevice, TY_INTERFACE_HANDLE* pIface);

/// @brief Force a ethernet device to use new IP address, useful when device use persistent IP and cannot be found.
/// @param  [in]  ifaceHandle   Interface handle.
/// @param  [in]  MAC           Device MAC, should be "xx:xx:xx:xx:xx:xx".
/// @param  [in]  newIP         New IP.
/// @param  [in]  newNetMask    New subnet mask.
/// @param  [in]  newGateway    New gateway.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_NOT_INITED        TYInitLib not called.
/// @retval TY_STATUS_INVALID_INTERFACE Invalid interface handle.
/// @retval TY_STATUS_WRONG_TYPE        Wrong interface type, should be network.
/// @retval TY_STATUS_NULL_POINTER      MAC or newIP/newNetMask/newGateway is NULL.
/// @retval TY_STATUS_INVALID_PARAMETER MAC is not valid.
/// @retval TY_STATUS_TIMEOUT           No device found.
/// @retval TY_STATUS_DEVICE_ERROR      Set new IP failed.
TY_CAPI TYForceDeviceIP           (TY_INTERFACE_HANDLE ifaceHandle, const char* MAC, const char* newIP, const char* newNetMask, const char* newGateway);

/// @brief Close device by device handle.
/// @param  [in]  hDevice       Device handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_IDLE              Device has been closed.
TY_CAPI TYCloseDevice             (TY_DEV_HANDLE hDevice);


/// @brief Get base info of the open device.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] info          Base info out.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      componentIDs is NULL.
TY_CAPI TYGetDeviceInfo           (TY_DEV_HANDLE hDevice, TY_DEVICE_BASE_INFO* info);

/// @brief Get all components IDs.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] componentIDs  All component IDs this device has. (bit flag).
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      componentIDs is NULL.
/// @see TY_DEVICE_COMPONENT_LIST
TY_CAPI TYGetComponentIDs         (TY_DEV_HANDLE hDevice, int32_t* componentIDs);

/// @brief Get all enabled components IDs.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] componentIDs  Enabled component IDs.(bit flag)
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      componentIDs is NULL.
/// @see TY_DEVICE_COMPONENT_LIST
TY_CAPI TYGetEnabledComponents    (TY_DEV_HANDLE hDevice, int32_t* componentIDs);

/// @brief Enable components.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentIDs  Components to be enabled.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Some components specified by componentIDs are invalid.
/// @retval TY_STATUS_BUSY      Device is capturing.
TY_CAPI TYEnableComponents        (TY_DEV_HANDLE hDevice, int32_t componentIDs);

/// @brief Disable components.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentIDs  Components to be disabled.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Some components specified by componentIDs are invalid.
/// @retval TY_STATUS_BUSY      Device is capturing.
/// @see TY_DEVICE_COMPONENT_LIST
TY_CAPI TYDisableComponents       (TY_DEV_HANDLE hDevice, int32_t componentIDs);



/// @brief Get total buffer size of one frame in current configuration.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] bufferSize    Buffer size per frame.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      bufferSize is NULL.
TY_CAPI TYGetFrameBufferSize      (TY_DEV_HANDLE hDevice, uint32_t* bufferSize);

/// @brief Enqueue a user allocated buffer.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  buffer        Buffer to be enqueued.
/// @param  [in]  bufferSize    Size of the input buffer.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      buffer is NULL.
/// @retval TY_STATUS_WRONG_SIZE        The input buffer is not large enough.
TY_CAPI TYEnqueueBuffer           (TY_DEV_HANDLE hDevice, void* buffer, uint32_t bufferSize);

/// @brief Clear the internal buffer queue, so that user can release all the buffer.
/// @param  [in]  hDevice       Device handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_BUSY      Device is capturing.
TY_CAPI TYClearBufferQueue        (TY_DEV_HANDLE hDevice);



/// @brief Start capture.
/// @param  [in]  hDevice       Device handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT No components enabled.
/// @retval TY_STATUS_BUSY              Device has been started.
/// @retval TY_STATUS_DEVICE_ERROR      Start capture failed.
TY_CAPI TYStartCapture            (TY_DEV_HANDLE hDevice);

/// @brief Stop capture.
/// @param  [in]  hDevice       Device handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_IDLE              Device is not capturing.
/// @retval TY_STATUS_DEVICE_ERROR      Stop capture failed.
TY_CAPI TYStopCapture             (TY_DEV_HANDLE hDevice);

/// @brief Send a software trigger to capture a frame when device works in trigger mode.
/// @param  [in]  hDevice       Device handle.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_FEATURE   Not support soft trigger.
/// @retval TY_STATUS_IDLE              Device has not started capture.
/// @retval TY_STATUS_WRONG_MODE        Not in trigger mode.
TY_CAPI TYSendSoftTrigger         (TY_DEV_HANDLE hDevice);

/// @brief Register device status callback. Register NULL to clean callback.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  callback      Callback function.
/// @param  [in]  userdata      User private data.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_BUSY      Device is capturing.
TY_CAPI TYRegisterEventCallback   (TY_DEV_HANDLE hDevice, TY_EVENT_CALLBACK callback, void* userdata);

/// @brief Fetch one frame.
/// @param  [in]  hDevice       Device handle.
/// @param  [out] frame         Frame data to be filled.
/// @param  [in]  timeout       Timeout in milliseconds. <0 for infinite.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_NULL_POINTER      frame is NULL.
/// @retval TY_STATUS_IDLE              Device capturing is not started.
/// @retval TY_STATUS_WRONG_MODE        Callback has been registered, this function is disabled.
/// @retval TY_STATUS_TIMEOUT   Timeout.
TY_CAPI TYFetchFrame              (TY_DEV_HANDLE hDevice, TY_FRAME_DATA* frame, int32_t timeout);


/// @brief Check  whether a component has a specific feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] value         Whether has feature.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_NULL_POINTER      value is NULL.
TY_CAPI TYHasFeature              (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool* value);

/// @brief Get feature info.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] featureInfo   Feature info.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_NULL_POINTER      featureInfo is NULL.
TY_CAPI TYGetFeatureInfo          (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_FEATURE_INFO* featureInfo);



/// @brief Get value range of integer feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] intRange      Integer range to be filled.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_INT.
/// @retval TY_STATUS_NULL_POINTER      intRange is NULL.
TY_CAPI TYGetIntRange             (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_INT_RANGE* intRange);

/// @brief Get value of integer feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] value         Integer value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_INT.
/// @retval TY_STATUS_NULL_POINTER      value is NULL.
TY_CAPI TYGetInt                  (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t* value);

/// @brief Set value of integer feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  value         Integer value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_INT.
/// @retval TY_STATUS_OUT_OF_RANGE      value is out of range.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetInt                  (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t value);

/// @brief Get value range of float feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] floatRange    Float range to be filled.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_FLOAT.
/// @retval TY_STATUS_NULL_POINTER      floatRange is NULL.
TY_CAPI TYGetFloatRange           (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_FLOAT_RANGE* floatRange);

/// @brief Get value of float feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] value         Float value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_FLOAT.
/// @retval TY_STATUS_NULL_POINTER      value is NULL.
TY_CAPI TYGetFloat                (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, float* value);

/// @brief Set value of float feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  value         Float value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_FLOAT.
/// @retval TY_STATUS_OUT_OF_RANGE      value is out of range.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetFloat                (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, float value);

/// @brief Get number of enum entries.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] entryCount    Entry count.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_ENUM.
/// @retval TY_STATUS_NULL_POINTER      entryCount is NULL.
TY_CAPI TYGetEnumEntryCount       (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, uint32_t* entryCount);

/// @brief Get list of enum entries.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] entries       Output entries.
/// @param  [in]  entryCount    Array size of input parameter "entries".
/// @param  [out] filledEntryCount      Number of filled entries.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_ENUM.
/// @retval TY_STATUS_NULL_POINTER      entries or filledEntryCount is NULL.
TY_CAPI TYGetEnumEntryInfo        (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_ENUM_ENTRY* entries, uint32_t entryCount, uint32_t* filledEntryCount);

/// @brief Get current value of enum feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] value         Enum value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_ENUM.
/// @retval TY_STATUS_NULL_POINTER      value is NULL.
TY_CAPI TYGetEnum                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t* value);

/// @brief Set value of enum feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  value         Enum value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_ENUM.
/// @retval TY_STATUS_INVALID_PARAMETER value is invalid.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetEnum                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t value);

/// @brief Get value of bool feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] value         Bool value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_BOOL.
/// @retval TY_STATUS_NULL_POINTER      value is NULL.
TY_CAPI TYGetBool                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool* value);

/// @brief Set value of bool feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  value         Bool value.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_BOOL.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetBool                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool value);

/// @brief Get internal buffer size of string feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] size          String length including '\0'.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_STRING.
/// @retval TY_STATUS_NULL_POINTER      size is NULL.
/// @see TYGetString
TY_CAPI TYGetStringLength         (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, uint32_t* size);

/// @brief Get value of string feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] buffer        String buffer.
/// @param  [in]  bufferSize    Size of buffer.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_STRING.
/// @retval TY_STATUS_NULL_POINTER      buffer is NULL.
/// @see TYGetStringLength
TY_CAPI TYGetString               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, char* buffer, uint32_t bufferSize);

/// @brief Set value of string feature.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  buffer        String buffer.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_STRING.
/// @retval TY_STATUS_NULL_POINTER      buffer is NULL.
/// @retval TY_STATUS_OUT_OF_RANGE      Input string is too long.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetString               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, const char* buffer);

/// @brief Get value of struct.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [out] pStruct       Pointer of struct.
/// @param  [in]  structSize    Size of input buffer pStruct..
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_STRUCT.
/// @retval TY_STATUS_NULL_POINTER      pStruct is NULL.
/// @retval TY_STATUS_WRONG_SIZE        structSize incorrect.
TY_CAPI TYGetStruct               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, void* pStruct, uint32_t structSize);

/// @brief Set value of struct.
/// @param  [in]  hDevice       Device handle.
/// @param  [in]  componentID   Component ID.
/// @param  [in]  featureID     Feature ID.
/// @param  [in]  pStruct       Pointer of struct.
/// @param  [in]  structSize    Size of struct.
/// @retval TY_STATUS_OK        Succeed.
/// @retval TY_STATUS_INVALID_HANDLE    Invalid device handle.
/// @retval TY_STATUS_INVALID_COMPONENT Invalid component ID.
/// @retval TY_STATUS_INVALID_FEATURE   Invalid feature ID.
/// @retval TY_STATUS_NOT_PERMITTED     The feature is not writable.
/// @retval TY_STATUS_WRONG_TYPE        The feature's type is not TY_FEATURE_STRUCT.
/// @retval TY_STATUS_NULL_POINTER      pStruct is NULL.
/// @retval TY_STATUS_WRONG_SIZE        structSize incorrect.
/// @retval TY_STATUS_BUSY              Device is capturing, the feature is locked.
TY_CAPI TYSetStruct               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, void* pStruct, uint32_t structSize);


//------------------------------------------------------------------------------
//  Version check
//------------------------------------------------------------------------------
TY_CAPI _TYInitLib(void);
static inline TY_STATUS TYInitLib(void)
{
    TY_VERSION_INFO soVersion;
    TYLibVersion(&soVersion);
    if(!(soVersion.major == TY_LIB_VERSION_MAJOR && soVersion.minor >= TY_LIB_VERSION_MINOR)){
        abort();   // generate fault directly
    }
    return _TYInitLib();
}

//------------------------------------------------------------------------------
//  Summary
//------------------------------------------------------------------------------
TY_EXTC TY_EXPORT const char* TY_STDC TYErrorString (TY_STATUS errorID);

inline TY_STATUS    TYInitLib                 (void);
TY_CAPI             TYDeinitLib               (void);
TY_CAPI             TYLibVersion              (TY_VERSION_INFO* version);

TY_CAPI             TYUpdateInterfaceList     ();
TY_CAPI             TYGetInterfaceNumber      (uint32_t* pNumIfaces);
TY_CAPI             TYGetInterfaceList        (TY_INTERFACE_INFO* pIfaceInfos, uint32_t bufferCount, uint32_t* filledCount);
TY_CAPI             TYHasInterface            (const char* ifaceID, bool* value);
TY_CAPI             TYOpenInterface           (const char* ifaceID, TY_INTERFACE_HANDLE* outHandle);
TY_CAPI             TYCloseInterface          (TY_INTERFACE_HANDLE ifaceHandle);

TY_CAPI             TYUpdateDeviceList        (TY_INTERFACE_HANDLE ifaceHandle);
TY_CAPI             TYGetDeviceNumber         (TY_INTERFACE_HANDLE ifaceHandle, uint32_t* deviceNumber);
TY_CAPI             TYGetDeviceList           (TY_INTERFACE_HANDLE ifaceHandle, TY_DEVICE_BASE_INFO* deviceInfos, uint32_t bufferCount, uint32_t* filledDeviceCount);
TY_CAPI             TYHasDevice               (TY_INTERFACE_HANDLE ifaceHandle, const char* deviceID, bool* value);
TY_CAPI             TYOpenDevice              (TY_INTERFACE_HANDLE ifaceHandle, const char* deviceID, TY_DEV_HANDLE* outDeviceHandle);
TY_CAPI             TYOpenDeviceWithIP        (TY_INTERFACE_HANDLE ifaceHandle, const char* IP, TY_DEV_HANDLE* deviceHandle);
TY_CAPI             TYGetDeviceInterface      (TY_DEV_HANDLE hDevice, TY_INTERFACE_HANDLE* pIface);
TY_CAPI             TYForceDeviceIP           (TY_INTERFACE_HANDLE ifaceHandle, const char* MAC, const char* newIP, const char* newNetMask, const char* newGateway);
TY_CAPI             TYCloseDevice             (TY_DEV_HANDLE hDevice);

TY_CAPI             TYGetDeviceInfo           (TY_DEV_HANDLE hDevice, TY_DEVICE_BASE_INFO* info);
TY_CAPI             TYGetComponentIDs         (TY_DEV_HANDLE hDevice, int32_t* componentIDs);
TY_CAPI             TYGetEnabledComponents    (TY_DEV_HANDLE hDevice, int32_t* componentIDs);
TY_CAPI             TYEnableComponents        (TY_DEV_HANDLE hDevice, int32_t componentIDs);
TY_CAPI             TYDisableComponents       (TY_DEV_HANDLE hDevice, int32_t componentIDs);

TY_CAPI             TYGetFrameBufferSize      (TY_DEV_HANDLE hDevice, uint32_t* outSize);
TY_CAPI             TYEnqueueBuffer           (TY_DEV_HANDLE hDevice, void* buffer, uint32_t bufferSize);
TY_CAPI             TYClearBufferQueue        (TY_DEV_HANDLE hDevice);

TY_CAPI             TYStartCapture            (TY_DEV_HANDLE hDevice);
TY_CAPI             TYStopCapture             (TY_DEV_HANDLE hDevice);
TY_CAPI             TYSendSoftTrigger         (TY_DEV_HANDLE hDevice);
TY_CAPI             TYRegisterEventCallback   (TY_DEV_HANDLE hDevice, TY_EVENT_CALLBACK callback, void* userdata);
TY_CAPI             TYFetchFrame              (TY_DEV_HANDLE hDevice, TY_FRAME_DATA* frame, int32_t timeout);

TY_CAPI             TYHasFeature              (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool* value);
TY_CAPI             TYGetFeatureInfo          (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_FEATURE_INFO* featureInfo);
TY_CAPI             TYGetIntRange             (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_INT_RANGE* intRange);
TY_CAPI             TYGetInt                  (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t* value);
TY_CAPI             TYSetInt                  (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t value);
TY_CAPI             TYGetFloatRange           (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_FLOAT_RANGE* floatRange);
TY_CAPI             TYGetFloat                (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, float* value);
TY_CAPI             TYSetFloat                (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, float value);
TY_CAPI             TYGetEnumEntryCount       (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, uint32_t* entryCount);
TY_CAPI             TYGetEnumEntryInfo        (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, TY_ENUM_ENTRY* entries, uint32_t entryCount, uint32_t* filledEntryCount);
TY_CAPI             TYGetEnum                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t* value);
TY_CAPI             TYSetEnum                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, int32_t value);
TY_CAPI             TYGetBool                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool* value);
TY_CAPI             TYSetBool                 (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, bool value);
TY_CAPI             TYGetStringLength         (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, uint32_t* length);
TY_CAPI             TYGetString               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, char* buffer, uint32_t bufferSize);
TY_CAPI             TYSetString               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, const char* buffer);
TY_CAPI             TYGetStruct               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, void* pStruct, uint32_t structSize);
TY_CAPI             TYSetStruct               (TY_DEV_HANDLE hDevice, TY_COMPONENT_ID componentID, TY_FEATURE_ID featureID, void* pStruct, uint32_t structSize);


#endif // TY_API_H_

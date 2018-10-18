#ifndef PERCIPIO_GEN_TL_XML_REG_H_
#define PERCIPIO_GEN_TL_XML_REG_H_

// GigE extend
#define REG_GEV_EXT_Stream_Component_ID(n)  (0x00100000 + (n)*4) // RO, component ID of stream n


// components
#define REG_Component_Device_Base           (0x01000000)
#define REG_Component_Depth_Base            (0x02000000)
#define REG_Component_LeftIR_Base           (0x03000000)
#define REG_Component_RightIR_Base          (0x04000000)
#define REG_Component_LeftColor_Base        (0x05000000)
#define REG_Component_RightColor_Base       (0x06000000)
#define REG_Component_Laser_Base            (0x07000000)
#define REG_Component_BrightHisto_Base      (0x08000000)

// device features
#define REG_Device_Special_Base             (REG_Component_Device_Base + 0x00400000)
#define REG_Device_Memory_Endian            (REG_Device_Special_Base + 0x0000) // RO, 0 for little endian, 1 for Big endian
#define REG_Device_Acuisition               (REG_Device_Special_Base + 0x0004) // RW, write 1 to start, 0 to stop
#define REG_Device_Trigger                  (REG_Device_Special_Base + 0x000c) // WO, trigger cmd
#define REG_Device_Descriptor_Size          (REG_Device_Special_Base + 0x0010) // RO,
#define REG_Device_License_Random_Check     (REG_Device_Special_Base + 0x0014) // WO, license random check cmd
#define REG_Device_Debug_Mode               (REG_Device_Special_Base + 0x0018) // RW, being debug mode
#define REG_Device_Override_Descriptor      (REG_Device_Special_Base + 0x001c) // WO, do override config
#define REG_Device_Packet_Delay             (REG_Device_Special_Base + 0x0020) // RW, streaming packet delay
#define REG_Device_Descriptor               (REG_Device_Special_Base + 0x00100000) // RW,
#define REG_Device_License                  (REG_Device_Special_Base + 0x00200000) // WO, license full check cmd
#define REG_Device_GenICam_Descriptor       (REG_Device_Special_Base + 0x00800000) // RO, 

// common features
#define REG_Common_Feature_Base             (0x00000000)
#define REG_TY_INT_WIDTH_MAX                (REG_Common_Feature_Base + 0x0000)
#define REG_TY_INT_HEIGHT_MAX               (REG_Common_Feature_Base + 0x0004)
#define REG_TY_INT_OFFSET_X                 (REG_Common_Feature_Base + 0x0008)
#define REG_TY_INT_OFFSET_Y                 (REG_Common_Feature_Base + 0x000c)
#define REG_TY_INT_WIDTH                    (REG_Common_Feature_Base + 0x0010)
#define REG_TY_INT_HEIGHT                   (REG_Common_Feature_Base + 0x0014)
#define REG_TY_ENUM_IMAGE_MODE              (REG_Common_Feature_Base + 0x0018)
#define REG_TY_INT_INTRINSIC_WIDTH          (REG_Common_Feature_Base + 0x001c)
#define REG_TY_INT_INTRINSIC_HEIGHT         (REG_Common_Feature_Base + 0x0020)

#define REG_TY_STRUCT_CAM_INTRINSIC         (REG_Common_Feature_Base + 0x0100)
#define REG_TY_STRUCT_EXTRINSIC_TO_LEFT_IR  (REG_Common_Feature_Base + 0x0124)
#define REG_TY_STRUCT_CAM_DISTORTION        (REG_Common_Feature_Base + 0x0164)
#define REG_TY_ENUM_TRIGGER_ACTIVATION      (REG_Common_Feature_Base + 0x0200)
#define REG_TY_INT_FRAME_PER_TRIGGER        (REG_Common_Feature_Base + 0x0204)
#define REG_TY_STRUCT_TRIGGER_PARAM         (REG_Common_Feature_Base + 0x0208) // RW, TY_TRIGGER_PARAM
#define REG_TY_BOOL_CMOS_SYNC               (REG_Common_Feature_Base + 0x020C)
#define REG_TY_INT_TRIGGER_DELAY            (REG_Common_Feature_Base + 0x0210)
#define REG_TY_BOOL_AUTO_EXPOSURE           (REG_Common_Feature_Base + 0x0300)
#define REG_TY_INT_EXPOSURE_TIME            (REG_Common_Feature_Base + 0x0304)
#define REG_TY_BOOL_AUTO_GAIN               (REG_Common_Feature_Base + 0x030c)
#define REG_TY_INT_GAIN                     (REG_Common_Feature_Base + 0x0310)
#define REG_TY_BOOL_AUTO_AWB                (REG_Common_Feature_Base + 0x0314)
#define REG_TY_INT_R_GAIN                   (REG_Common_Feature_Base + 0x0318)
#define REG_TY_INT_G_GAIN                   (REG_Common_Feature_Base + 0x031c)
#define REG_TY_INT_B_GAIN                   (REG_Common_Feature_Base + 0x0320)
#define REG_TY_BOOL_UNDISTORTION            (REG_Common_Feature_Base + 0x0324)
#define REG_TY_INT_ANALOG_GAIN              (REG_Common_Feature_Base + 0x0328)
#define REG_TY_INT_LASER_POWER              (REG_Common_Feature_Base + 0x0500)
#define REG_TY_BOOL_LASER_AUTO_CTRL         (REG_Common_Feature_Base + 0x0504)


#define REG_DEFINE_FEATURE_ADDR(comp, feat) \
    REG_##comp##_##feat = ((REG_Component_##comp##_Base) + (REG_##feat))

#define REG_DEFINE_COMPONENT_FEATURE_LIST(comp) \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_WIDTH_MAX              ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_HEIGHT_MAX             ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_OFFSET_X               ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_OFFSET_Y               ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_WIDTH                  ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_HEIGHT                 ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_ENUM_IMAGE_MODE            ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_STRUCT_CAM_INTRINSIC       ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_STRUCT_EXTRINSIC_TO_LEFT_IR), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_STRUCT_CAM_DISTORTION      ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_ENUM_TRIGGER_ACTIVATION    ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_FRAME_PER_TRIGGER      ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_STRUCT_TRIGGER_PARAM       ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_BOOL_AUTO_EXPOSURE         ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_EXPOSURE_TIME          ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_BOOL_AUTO_GAIN             ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_GAIN                   ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_BOOL_AUTO_AWB              ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_R_GAIN                 ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_G_GAIN                 ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_B_GAIN                 ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_BOOL_UNDISTORTION          ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_ANALOG_GAIN            ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_BOOL_LASER_AUTO_CTRL       ), \
    REG_DEFINE_FEATURE_ADDR(comp, TY_INT_LASER_POWER            ), \

// feature list defined such as 
//    REG_Depth_TY_INT_WIDTH = REG_Component_Depth_Base + REG_TY_INT_WIDTH,
enum {
  REG_DEFINE_COMPONENT_FEATURE_LIST(Depth      )
  REG_DEFINE_COMPONENT_FEATURE_LIST(LeftIR     )
  REG_DEFINE_COMPONENT_FEATURE_LIST(RightIR    )
  REG_DEFINE_COMPONENT_FEATURE_LIST(LeftColor  )
  REG_DEFINE_COMPONENT_FEATURE_LIST(RightColor )
  REG_DEFINE_COMPONENT_FEATURE_LIST(Laser      )
  REG_DEFINE_COMPONENT_FEATURE_LIST(BrightHisto)
};


// GigE
#define XML_REG_AcquisitionStart            (REG_Device_Acuisition)
#define XML_REG_AcquisitionStop             (REG_Device_Acuisition) 



#endif

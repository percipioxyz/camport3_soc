#include "../common/Utils.hpp"

static int fps_counter = 0;
static clock_t fps_tm = 0;

#ifdef _WIN32
static int get_fps() {
   const int kMaxCounter = 250;
   fps_counter++;
   if (fps_counter < kMaxCounter) {
     return -1;
   }
   int elapse = (clock() - fps_tm);
   int v = (int)(((float)fps_counter) / elapse * CLOCKS_PER_SEC);
   fps_tm = clock();

   fps_counter = 0;
   return v;
 }
#else
static int get_fps() {
  const int kMaxCounter = 200;
  struct timeval start;
  fps_counter++;
  if (fps_counter < kMaxCounter) {
    return -1;
  }

  gettimeofday(&start, NULL);
  int elapse = start.tv_sec * 1000 + start.tv_usec / 1000 - fps_tm;
  int v = (int)(((float)fps_counter) / elapse * 1000);
  gettimeofday(&start, NULL);
  fps_tm = start.tv_sec * 1000 + start.tv_usec / 1000;

  fps_counter = 0;
  return v;
}
#endif

void eventCallback(TY_EVENT_INFO *event_info, void *userdata)
{
    if (event_info->eventId == TY_EVENT_DEVICE_OFFLINE) {
        LOGD("=== Event Callback: Device Offline!");
        // Note: 
        //     Please set TY_BOOL_KEEP_ALIVE_ONOFF feature to false if you need to debug with breakpoint!
    }
    else if (event_info->eventId == TY_EVENT_LICENSE_ERROR) {
        LOGD("=== Event Callback: License Error!");
    }
}

int main(int argc, char* argv[])
{
    TY_INTERFACE_HANDLE hIface = NULL;
    TY_DEVICE_BASE_INFO devInfo;
    TY_DEV_HANDLE hDevice;
    int32_t color, ir, depth;
    color = ir = depth = 1;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-color=off") == 0) {
            color = 0;
        } else if(strcmp(argv[i], "-depth=off") == 0) {
            depth = 0;
        } else if(strcmp(argv[i], "-ir=off") == 0) {
            ir = 0;
        } else if(strcmp(argv[i], "-h") == 0) {
            LOGI("Usage: SimpleView_FetchFrame [-h]");
            return 0;
        }
    }

    if (!color && !depth && !ir) {
        LOGD("=== At least one component need to be on");
        return -1;
    }

    LOGD("=== Init lib");
    ASSERT_OK( TYInitLib() );
    TY_VERSION_INFO ver;
    ASSERT_OK( TYLibVersion(&ver) );
    LOGD("     - lib version: %d.%d.%d", ver.major, ver.minor, ver.patch);

    ASSERT_OK( TYUpdateInterfaceList() );
    ASSERT_OK( TYOpenInterface("raw", &hIface) );
    ASSERT_OK( TYUpdateDeviceList(hIface) );
    uint32_t n = 0;
    ASSERT_OK( TYGetDeviceList(hIface, &devInfo, 1, &n) );
    ASSERT ( n == 1 );
    ASSERT_OK( TYOpenDevice(hIface, devInfo.id, &hDevice) );

    int32_t allComps;
    ASSERT_OK( TYGetComponentIDs(hDevice, &allComps) );
    if(allComps & TY_COMPONENT_RGB_CAM  && color) {
        LOGD("=== Has RGB camera, open RGB cam");
        ASSERT_OK( TYEnableComponents(hDevice, TY_COMPONENT_RGB_CAM) );
    }

    int32_t componentIDs = 0;
    LOGD("=== Configure components, open depth cam");
    if (depth) {
        componentIDs = TY_COMPONENT_DEPTH_CAM;
    }

    if (ir) {
        componentIDs |= TY_COMPONENT_IR_CAM_LEFT | TY_COMPONENT_IR_CAM_RIGHT;
    }

    ASSERT_OK( TYEnableComponents(hDevice, componentIDs) );

    LOGD("=== Configure feature, set resolution to 640x480.");
    int err = TYSetEnum(hDevice, TY_COMPONENT_DEPTH_CAM, TY_ENUM_IMAGE_MODE, TY_IMAGE_MODE_DEPTH16_640x480);
    ASSERT(err == TY_STATUS_OK || err == TY_STATUS_NOT_PERMITTED);

    LOGD("=== Disable trigger mode");
    TY_TRIGGER_PARAM trigger;
    trigger.mode = TY_TRIGGER_MODE_OFF;
    ASSERT_OK(TYSetStruct(hDevice, TY_COMPONENT_DEVICE, TY_STRUCT_TRIGGER_PARAM, &trigger, sizeof(trigger)));

    LOGD("=== Start capture");
    ASSERT_OK( TYStartCapture(hDevice) );

    LOGD("=== While loop to fetch frame");
    bool exit_main = false;
    TY_FRAME_DATA frame;
    int index = 0;
    while(!exit_main) {
        int err = TYFetchFrame(hDevice, &frame, -1);
        if( err == TY_STATUS_OK ) {
            LOGD("=== Get frame %d", ++index);

            for (int i=0; i<frame.validCount; i++) {
                void *  image_pos  = frame.image[i].buffer;
                int32_t image_size = frame.image[i].width * frame.image[i].height * TYPixelSize(frame.image[i].pixelFormat);
                if (frame.image[i].componentID == TY_COMPONENT_IR_CAM_LEFT) {
                    LOGD("===   Image %d (LEFT_IR , %p, %d)", i, image_pos, image_size);
                }
                if (frame.image[i].componentID == TY_COMPONENT_IR_CAM_RIGHT) {
                    LOGD("===   Image %d (RIGHT_IR, %p, %d)", i, image_pos, image_size);
                }
                if (frame.image[i].componentID == TY_COMPONENT_RGB_CAM) {
                    LOGD("===   Image %d (RGB     , %p, %d)", i, image_pos, image_size);
                }
                if (frame.image[i].componentID == TY_COMPONENT_DEPTH_CAM) {
                    LOGD("===   Image %d (DEPTH   , %p, %d)", i, image_pos, image_size);
                }
                if (frame.image[i].componentID == TY_COMPONENT_BRIGHT_HISTO) {
                    LOGD("===   Image %d (HISTO   , %p, %d)", i, image_pos, image_size);
                }
            }

            int fps = get_fps();
            if (fps > 0){
                LOGI("fps: %d", fps);
            }

            // Note: 
            //   1. Image Buffers are allocated by the SDK in raw interface mode.
            //   2. Enqueue the image buffer as soon as possible. Copy them to local if needed. 
            //   3. Do not modify frame.userBuffer and frame.bufferSize!
            LOGD("=== Re-enqueue buffer(%p, %d)"
                , frame.userBuffer, frame.bufferSize);
            ASSERT_OK( TYEnqueueBuffer(hDevice, frame.userBuffer, frame.bufferSize) );
        }
    }

    ASSERT_OK( TYStopCapture(hDevice) );
    ASSERT_OK( TYCloseDevice(hDevice) );
    ASSERT_OK( TYCloseInterface(hIface) );
    ASSERT_OK( TYDeinitLib() );

    LOGD("=== Main done!");
    return 0;
}

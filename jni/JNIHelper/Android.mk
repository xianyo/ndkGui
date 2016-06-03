LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= JNIHelper
LOCAL_SRC_FILES:= JNIHelper.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS := -llog -landroid 

LOCAL_STATIC_LIBRARIES :=  android_native_app_glue

LOCAL_CFLAGS += -std=c++11

include $(BUILD_STATIC_LIBRARY)

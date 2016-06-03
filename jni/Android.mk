LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ndkgui
LOCAL_SRC_FILES := main.cpp
 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. $(LOCAL_PATH)/JNIHelper/ $(LOCAL_PATH)/JUIHelper/ 
LOCAL_CFLAGS :=
LOCAL_CPPFLAGS := -std=c++11 -DREMOVE_TEAPOT=1

LOCAL_LDLIBS := -llog -landroid
LOCAL_STATIC_LIBRARIES :=  android_native_app_glue JNIHelper JUIHelper 


include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH))
$(call import-module,JNIHelper)
$(call import-module,JUIHelper)
$(call import-module,android/native_app_glue)

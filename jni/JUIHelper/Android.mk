LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= JUIHelper
LOCAL_SRC_FILES:= \
    IdFactory.cpp\
    JUIBase.cpp\
    JUIButton.cpp\
    JUIDialog.cpp\
    JUITextView.cpp\
    JUIView.cpp\
    JUIWindow.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS := -llog -landroid

LOCAL_STATIC_LIBRARIES := JNIHelper

LOCAL_CFLAGS += -std=c++11


include $(BUILD_STATIC_LIBRARY)

$(call import-module,JNIHelper)

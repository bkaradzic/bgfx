LOCAL_PATH := $(call my-dir)

###########################
#
# BGFX static library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := BGFX

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../bx/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := $(LOCAL_PATH)/src/amalgamated.cpp


LOCAL_CFLAGS += -Wshadow -fPIC -no-canonical-prefixes -Wa,--noexecstack -fstack-protector -ffunction-sections -Wno-psabi -Wunused-value -Wundef
LOCAL_CFLAGS += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS

ifeq ($(APP_OPTIM),debug)
  LOCAL_CFLAGS += -DBGFX_CONFIG_DEBUG=1
else
endif

LOCAL_EXPORT_CFLAGS += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS

LOCAL_LDLIBS :=-lEGL -lGLESv2 -landroid

LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)

include $(BUILD_STATIC_LIBRARY)

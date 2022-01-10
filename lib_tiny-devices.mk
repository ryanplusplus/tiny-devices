__lib_tiny-devices_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

LIBS := tiny-devices $(LIBS)

INC_DIRS += \
  $(__lib_tiny-devices_path)include \

tiny-devices_ASFLAGS := $(ASFLAGS)
tiny-devices_CPPFLAGS := $(CPPFLAGS)
tiny-devices_CFLAGS := $(CFLAGS)

tiny-devices_DEFINES := $(DEFINES)

tiny-devices_INC_DIRS := \
  $(INC_DIRS) \

tiny-devices_SYS_INC_DIRS := \

tiny-devices_SRC_FILES := \

tiny-devices_SRC_DIRS := \
  $(__lib_tiny-devices_path)src \

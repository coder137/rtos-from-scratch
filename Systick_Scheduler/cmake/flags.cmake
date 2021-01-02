# Project Variables
set(COMMON_C_FLAGS
  -Og
  -g
  -mcpu=cortex-m4
  -mthumb
  -mfloat-abi=hard
  -mfpu=auto
  -Wall
  -pipe
)

set(USER_C_FLAGS 
  ${COMMON_C_FLAGS}
  -std=c11
  -fmessage-length=0 
  -ffunction-sections
  -fdata-sections 
  -fstack-usage
)

set(USER_LINK_FLAGS
  ${COMMON_C_FLAGS}
  -nostartfiles
  # -specs=nano.specs -specs=nosys.specs "SHELL:-u _printf_float" "SHELL:-u
  # _scanf_float" -nostdlib
  -static
  -Wl,--gc-sections
  -Wl,-Map,${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map
  -T${PROJECT_SOURCE_DIR}/l0_lowlevel/linker/gcc_arm.ld
)

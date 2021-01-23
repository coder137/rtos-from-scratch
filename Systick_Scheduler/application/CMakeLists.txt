target_sources(${USER_PROJECT_TARGET} PRIVATE
  osKernel.c

  # NOTE, if the assembly file below is used, use INLINE_ASSEMBLY=0
  # osKernel.S
)
target_compile_definitions(${USER_PROJECT_TARGET} PRIVATE
  # INLINE_ASSEMBLY=0
  INLINE_ASSEMBLY=1
)
target_include_directories(${USER_PROJECT_TARGET} PRIVATE
  .
)

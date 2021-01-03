target_sources(${USER_PROJECT_TARGET} PRIVATE
  osKernel.c
  osKernel.S
)
target_include_directories(${USER_PROJECT_TARGET} PRIVATE
  .
)

target_sources(${USER_PROJECT_TARGET} PRIVATE
  # Scheduler
  osKernel.c
  osKernel.S

  # Semaphore
  osSemaphore.c
)
target_include_directories(${USER_PROJECT_TARGET} PRIVATE
  .
)

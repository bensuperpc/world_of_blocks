install(
    TARGETS world_of_blocks_exe
    RUNTIME COMPONENT world_of_blocks_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()

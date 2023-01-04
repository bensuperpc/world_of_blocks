find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    message(NOTICE "ccache is enabled (found here: ${CCACHE_PROGRAM})")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "\"${CCACHE_PROGRAM}\"")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "\"${CCACHE_PROGRAM}\"")
else()
    message(NOTICE "ccache has not been found")
endif()

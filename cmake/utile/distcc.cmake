find_program(DISTCC_PROGRAM distcc)

message(WARNING "distcc module is in beta.")

if(DISTCC_PROGRAM)
    message(NOTICE "distcc is enabled (found here: ${DISTCC_PROGRAM})")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "\"${DISTCC_PROGRAM}\"")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "\"${DISTCC_PROGRAM}\"")
else()
    message(NOTICE "distcc has not been found")
endif()

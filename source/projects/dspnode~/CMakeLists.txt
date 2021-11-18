include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-pretarget.cmake)

#############################################################
# MAX EXTERNAL
#############################################################

include_directories( 
	"${MAX_SDK_INCLUDES}"
	"${MAX_SDK_MSP_INCLUDES}"
	"${MAX_SDK_JIT_INCLUDES}"

    # Add any additional includes here
	"/usr/local/Cellar/julia/1.6.2_1/include/julia"
    # "${CMAKE_CURRENT_SOURCE_DIR}/../../include"  # e.g. if you put your includes in /source/include
)

set(PROJECT_SRC
    # Add any files you need to compile
    "dspnode~.c"
)

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-posttarget.cmake)
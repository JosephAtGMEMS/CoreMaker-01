configure_file(helloWorldConfig.h.in helloWorldConfig.h)

add_executable(${APP_TARGET})

include(${MBED_CONFIG_PATH}/mbed_config.cmake)

mbed_configure_app_target(${APP_TARGET})

target_include_directories(${APP_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_sources(${APP_TARGET}
    PRIVATE
        helloWorld.cpp
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        mbed-os
        mbed-usb
        mbed-netsocket
        mbed-storage
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

configure_file(factoryConfig.h.in factoryConfig.h)

add_executable(${APP_TARGET})

include(${MBED_CONFIG_PATH}/mbed_config.cmake)

mbed_configure_app_target(${APP_TARGET})

target_include_directories(${APP_TARGET}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/
      ${CMAKE_CURRENT_SOURCE_DIR}/..
      ${CMAKE_CURRENT_SOURCE_DIR}/../nvt_rs485/
      ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/
      ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/BME680
      ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/GMP102
      ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/KX122-1037
      ${CMAKE_CURRENT_SOURCE_DIR}/../sd_card
      ${CMAKE_CURRENT_SOURCE_DIR}/../libsensiml
      ${CMAKE_CURRENT_BINARY_DIR}
)

target_sources(${APP_TARGET}
    PRIVATE
        main.cpp
        DebounceIn.cpp
        lightEffect.hpp
        jWrite.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/ADS131E.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/GMC306.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/AcousticNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/SensorHub.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/BME680/mbed_bme680.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/BME680/bme680.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/GMP102/mbed_gmp102.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/GMP102/gmp102.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/KX122-1037/KX122.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../sd_card/NuSDBlockDevice.cpp
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        mbed-os
        mbed-usb
        mbed-netsocket
        mbed-storage
	${CMAKE_CURRENT_SOURCE_DIR}/../libsensiml/libsensiml.a
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

cmake_minimum_required(VERSION 3.10)
project(test)

# # 启用C标准
# set(CMAKE_C_STANDARD 11)


set(HWMQTT_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/huaweicloud-iot-device-sdk-c/libhwmqtt.so)

add_custom_target(build_hwmqtt ALL
                    COMMAND ${CMAKE_MAKE_PROGRAM}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/huaweicloud-iot-device-sdk-c/
                    COMMENT "Original hwmqtt makefile target")


add_library(hwmqtt SHARED IMPORTED)

set_property(TARGET hwmqtt APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(hwmqtt PROPERTIES IMPORTED_LOCATION_NOCONFIG "${HWMQTT_LIBRARY}")

add_dependencies(hwmqtt build_hwmqtt)

add_subdirectory(src)

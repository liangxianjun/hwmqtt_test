set(HWMQTT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/hwmqtt)

include_directories(${HWMQTT_INCLUDE_DIR}/agentlite)
include_directories(${HWMQTT_INCLUDE_DIR}/base)
include_directories(${HWMQTT_INCLUDE_DIR}/util)
include_directories(${HWMQTT_INCLUDE_DIR}/service)
include_directories(${HWMQTT_INCLUDE_DIR}/third_party/cjson)

add_executable(test main.cpp)

target_link_libraries(test ${PROJECT_SOURCE_DIR}/3rdparty/huaweicloud-iot-device-sdk-c/libhwmqtt.so)

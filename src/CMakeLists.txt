add_executable(test main.cpp)

# include_directories(../3rdparty/huaweicloud-iot-device-sdk-c/include/agentlite)

# include_directories(../3rdparty/huaweicloud-iot-device-sdk-c/include/third_party/cjson)
# target_include_directories(test PRIVATE 3rdparty/huaweicloud-iot-device-sdk-c/include/agentlite)
target_link_libraries(test hwmqtt)

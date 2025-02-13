cmake_minimum_required(VERSION 3.10.0)
project(mqtt_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN YES)
set(CPM_SOURCE_CACHE ${PROJECT_SOURCE_DIR}/.cache/cpm)

include(cmake/get_cpm.cmake)

set(PAHO_BUILD_STATIC 1)

CPMAddPackage("gh:eclipse-paho/paho.mqtt.c#v1.3.14")

file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.h")

add_executable(mqtt_test ${SOURCES})

# c: client
# a: async 
# s: socket
# eg: mqtt3as -> mqtt3 use "async", use "socket"

target_link_libraries(mqtt_test PRIVATE paho-mqtt3as-static)

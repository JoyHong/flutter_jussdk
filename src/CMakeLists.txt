# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.18.1)

project(pgm LANGUAGES CXX)

set(SRC
        include/PGM.c.cpp
        include/PGMCrypto.cpp
        include/PGMI.cpp
        include/Status/StatusPub1Pub.cpp
        include/Message/MessagePub1Agent.cpp
        include/Message/MessagePub1Pub.cpp
        include/Group/GroupPub1Agent.cpp
        include/Group/GroupPub1Pub.cpp
        include/Global/GlobalAgent.cpp
        include/Global/GlobalPub.cpp
)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID_STL=c++_static")

# 添加源文件
add_library(pgm SHARED ${SRC})

set(CMAKE_ANDROID_ARM_MODE TRUE)
set(CMAKE_ANDROID_ARM_NEON TRUE)

# 链接库
target_link_libraries(pgm
        ${CMAKE_CURRENT_SOURCE_DIR}/../android/libs/${CMAKE_ANDROID_ARCH_ABI}/libmtc.so
        ${CMAKE_CURRENT_SOURCE_DIR}/../android/libs/${CMAKE_ANDROID_ARCH_ABI}/libCommonSe.so
)

# 设置输出库的名称和路径
set_target_properties(pgm PROPERTIES
        OUTPUT_NAME "pgm"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../android/libs/${CMAKE_ANDROID_ARCH_ABI}"
)

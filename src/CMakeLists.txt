# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(flutter_jussdk_library VERSION 0.0.1 LANGUAGES C)

add_library(flutter_jussdk SHARED
  "flutter_jussdk.c"
)

set_target_properties(flutter_jussdk PROPERTIES
  PUBLIC_HEADER flutter_jussdk.h
  OUTPUT_NAME "flutter_jussdk"
)

target_compile_definitions(flutter_jussdk PUBLIC DART_SHARED_LIB)

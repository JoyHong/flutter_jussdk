# The Flutter tooling requires that developers have a version of Visual Studio
# installed that includes CMake 3.14 or later. You should not increase this
# version, as doing so will cause the plugin to fail to compile for some
# customers of the plugin.
cmake_minimum_required(VERSION 3.14)

# Project-level configuration.
set(PROJECT_NAME "flutter_jussdk")
project(${PROJECT_NAME} LANGUAGES CXX)

# Explicitly opt in to modern CMake behaviors to avoid warnings with recent
# versions of CMake.
cmake_policy(VERSION 3.14...3.25)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "flutter_jussdk_plugin")

# Invoke the build for native code shared with the other target platforms.
# This can be changed to accommodate different builds.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../src" "${CMAKE_CURRENT_BINARY_DIR}/shared")

# Any new source files that you add to the plugin should be added here.
list(APPEND PLUGIN_SOURCES
        "flutter_jussdk_plugin.cpp"
        "flutter_jussdk_plugin.h"
)

# Define the plugin library target. Its name must not be changed (see comment
# on PLUGIN_NAME above).
add_library(${PLUGIN_NAME} SHARED
        "include/flutter_jussdk/flutter_jussdk_plugin_c_api.h"
        "flutter_jussdk_plugin_c_api.cpp"
        ${PLUGIN_SOURCES}
)

# Apply a standard set of build settings that are configured in the
# application-level CMakeLists.txt. This can be removed for plugins that want
# full control over build settings.
apply_standard_settings(${PLUGIN_NAME})

# Symbols are hidden by default to reduce the chance of accidental conflicts
# between plugins. This should not be removed; any symbols that should be
# exported should be explicitly exported with the FLUTTER_PLUGIN_EXPORT macro.
set_target_properties(${PLUGIN_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)

# Source include directories and library dependencies. Add any plugin-specific
# dependencies here.
target_include_directories(${PLUGIN_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter flutter_wrapper_plugin)

# List of absolute paths to libraries that should be bundled with the plugin.
# This list could contain prebuilt libraries, or libraries created by an
# external build triggered from this build file.
set(flutter_jussdk_bundled_libraries
  # Defined in ../src/CMakeLists.txt.
  # This can be changed to accommodate different builds.
  $<TARGET_FILE:flutter_jussdk>
  "${CMAKE_CURRENT_SOURCE_DIR}/CommonSe.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/jssmme.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/libaom.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/libj264.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/mtc.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/zmf.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/zmfJni.dll"
  "${CMAKE_CURRENT_SOURCE_DIR}/zmfmanaged.dll"
  PARENT_SCOPE
)

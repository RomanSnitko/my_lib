cmake_minimum_required(VERSION 3.20)
project(mylib VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(mylib src/writer.cpp)
add_library(mylib::mylib ALIAS mylib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GEN_DIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/mylib_config.hpp.in
  ${GEN_DIR}/mylib_config.hpp
  @ONLY
)

set(GEN_HDR ${GEN_DIR}/mylib_generated.hpp)

add_custom_command(
  OUTPUT ${GEN_HDR}
  COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_header.py ${GEN_HDR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_header.py
)

add_custom_target(mylib_generate_headers DEPENDS ${GEN_HDR})
add_dependencies(mylib mylib_generate_headers)

target_include_directories(mylib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${GEN_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

find_package(ZLIB REQUIRED)
target_link_libraries(mylib PUBLIC ZLIB::ZLIB)

install(TARGETS mylib
  EXPORT mylibTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES
  ${GEN_DIR}/mylib_config.hpp
  ${GEN_HDR}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(mylib_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mylib)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mylibConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/mylibConfig.cmake
  INSTALL_DESTINATION ${mylib_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/mylibConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/mylibConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/mylibConfigVersion.cmake
  DESTINATION ${mylib_INSTALL_CMAKEDIR}
)

install(EXPORT mylibTargets
  NAMESPACE mylib::
  FILE mylibTargets.cmake
  DESTINATION ${mylib_INSTALL_CMAKEDIR}
)

export(EXPORT mylibTargets
  NAMESPACE mylib::
  FILE ${CMAKE_CURRENT_BINARY_DIR}/mylibTargets.cmake
)

option(MYLIB_BUILD_TESTS "Build tests" ON)

if(MYLIB_BUILD_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(mylib_gtest
    test/test_gtest.cpp
    test/test_gzip.cpp
  )
  target_link_libraries(mylib_gtest PRIVATE mylib GTest::gtest_main)

  enable_testing()
  add_test(NAME mylib_gtest COMMAND mylib_gtest)
endif()

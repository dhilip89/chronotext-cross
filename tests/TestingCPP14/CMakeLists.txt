cmake_minimum_required (VERSION 3.2.2)

project(TestingCPP14)

set(BOOST_ROOT "$ENV{CROSS_PATH}/tree/boost/${PLATFORM}")
set(GTEST_ROOT "$ENV{CROSS_PATH}/tree/gtest/${PLATFORM}")

set(INCLUDE_DIRS
  "${BOOST_ROOT}/include"
  "${GTEST_ROOT}/include"
)

set(LIBRARIES
  "${BOOST_ROOT}/lib/libboost_system.a"
  "${BOOST_ROOT}/lib/libboost_filesystem.a"
  "${GTEST_ROOT}/lib/libgtest.a"
  "${GTEST_ROOT}/lib/libgtest_main.a"
)

set(SRC_FILES
  src/main.cpp
)

include("$ENV{CROSS_PATH}/core/cmake/test.cmake")

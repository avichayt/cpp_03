cmake_minimum_required(VERSION 3.12)
project(cpp_03)

set(CMAKE_CXX_STANDARD 14)

set(EIGEN_DIR "C:\\cygwin64\\usr\\include\\eigen-eigen-323c052e1731")

include_directories(${EIGEN_DIR})



add_executable(cpp_03 Matrix.cpp Matrix.hpp TimeChecker.cpp tester.cpp Complex.h Complex.cpp )

TARGET_LINK_LIBRARIES(cpp_03 ${EIGEN_DIR})
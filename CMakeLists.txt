cmake_minimum_required(VERSION 2.8.11)

project(RSA)

set(RSA_VERSION_MAJOR 0)
set(RSA_VERSION_MINOR 0)
set(RSA_VERSION_PATCH 0)

list(APPEND CMAKE_CXX_FLAGS "-std=c++1y -g")

add_executable(encrypt encrypt.cpp math.cpp math.hpp)
add_executable(decrypt decrypt.cpp math.cpp math.hpp)

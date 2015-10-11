cmake_minimum_required(VERSION 2.8.11)

project(RSA)

list(APPEND CMAKE_CXX_FLAGS "-std=c++1y")

set(ENCRYPT_SOURCES
	Encrypt.cpp
	Math.cpp
	Math.hpp)

set(DECRYPT_SOURCES
	Decrypt.cpp
	Math.cpp
	Math.hpp)

add_executable(encrypt ${ENCRYPT_SOURCES})
add_executable(decrypt ${DECRYPT_SOURCES})

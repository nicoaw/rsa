cmake_minimum_required(VERSION 2.8.11)

project(RSA)

list(APPEND CMAKE_CXX_FLAGS "-std=c++1y")

set(RSA_SOURCES
	Crypt.cpp
	Crypt.hpp
	main.cpp)

set(RSA_DEPS
	boost_program_options)

add_executable(rsa ${RSA_SOURCES})
target_link_libraries(rsa ${RSA_DEPS})

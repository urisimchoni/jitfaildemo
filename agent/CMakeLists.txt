cmake_minimum_required(VERSION 3.8)
project(JitFailAgent)

find_package(JNI)

include_directories("${JNI_INCLUDE_DIRS}")

set(SOURCE_FILES
	AgentAPI.h
	MyAgent.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# default to debug build
IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   message(STATUS "Defaulting to debug build")
   SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "GCC/Clang detected")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

add_library(JitFailAgent SHARED ${SOURCE_FILES})

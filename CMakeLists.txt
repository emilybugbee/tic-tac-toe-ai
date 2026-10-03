# Copyright (c) 2025 Nathan Greenfield. All rights reserved

# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)

# Project name
project(P05 VERSION 1.0)

# Build for C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX AND NOT APPLE)
	message("Building for linux")

	# Where any include files are
	include_directories(src)
	include_directories(ITPLib)

	# Subdirectories to build
	add_subdirectory(src)
	add_subdirectory(tests)

else()
	message("Building for display")

	# Any source files in this directory
	set(SOURCE_FILES main.cpp)

	# Where any include files are
	include_directories(src)
	include_directories(ITPLib)

	# Subdirectories to build
	add_subdirectory(src)
	add_subdirectory(tests)

	# Location of files to link
	link_directories(ITPLib)

	# Name of executable
	add_executable(main ${SOURCE_FILES})

	# Link main vs the source library
	if (WIN32)
		target_link_libraries(main src ITPlib)
	elseif (APPLE)
		find_library(COCOA_LIBRARY Cocoa)
		target_link_libraries(main src ITPlib ${COCOA_LIBRARY})
	elseif ()
		target_link_libraries(main src ITPlib)
	endif()
endif()



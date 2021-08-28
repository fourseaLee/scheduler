cmake_minimum_required(VERSION 2.8)

project(scheduler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_BUILD_TYPE "Debug")

include_directories(./src)

aux_source_directory(./src DIR_SRCS)

set(base_src src/main.cpp
	     src/scheduler.cpp        
	     src/sync.cpp             
	     src/threadinterrupt.cpp
	     )

set(link_lib pthread boost_system)

add_executable(schedulerd ${base_src})

target_link_libraries(schedulerd ${link_lib})

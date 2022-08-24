cmake_minimum_required(VERSION 3.22)
project(case_benchmark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

set(ABSL_PROPAGATE_CXX_STD ON)
add_subdirectory(libs/abseil-cpp)

add_executable(case_benchmark)
target_sources(case_benchmark PRIVATE
	main.cpp
	using_for_each.h
	using_loop_if.h
	using_absl_table.h
	using_8.h
)
target_include_directories(case_benchmark PRIVATE SYSTEM
	${CMAKE_CURRENT_SOURCE_DIR}/libs/catch2/include
)
target_link_libraries(case_benchmark PRIVATE
	absl::base
	absl::strings
)

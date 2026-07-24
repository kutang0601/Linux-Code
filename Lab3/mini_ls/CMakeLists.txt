cmake_minimum_required(VERSION 3.10)

project(mini_ls)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
	mini_ls

	src/main.c
	src/dir.c
	src/list.c
	src/option.c
	src/print.c
	src/sort.c
	src/util.c
)

target_include_directories(
	mini_ls

	PRIVATE

	include
)


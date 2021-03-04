cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_CXX_STANDARD 89)

find_library(OPENGL_FRAMEWORK OpenGL)
find_library(APPKIT_FRAMEWORK AppKit)

include_directories(./include)
include_directories(./include/gnl)
include_directories(./include/libft)

set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/include)
set(SRCS
        src/cub3D.c
        src/parser.c)

add_executable(cub3D main.c ${SRCS})

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_FRAMEWORK}
        ${APPKIT_FRAMEWORK}
        ${LINK_LIBRARIES}/gnl/gnl.a
        ${LINK_LIBRARIES}/libft/libft.a)

cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_CXX_STANDARD 89)

find_library(OPENGL_FRAMEWORK OpenGL)
find_library(APPKIT_FRAMEWORK AppKit)
find_library(SDL2_FRAMEWORK SDL2)

include_directories(headers)
include_directories(libraries/gnl)
include_directories(libraries/libft)
include_directories(libraries/mlx)
include_directories(libraries/sound)
include_directories(libraries/zlib)
include_directories(libraries/sdl2/SDL2.framework/Headers)


set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/libraries)
set(SRCS
		src/cub3d.c
		src/parser.c
		src/texture.c
		src/events.c
		src/timer.c
		src/world.c
		src/renderer.c
		src/utils.c
		src/player.c
		src/mouse.c
		src/collisions.c
		src/story.c
		src/battle.c
		src/font.c
		src/hud.c
		src/key.c
		src/raycaster.c
		src/screenshot.c
		src/battle_v3.c
		src/mouse_event.c)

add_executable(${PROJECT_NAME} main.c ${SRCS})

target_link_libraries(${PROJECT_NAME}
		${OPENGL_FRAMEWORK}
		${APPKIT_FRAMEWORK}
		${SDL2_FRAMEWORK}
		${LINK_LIBRARIES}/sound/sound.a
		${LINK_LIBRARIES}/zlib/libz.a
		${LINK_LIBRARIES}/gnl/gnl.a
		${LINK_LIBRARIES}/libft/libft.a
		${LINK_LIBRARIES}/mlx/libmlx.a)

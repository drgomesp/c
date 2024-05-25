cmake_minimum_required(VERSION 3.28)
project(c C)

find_package(OpenGL REQUIRED)

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -ggdb")

add_executable(c
        src/opengl.c
        src/ppm.c
)

target_link_libraries(c ${OPENGL_LIBRARIES} glew glfw)

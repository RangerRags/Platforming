cmake_minimum_required(VERSION 3.20)
project(Platforming C)

set(CMAKE_C_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(Platforming main.c)
target_link_libraries(Platforming raylib)
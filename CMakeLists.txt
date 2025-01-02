cmake_minimum_required(VERSION 3.14)
project(EstudoDirigido)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -Wall -Wextra -Wpedantic")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()
add_subdirectory(tests)

add_executable(EstudoDirigido ./src/main.cpp ./src/search_strategy.cpp ./src/project.cpp)
add_executable(Timing ./timing/time_measurement.cpp ./src/search_strategy.cpp ./src/project.cpp)
cmake_minimum_required(VERSION 3.10.0)
project(Villainess VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Villainess ${SRC_FILES})

target_include_directories(Villainess
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/include/Villainess
)

target_compile_definitions(Villainess
    PRIVATE VILLAINESS_VERSION="${PROJECT_VERSION}"
)
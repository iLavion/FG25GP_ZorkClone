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

file(GLOB_RECURSE GAME_SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)
list(FILTER GAME_SRC_FILES EXCLUDE REGEX "src/main\\.cpp$")

file(GLOB_RECURSE TEST_SRC_FILES CONFIGURE_DEPENDS
    tests/*.cpp
)

add_executable(VillainessTests ${GAME_SRC_FILES} ${TEST_SRC_FILES})

target_include_directories(VillainessTests
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/include/Villainess
    PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

target_compile_definitions(VillainessTests
    PRIVATE VILLAINESS_VERSION="${PROJECT_VERSION}"
)
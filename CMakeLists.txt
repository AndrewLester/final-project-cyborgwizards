cmake_minimum_required (VERSION 3.13...3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(
    sensations  # Project name, change this as needed.
    LANGUAGES C CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")  # Keep all runtime files in one directory.

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Ensure the C++17 standard is available.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enforce UTF-8 encoding on MSVC.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

# Enable warnings recommended for new projects.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

set(BUILD_SHARED_LIBS ON)  # Builds libtcod has a shared library.
add_subdirectory("libtcod")  # This will error if you haven't initialized libtcod the submodule!

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main libtcod::libtcod)

# Catch2

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

set(testing_sources ${SOURCE_FILES})
list(REMOVE_ITEM testing_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(tests tests/test.cpp ${testing_sources})
target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain SDL2::SDL2 SDL2::SDL2main libtcod::libtcod)

# Failed attempt of autodetecting test files - will break #include
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/catch2-src/extras)
# include(CTest)
# include(Catch)
# catch_discover_tests(tests)

# Include Directories

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    "${CMAKE_CURRENT_SOURCE_DIR}/includes/event"
    "${CMAKE_CURRENT_SOURCE_DIR}/includes/item"
    "${CMAKE_CURRENT_SOURCE_DIR}/includes/map"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-windows/include/SDL2"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/arm64-osx/include/SDL2"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-osx/include/SDL2"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/x64-linux/include/SDL2"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg_installed/**"
    "${CMAKE_CURRENT_SOURCE_DIR}/libtcod/src"
)

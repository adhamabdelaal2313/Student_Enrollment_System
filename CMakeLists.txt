cmake_minimum_required(VERSION 3.16)
project(StudentEnrollmentSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use vcpkg if available
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Find packages (optional for GUI)
find_package(imgui CONFIG QUIET)
find_package(glfw3 CONFIG QUIET)
find_package(glad CONFIG QUIET)

if(imgui_FOUND AND glfw3_FOUND AND glad_FOUND)
    message(STATUS "GUI dependencies found - building GUI version")
    set(BUILD_GUI ON)
else()
    message(STATUS "GUI dependencies not found - building console/standalone only")
    set(BUILD_GUI OFF)
endif()

add_subdirectory(src) 
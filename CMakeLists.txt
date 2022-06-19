cmake_minimum_required(VERSION 3.19)

project(CalendarGenerator)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CTest)

find_program(CONAN_EXE conan)

if(CONAN_EXE)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=ddf0fafacf48b5c4912ecce5701c252532437c40277734cad5f4a8084470adbc
                TLS_VERIFY ON)
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_configure(REQUIRES
            boost/1.76.0
            fmt/8.0.0
            gtest/1.11.0
            GENERATORS cmake_find_package)

    conan_cmake_autodetect(settings)

    conan_cmake_install(PATH_OR_REFERENCE .
            BUILD missing
            REMOTE conan-center
            SETTINGS ${settings})

    set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
endif()

set(TARGET_NAME calendergenerator)

set(SOURCES
        datehelper.cpp
        htmlgenerator.cpp
)

add_library(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(fmt REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE fmt)

set(EXE_NAME EtasTest)
add_executable(${EXE_NAME} main.cpp)

find_package(Boost 1.76.0 COMPONENTS program_options REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE Boost::program_options ${TARGET_NAME})

add_subdirectory(test)


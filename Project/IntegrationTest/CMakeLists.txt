cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ../../Project/IntegrationTest/bin)
include_directories(../../Library)

add_executable(EnvironmentTest source/EnvironmentTest.cpp)

if(BUILD_SFML_TEST)
    add_executable(SFMLTest source/SFMLTest.cpp)
    find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
    if(SFML_FOUND)
        target_link_libraries(SFMLTest sfml-graphics)
    endif()
endif()

add_executable(SimulatorTest source/SimulatorTest.cpp)
target_compile_definitions(SimulatorTest PRIVATE PAX_SAPIENTICA_DEBUG)
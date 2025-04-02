cmake_minimum_required(VERSION 3.10)
project(Breach_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MAIN src/main.cpp)

set(SOURCES src/TokenizerTest.cpp
	Dependencies/glad/src/glad.c)

# Components include
add_subdirectory(${CMAKE_SOURCE_DIR}/Components/Breach_StringLib)

set(COMPONENTS Breach_StringLib)

# Dependencies include
add_subdirectory(${CMAKE_SOURCE_DIR}/Dependencies/glfw)

include_directories(${CMAKE_SOURCE_DIR}/Dependencies/glad/include)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${COMPONENTS} glfw GL)

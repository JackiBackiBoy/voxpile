cmake_minimum_required(VERSION 3.20.0)

project(voxpile)
set(NAME "voxpile")
set(GLFW_PATH ${PROJECT_SOURCE_DIR}/vendor/GLFW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)


# 1. Load OpenGL via GLAD
set(GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/GLAD/include)

# 2. Load GLFW
if (DEFINED GLFW_PATH) 
  message(STATUS "Using GLFW at: " ${GLFW_PATH})
  set(GLFW_INCLUDE_DIR ${GLFW_PATH}/include)
  set(GLFW_LIB ${GLFW_PATH}/lib)
endif()

# Retrieve all source and header files
file(GLOB_RECURSE CPP_SOURCE_FILES ${CMAKE_HOME_DIRECTORY}/src/*.cpp)
file(GLOB_RECURSE CPP_HEADER_FILES ${CMAKE_HOME_DIRECTORY}/src/*.hpp)
file(GLOB_RECURSE C_SOURCE_FILES ${CMAKE_HOME_DIRECTORY}/src/*.c)
add_executable(${NAME} ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES} ${C_SOURCE_FILES})

# Compiler settings
target_compile_features(${NAME} PUBLIC cxx_std_17)

# Include and link libraries
target_include_directories(${NAME} PUBLIC
  ${GLFW_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
)

target_link_directories(${NAME} PUBLIC
  ${GLFW_LIB}
)

target_link_libraries(${NAME} glfw3)

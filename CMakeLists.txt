cmake_minimum_required(VERSION 3.12)

# Set project name as a variable
set(ProjectName Sandbox)

project(${ProjectName})

add_library(imgui STATIC
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp
)

# Add the include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLM
)

# Collect all .cpp and .h files from the src directory
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Use the ProjectName variable for the executable
add_executable(${ProjectName} ${SRC_FILES})

# Link against libraries
target_link_libraries(${ProjectName}
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/lib/glew32.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib-vc2019/glfw3.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib-vc2019/glfw3dll.lib
    opengl32.lib
    imgui
)
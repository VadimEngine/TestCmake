cmake_minimum_required(VERSION 3.12)

project(Sandbox)

# Create static library for imgui
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
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/Win32/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLM
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/include
    ${CMAKE_SOURCE_DIR}/src/Application
    ${CMAKE_SOURCE_DIR}/src/Graphics
    ${CMAKE_SOURCE_DIR}/src/GUI
    ${CMAKE_SOURCE_DIR}/src/Scenes
)

# Collect all .cpp and .h files from the src directory
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Create Executable target
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# Link against libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/lib/Win32/glew32s.lib # Statically link without requiring glew32.dll
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/Win32/lib-vc2019/glfw3.lib # TODO make glfw for x86?
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/Win32/lib-vc2019/glfw3dll.lib
    opengl32.lib
    imgui
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/lib/SOIL.lib
)
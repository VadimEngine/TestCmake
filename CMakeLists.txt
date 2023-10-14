cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(Sandbox)

# Add an option for the build mode (x64 or Win32)
set(BUILD_MODE "x64" CACHE STRING "Build mode: x64 or Win32")
set_property(CACHE BUILD_MODE PROPERTY STRINGS "x64" "Win32")

# Add the include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLM
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/contrib

    ${CMAKE_SOURCE_DIR}/src/Application
    ${CMAKE_SOURCE_DIR}/src/Graphics
    ${CMAKE_SOURCE_DIR}/src/GUI
    ${CMAKE_SOURCE_DIR}/src/Scenes
    ${CMAKE_SOURCE_DIR}/src/Entities
)

# Collect all .cpp and .h files from the src directory
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

list(APPEND SRC_FILES
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp
)

# Create Executable target
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# Link against libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/lib/${BUILD_MODE}/glew32s.lib # Statically link without requiring glew32.dll
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/${BUILD_MODE}/glfw3.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/${BUILD_MODE}/glfw3dll.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/lib/${BUILD_MODE}/SOIL.lib
    opengl32.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/lib/assimp-vc142-mtd.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/lib/zlibstaticd.lib
)
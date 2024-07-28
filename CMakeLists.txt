cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
project(Sandbox)

# Add an option for the build mode (x64 or Win32)
set(BUILD_MODE "x64" CACHE STRING "Build mode: x64 or Win32")
set_property(CACHE BUILD_MODE PROPERTY STRINGS "x64" "Win32")
# For Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()

# Add the include directories
include_directories(
    # Third party
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/include # OpenGl windows
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/include # OpenGL api
    ${CMAKE_SOURCE_DIR}/ThirdParty/imgui # GUI components
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLM # Graphics Mathimatics
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/include # Image file loading
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/include # 3d model file loading
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/contrib # 3d model file loading
    ${CMAKE_SOURCE_DIR}/ThirdParty/openAL/include # Audio
    ${CMAKE_SOURCE_DIR}/ThirdParty/sndfile/include # Audio file loading
    ${CMAKE_SOURCE_DIR}/ThirdParty/freetype/include # Font/Text Rendering

    # source code
    ${CMAKE_SOURCE_DIR}/src/Application
    ${CMAKE_SOURCE_DIR}/src/Application/Scenes/Games
    ${CMAKE_SOURCE_DIR}/src/Audio
    ${CMAKE_SOURCE_DIR}/src/Graphics
    ${CMAKE_SOURCE_DIR}/src/GUI
    ${CMAKE_SOURCE_DIR}/src/Application/Scenes
    ${CMAKE_SOURCE_DIR}/src/Entities
    ${CMAKE_SOURCE_DIR}/src/Entities/Render
    ${CMAKE_SOURCE_DIR}/src/Entities/Physics
    ${CMAKE_SOURCE_DIR}/src/Utils
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

# Add Google Test
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/googletest)

# Core library
add_library( ${PROJECT_NAME}Core ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}Core
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLEW/lib/${BUILD_MODE}/glew32s.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/${BUILD_MODE}/glfw3.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/${BUILD_MODE}/glfw3dll.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/SOIL/lib/${BUILD_MODE}/SOIL.lib
    opengl32.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/lib/assimp-vc142-mtd.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/assimp/lib/zlibstaticd.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/openAL/lib/${BUILD_MODE}/al-excommon.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/openAL/lib/${BUILD_MODE}/OpenAL32.lib
    winmm.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/sndfile/lib/${BUILD_MODE}/sndfile.lib
    ${CMAKE_SOURCE_DIR}/ThirdParty/freetype/lib/${BUILD_MODE}/freetype.lib
)

# Main application
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Core)

# Test directory
add_subdirectory(tests)
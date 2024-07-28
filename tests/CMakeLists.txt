cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}_test ${Sources})
target_link_libraries(${PROJECT_NAME}_test PUBLIC 
    gtest_main
    ${PROJECT_NAME}Core
)

target_include_directories(${PROJECT_NAME}_test PUBLIC 
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

add_test(
    NAME ${PROJECT_NAME}_test
    COMMAND ${PROJECT_NAME}_test
)

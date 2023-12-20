cmake_minimum_required(VERSION 3.10)

project(2dgl)


set(GLAD C:/Dev/glad/)
set(GLFW_DIR C:/Dev/glfw-3.3.7.bin.WIN64/)
set(STB_DIR C:/Dev/stb/)
set(JSON_DIR C:/Dev/json/)
set(SDL_DIR C:/Dev/SDL2/)
set(SDLMIX_DIR C:/Dev/SDL2_mixer-2.0.0/)


file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Other/*.cpp")


add_executable(${PROJECT_NAME} Main.cpp ${SRC} ${GLAD}/src/glad.c)


target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECTS="${CMAKE_CURRENT_SOURCE_DIR}/Other/Projects/")


find_package(OpenGL REQUIRED)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/Other
	${GLAD}include/
	${STB_DIR}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}include ${SDL_DIR}include ${SDLMIX_DIR}include ${JSON_DIR})





#C:\Dev\SDL2_mixer-2.0.0\lib\x64 lib-vc2022/  C:\Dev\SDL2\lib\x64
target_link_libraries (${PROJECT_NAME} PRIVATE ${GLFW_DIR}lib-vc2022/glfw3.lib ${SDL_DIR}/lib/x64/SDL2.lib ${SDL_DIR}/lib/x64/SDL2main.lib ${SDLMIX_DIR}lib/x64/SDL2_mixer.lib )
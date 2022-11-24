cmake_minimum_required(VERSION 3.0)

project(practice1)

set(CMAKE_CXX_FLAGS "-ldl")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB cxx CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB c CONFIGURE_DEPENDS "src/*.c")

add_executable(practice1 ${cxx} ${c})

set(OpenGL_GL_PREFERENCE "GLVND")#use glvnd? what the fuck
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(practice1 PUBLIC ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(practice1 ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} dl)#just dl? its all i need..? i love cmake :)

add_custom_target(copyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/*
            ${CMAKE_CURRENT_BINARY_DIR}/resources/
)
add_dependencies(copyResources practice1)


install(TARGETS practice1 RUNTIME DESTINATION bin)

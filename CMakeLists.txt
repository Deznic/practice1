cmake_minimum_required(VERSION 3.0)

project(practice1)

set(CMAKE_CXX_FLAGS "-ldl")

file(GLOB cxx CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB c CONFIGURE_DEPENDS "src/*.c")

add_executable(practice1 ${cxx} ${c})

set(OpenGL_GL_PREFERENCE "GLVND")#use glvnd? what the fuck
find_package(OpenGL REQUIRED)

target_include_directories(practice1 PUBLIC ${OPENGL_INCLUDE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(practice1 ${OPENGL_LIBRARIES} dl)#just dl? its all i need..? i love cmake :)

install(TARGETS practice1 RUNTIME DESTINATION bin)

# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.25
cmake_policy(SET CMP0009 NEW)

# c at CMakeLists.txt:8 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/deznic/projects/Practice1/src/*.c")
set(OLD_GLOB
  "/home/deznic/projects/Practice1/src/glad.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/deznic/projects/Practice1/build/CMakeFiles/cmake.verify_globs")
endif()

# cxx at CMakeLists.txt:7 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/deznic/projects/Practice1/src/*.cpp")
set(OLD_GLOB
  "/home/deznic/projects/Practice1/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/deznic/projects/Practice1/build/CMakeFiles/cmake.verify_globs")
endif()
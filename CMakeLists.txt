cmake_minimum_required (VERSION 3.0)
project (test)

# enable_language(C ASM)
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
# add_executable(test src/test.asm src/main.cpp)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set_source_files_properties(src/test.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")

set(CMAKE_CXX_STANDARD 11)

add_executable(test src/test.asm src/main.cpp)

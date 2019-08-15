cmake_minimum_required (VERSION 3.0)
project (test)

# setup nasm
enable_language(ASM_NASM)
#set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
#set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
#    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

#set_source_files_properties(test/nasm/test.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")
#set(CMAKE_CXX_STANDARD 11)

add_executable(test1 test/nasm/test.asm test/nasm/main.cpp)

add_library(auread STATIC src/input/decode_audio_file.c)

add_executable(read_audio_file test/input/main-test.c)
target_link_libraries(read_audio_file avcodec avformat avutil swresample auread)

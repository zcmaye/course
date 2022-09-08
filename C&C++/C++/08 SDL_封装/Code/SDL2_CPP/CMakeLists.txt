cmake_minimum_required(VERSION 3.2)
#项目名称
project(sdl)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

#添加include目录和lib目录
include_directories("F:/Tools/SDL2/SDL2-2.0.22/include/" "F:/Tools/SDL2/SDL2_mixer-2.6.1/include" "F:/Tools/SDL2/SDL2_image-2.6.1/include")
#32位
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    link_directories("F:/Tools/SDL2/SDL2-2.0.22/lib/x86/" "F:/Tools/SDL2/SDL2_mixer-2.6.1/lib/x86" "F:/Tools/SDL2/SDL2_image-2.6.1/lib/x86")
    message(STATUS "build in x86")
#64位
else()
    link_directories("F:/Tools/SDL2/SDL2-2.0.22/lib/x64/" "F:/Tools/SDL2/SDL2_mixer-2.6.1/lib/x64" "F:/Tools/SDL2/SDL2_image-2.6.1/lib/x64")
    message(STATUS "build in x64")
endif()

aux_source_directory(. MY_SOURCES)

#用指定的源文件生成目标sdl
add_executable(sdl main.cpp ${MY_SOURCES})

#连接库
target_link_libraries(sdl SDL2 SDL2main SDL2_image SDL2_mixer)





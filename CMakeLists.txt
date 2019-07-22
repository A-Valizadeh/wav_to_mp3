cmake_minimum_required(VERSION 3.5)

project(wav_to_mp3)
set (CMAKE_CXX_FLAGS "-std=c++14")
add_executable(wav_to_mp3 main.cpp wav_to_mp3.cpp wavFileHandler.cpp ) 
if(UNIX)
target_link_libraries(wav_to_mp3 libmp3lame.a pthread) 
else()
target_link_libraries(wav_to_mp3 libmp3lame.dll.a pthread) 
endif()


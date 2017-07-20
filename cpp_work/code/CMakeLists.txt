include_directories(
"inc/" 
)

file(GLOB_RECURSE files
./src/*.cpp
)


add_executable(service ${files} ${CMAKE_CURRENT_SOURCE_DIR}/UserConfigInit.cpp)

add_oss_lib(service)

#target_link_libraries(service)


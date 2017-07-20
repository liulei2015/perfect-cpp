CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(cpp-work-ft)

set(cpp_work_code ${CMAKE_CURRENT_SOURCE_DIR}/../../code)
set(tools_dir ${cpp_work_code}/../../tools)
set(infra_dir ${cpp_work_code}/../../infra)

include_directories(
"include/"
"../utest/include/"
"../benchmark/inc/"
"${cpp_work_code}/inc/"
"${tools_dir}/include/"
"${infra_dir}/include/"
)

IF(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -w -rdynamic -std=c++11 -O2 -fprofile-arcs -ftest-coverage")
  set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -fprofile-arcs -ftest-coverage -g3 ")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-invalid-offsetof -O2")
ENDIF(UNIX)

add_definitions(
-DUSI_FT
)
    
link_directories("${tools_dir}/lib") 

add_subdirectory("cpp_work")
add_subdirectory("infra")


FILE(GLOB_RECURSE ftest_files
include/*.h
include/*.hpp
src/*.cpp
src/*.cc
)

FILE(GLOB_RECURSE utest_files
../utest/include/*.h
../utest/include/*.hpp
../utest/src/*.cpp
../utest/src/*.cc
)

FILE(GLOB_RECURSE benchmark_test_files
../benchmark/include/*.h
../benchmark/include/*.hpp
../benchmark/src/*.cpp
../benchmark/src/*.cc
)

SET(all_files ${ftest_files} ${utest_files} ${benchmark_test_files})  

add_executable(ftest ${all_files})

target_link_libraries(ftest cpp_work infra mockcpp gtest libcelero.so pthread)




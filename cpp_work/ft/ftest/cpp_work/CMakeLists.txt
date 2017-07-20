
INCLUDE_DIRECTORIES(
)

set(files "")

file(GLOB_RECURSE files
${cpp_work_code}/src/*.cpp
${cpp_work_code}/src/*.cc
${cpp_work_code}/inc/*.hpp
)

add_library(cpp_work ${files})

target_link_libraries(cpp_work infra)


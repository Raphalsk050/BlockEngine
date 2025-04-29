cmake_minimum_required(VERSION 3.31)
project(block_engine)

set(CMAKE_CXX_STANDARD 20)
set(glm_DIR third_party/glm)
set(glfw_DIR third_party/glfw)
set(glad_DIR third_party/glad)
set(spdlog_DIR third_party/spdlog)

# GLM ===================
add_subdirectory(${glm_DIR})
add_subdirectory(${glfw_DIR})
add_subdirectory(${spdlog_DIR})

add_library(glad STATIC
        ${glad_DIR}/src/glad.c
)

include_directories(
        ${glad_DIR}/include
)

add_executable(block_engine
        src/types.h
        src/block_engine.h
        main.cpp)

# Compile commands
target_compile_definitions(block_engine
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

target_sources(block_engine PRIVATE
        $<$<CONFIG:Debug>:src/log/belog.cpp>
)

target_link_libraries(block_engine PUBLIC glm glfw glad spdlog)

cmake_minimum_required(VERSION 3.1.0)

project(Info)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Info")
# Set the dll/lib filename
set(DesignPatterns_filename "DesignPatterns")

# Set the include folder. Relative to this file path
set(IncludePath "include")
 

set(SOURCES
    main.cpp
)

add_executable(Info_s ${SOURCES})
add_executable(Info_d ${SOURCES})

target_link_libraries(Info_s DesignPatterns_static)
target_compile_definitions(Info_s PUBLIC BUILD_STATIC)

target_link_libraries(Info_d DesignPatterns_shared)


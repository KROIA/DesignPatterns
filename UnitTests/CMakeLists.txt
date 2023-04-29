cmake_minimum_required(VERSION 3.1.0)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME ProjectName)   
string(REPLACE " " "_" ProjectId ${ProjectName})
project(${ProjectName})

project(${ProjectName})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ProjectName}")

# Macro to search for files with given file ending.
# call:
#   FILE_DIRECTORIES(H_FILES *.h)
#
# all *.h files will be saved in the H_FILES variable
MACRO(FILE_DIRECTORIES return_list ending)
    FILE(GLOB_RECURSE new_list ${ending})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()


# Get all source files
FILE_DIRECTORIES(H_FILES *.h)
FILE_DIRECTORIES(CPP_FILES *.cpp)

# Combine headers and cources
set(SOURCES
    ${CPP_FILES}
    ${H_FILES}
)

add_executable(${ProjectName}-s ${SOURCES})
add_executable(${ProjectName} ${SOURCES})

target_link_libraries(${ProjectName}-s Utilities_static)
target_link_libraries(${ProjectName} Utilities_shared)
target_compile_definitions(${ProjectName}-s PUBLIC BUILD_STATIC)

set_target_properties(${ProjectName}-s PROPERTIES DEBUG_POSTFIX "-d" )
set_target_properties(${ProjectName} PROPERTIES DEBUG_POSTFIX "-d" )

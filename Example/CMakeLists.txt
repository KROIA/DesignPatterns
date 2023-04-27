
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Example")


MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SubDirs ${CMAKE_CURRENT_SOURCE_DIR})

FOREACH(SubDir ${SubDirs})
  ADD_SUBDIRECTORY(${SubDir})
ENDFOREACH()

# add_subdirectory(Info)
# add_subdirectory(Singelton)
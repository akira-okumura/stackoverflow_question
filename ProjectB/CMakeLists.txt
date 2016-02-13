cmake_minimum_required(VERSION 2.6)

project(ProjectB)

find_package(ProjectA CONFIG REQUIRED)
include_directories(${ProjectA_INCLUDE_DIRS})
message(${ProjectA_INCLUDE_DIRS})
list(APPEND EXTLIBS ${ProjectA_LIBRARIES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(APPLE)
  #set(CMAKE_MACOSX_RPATH ON)
  set(MACOS_RPATH ON)
endif()

add_library(ProjectB SHARED ${SOURCES})
target_link_libraries(ProjectB ${EXTLIBS})
add_executable(exeB ${CMAKE_CURRENT_SOURCE_DIR}/exeB.cxx)
target_link_libraries(exeB ProjectB ${EXTLIBS})

find_package(SWIG REQUIRED)
find_package(PythonLibs REQUIRED)
include(${SWIG_USE_FILE})
include_directories(${PYTHON_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_FORMAT_MACROS")
set_source_files_properties(project_b.i PROPERTIES CPLUSPLUS ON)
swig_add_module(project_b python project_b.i ${SOURCES})
swig_link_libraries(project_b ${PYTHON_LIBRARIES} ${EXTLIBS})

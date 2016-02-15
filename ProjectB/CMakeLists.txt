cmake_minimum_required(VERSION 2.6)

project(ProjectB)

find_package(ProjectA CONFIG REQUIRED)
include_directories(${ProjectA_INCLUDE_DIRS})
message(${ProjectA_INCLUDE_DIRS})
list(APPEND EXTLIBS ${ProjectA_LIBRARIES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(APPLE)
  set(CMAKE_MACOSX_RPATH TRUE)

# The following settings were copied from
# https://cmake.org/Wiki/CMake_RPATH_handling
# to avoid the rpath issue that appears on OS X El Capitan

  # use, i.e. don't skip the full RPATH for the build tree
  set(CMAKE_SKIP_BUILD_RPATH  FALSE)

  # when building, don't use the install RPATH already
  # (but later on when installing)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) # Changed to TRUE by A.O. 

  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

  # add the automatically determined parts of the RPATH
  # which point to directories outside the build tree to the install RPATH
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

  # the RPATH to be used when installing, but only if it's not a system directory
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
     set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  endif("${isSystemDir}" STREQUAL "-1")
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

execute_process(COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)

install(TARGETS _project_b DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ${CMAKE_BINARY_DIR}/project_b.py DESTINATION ${PYTHON_SITE_PACKAGES} COMPONENT pylibrary)

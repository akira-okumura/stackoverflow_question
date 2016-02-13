cmake_minimum_required(VERSION 2.6)

project(ProjectA)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
endif()

add_library(ProjectA SHARED ${SOURCES})
install(TARGETS ProjectA LIBRARY DESTINATION lib COMPONENT library)
file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/ProjectA/*h")
install(FILES ${INCS} DESTINATION include/ProjectA/ COMPONENT headers)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ProjectAConfig.cmake" DESTINATION lib/cmake/ProjectA COMPONENT devel)

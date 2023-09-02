cmake_minimum_required(VERSION 3.13)
project(comarray_so 
    LANGUAGES CXX 
    VERSION 1.0.0 
)

set(Release_mode -g0 -O2 -Wall)
set(Debug_mode -g2 -O0)

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/cprjct/mylibs)
set(CMAKE_INSTALL_LIBDIR /sos)
set(CMAKE_INSTALL_INCLUDEDIR /include)


include_directories(/usr/include /usr/local/include ${CMAKE_SOURCE_DIR}/include)

add_library(logger SHARED logger.cpp)

target_compile_features(logger PUBLIC ${COMPILE_FEATURES})

target_compile_options(logger 
    PUBLIC $<IF:$<CONFIG:Release>, ${Release_mode}, ${Debug_mode}>
)

## install shared object 
install(TARGETS logger
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}${CMAKE_INSTALL_LIBDIR}/
)

## install include file
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_PREFIX}${CMAKE_INSTALL_INCLUDEDIR} 
    FILES_MATCHING PATTERN "*.h"
)

message(STATUS "CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message(STATUS "CMAKE_PROJECT_VERSION: ${CMAKE_PROJECT_VERSION}")

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_BUILD_TOOL:  ${CMAKE_BUILD_TOOL}")
message(STATUS "COMPILE_FEATURES: ${COMPILE_FEATURES}")

message(STATUS "CMAKE_INSTALL_PREFIX:  ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")


cmake_minimum_required(VERSION 3.13)
project(comarray_so LANGUAGES CXX VERSION 1.0.0 )

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/cprjct/mylibs)
set(CMAKE_INSTALL_LIBDIR /sos)
set(CMAKE_INSTALL_INCLUDEDIR /include)

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("CMAKE_BUILD_TOOL:  ${CMAKE_BUILD_TOOL}")
message("CMAKE_INSTALL_PREFIX:  ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}\n\n")

set(Release_mode -g0 -O2 -Wall)
set(Debug_mode -g2 -O0)

include_directories(/usr/include /usr/local/include ${CMAKE_SOURCE_DIR}/include)

add_library(logger SHARED logger.cpp)

target_compile_features(logger PUBLIC cxx_std_17)

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
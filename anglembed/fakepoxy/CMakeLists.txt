cmake_minimum_required(VERSION 3.20)
project(fakepoxy)

include_directories(include)

add_library(fakepoxy STATIC fakepoxy.c)

set(FAKEPOXY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
configure_file(${CMAKE_CURRENT_LIST_DIR}/fakepoxy.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/fakepoxy.pc.in0 @ONLY)

# FIXME: Deploy files at configuration times..

file(GENERATE OUTPUT ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/epoxy.pc
    #NEWLINE_STYLE UNIX # Not supported with current qemubuild image
    INPUT ${CMAKE_CURRENT_BINARY_DIR}/fakepoxy.pc.in0)

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/epoxy/gl.h
    ${CMAKE_INSTALL_PREFIX}/include/epoxy/gl.h)

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/epoxy/egl.h
    ${CMAKE_INSTALL_PREFIX}/include/epoxy/egl.h)


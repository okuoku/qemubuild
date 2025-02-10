cmake_minimum_required(VERSION 3.20)
project(fakepoxy)

set(glheaderdir ${ANGLE_ROOT}/include)
include_directories(${glheaderdir})
include_directories(include)

add_library(fakepoxy STATIC fakepoxy.c)

set(FAKEPOXY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
configure_file(${CMAKE_CURRENT_LIST_DIR}/fakepoxy.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/fakepoxy.pc.in0 @ONLY)

# Deploy GL Headers from ANGLE

# FIXME: Deploy files at configuration times..



set(glheaders
    EGL/egl.h
    EGL/eglext.h
    EGL/eglext_angle.h # ANGLE
    EGL/eglplatform.h
    GLES/gl.h
    GLES/glext.h
    GLES/glplatform.h
    GLES2/gl2.h
    GLES2/gl2ext.h
    GLES2/gl2ext_angle.h # ANGLE
    GLES2/gl2platform.h
    GLES3/gl3.h
    GLES3/gl31.h
    GLES3/gl32.h
    GLES3/gl3platform.h)


# FIXME: Deploy headers at configuration time
#        We should find better location...

foreach(e ${glheaders})
    message(STATUS "Deploy header ${e}")
    configure_file(
        ${glheaderdir}/${e}
        ${CMAKE_INSTALL_PREFIX}/include/${e}
        COPYONLY)
endforeach()

file(GENERATE OUTPUT ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/epoxy.pc
    #NEWLINE_STYLE UNIX # Not supported with current qemubuild image
    INPUT ${CMAKE_CURRENT_BINARY_DIR}/fakepoxy.pc.in0)

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/epoxy/gl.h
    ${CMAKE_INSTALL_PREFIX}/include/epoxy/gl.h)

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/epoxy/egl.h
    ${CMAKE_INSTALL_PREFIX}/include/epoxy/egl.h)


cmake_minimum_required(VERSION 3.20)
project(anglembed)

set(root ${CMAKE_CURRENT_LIST_DIR}/../gldeps)

# glslang and SPIRV-Tools

set(SPIRV_WERROR OFF CACHE BOOL "" FORCE)
set(SPIRV-Headers_SOURCE_DIR ${root}/SPIRV-Headers)
set(SKIP_GLSLANG_INSTALL OFF CACHE BOOL "" FORCE)
set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "" FORCE)
set(SKIP_SPIRV_TOOLS_INSTALL OFF CACHE BOOL "" FORCE)
set(SPIRV_SKIP_EXECUTABLES ON CACHE BOOL "" FORCE)

add_subdirectory(${root}/SPIRV-Tools SPIRV-Tools)
add_subdirectory(${root}/glslang glslang)

# Workaround for glslang-default-resource-limits
set(glslang-resource-limits-srcs
    ${root}/glslang/glslang/ResourceLimits/ResourceLimits.cpp
    ${root}/glslang/glslang/ResourceLimits/resource_limits_c.cpp)
include_directories(${root}/glslang)
add_library(my-glslang-default-resource-limits STATIC
    ${glslang-resource-limits-srcs})

# Angle

set(ANGLE_SPIRV_HEADERS_ROOT ${root}/SPIRV-Headers)
set(ANGLE_VULKAN_HEADERS_ROOT ${root}/Vulkan-Headers)
set(ANGLE_SPIRV_TOOLS_ROOT ${root}/SPIRV-Tools)
set(ANGLE_VOLK_ROOT ${root}/volk) # Vulkan only?
set(ANGLE_VMA_ROOT ${root}/VulkanMemoryAllocator) # Vulkan only?
set(ANGLE_GLSLANG_ROOT ${root}/glslang)
set(ANGLE_SPIRV_CROSS_ROOT ${root}/SPIRV-Cross)
set(ANGLE_BACKEND Vulkan)

set(ANGLE_ROOT ${root}/angle)
set(CHROMIUM_ZLIB_ROOT ${root}/chromium-zlib)

add_subdirectory(${root}/angle-static-cmake angle)


# Fakepoxy

set(glheaderdir ${root}/angle/include)

set(glheaders
    EGL/egl.h
    EGL/eglext.h
    EGL/eglext_angle.h # ANGLE
    EGL/eglplatform.h
    GLES2/gl2.h
    GLES2/gl2ext.h
    GLES2/gl2ext_angle.h # ANGLE
    GLES2/gl2platform.h
    GLES3/gl3.h
    GLES3/gl31.h
    GLES3/gl32.h
    GLES3/gl3platform.h)

include_directories(${glheaderdir})
add_subdirectory(fakepoxy)

# FIXME: Deploy headers at configuration time
#        We should find better location...

foreach(e ${glheaders})
    message(STATUS "Deploy header ${e}")
    configure_file(
        ${glheaderdir}/${e}
        ${CMAKE_INSTALL_PREFIX}/include/${e}
        COPYONLY)
endforeach()

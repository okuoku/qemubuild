#ifndef FAKEPOXY_GL_H
#define FAKEPOXY_GL_H

/* qemu workarounds */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wstrict-prototypes"

#define GL_GLEXT_PROTOTYPES
#define KHRONOS_STATIC

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2ext_angle.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
// }

bool epoxy_has_gl_extension(const char *ext);
bool epoxy_is_desktop_gl(void);
int epoxy_gl_version(void);

/* Types */
typedef double GLclampd;

/* APIs */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wpedantic"
void fakepoxy__unimpl(const char* funcname);
// func(...) macro is GCC extension
#define FEUNIMPL(func) static void func(...){ fakepoxy__unimpl(__func__); } static void func(...)
FEUNIMPL(glTexImage2DMultisample);
#define glBindFragDataLocationIndexed glBindFragDataLocationIndexedEXT
//#define glTextureView glTextureViewOES
FEUNIMPL(glTextureView); /* Conditional? */
#define glFramebufferTexture3D glFramebufferTexture3DOES
FEUNIMPL(glFramebufferTexture1D);
FEUNIMPL(glTextureBarrier);
FEUNIMPL(glColorMaskIndexedEXT);
FEUNIMPL(glClearDepth);
#define glClearTexSubImage glClearTexSubImageEXT
//#define glScissorIndexed glScissorIndexedOES
FEUNIMPL(glScissorIndexed); /* Conditional? */
//#define glViewportIndexedf glViewportIndexedfOES
FEUNIMPL(glViewportIndexedf); /* Conditional? */
FEUNIMPL(glDepthRangeIndexed); /* ??? */
#define glDepthRangeIndexedfOES glDepthRangeIndexedfOES_unimpl
FEUNIMPL(glDepthRangeIndexedfOES_unimpl); /* Conditional? */
FEUNIMPL(glDepthRange);
#define glDepthRangefOES glDepthRangef
#define glVertexAttribDivisorARB glVertexAttribDivisor
FEUNIMPL(glBindVertexBuffers);
#define glBindBufferARB glBindBuffer
FEUNIMPL(glPrimitiveRestartIndex);
FEUNIMPL(glPrimitiveRestartIndexNV);
FEUNIMPL(glMultiDrawArraysIndirectCountARB);
#define glMultiDrawArraysIndirect glMultiDrawArraysIndirectEXT
#define glDrawArraysInstancedBaseInstance glDrawArraysInstancedBaseInstanceEXT
#define glDrawArraysInstancedARB glDrawArraysInstanced
FEUNIMPL(glMultiDrawElementsIndirectCountARB);
#define glMultiDrawElementsIndirect glMultiDrawElementsIndirectEXT
#define glDrawElementsInstancedBaseVertexBaseInstance glDrawElementsInstancedBaseVertexBaseInstanceEXT
#define glDrawElementsInstancedBaseInstance glDrawElementsInstancedBaseInstanceEXT
#define glDrawElementsInstancedARB glDrawElementsInstanced
#define glBlendFuncSeparateiARB glBlendFuncSeparatei
#define glBlendEquationSeparateiARB glBlendEquationSeparatei
FEUNIMPL(glEnableIndexedEXT);
FEUNIMPL(glDisableIndexedEXT);
#define glPolygonMode glPolygonModeNV
#define glClipControl glClipControlEXT
#define glProvokingVertexEXT glProvokingVertexANGLE /* OK? */
FEUNIMPL(glPointParameteri);
FEUNIMPL(glLineStipple);
FEUNIMPL(glClampColor);
#define glGenBuffersARB glGenBuffers
#define glBufferStorage glBufferStorageEXT
FEUNIMPL(glTexImage3DMultisample);
FEUNIMPL(glTexStorage1D);
FEUNIMPL(glTexImage1D);
FEUNIMPL(glPixelZoom);
FEUNIMPL(glWindowPos2i);
FEUNIMPL(glDrawPixels);
FEUNIMPL(glPixelTransferf);
FEUNIMPL(glCompressedTexSubImage1D);
FEUNIMPL(glTexSubImage1D);
FEUNIMPL(glGetnCompressedTexImageARB);
#define glGetCompressedTexImage glGetCompressedTexImageANGLE
FEUNIMPL(glGetnTexImageARB);
#define glGetTexImage glGetTexImageANGLE
#define glReadnPixelsARB glReadnPixelsEXT
FEUNIMPL(glPolygonStipple);
FEUNIMPL(glClipPlane);
FEUNIMPL(glPatchParameterfv);
FEUNIMPL(glGetQueryObjectui64v);
FEUNIMPL(glBeginQueryIndexed);
#define glQueryCounter glQueryCounterEXT
FEUNIMPL(glEndQueryIndexed);
FEUNIMPL(glGetQueryObjectiv);
FEUNIMPL(glGetQueryObjecti64v);
//#define glEndConditionalRender glEndConditionalRenderNV
FEUNIMPL(glEndConditionalRender); /* Conditional? */
#define glEndConditionalRenderNV glEndConditionalRenderNV_unimpl
FEUNIMPL(glEndConditionalRenderNV_unimpl); /* Conditional? */
//#define glBeginConditionalRender glBeginConditionalRenderNV
FEUNIMPL(glBeginConditionalRender); /* Conditional? */
#define glBeginConditionalRenderNV glBeginConditionalRenderNV_unimpl
FEUNIMPL(glBeginConditionalRenderNV_unimpl); /* Conditional? */

/* Downlevels */
/* Angle do not like calling GLES3.2 functions from 3.1 context */
#define glCopyImageSubData glCopyImageSubDataEXT
#define glSamplerParameterIuiv glSamplerParameterIuivEXT

#pragma GCC diagnostic pop

/* Tokens */
#define GL_FRAMEBUFFER_SRGB GL_FRAMEBUFFER_SRGB_EXT
#define GL_TEXTURE_1D_ARRAY 0x8C18
#define GL_BGRA 0x80E1
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_ABGR_EXT 0x8000
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT
#define GL_R3_G3_B2 0x2A10
#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#define GL_RGBA16 0x805B
#define GL_DEPTH24_STENCIL8_EXT GL_DEPTH24_STENCIL8_OES
#define GL_DEPTH_COMPONENT32F 0x8CAC /* GL_DEPTH_COMPONENT32? */
#define GL_R16 0x822A
#define GL_RG16 0x822C
#define GL_ALPHA8 GL_ALPHA8_OES
#define GL_ALPHA8UI_EXT 0x8D7E
#define GL_ALPHA16 0x803E
#define GL_ALPHA_INTEGER 0x8D97
#define GL_LUMINANCE8UI_EXT 0x8D80
#define GL_LUMINANCE_INTEGER_EXT 0x8D9C
#define GL_LUMINANCE_ALPHA8UI_EXT 0x8D81
#define GL_LUMINANCE_ALPHA_INTEGER_EXT 0x8D9D
#define GL_ALPHA8I_EXT 0x8D90
#define GL_LUMINANCE8I_EXT 0x8D92
#define GL_LUMINANCE_ALPHA8I_EXT 0x8D93
#define GL_ALPHA16UI_EXT 0x8D78
#define GL_LUMINANCE_ALPHA16UI_EXT 0x8D7B
#define GL_ALPHA16I_EXT 0x8D8A
#define GL_LUMINANCE16I_EXT 0x8D8C
#define GL_LUMINANCE_ALPHA16I_EXT 0x8D8D
#define GL_ALPHA32UI_EXT 0x8D72
#define GL_LUMINANCE_ALPHA32UI_EXT 0x8D75
#define GL_ALPHA32I_EXT 0x8D84
#define GL_LUMINANCE32I_EXT 0x8D86
#define GL_LUMINANCE_ALPHA32I_EXT 0x8D87
#define GL_ALPHA16F_ARB GL_ALPHA16F_EXT
#define GL_LUMINANCE16F_ARB GL_LUMINANCE16F_EXT
#define GL_LUMINANCE_ALPHA16F_ARB GL_LUMINANCE_ALPHA16F_EXT
#define GL_HALF_FLOAT_ARB 0x140B /* GL_HALF_FLOAT_OES? */
#define GL_ALPHA32F_ARB GL_ALPHA32F_EXT
#define GL_LUMINANCE32F_ARB GL_LUMINANCE32F_EXT
#define GL_LUMINANCE_ALPHA32F_ARB GL_LUMINANCE_ALPHA32F_EXT
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGBA16_SNORM 0x8F9B
#define GL_ALPHA8_SNORM 0x9014
#define GL_LUMINANCE8_ALPHA8_SNORM 0x9016
#define GL_ALPHA16_SNORM 0x9018
#define GL_LUMINANCE16_ALPHA16_SNORM 0x901A
#define GL_COMPRESSED_RED_RGTC1 GL_COMPRESSED_RED_RGTC1_EXT
#define GL_COMPRESSED_SIGNED_RED_RGTC1 GL_COMPRESSED_SIGNED_RED_RGTC1_EXT
#define GL_COMPRESSED_RG_RGTC2 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE
#define GL_BGRA_INTEGER 0x8D9B
#define GL_COMPRESSED_RGBA_BPTC_UNORM GL_COMPRESSED_RGBA_BPTC_UNORM_EXT
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT
#define GL_TEXTURE_RECTANGLE_NV 0x84F5 /* GL_TEXTURE_RECTANGLE_ANGLE? */
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#define GL_TIME_ELAPSED GL_TIME_ELAPSED_EXT
#define GL_ALPHA_TEST 0x0BC0
#define GL_INTERLEAVED_ATTRIBS_EXT GL_INTERLEAVED_ATTRIBS
#define GL_TEXTURE_1D 0x0DE0
#define GL_TEXTURE_1D_ARRAY 0x8C18
#define GL_CLAMP 0x2900 /* CLAMP? */
#define GL_MIRROR_CLAMP_EXT 0x8742
#define GL_MIRROR_CLAMP_TO_BORDER_EXT 0x8912
#define GL_COMPARE_R_TO_TEXTURE 0x884E
#define GL_TEXTURE_LOD_BIAS 0x8501
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#define GL_DEPTH_TEXTURE_MODE 0x884B
#define GL_TEXTURE_SWIZZLE_RGBA 0x8E46
#define GL_DOUBLE 0x140A /* DOUBLE? */
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT_EXT
#define GL_QUERY_BUFFER_BARRIER_BIT 0x00008000
#define GL_QUAD_STRIP 0x0008
#define GL_POLYGON 0x0009
#define GL_PRIMITIVE_RESTART 0x8558 /* FIXME: NOT EXISTS */
#define GL_PRIMITIVE_RESTART_NV 0x8558 
#define GL_PARAMETER_BUFFER_ARB 0x80EE
#define GL_SRC1_COLOR 0x88F9
#define GL_SRC1_ALPHA 0x8589
#define GL_ONE_MINUS_SRC1_COLOR 0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA 0x88FB
#define GL_CLEAR 0x1500
#define GL_NOR 0x1508
#define GL_AND_INVERTED 0x1504
#define GL_COPY_INVERTED 0x150C
#define GL_AND_REVERSE 0x1502
#define GL_XOR 0x1506
#define GL_NAND 0x150E
#define GL_AND 0x1501
#define GL_EQUIV 0x1509
#define GL_NOOP 0x1505
#define GL_OR_INVERTED 0x150D
#define GL_COPY 0x1503
#define GL_OR_REVERSE 0x150B
#define GL_OR 0x1507
#define GL_SET 0x150F
#define GL_COLOR_LOGIC_OP 0x0BF2 /* GL_COLOR_LOGIC_OP_ANGLE? */
#define GL_POINT 0x1B00
#define GL_LINE 0x1B01
#define GL_FILL 0x1B02
#define GL_DEPTH_CLAMP GL_DEPTH_CLAMP_EXT
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_POLYGON_OFFSET_LINE GL_POLYGON_OFFSET_LINE_NV
#define GL_POLYGON_OFFSET_POINT GL_POLYGON_OFFSET_POINT_NV
#define GL_FLAT 0x1D00
#define GL_SMOOTH 0x1D01
#define GL_ZERO_TO_ONE GL_ZERO_TO_ONE_EXT
#define GL_NEGATIVE_ONE_TO_ONE GL_NEGATIVE_ONE_TO_ONE_EXT
#define GL_LOWER_LEFT GL_LOWER_LEFT_EXT
#define GL_POLYGON_STIPPLE 0x0B42
#define GL_POINT_SPRITE 0x8861 /* GL_POINT_SPRITE_OES? */
#define GL_POINT_SPRITE_COORD_ORIGIN 0x8CA0
#define GL_UPPER_LEFT GL_UPPER_LEFT_EXT
#define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
#define GL_CLIP_PLANE0 0x3000
#define GL_LINE_SMOOTH 0x0B20
#define GL_POLYGON_SMOOTH 0x0B41
#define GL_CLAMP_VERTEX_COLOR_ARB 0x891A
#define GL_CLAMP_FRAGMENT_COLOR_ARB 0x891B
#define GL_MULTISAMPLE 0x809D
#define GL_TEXTURE_MAX_ANISOTROPY GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAP_PERSISTENT_BIT GL_MAP_PERSISTENT_BIT_EXT
#define GL_MAP_COHERENT_BIT GL_MAP_COHERENT_BIT_EXT
#define GL_ELEMENT_ARRAY_BUFFER_ARB GL_ELEMENT_ARRAY_BUFFER
#define GL_QUERY_BUFFER 0x9192
#define GL_PIXEL_PACK_BUFFER_ARB GL_PIXEL_PACK_BUFFER_NV
#define GL_DEPTH_SCALE 0x0D1E
#define GL_PACK_INVERT_MESA 0x8758
#define GL_CLAMP_READ_COLOR_ARB 0x891C
#define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8E74
#define GL_PATCH_DEFAULT_INNER_LEVEL 0x8E73
#define GL_SCALED_RESOLVE_NICEST_EXT 0x90BB
#define GL_QUERY_RESULT_AVAILABLE_ARB GL_QUERY_RESULT_AVAILABLE_EXT
#define GL_QUERY_RESULT_ARB GL_QUERY_RESULT_EXT
#define GL_VERTICES_SUBMITTED_ARB 0x82EE
#define GL_VERTEX_SHADER_INVOCATIONS_ARB 0x82F0
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB 0x82F3
#define GL_CLIPPING_INPUT_PRIMITIVES_ARB 0x82F6
#define GL_CLIPPING_OUTPUT_PRIMITIVES_ARB 0x82F7
#define GL_FRAGMENT_SHADER_INVOCATIONS_ARB 0x82F4
#define GL_TESS_CONTROL_SHADER_PATCHES_ARB 0x82F1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB 0x82F2
#define GL_COMPUTE_SHADER_INVOCATIONS_ARB 0x82F5 
#define GL_SAMPLES_PASSED_ARB 0x8914 /* GL_SAMPLES_PASSED? */
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB 0x82ED /* GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW? */
#define GL_QUERY_RESULT_NO_WAIT 0x9194
#define GL_QUERY_WAIT_INVERTED 0x8E17
#define GL_QUERY_WAIT 0x8E13
#define GL_QUERY_NO_WAIT_INVERTED 0x8E18
#define GL_QUERY_NO_WAIT GL_QUERY_NO_WAIT_NV
#define GL_QUERY_BY_REGION_WAIT_INVERTED GL_QUERY_BY_REGION_WAIT_NV
#define GL_QUERY_BY_REGION_WAIT GL_QUERY_BY_REGION_WAIT_NV
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8E1A
#define GL_QUERY_BY_REGION_NO_WAIT GL_QUERY_BY_REGION_NO_WAIT_NV
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88FC
#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB 0x8F9F
#define GL_MAX_VIEWPORTS GL_MAX_VIEWPORTS_OES
#define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#define GL_MAX_IMAGE_SAMPLES 0x906D
#define GL_MAX_TEXTURE_MAX_ANISOTROPY GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX 0x9047
#define GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX 0x9048
#define GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX 0x904A
#define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX 0x904B
#define GL_VBO_FREE_MEMORY_ATI 0x87FB

#define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32_OES
#define GL_LUMINANCE16UI_EXT 0x8D7A
#define GL_LINE_STIPPLE 0x0B24
#define GL_TEXTURE_RECTANGLE GL_TEXTURE_RECTANGLE_NV
#define GL_ARRAY_BUFFER_ARB GL_ARRAY_BUFFER
#define GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB 0x82EC
#define GL_PRIMITIVES_SUBMITTED_ARB 0x82EF


/* qemu workarounds */
#define GL_FRAMEBUFFER_EXT GL_FRAMEBUFFER
#define glFramebufferTexture2DEXT glFramebufferTexture2D

// {
#ifdef __cplusplus
};
#endif

#pragma GCC diagnostic pop

#endif

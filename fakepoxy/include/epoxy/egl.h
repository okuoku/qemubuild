#define EGL_EGLEXT_PROTOTYPES
#define KHRONOS_STATIC

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>

#ifdef __cplusplus
extern "C" {
#endif
// }

#include <stdbool.h>
bool epoxy_has_egl_extension(EGLDisplay dpy, const char *ext);

// {
#ifdef __cplusplus
};
#endif

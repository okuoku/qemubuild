#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2ext_angle.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
// }

bool epoxy_has_gl_extension(const char *ext);
bool epoxy_is_desktop_gl(void);
int epoxy_gl_version(void);

// {
#ifdef __cplusplus
};
#endif

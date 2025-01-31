#include <epoxy/egl.h>
#include <epoxy/gl.h>

/* Fakepoxy */
bool
epoxy_is_desktop_gl(void){
    return false;
}

int 
epoxy_gl_version(void){
    /* FIXME: Implement this */
    return 32;
}

bool 
epoxy_has_gl_extension(const char *extension){
    /* FIXME: Implement this */
    return true;
}

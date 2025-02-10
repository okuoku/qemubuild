#include <epoxy/egl.h>
#include <epoxy/gl.h>

#include <stdio.h>
#include <string.h>

void
fakepoxy__unimpl(const char* func){
    fprintf(stderr, "FAKEPOXY: Unimpl [%s]\n", func);
    return;
}

/* Fakepoxy */
bool
epoxy_is_desktop_gl(void){
    return false;
}

int 
epoxy_gl_version(void){
    /* FIXME: Implement this */
    return 31;
}

bool 
epoxy_has_egl_extension(EGLDisplay dpy, const char *extension){
    /* FIXME: Implement this */
    fprintf(stderr, "FAKEPOXY: EGL extension [%s] => false (hardcoded)\n",
            extension);
    return false;
}

static int
tknlen(const char* tkn){
    int res = 0;

    while((*tkn != ' ') && (*tkn != 0)){
        tkn++;
        res++;
    }

    return res;
}

bool 
epoxy_has_gl_extension(const char *extension){
    const int tgtlen = strnlen(extension, 255);
    const char* lis = (const char*)glGetString(GL_EXTENSIONS);
    const char* p = lis;
    bool res = false;

    if(! lis){
        fprintf(stderr, "FAKEPOXY: No extensions?\n");
        return false;
    }

    while(1){
        //fprintf(stderr, "FAKEPOXY: strstr %s\n", p);
        p = strstr(p, extension);
        if(!p){
            break;
        }
        const int len = tknlen(p);
        if(len == tgtlen){
            res = true;
            break;
        }
        p += len;
    }

    if(res){
        fprintf(stderr, "FAKEPOXY: GL extension [%s] => true\n", extension);
    }else{
        fprintf(stderr, "FAKEPOXY: GL extension [%s] => false\n", extension);
    }

    return res;
}

FROM alpine:edge

# On Alpine linux, meson depends on samurai so we use samurai...
RUN apk update && apk add mingw-w64-gcc ca-certificates git meson cmake py3-yaml py3-setuptools pkgconf

LABEL org.opencontainers.image.source=https://github.com/okuoku/qemubuild

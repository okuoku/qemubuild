find_program(CYGPATH cygpath)
if(CYGPATH)
    execute_process(
        COMMAND cygpath -am ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        OUTPUT_VARIABLE reporoot
        RESULT_VARIABLE rr)
    if(rr)
        message(STATUS "Failed to covert path: ${rr}")
    endif()
else()
    set(reporoot0 ${CMAKE_CURRENT_LIST_DIR})
    # Convert to CMake path for readability
    file(TO_CMAKE_PATH "${reporoot0}" reporoot)
endif()

message(STATUS "reporoot = [${reporoot}]")

function(run_docker script)
    execute_process(COMMAND
        docker run ${isolation} --rm
        "-vtmp:${dockerroot}objs"
        "-vlibs:${dockerroot}libs"
        "-vdist:${dockerroot}dist"
        "-v${reporoot}:${dockerroot}srcs"
        "-v${reporoot}/out:${dockerroot}out"
        qemubuild
        ${dockershell} "${script}"
        RESULT_VARIABLE rr)
    if(rr)
        message(FATAL_ERROR "Failed to run ${script}")
    endif()
endfunction()

function(build_meson projname adddef)
    message(STATUS "Meson setup ${projname}")
    run_docker("PKG_CONFIG_PATH=${cmakeroot}libs/lib/pkgconfig ${shell_crosscompile} ${meson} setup --prefix=${cmakeroot}libs --buildtype=release -Ddefault_library=static ${adddef} ${meson_crosscompile} ${cmakeroot}srcs/deps/${projname} ${cmakeroot}objs/${projname}")
    message(STATUS "Meson compile ${projname}")
    run_docker("${meson} compile -C ${cmakeroot}objs/${projname}")
    run_docker("${meson} install -C ${cmakeroot}objs/${projname}")
endfunction()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out)

if(WIN32)
    set(shell_crosscompile)
    set(meson_crosscompile)
    set(cmake_crosscompile)
    set(qemu_crosscompile)
    set(cmake_crossflag)
    set(isolation --isolation process)
    set(dockerroot "c:\\")
    set(cmakeroot "c:/")
    set(dockershell "c:\\msys64\\msys2_shell.cmd" -here -no-start -ucrt64 -defterm -c)
    set(cmake "/ucrt64/bin/cmake")
    set(meson "/ucrt64/bin/meson")
else()
    message(STATUS "Crosscompiling...")
    set(shell_crosscompile "CC=x86_64-w64-mingw32-gcc CXX=x86_64-w64-mingw32-g++ CFLAGS=-mcrtdll=ucrt CXXFLAGS=-mcrtdll=ucrt PKG_CONFIG=pkg-config")
    set(shell_crosscompile_qemu "CFLAGS=-mcrtdll=ucrt CXXFLAGS=-mcrtdll=ucrt PKG_CONFIG=pkg-config")
    set(meson_crosscompile "--cross-file ${cmakeroot}/srcs/x86_64-w64-mingw32.txt")
    set(qemu_crosscompile "--cross-prefix=x86_64-w64-mingw32- --host-cc=cc --extra-ldflags=-mcrtdll=ucrt")
    set(cmake_crosscompile "-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_C_FLAGS=-mcrtdll=ucrt -DCMAKE_CXX_FLAGS=-mcrtdll=ucrt")
    set(cmake_crossflag "-mcrtdll=ucrt")
    set(isolation)
    set(dockerroot "/")
    set(cmakeroot "/")
    set(dockershell sh -c)
    set(cmake "cmake")
    set(meson "meson")
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out)

# Deps
build_meson(glib "")
build_meson(pixman "")
build_meson(libslirp "")
#build_meson(libepoxy "-Degl=yes")
build_meson(virglrenderer "")

# SDL2
message(STATUS "SDL2 configure")
run_docker("${cmake} -G Ninja ${cmake_crosscompile} -DSDL_STATIC=ON -DSDL_SHARED=OFF -DSDL_OPENGL=OFF -DCMAKE_BUILD_TYPE=RelWithDebInfo '-DCMAKE_C_FLAGS=-DSDL_VIDEO_STATIC_ANGLE -DKHRONOS_STATIC ${cmake_crossflag}' -DCMAKE_INSTALL_PREFIX=${cmakeroot}libs -B ${cmakeroot}objs/SDL2 -S ${cmakeroot}srcs/deps/SDL2")
message(STATUS "SDL2 build")
run_docker("${cmake} --build ${cmakeroot}objs/SDL2")
message(STATUS "SDL2 install")
run_docker("${cmake} --install ${cmakeroot}objs/SDL2")

# qemu
message(STATUS "qemu configure")
# FIXME: Remove --extra-ldflags=-liconv
run_docker("mkdir -p ${cmakeroot}objs/qemu && cd ${cmakeroot}objs/qemu && ${shell_crosscompile_qemu} PKG_CONFIG_PATH=${cmakeroot}libs/lib/pkgconfig ${cmakeroot}srcs/qemu/configure --enable-whpx --enable-system --enable-slirp --enable-vnc --target-list=aarch64-softmmu,arm-softmmu,avr-softmmu,riscv32-softmmu,riscv64-softmmu,x86_64-softmmu --prefix=${cmakeroot}dist --disable-gio --disable-curl --disable-zstd --disable-bzip2 --disable-curses --static --disable-werror \"--extra-cflags=-DLIBSLIRP_STATIC ${cmake_crossflag}\" ${qemu_crosscompile}")
message(STATUS "qemu build")
run_docker("ninja -C ${cmakeroot}objs/qemu")
message(STATUS "qemu install")
run_docker("ninja -C ${cmakeroot}objs/qemu install")

# Extract files
message(STATUS "Extracting...")
run_docker("cp -rp ${cmakeroot}dist/* ${cmakeroot}/out/")
message(STATUS "Done")

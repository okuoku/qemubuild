function(run_docker script)
    execute_process(COMMAND
        docker run --isolation process --rm
        "-vtmp:c:\\objs"
        "-vlibs:c:\\libs"
        "-vdist:c:\\dist"
        "-ve:/repos/qemubuild:c:\\srcs"
        "-ve:/repos/qemubuild/out:c:\\out"
        qemubuild 
        "c:\\msys64\\msys2_shell.cmd" -here -no-start -ucrt64 -defterm 
        -c "${script}"
        RESULT_VARIABLE rr)
    if(rr)
        message(FATAL_ERROR "Failed to run ${script}")
    endif()
endfunction()

function(build_meson projname adddef)
    message(STATUS "Meson setup ${projname}")
    run_docker("PKG_CONFIG_PATH=c:/libs/lib/pkgconfig /ucrt64/bin/meson setup  --prefix=c:/libs --buildtype=release -Ddefault_library=static ${adddef} c:/srcs/deps/${projname} c:/objs/${projname}")
    message(STATUS "Meson compile ${projname}")
    run_docker("/ucrt64/bin/meson compile -C c:/objs/${projname}")
    run_docker("/ucrt64/bin/meson install -C c:/objs/${projname}")
endfunction()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out)

# Deps
build_meson(glib "")
build_meson(pixman "")
build_meson(libslirp "")
build_meson(libepoxy "-Degl=yes")
build_meson(virglrenderer "")

# SDL2
message(STATUS "SDL2 configure")
run_docker("/ucrt64/bin/cmake -G Ninja -DSDL_STATIC=ON -DSDL_SHARED=OFF -DSDL_OPENGL=OFF -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=c:/libs -B c:/objs/SDL2 -S c:/srcs/deps/SDL2")
message(STATUS "SDL2 build")
run_docker("/ucrt64/bin/cmake --build c:/objs/SDL2")
message(STATUS "SDL2 install")
run_docker("/ucrt64/bin/cmake --install c:/objs/SDL2")

# qemu
message(STATUS "qemu configure")
run_docker("mkdir -p c:/objs/qemu && cd c:/objs/qemu && PKG_CONFIG_PATH=c:/libs/lib/pkgconfig c:/srcs/qemu/configure --enable-whpx --enable-system --enable-slirp --enable-vnc --target-list=aarch64-softmmu,arm-softmmu,avr-softmmu,riscv32-softmmu,riscv64-softmmu,x86_64-softmmu --prefix=c:/dist --disable-gio --disable-curl --disable-zstd --disable-bzip2 --disable-curses --static --extra-ldflags=-liconv --disable-werror --extra-cflags=-DLIBSLIRP_STATIC")
message(STATUS "qemu build")
run_docker("ninja -C c:/objs/qemu")
message(STATUS "qemu install")
run_docker("ninja -C c:/objs/qemu install")

# Extract files
message(STATUS "Extracting...")
run_docker("cp -rp c:/dist/* c:/out/")
message(STATUS "Done")

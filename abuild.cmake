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
        docker run --isolation process --rm
        "-vtmp:c:\\objs"
        "-vlibs:c:\\libs"
        "-vdist:c:\\dist"
        "-v${reporoot}:c:\\srcs"
        "-v${reporoot}/out:c:\\out"
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

# Anglembed
message(STATUS "Anglembed configure")
run_docker("/ucrt64/bin/cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=c:/libs -B c:/objs/anglembed -S c:/srcs/anglembed")
message(STATUS "Anglembed build")
run_docker("/ucrt64/bin/cmake --build c:/objs/anglembed")

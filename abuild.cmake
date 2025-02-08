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
    run_docker("PKG_CONFIG_PATH=c:/libs/lib/pkgconfig /ucrt64/bin/meson setup  --prefix=c:/libs --buildtype=release -Ddefault_library=static ${adddef} c:/srcs/deps/${projname} c:/objs/${projname}")
    message(STATUS "Meson compile ${projname}")
    run_docker("/ucrt64/bin/meson compile -C c:/objs/${projname}")
    run_docker("/ucrt64/bin/meson install -C c:/objs/${projname}")
endfunction()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out)

if(WIN32)
    set(cmake_crosscompile)
    set(isolation --isolation process)
    set(dockerroot "c:\\")
    set(cmakeroot "c:/")
    set(dockershell "c:\\msys64\\msys2_shell.cmd" -here -no-start -ucrt64 -defterm -c)
    set(cmake "/ucrt64/bin/cmake")
else()
    message(STATUS "Crosscompiling...")
    set(cmake_crosscompile "-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_C_FLAGS=-mcrtdll=ucrt -DCMAKE_CXX_FLAGS=-mcrtdll=ucrt")
    set(isolation)
    set(dockerroot "/")
    set(cmakeroot "/")
    set(dockershell sh -c)
    set(cmake "cmake")
endif()

# Anglembed
message(STATUS "Anglembed configure")
run_docker("${cmake} -G Ninja ${cmake_crosscompile} -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=${cmakeroot}libs -B ${cmakeroot}objs/anglembed -S ${cmakeroot}srcs/anglembed")
message(STATUS "Anglembed build")
run_docker("${cmake} --build ${cmakeroot}objs/anglembed")

cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

project(libgsf
        DESCRIPTION "libgsf"
        LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library(libgsf SHARED)

#target_compile_options(libgsf PRIVATE
#                       -Wall -Werror=init-self -Werror=missing-include-dirs
#			 -Wsign-compare -Werror=pointer-arith
#			 -Wchar-subscripts -Wwrite-strings
#			 -Wdeclaration-after-statement -Wnested-externs
#			 -Wmissing-noreturn
#			 -Werror=missing-prototypes -Werror=nested-externs
#			 -Werror=implicit-function-declaration
#			 -Wmissing-declarations -Wno-pointer-sign
#			 -Werror=format-security -Wbitwise -Wcast-to-as
#			 -Wdefault-bitfield-sign -Wdo-while -Wparen-string
#			 -Wptr-subtraction-blows -Wreturn-void -Wtypesign
#			 -Wstrict-prototypes -Wno-error=format-nonliteral)

target_sources(libgsf
               PRIVATE
               gsf/gsf-infile-msvba.c gsf/gsf-input-gzip.h gsf/gsf-input.h gsf/gsf-outfile-stdio.h gsf/gsf-output-impl.h gsf/gsf-timestamp.c
               gsf/gsf-infile-msvba.h gsf/gsf-input-http.c gsf/gsf-libxml.c gsf/gsf-outfile-zip.c gsf/gsf-output-iochannel.c gsf/gsf-timestamp.h
               gsf/gsf-blob.c gsf/gsf-infile-stdio.c gsf/gsf-input-http.h gsf/gsf-libxml.h gsf/gsf-outfile-zip.h gsf/gsf-output-iochannel.h gsf/gsf-utils.c
               gsf/gsf-blob.h gsf/gsf-infile-stdio.h gsf/gsf-input-impl.h gsf/gsf-meta-names.h gsf/gsf-outfile.c gsf/gsf-output-memory.c gsf/gsf-utils.h
               gsf/gsf-clip-data.c gsf/gsf-infile-tar.c gsf/gsf-input-iochannel.c gsf/gsf-msole-impl.h gsf/gsf-outfile.h gsf/gsf-output-memory.h gsf/gsf-zip-impl.h
               gsf/gsf-clip-data.h gsf/gsf-infile-tar.h gsf/gsf-input-iochannel.h gsf/gsf-msole-utils.c gsf/gsf-output-bzip.c gsf/gsf-output-stdio.c gsf/gsf-zip-utils.c
               gsf/gsf-doc-meta-data.c gsf/gsf-infile-zip.c gsf/gsf-input-memory.c gsf/gsf-msole-utils.h gsf/gsf-output-bzip.h gsf/gsf-output-stdio.h gsf/gsf.h
               gsf/gsf-doc-meta-data.h gsf/gsf-infile-zip.h gsf/gsf-input-memory.h gsf/gsf-open-pkg-utils.c gsf/gsf-output-csv.c gsf/gsf-output.c ${CMAKE_BINARY_DIR}/include/version.c
               gsf/gsf-docprop-vector.c gsf/gsf-infile.c gsf/gsf-input-proxy.c gsf/gsf-open-pkg-utils.h gsf/gsf-output-csv.h gsf/gsf-output.h
               gsf/gsf-docprop-vector.h gsf/gsf-infile.h gsf/gsf-input-proxy.h gsf/gsf-opendoc-utils.c gsf/gsf-output-gio.c gsf/gsf-priv.c
               gsf/gsf-fwd.h gsf/gsf-input-bzip.c gsf/gsf-input-stdio.c gsf/gsf-opendoc-utils.h gsf/gsf-output-gio.h gsf/gsf-priv.h
               gsf/gsf-impl-utils.h gsf/gsf-input-bzip.h gsf/gsf-input-stdio.h gsf/gsf-outfile-impl.h gsf/gsf-output-gzip.c gsf/gsf-shared-memory.c
               gsf/gsf-infile-impl.h gsf/gsf-input-gio.c gsf/gsf-input-textline.c gsf/gsf-outfile-msole.c gsf/gsf-output-gzip.h gsf/gsf-shared-memory.h
               gsf/gsf-infile-msole.c gsf/gsf-input-gio.h gsf/gsf-input-textline.h gsf/gsf-outfile-msole.h gsf/gsf-output-iconv.c gsf/gsf-structured-blob.c
               gsf/gsf-infile-msole.h gsf/gsf-input-gzip.c gsf/gsf-input.c gsf/gsf-outfile-stdio.c gsf/gsf-output-iconv.h gsf/gsf-structured-blob.h
               )

target_include_directories(libgsf PUBLIC ${CMAKE_BINARY_DIR}/include ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/gsf ${glib_INCLUDE_DIRS})

set(LIBGSF_MAJOR_VERSION 1)
set(LIBGSF_MINOR_VERSION 14)
set(LIBGSF_MICRO_VERSION 53)

file(CONFIGURE OUTPUT include/version.c CONTENT "\
int libgsf_major_version = @LIBGSF_MAJOR_VERSION@;	/* The ABI version */
int libgsf_minor_version = @LIBGSF_MINOR_VERSION@;	/* The API version */
int libgsf_micro_version = @LIBGSF_MICRO_VERSION@;	/* bug fixes */
")

configure_file(${CMAKE_SOURCE_DIR}/gsf-config.h.in.1 ${CMAKE_BINARY_DIR}/include/gsf-config.h COPYONLY)

find_package(PkgConfig REQUIRED)
find_package(ZLIB)
find_package(BZip2)
find_package(LibXml2)
find_package(glib REQUIRED)

target_link_libraries(libgsf PRIVATE ZLIB::ZLIB BZip2::BZip2 LibXml2::LibXml2
                      PUBLIC glib::glib)
add_subdirectory(tools)
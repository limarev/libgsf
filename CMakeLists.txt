cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

project(gsf
        DESCRIPTION "gsf"
        VERSION 1.14.53
        LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_library(gsf SHARED)

#target_compile_options(gsf PRIVATE
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

target_sources(gsf
               PRIVATE
               ${CMAKE_BINARY_DIR}/version/version.c
               gsf/gsf-blob.c
               gsf/gsf-clip-data.c
               gsf/gsf-doc-meta-data.c
               gsf/gsf-docprop-vector.c
               gsf/gsf-infile-msole.c
               gsf/gsf-infile-stdio.c
               gsf/gsf-infile-tar.c
               gsf/gsf-infile-zip.c
               gsf/gsf-infile.c
               gsf/gsf-input-bzip.c
               gsf/gsf-input-gio.c
               gsf/gsf-input-gzip.c
               gsf/gsf-input-http.c
               gsf/gsf-input-iochannel.c
               gsf/gsf-input-memory.c
               gsf/gsf-input-proxy.c
               gsf/gsf-input-stdio.c
               gsf/gsf-input-textline.c
               gsf/gsf-input.c
               gsf/gsf-libxml.c
               gsf/gsf-msole-impl.h
               gsf/gsf-msole-utils.c
               gsf/gsf-open-pkg-utils.c
               gsf/gsf-opendoc-utils.c
               gsf/gsf-outfile-msole.c
               gsf/gsf-outfile-stdio.c
               gsf/gsf-outfile-zip.c
               gsf/gsf-outfile.c
               gsf/gsf-output-bzip.c
               gsf/gsf-output-csv.c
               gsf/gsf-output-gio.c
               gsf/gsf-output-gzip.c
               gsf/gsf-output-iconv.c
               gsf/gsf-output-iochannel.c
               gsf/gsf-output-memory.c
               gsf/gsf-output-stdio.c
               gsf/gsf-output.c
               gsf/gsf-priv.c
               gsf/gsf-priv.h
               gsf/gsf-shared-memory.c
               gsf/gsf-structured-blob.c
               gsf/gsf-timestamp.c
               gsf/gsf-utils.c
               gsf/gsf-zip-impl.h
               gsf/gsf-zip-utils.c
               gsf/gsf-infile-msvba.c

               PUBLIC FILE_SET HEADERS FILES
               gsf/gsf-clip-data.h
               gsf/gsf-doc-meta-data.h
               gsf/gsf-docprop-vector.h
               gsf/gsf-fwd.h
               gsf/gsf-impl-utils.h
               gsf/gsf-infile-impl.h
               gsf/gsf-infile-msole.h
               gsf/gsf-blob.h
               gsf/gsf-fwd.h
               gsf/gsf-infile-msvba.h
               gsf/gsf-infile-stdio.h
               gsf/gsf-infile-tar.h
               gsf/gsf-infile-zip.h
               gsf/gsf-infile.h
               gsf/gsf-input-bzip.h
               gsf/gsf-input-gio.h
               gsf/gsf-input-gzip.h
               gsf/gsf-input-http.h
               gsf/gsf-input-impl.h
               gsf/gsf-input-iochannel.h
               gsf/gsf-input-memory.h
               gsf/gsf-input-proxy.h
               gsf/gsf-input-stdio.h
               gsf/gsf-input-textline.h
               gsf/gsf-input.h
               gsf/gsf-libxml.h
               gsf/gsf-meta-names.h
               gsf/gsf-msole-utils.h
               gsf/gsf-open-pkg-utils.h
               gsf/gsf-opendoc-utils.h
               gsf/gsf-outfile-impl.h
               gsf/gsf-outfile-msole.h
               gsf/gsf-outfile-stdio.h
               gsf/gsf-outfile-zip.h
               gsf/gsf-outfile.h
               gsf/gsf-output-bzip.h
               gsf/gsf-output-csv.h
               gsf/gsf-output-gio.h
               gsf/gsf-output-gzip.h
               gsf/gsf-output-iconv.h
               gsf/gsf-output-impl.h
               gsf/gsf-output-iochannel.h
               gsf/gsf-output-memory.h
               gsf/gsf-output-stdio.h
               gsf/gsf-output.h
               gsf/gsf-shared-memory.h
               gsf/gsf-structured-blob.h
               gsf/gsf-timestamp.h
               gsf/gsf-utils.h
               gsf/gsf.h
               )


file(CONFIGURE OUTPUT version/version.c CONTENT "\
int libgsf_major_version = @PROJECT_VERSION_MAJOR@;	/* The ABI version */
int libgsf_minor_version = @PROJECT_VERSION_MINOR@;	/* The API version */
int libgsf_micro_version = @PROJECT_VERSION_PATCH@;	/* bug fixes */
")

configure_file(${CMAKE_SOURCE_DIR}/gsf-config.h.in.1 ${CMAKE_BINARY_DIR}/include/gsf-config.h COPYONLY)

find_package(ZLIB)
find_package(BZip2)
find_package(LibXml2)
find_package(glib REQUIRED)

target_include_directories(gsf
                           PRIVATE ${CMAKE_BINARY_DIR}/version ${CMAKE_BINARY_DIR}/include ${CMAKE_SOURCE_DIR}/gsf
                           INTERFACE $<INSTALL_INTERFACE:include>)

target_link_libraries(gsf
                      PRIVATE ZLIB::ZLIB BZip2::BZip2 LibXml2::LibXml2
                      PUBLIC glib::glib)

set_target_properties(gsf
                      PROPERTIES
                      INSTALL_RPATH $ORIGIN)

#add_subdirectory(tools)

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

include(CPack)
include(GNUInstallDirs)

install(TARGETS gsf
        EXPORT gsf_targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FILE_SET HEADERS)

# активируем EXPORT_PACKAGE_DEPENDENCIES
set(CMAKE_EXPERIMENTAL_EXPORT_PACKAGE_DEPENDENCIES "1942b4fa-b2c5-4546-9385-83f254070067")
install(EXPORT gsf_targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gsf
        NAMESPACE gsf::
        EXPORT_PACKAGE_DEPENDENCIES)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/gsf-config.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/gsf-config.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gsf
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/gsf-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/gsf-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/gsf-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gsf)
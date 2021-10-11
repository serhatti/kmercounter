project(kmercounter)
include(ExternalProject)
cmake_minimum_required(VERSION 2.8.8)
find_package(Git REQUIRED)
#on debian syst. install zlib1g-dev .. necessary to run on gzipped fast files
find_package( ZLIB REQUIRED )
add_compile_options("-Wfatal-errors")

#where shared libs headers and executables go in
set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install)

set(EXTERNAL_DIR ${CMAKE_CURRENT_BINARY_DIR}/externals)

#we only need kseq.h header (include only...)
ExternalProject_Add(
    seqtk
    PREFIX ${EXTERNAL_DIR}
    GIT_REPOSITORY https://github.com/lh3/seqtk.git
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)


ExternalProject_Add(
    googlesparsehash
    PREFIX ${EXTERNAL_DIR}
    GIT_REPOSITORY https://github.com/sparsehash/sparsehash
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_DIR}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    LOG_DOWNLOAD ON
    #INSTALL_DIR ${INSTALL_DIR}

)

ExternalProject_Add(
    libbf
    PREFIX ${EXTERNAL_DIR}
    GIT_REPOSITORY  https://github.com/mavam/libbf
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    UPDATE_COMMAND ""
    LOG_DOWNLOAD ON
    INSTALL_COMMAND make install
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
    #INSTALL_DIR ${INSTALL_DIR}
)

ExternalProject_Add(
    anyoption
    #... this project has no install target out of the box ....
    #I dont want to modify that project ,so  will add a custom command for installation below
    PREFIX ${EXTERNAL_DIR}
    GIT_REPOSITORY  https://github.com/hackorama/AnyOption.git
    TIMEOUT 10
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ""
    LOG_DOWNLOAD ON
    #package natively has no install target so do nothing other than printing a message
    INSTALL_COMMAND cmake -E echo " skipping install step for anyoption ..."

)


# workaround for anyoption.... deploy installation files manually
#probably must migrate into a cl parser with a better build
#probably if something breaks in the future it will be because of this below
add_custom_command(
        TARGET anyoption POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${EXTERNAL_DIR}/src/anyoption/libanyoption.so
                ${INSTALL_DIR}/lib/libanyoption.so

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${EXTERNAL_DIR}/src/anyoption/anyoption.h
                ${INSTALL_DIR}/include/anyoption/anyoption.h
)
#deploy kseq.h (include-only header)
add_custom_command(
        TARGET seqtk POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${EXTERNAL_DIR}/src/seqtk/kseq.h
                ${INSTALL_DIR}/include/seqtk/kseq.h
)



#dump a small setup script to append to path and lib paths osx/and linux only
if(UNIX)
  FILE(WRITE ${INSTALL_DIR}/setup.sh "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${INSTALL_DIR}/lib\n")
endif()
if(APPLE)
  FILE(WRITE ${INSTALL_DIR}/setup.sh "export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:${INSTALL_DIR}/lib\n")
endif()
FILE(APPEND ${INSTALL_DIR}/setup.sh "export PATH=$PATH:${INSTALL_DIR}/bin")

#folder for shared libraries being developed
add_subdirectory(source/kmercounter)
# executables reside below
add_subdirectory(source/utils)

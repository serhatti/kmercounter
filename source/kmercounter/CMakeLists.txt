include_directories(${INSTALL_DIR}/include)
set(LIBNAME KmerCounter)

FILE(GLOB CXXS *.cxx)
FILE(GLOB HEADERS *.h)
add_library(${LIBNAME} SHARED ${HEADERS} ${CXXS})
#add those dependency for multithreaded build with -j
add_dependencies(${LIBNAME} libbf googlesparsehash)
#deploy the *.so on the  fly
set_target_properties(${LIBNAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR}/lib)

#deploy header files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${INSTALL_DIR}/include/
    FILES_MATCHING
        PATTERN *.h
)

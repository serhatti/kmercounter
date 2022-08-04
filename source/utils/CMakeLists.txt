#author : Serhat Istin	
#	  istins@gmail.com
include_directories(${INSTALL_DIR}/include)
link_directories(${INSTALL_DIR}/lib )

FILE(GLOB appsources *.cpp)
FILE(GLOB appheaders *.h)


# ... any .cpp file put here is supposed to be an executable application linked to the libraries below
#appname is the same as the source name but .cpp extensions removed
#all cpp files are built into its executable & linked automatically

foreach( appfile ${appsources})
    get_filename_component(appname ${appfile} NAME_WE ) 
    add_executable(${appname} ${appfile})
    set_target_properties(${appname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR}/bin)
    add_dependencies(${appname}  KmerCounter anyoption seqtk)
    target_link_libraries(${appname} -lKmerCounter -lanyoption -lbf -lz)     
    endforeach( appfile ${appsources})
#or one may do it one by one per file and have full control of  what to link include  to etc ...


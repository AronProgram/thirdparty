
file(GLOB_RECURSE  GLOBAL_INCLUDES  "*.h" )
file(GLOB_RECURSE  GLOBAL_SOURCES   "*.cpp" "*.h" )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pccl_logicrpc STATIC ${GLOBAL_SOURCES} )

include_directories("." 
                    "./protocol/websocket" 
					"/usr/local/tars/cpp/include"
					"/usr/local/include/json"
					)


target_link_libraries(	pccl_logicrpc 	
						"/usr/local/tars/cpp/lib/libtarsservant.a" 
						"/usr/local/tars/cpp/lib/libtarsparse.a" 
						"/usr/local/tars/cpp/lib/libtarsutil.a"
						"/usr/local/lib/libjsoncpp.a"
						pthread
						)


install(TARGETS  pccl_logicrpc         DESTINATION  /usr/local/tars/cpp/lib)	
install(FILES   ${GLOBAL_INCLUDES}     DESTINATION  /usr/local/tars/cpp/include/pccl)	


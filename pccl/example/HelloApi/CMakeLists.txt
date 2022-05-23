
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_executable(HelloApi ${GLOBAL_SOURCES})


include_directories("./"  
					"./api"
					"/usr/local/tars/cpp/include"
					"/usr/local/include/json"	
					"${PROJECT_SOURCE_DIR}/src/framework/logicrpc"
					)


target_link_libraries(HelloApi 
					  pccl_logicrpc
					  
					 )




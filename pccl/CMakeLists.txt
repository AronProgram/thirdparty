#################################################### 
## project 
## 
####################################################
cmake_minimum_required (VERSION 3.0)
project (PCCL) 


####################################################
## third library
####################################################

include("${PROJECT_SOURCE_DIR}/cmake/BuildFunction.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/Common.cmake")



####################################################
## add dir
## 
####################################################

add_subdirectory(src)
#add_subdirectory(example)



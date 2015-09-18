project(rightsfs)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/rightsfs SRC_LIST)
aux_source_directory(./src/rightsfs/common SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

 find_package(FUSE 2.8 REQUIRED)

 if(FUSE_FOUND)
 add_definitions(${FUSE_DEFINITIONS})
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-DFUSE_USE_VERSION=28)
 include_directories(${FUSE_INCLUDE_DIRS})
 target_link_libraries(${PROJECT_NAME} ${FUSE_LIBRARIES})
 endif()

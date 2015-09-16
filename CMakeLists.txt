project(zcachefs)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES(
        pthread
)


 find_package(FUSE 2.6 REQUIRED)

 if(FUSE_FOUND)
 add_definitions(${FUSE_DEFINITIONS})
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-DFUSE_USE_VERSION=26)
 include_directories(${FUSE_INCLUDE_DIRS})
 target_link_libraries(${PROJECT_NAME} ${FUSE_LIBRARIES})
 endif()

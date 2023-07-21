cmake_minimum_required (VERSION 3.26)
project (tiler VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set (SOURCES ${PROJECT_SOURCE_DIR}/src/main.c ${PROJECT_SOURCE_DIR}/src/tiler.c)
add_executable (tiler ${SOURCES})
target_link_libraries(tiler ${SDL2_LIBRARIES})

target_include_directories (tiler PUBLIC ${PROJECT_SOURCE_DIR}/src/include)
configure_file (${PROJECT_SOURCE_DIR}/src/include/tconf.h.in ${PROJECT_SOURCE_DIR}/src/include/tconf.h)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED true)

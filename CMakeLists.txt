cmake_minimum_required(VERSION 2.6)

PROJECT (time_wheel)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(./include)
########################################################################################core
SET(CORE_LIST ${PROJECT_SOURCE_DIR})
FILE(GLOB_RECURSE LIBRARY_LIST_SRC ${CORE_LIST}/src/*.cpp) 
FILE(GLOB_RECURSE LIBRARY_LIST_INCLUDE ${CORE_LIST}/include/*.h) 
FILE(GLOB_RECURSE EXAMPLE_LIST_SRC ${CORE_LIST}/example/*.cpp) 
SOURCE_GROUP("Library Header Files" FILES ${LIBRARY_LIST_INCLUDE})
SOURCE_GROUP("Library Source Files" FILES ${LIBRARY_LIST_SRC})
SOURCE_GROUP("Example Source Files" FILES ${EXAMPLE_LIST_SRC})

ADD_EXECUTABLE(timewheel 
${LIBRARY_LIST_INCLUDE}
${LIBRARY_LIST_SRC}
${EXAMPLE_LIST_SRC}
)




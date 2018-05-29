project(STASM)

#**************************************************************************************************
# General cMake settings
#**************************************************************************************************
cmake_minimum_required(VERSION 2.8)

#**************************************************************************************************
# Preprocessor definitions
#**************************************************************************************************
if (CMAKE_CL_64)
 add_definitions(-DWIN64)
 set(PLATFORM x64)
else (CMAKE_CL_64)
 set(PLATFORM x86)
endif (CMAKE_CL_64)

if(WIN32)
  ADD_DEFINITIONS(-DIGTB_EXPORTS)
  ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
endif(WIN32)

enable_testing()

#**************************************************************************************************
# Search for OpenCV
#**************************************************************************************************
find_package(OpenCV REQUIRED PATHS /usr/local/opt/opencv3)
message(STATUS " OpenCV library version: ${OpenCV_VERSION}")
if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

LINK_DIRECTORIES(
  ${OpenCV_LIB_DIR}
)

SET(STASM_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

SET(OBJ_STASM
${STASM_BASE_DIR}/stasm/asm.cpp
${STASM_BASE_DIR}/stasm/classicdesc.cpp
${STASM_BASE_DIR}/stasm/convshape.cpp
${STASM_BASE_DIR}/stasm/err.cpp
${STASM_BASE_DIR}/stasm/eyedet.cpp
${STASM_BASE_DIR}/stasm/eyedist.cpp
${STASM_BASE_DIR}/stasm/faceroi.cpp
${STASM_BASE_DIR}/stasm/hat.cpp
${STASM_BASE_DIR}/stasm/hatdesc.cpp
${STASM_BASE_DIR}/stasm/landmarks.cpp
${STASM_BASE_DIR}/stasm/misc.cpp
${STASM_BASE_DIR}/stasm/pinstart.cpp
${STASM_BASE_DIR}/stasm/print.cpp
${STASM_BASE_DIR}/stasm/shape17.cpp
${STASM_BASE_DIR}/stasm/shapehacks.cpp
${STASM_BASE_DIR}/stasm/shapemod.cpp
${STASM_BASE_DIR}/stasm/startshape.cpp
${STASM_BASE_DIR}/stasm/stasm.cpp
${STASM_BASE_DIR}/stasm/stasm_lib.cpp
)

SET(OBJ_MOD1
${STASM_BASE_DIR}/stasm/MOD_1/facedet.cpp
${STASM_BASE_DIR}/stasm/MOD_1/initasm.cpp
)

include_directories(${STASM_BASE_DIR}/stasm)
include_directories(${STASM_BASE_DIR}/stasm/MOD_1)

SET(STASM_INCLUDE_DIRS
${STASM_BASE_DIR}/stasm
${STASM_BASE_DIR}/stasm/MOD_1
)

SET(LIBS ${OpenCV_LIBS})

set(STASM_LIB stasm)
add_library(${STASM_LIB} ${OBJ_MOD1} ${OBJ_STASM})
target_link_libraries(${STASM_LIB} ${LIBS})

SET(STASM_UTIL stasm_util)
add_executable(${STASM_UTIL} stasm_util.cpp)
target_link_libraries(${STASM_UTIL} ${STASM_LIB} ${LIBS})

#**************************************************************************************************
# Test
#**************************************************************************************************

add_test(stasm_util -f ../data ../data/testface.jpg)

#**************************************************************************************************
# Generate batch files for examples
#**************************************************************************************************
#setup Config.cmake
configure_file(STASMConfig.cmake.in
  "${PROJECT_BINARY_DIR}/STASMConfig.cmake" @ONLY)

INSTALL(
FILES ${PROJECT_BINARY_DIR}/STASMConfig.cmake
DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/
COMPONENT dev)

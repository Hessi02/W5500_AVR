set(INC_DIR "include")
set(SRC_DIR "src")

file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS "${INC_DIR}/*.h"   "${SRC_DIR}/*.h" 
                                          "${INC_DIR}/*.hpp" "${SRC_DIR}/*.hpp" 
                                          "${INC_DIR}/*.c"   "${SRC_DIR}/*.c" 
                                          "${INC_DIR}/*.cpp" "${SRC_DIR}/*.cpp")

add_library(W5500_AVR ${INCLUDE_FILES})

set_target_properties(W5500_AVR PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
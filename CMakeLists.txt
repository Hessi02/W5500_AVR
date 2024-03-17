file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS "inc/*.h"   "src/*.h" 
                                          "inc/*.hpp" "src/*.hpp" 
                                          "inc/*.c"   "src/*.c" 
                                          "inc/*.cpp" "src/*.cpp")

add_library(W5500_AVR ${INCLUDE_FILES})

set_target_properties(W5500_AVR PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
add_library(AVR_VECTOR STATIC "heap.hpp" "element.hpp" "vector.hpp")

set_target_properties(AVR_VECTOR PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(AVR_VECTOR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
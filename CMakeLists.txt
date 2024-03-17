add_library(W5500_AVR)

set_target_properties(W5500_AVR PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
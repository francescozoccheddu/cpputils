cmake_minimum_required (VERSION 3.12)

# library

add_library (cpputils INTERFACE)

set_target_properties (cpputils PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)

target_include_directories (cpputils
    INTERFACE "./include"
)

target_compile_features (cpputils INTERFACE cxx_std_20)

# testbench

option (CPPUTILS_ENABLE_TESTBENCH OFF)

if (CPPUTILS_ENABLE_TESTBENCH)

add_executable (cpputils-testbench 
    "./testbench.cpp" 
)

target_link_libraries (cpputils-testbench 
    PRIVATE cpputils
)

endif()
cmake_minimum_required(VERSION 3.25.0)
project(CppTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)   
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CppTestClassSetup src/main_class_setup.cpp)
add_executable(CppTestPointers src/main_pointers.cpp)
add_executable(CppTestDataStructures src/main_data_structures.cpp)
add_executable(CppTestTemplates src/main_templates.cpp)
add_executable(CppTestNumerics src/main_numerics.cpp)
add_executable(CppTestOop src/main_oop.cpp)

# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
# set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
# if(WIN32)
#     set_target_properties(CppTestClassSetup PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
#     set_target_properties(CppTestPointers PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
#     set_target_properties(CppTestDataStructures PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
# endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

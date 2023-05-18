cmake_minimum_required(VERSION 3.16)
project(ApexCore VERSION 0.1.0)

include(CTest)
enable_testing()


# profile cpp options
add_compile_options($<$<CONFIG:Debug>:-g>)
add_compile_options($<$<CONFIG:Release>:-O3>)
add_compile_options($<$<CONFIG:Release>:-DNDEBUG>)

# cpp std
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# add conan generator folder
list(PREPEND CMAKE_PREFIX_PATH "${CONAN_GENERATORS_FOLDER}")
list(PREPEND CMAKE_PREFIX_PATH "${CPPSHIP_DEPS_DIR}")

# Package finders
find_package(RapidJSON REQUIRED)
find_package(glfw3 REQUIRED)

add_library(ApexCore_deps INTERFACE)
target_link_libraries(ApexCore_deps INTERFACE rapidjson)
target_link_libraries(ApexCore_deps INTERFACE glfw)

# LIB
add_library(ApexCore_lib /home/gameforabit/Documents/ApexCore/lib/ApexCore.cpp
/home/gameforabit/Documents/ApexCore/lib/Globals.cpp
/home/gameforabit/Documents/ApexCore/lib/Graphics/Color.cpp
/home/gameforabit/Documents/ApexCore/lib/glad.cpp)
set_target_properties(ApexCore_lib PROPERTIES OUTPUT_NAME "ApexCore")

target_include_directories(ApexCore_lib PUBLIC /home/gameforabit/Documents/ApexCore/include)

target_link_libraries(ApexCore_lib PUBLIC ApexCore_deps)

# Dev Package finders
add_library(ApexCore_dev_deps INTERFACE)
target_link_libraries(ApexCore_dev_deps INTERFACE ApexCore_deps)

# Tests
find_package(GTest REQUIRED)

add_executable(Log_test /home/gameforabit/Documents/ApexCore/tests/Log.cpp)
target_link_libraries(Log_test PRIVATE GTest::gtest_main)
target_link_libraries(Log_test PRIVATE ApexCore_lib)
target_link_libraries(Log_test PRIVATE ApexCore_dev_deps)
add_test(Log_test Log_test)

add_executable(window_creation_test /home/gameforabit/Documents/ApexCore/tests/window_creation.cpp)
target_link_libraries(window_creation_test PRIVATE GTest::gtest_main)
target_link_libraries(window_creation_test PRIVATE ApexCore_lib)
target_link_libraries(window_creation_test PRIVATE ApexCore_dev_deps)
add_test(window_creation_test window_creation_test)

# Groups
add_custom_target(cppship_group_binaries DEPENDS ApexCore_lib)
add_custom_target(cppship_group_examples DEPENDS )
add_custom_target(cppship_group_benches DEPENDS )
add_custom_target(cppship_group_tests DEPENDS Log_test window_creation_test)

# Footer
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

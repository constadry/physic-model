cmake_minimum_required(VERSION 3.17)
project(Physic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(Physic main.cpp Object.hpp Ball.hpp Cannon.hpp Block.hpp Land.hpp Header.hpp numbers.hpp)

set(SFML_DIR "C:\\Users\\behap\\CLionProjects\\lib\\sfml\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(Physic sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
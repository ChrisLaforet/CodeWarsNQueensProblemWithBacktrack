cmake_minimum_required(VERSION 3.20)
project(CodeWarsNQueensProblem)

include_directories(c:\\GoogleTest\\h\\)
set(CMAKE_CXX_STANDARD 14)

link_directories(c:\\GoogleTest\\lib\\)
add_executable(CodeWarsNQueensProblem n_queens.cpp n_queens.h unittests.cpp)
set_property(TARGET CodeWarsNQueensProblem PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_link_libraries(CodeWarsNQueensProblem gtestd gtest_maind)
#link_libraries(CodeWarsNQueensProblem gtestd gtest_maind)

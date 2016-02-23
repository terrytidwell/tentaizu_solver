include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(test_solver test_solver.cpp)
add_test(test_solver test_solver ${PROJECT_SOURCE_DIR}/board_files/b1.board)

# tentaizu_solver
A basic tentaizu puzzle solver

# Assumed Rules
* An N x N grid is given with 10 stars to place on the board
* Within the grid are numbers indiciating locations requiring an adjacent number of stars equal to that number
* All stars are to be placed by adjacent numbers

# To Build
* mkdir build && cd build
* cmake .. && make
* ctest -V

# Output
* The board_files folder contains one board that is solved by the program
* The output of the test is the original board followed with the solution
* Asterisks indicate a star placement, and on the final board, all non-zero constraints from the orignal board are displayed as 0

# Future Work
* See issues page

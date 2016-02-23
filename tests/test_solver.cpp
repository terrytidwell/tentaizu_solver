#include <fstream>
#include <iostream>
#include "tentaizu_parser.hpp"
#include "tentaizu_solver.hpp"

using namespace tentaizu;

int main(int argc, char** argv)
{
	/* Read in Board */
	parser<7,7> p; 
	auto board_one = p.parse(argv[1]);
	std::cout << board_one.to_string().str() << std::endl;	
	
	/* Solve Puzzle */
	solver<7,7> s(board_one);
	s.solve();	
	auto ans = s.get_ans();

	std::cout << "\n answer:" << std::endl;
	if(s.is_solved())
		std::cout << ans.to_string().str() << std::endl;	
	else
		throw std::logic_error("puzzle not solved\n");
	
	return EXIT_SUCCESS;
}

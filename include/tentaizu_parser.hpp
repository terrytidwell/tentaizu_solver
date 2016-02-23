#pragma once

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>

#include "tentaizu_board.hpp"

namespace tentaizu
{

template<int height, int width>
class parser
{
	public:
		parser() = default;
		board<height, width> parse(const std::string& f_name);

	private:
		struct tentaizu_cell construct_cell(int pos, char c);
		void post_process_board(board<height, width>& b);
		void zero_out_board(board<height, width>& b);
		void generate_constraint_list(board<height,width>& b);
};


template<int height, int width>
board<height, width> parser<height, width>::parse(const std::string& f_name)
{
	std::ifstream in(f_name);
	assert(in.good());
	board<height, width> b;	
	auto& a = b._board;
	std::string line; auto count = 0;
	while(std::getline(in, line))
	{
		assert(line.size() == width);
		for(auto c = 0; c < line.size(); ++c)
		{
			a.push_back(std::move(construct_cell(c + count * width, line[c])));
		}
		count++;	
	}
	assert(a.size() == height * width);	
	post_process_board(b);
	return b;
}

template<int height, int width>
struct tentaizu_cell parser<height, width>::construct_cell(int pos, char c)
{
	if(isdigit(c))
		return tentaizu_cell(pos, (int) c - '0', false, true, false);
	else if(c == '-')
		return tentaizu_cell(pos, INT_MAX, false, false, false);
	else
		throw std::logic_error("invalid character in board file");
}


template<int height, int width>
void parser<height, width>::post_process_board(board<height, width>& b)
{
	b.gen_offsets();
	zero_out_board(b);
	generate_constraint_list(b);
}

template<int height, int width>
void parser<height,width>::zero_out_board(board<height, width>& b)
{
	auto& offsets = b.offsets;
	auto& board = b._board;
	for(auto i = 0; i < height * width; ++i)
	{	
		if(board[i].constraint_value == 0)
		{
			board[i].constraint_value = INT_MIN;
			for(auto j = 0; j < offsets.size(); ++j)
			{
				auto loc = i + (width * offsets[j].first) + offsets[j].second;
				if(b.is_in_bounds(i, offsets[j]))
				{
					board[loc].is_zeroed_out = true;
				}
			}	
		}
	}
}

template<int height, int width>
void parser<height, width>::generate_constraint_list(board<height,width>& b)
{
	std::vector<int> cons;
	auto& board = b._board;
	for(auto i = 0; i < height * width; ++i)
	{
		auto& cell = board[i];
		if(cell.is_constraint && cell.constraint_value != INT_MIN)
			cons.push_back(i);
	}
	b.set_constrain_positions(cons);	
}

} // end namespace tentaizu

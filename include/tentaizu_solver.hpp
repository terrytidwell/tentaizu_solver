#pragma once

#include <vector>
#include <utility>

#include "tentaizu_board.hpp"

namespace tentaizu
{

static const int star_count = 10;

enum star_action
{
	STAR_ADD,
	STAR_REMOVE,
};

template<int height, int width>
class solver
{
	public:
		solver(board<height, width> b); 
		void solve();
		void solve_helper(int stars_to_place);
		board<height, width>& get_ans();
		bool is_solved();

	private:
		bool is_answer();
		bool is_cell_assignable(int);
		void update_star_count(int star_loc, enum star_action);
		bool is_constraint_violated();
		void preprocess_board();

	private:
		std::vector<std::pair<int,int>> offsets;
		bool solved;
		board<height, width> b;
		board<height, width> ans;		
};
		
template<int height, int width>
bool solver<height, width>::is_solved()
{
	return solved;
}

template<int height, int width>
board<height, width>& solver<height, width>::get_ans()
{
	return ans;
}

template<int height, int width>
solver<height,width>::solver(board<height, width> b) 
	: solved(false), b(b) 
{
	offsets = b.offsets;
}

template<int height, int width>
void solver<height, width>::solver<height, width>::solve()
{
	solve_helper(star_count);
}

template<int height, int width>
inline void solver<height, width>::update_star_count(int star_loc, enum star_action act)
{
	auto& board = b._board;
	for(auto offset : offsets)
	{
		auto offset_loc = star_loc + offset.first * width + offset.second;
		if(b.is_in_bounds(star_loc, offset))
		{
			auto& cell = board[offset_loc];
			if(cell.is_constraint)
			{
				if(act == star_action::STAR_ADD)
					cell.constraint_value--;
				else
					cell.constraint_value++;
			}
		}
	}
	auto& cell = board[star_loc];
	if(act == star_action::STAR_ADD)
	{
		cell.contains_star = true;
	}
	else
		cell.contains_star = false;
}

template<int height, int width>
bool solver<height, width>::is_answer()
{
	auto& board = b._board;
	auto constraint_positions = b._constraint_positions;
	for(auto pos : constraint_positions)
		if(board[pos].constraint_value != 0)
			return false;
	return true;
}

template<int height, int width>
bool solver<height, width>::is_constraint_violated()
{
	auto& board = b._board;
	auto constraint_positions = b._constraint_positions;
	for(auto pos : constraint_positions)
		if(board[pos].constraint_value < 0)
			return true;
	return false;
}

template<int height, int width>
bool solver<height,width>::is_cell_assignable(int loc)
{
	auto& board = b._board;
	auto& cell = board[loc];
	if(!cell.contains_star & !cell.is_constraint & !cell.is_zeroed_out)
		return true;
	return false;
}

template<int height, int width>
void solver<height,width>::solve_helper(int stars_to_place)
{
	if(!stars_to_place) 
	{
		if(is_answer())	
		{
			ans = b;
			solved = true;	
		}	
		return;
	}

	if(is_constraint_violated())
		return;

	auto& locs = b._board;
	auto constraints = b._constraint_positions;

	for(const auto constraint : constraints) 
	{
		auto& cell = locs[constraint];
	
		/* Handle More Efficiently */
		if(cell.constraint_value <= 0) continue;

		/* For each adjacent entry, attempt to place the stars */
		auto cur_pos = cell.pos;
		for(auto j = 0; j < offsets.size(); ++j)	
		{
			auto loc = cur_pos + offsets[j].first * width + offsets[j].second;
			bool assigned = false;

			/* Place star if at a valid position that doesn't have a num or star yet */
			if(b.is_in_bounds(cur_pos, offsets[j]) && is_cell_assignable(loc))
			{
				update_star_count(loc, star_action::STAR_ADD);
				solve_helper(stars_to_place - 1);
				assigned = true;
			}

			if(solved)
				return;

			if(b.is_in_bounds(cur_pos, offsets[j]) && assigned)
				update_star_count(loc, star_action::STAR_REMOVE);
		}
	}

	/* Handle case where each constraint is satisfied but stars remain */	
}

} // end tentaizu namespace

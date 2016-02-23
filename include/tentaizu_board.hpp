#pragma once

#include <initializer_list>
#include <vector>
#include <sstream>

namespace tentaizu
{

struct tentaizu_cell
{
	public:
		tentaizu_cell(int pos, int constraint_value, bool is_zeroed_out,
					  bool is_constraint, bool contains_star)
					   : pos(pos), constraint_value(constraint_value),
						 is_zeroed_out(is_zeroed_out), is_constraint(is_constraint),
						 contains_star(contains_star)
		{}		  

	public:
		int pos;
		int constraint_value;
		bool is_zeroed_out;
		bool is_constraint;
		bool contains_star;
};


template<int height, int width>
class board
{
	public:
		board() {}
		int get_height() const 		 { return h; }  
		int get_width()  const 		 { return w; }  
		void gen_offsets();
		void set_constrain_positions(std::vector<int>& v);
		std::vector<tentaizu_cell> _board;
		std::vector<int> _constraint_positions;
		std::vector<std::pair<int,int>> offsets;
		std::stringstream to_string();
		bool is_in_bounds(int point, std::pair<int, int> offset);

	private:
		int h = height;
		int w = width;
};

template<int height, int width>
void board<height, width>::set_constrain_positions(std::vector<int>& v)
{
	_constraint_positions = v;
}

template<int height, int width>
inline void board<height, width>::gen_offsets()
{
	for(int i = -1; i <= 1; ++i)
	{
		for(int j = -1; j <= 1; ++j)
		{
			if(j == 0 && i == 0) continue;
			offsets.push_back(std::make_pair(i,j));
		}
	}
}

template<int height, int width>
std::stringstream board<height,width>::to_string()
{
	std::stringstream os;
	auto& board = _board;
	for(auto i = 0; i < height * width; ++i)
	{
		if(i % w == 0 && i) 
			os << '\n';	
		auto& cell = board[i];
		if(cell.is_constraint)
		{	
			if(cell.constraint_value == INT_MIN)
				os << 0;
			else
				os << cell.constraint_value;
		}
		else if(cell.contains_star)
			os << '*';
		else if(cell.is_zeroed_out)
			os << 'x';
		else
			os << '-';
	}
	return os;
}

template<int height, int width>
inline bool board<height, width>::is_in_bounds(int point, std::pair<int, int> offset)
{
	auto p_cords = std::make_pair(point/width, point % width);
	auto total_cords = std::make_pair(p_cords.first + offset.first, p_cords.second + offset.second);
	return total_cords.first >= 0 && total_cords.second >= 0 &&
		   total_cords.second < height && total_cords.first < width ? true : false;
}

}


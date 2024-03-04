#include "box.hpp"

Box::Box(int length, int grid, const std::vector<Point>& points) : length(length), grid(grid), Figure(points) {}
Box::~Box() {}

void Box::generate_points() {
	
}

Figure::FigureType Box::get_type() {
	return Figure::FigureType::BOX;
}
#include "cone.hpp"

Cone::Cone(int radius, int height, int slices, int stacks, const std::vector<Point>& points) : radius(radius), height(height), slices(slices), stacks(stacks), Figure(points) {}
Cone::~Cone() {}

void Cone::generate_points() {
	points.clear();
	// nothing here yet
}

Figure::FigureType Cone::get_type() {
	return Figure::FigureType::CONE;
}
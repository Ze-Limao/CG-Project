#include "cone.hpp"

Cone::Cone(int radius, int height, int slices, int stacks, const std::vector<Point>& points) : radius(radius), height(height), slices(slices), stacks(stacks), Figure(points) {}
Cone::~Cone() {}

void Cone::generate_points() {
	points.clear();

    // Base of the cone
    for (int i = 0; i <= slices; i++) {
        float theta = (2.0f * PI * i) / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        add_point(Point(x, 0.0f, z));
    }

    // Stack height
    float stack_height = static_cast<float>(height) / stacks;

	// Proportion of the radius for each stack
	float proportion = radius / static_cast<float>(stacks);
	float radius1, radius2;
    // Each stack is progressively smaller than the previous one
    for (int i = 0; i < stacks; i++) {
		radius1 = radius - (proportion * i); // Radius of the current stack
		radius2 = radius - (proportion * (i + 1)); // Radius of the next stack

		float z1 = radius1 * sin(0); 
		float x1 = radius1 * cos(0); 

		float z2 = radius2 * sin(0); 
		float x2 = radius2 * cos(0); 


        for (int j = 0; j <= slices; j++) {
			float theta = (2.0f * PI * j) / slices;
			float x3 = radius1 * cos(theta);
			float z3 = radius1 * sin(theta);

			float x4 = radius2 * cos(theta);
			float z4 = radius2 * sin(theta);

			// Triangle 1
			add_point(Point(x1, stack_height * (i + 1), z1));
			add_point(Point(x3, stack_height * i, z3));
			add_point(Point(x4, stack_height * (i + 1), z4));

			// Triangle 2
			add_point(Point(x1, stack_height * (i + 1), z1));
			add_point(Point(x2, stack_height * i, z2));
			add_point(Point(x3, stack_height * i, z3));
		}
	}	
}
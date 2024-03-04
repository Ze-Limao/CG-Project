#include "box.hpp"
#include "plane.hpp"

Box::Box(int length, int grid, const std::vector<Point>& points) : length(length), grid(grid), Figure(points) {}
Box::~Box() {}

void Box::generate_points() {
	points.clear();

	int divisions = grid + 1;
	float step = length / grid;

    // Bottom face (plane)
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = -length / 2 + i * step;
            float y = -length / 2;
            float z = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, z));
            add_point(Point(x + step, y, z));
            add_point(Point(x + step, y, z + step));

            // 1 -- 3
            // |  / |
            // | /  |
            // 2 -- 4

            // Triangle 2
            add_point(Point(x, y, z));
            add_point(Point(x + step, y, z + step));
            add_point(Point(x, y, z + step));
        }
    }

    // Front face
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = -length / 2 + i * step;
            float y = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, length / 2));
            add_point(Point(x + step, y, length / 2));
            add_point(Point(x + step, y + step, length / 2));

            // Triangle 2
            add_point(Point(x, y, length / 2));
            add_point(Point(x + step, y + step, length / 2));
            add_point(Point(x, y + step, length / 2));
        }
    }

    // Back face
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = -length / 2 + i * step;
            float y = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, -length / 2));
            add_point(Point(x + step, y, -length / 2));
            add_point(Point(x + step, y + step, -length / 2));

            // Triangle 2
            add_point(Point(x, y, -length / 2));
            add_point(Point(x + step, y + step, -length / 2));
            add_point(Point(x, y + step, -length / 2));
        }
    }

    // Left face
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = -length / 2;
            float y = -length / 2 + i * step;
            float z = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, z));
            add_point(Point(x, y + step, z));
            add_point(Point(x, y + step, z + step));

            // Triangle 2
            add_point(Point(x, y, z));
            add_point(Point(x, y + step, z + step));
            add_point(Point(x, y, z + step));
        }
    }

    // Right face
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = length / 2;
            float y = -length / 2 + i * step;
            float z = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, z));
            add_point(Point(x, y + step, z));
            add_point(Point(x, y + step, z + step));

            // Triangle 2
            add_point(Point(x, y, z));
            add_point(Point(x, y + step, z + step));
            add_point(Point(x, y, z + step));
        }
    }

    // Top face
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = -length / 2 + i * step;
            float y = length / 2;
            float z = -length / 2 + j * step;

            // Triangle 1
            add_point(Point(x, y, z));
            add_point(Point(x + step, y, z));
            add_point(Point(x + step, y, z + step));

            // Triangle 2
            add_point(Point(x, y, z));
            add_point(Point(x + step, y, z + step));
            add_point(Point(x, y, z + step));
        }
    }
}
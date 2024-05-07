#include "box.hpp"
#include "plane.hpp"

Box::Box(
    int length, 
    int grid, 
    const std::vector<Point>& points, 
    const std::vector<Point>& normals, 
    const std::vector<Point>& texture_coords
) : length(length), grid(grid), Figure(points, normals, texture_coords) {}

Box::~Box() {}

void Box::generate_points() {
	points.clear();

    float dimension2 = static_cast<float>(length) / 2;
    float div_side = static_cast<float>(length) / grid;

    Point normal = Point(0.0f, -1.0f, 0.0f);
    // Bottom face (reversed plane)
    for (int line = 0; line < grid; line++) {
        float z1 = -dimension2 + line * div_side;
        float z2 = z1 + div_side;
        for (int column = 0; column < grid; column++) {
            float x1 = -dimension2 + column * div_side;
            float x2 = x1 + div_side;

            // 1 -- 3
            // | \  |
            // |  \ |
            // 2 -- 4

            // First triangle
            add_point_full(Point(x1, -dimension2, z1), normal); // 1
            add_point_full(Point(x2, -dimension2, z1), normal); // 3
            add_point_full(Point(x2, -dimension2, z2), normal); // 2

            // Second triangle
            add_point_full(Point(x2, -dimension2, z2), normal); // 3
            add_point_full(Point(x1, -dimension2, z2), normal); // 4
            add_point_full(Point(x1, -dimension2, z1), normal); // 2

        }
    }

    normal = Point(0.0f, 1.0f, 0.0f);
    // Top face (normal plane)
    for (int line = 0; line < grid; line++) {
        float z1 = -dimension2 + line * div_side;
        float z2 = z1 + div_side;
        for (int column = 0; column < grid; column++) {
            float x1 = -dimension2 + column * div_side;
            float x2 = x1 + div_side;

            // 1 -- 3
            // | \  |
            // |  \ |
            // 2 -- 4

            // First triangle
            add_point_full(Point(x1, dimension2, z1), normal); // 1
            add_point_full(Point(x1, dimension2, z2), normal); // 2
            add_point_full(Point(x2, dimension2, z2), normal); // 4

            // Second triangle
            add_point_full(Point(x2, dimension2, z2), normal); // 4
            add_point_full(Point(x2, dimension2, z1), normal); // 3
            add_point_full(Point(x1, dimension2, z1), normal); // 1
        }
    }

    normal = Point(0.0f, 0.0f, 1.0f);
    // Front face
    for (int line = 0; line < grid; line++) {
        float x1 = -dimension2  + line * div_side;
        float x2 = x1 + div_side;
        for (int collumn = 0; collumn < grid; collumn++) {
            float y1 = -dimension2  + collumn * div_side;
            float y2 = y1 + div_side;

            // Triangle 1
            add_point_full(Point(x1, y1, dimension2), normal);
            add_point_full(Point(x2, y1, dimension2), normal);
            add_point_full(Point(x1, y2, dimension2), normal);

            // Triangle 2
            add_point_full(Point(x2, y2, dimension2), normal);
            add_point_full(Point(x1, y2, dimension2), normal);
            add_point_full(Point(x2, y1, dimension2), normal);
        }
    }

    normal = Point(0.0f, 0.0f, -1.0f);
    // Back face
    for (int line = 0; line < grid; line++) {
        float x1 = -dimension2 + line * div_side;
        float x2 = x1 + div_side;
        for (int collumn = 0; collumn < grid; collumn++) {
            float y1 = -dimension2 + collumn * div_side;
            float y2 = y1 + div_side;

            // Triangle 1
            add_point_full(Point(x1, y1, -dimension2), normal);
            add_point_full(Point(x1, y2, -dimension2), normal);
            add_point_full(Point(x2, y1, -dimension2), normal);

            // Triangle 2
            add_point_full(Point(x2, y1, -dimension2), normal);
            add_point_full(Point(x1, y2, -dimension2), normal);
            add_point_full(Point(x2, y2, -dimension2), normal);
        }
    }

    normal = Point(-1.0f, 0.0f, 0.0f);
    // Left face
    for (int line = 0; line < grid; line++) {
        float z1 = -dimension2 + line * div_side;
        float z2 = z1 + div_side;
        for (int collumn = 0; collumn < grid; collumn++) {
            float y1 = -dimension2 + collumn * div_side;
            float y2 = y1 + div_side;

            // Triangle 1
            add_point_full(Point(-dimension2, z1, y1), normal);
            add_point_full(Point(-dimension2, z2, y2), normal);
            add_point_full(Point(-dimension2, z2, y1), normal);

            // Triangle 2
            add_point_full(Point(-dimension2, z2, y2), normal);
            add_point_full(Point(-dimension2, z1, y1), normal);
            add_point_full(Point(-dimension2, z1, y2), normal);
        }
    }

    normal = Point(1.0f, 0.0f, 0.0f);
    // Right face
    for (int line = 0; line < grid; line++) {
        float z1 = -dimension2  + line * div_side;
        float z2 = z1 + div_side;
        for (int collumn = 0; collumn < grid; collumn++) {
            float y1 = -dimension2  + collumn * div_side;
            float y2 = y1 + div_side;

            // Triangle 1
            add_point_full(Point(dimension2, z1, y1), normal);
            add_point_full(Point(dimension2, z2, y1), normal);
            add_point_full(Point(dimension2, z2, y2), normal);


            // Triangle 2
            add_point_full(Point(dimension2, z2, y2), normal);
            add_point_full(Point(dimension2, z1, y2), normal);
            add_point_full(Point(dimension2, z1, y1), normal);
        }
    }
}

Figure::FigureType Box::get_type() {
	return Figure::FigureType::BOX;
}
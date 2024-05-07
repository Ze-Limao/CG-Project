#include "cone.hpp"
#include <iostream>

Cone::Cone(
    int radius, 
    int height, 
    int slices, 
    int stacks, 
    const std::vector<Point>& points, 
    const std::vector<Point>& normals, 
    const std::vector<Point>& texture_coords
) : radius(radius), height(height), slices(slices), stacks(stacks), Figure(points, normals, texture_coords) {}

Cone::~Cone() {}

void Cone::generate_points() {
	points.clear();

    // Base
    float alpha = (2.0f * PI) / slices;
    float start = 0.0f;
    std::vector<Point> base(slices);
    std::vector<Point> temp_normals(slices);

    Point origin = Point(0.0f, 0.0f, 0.0f);
    Point apex = Point(0.0f, height, 0.0f);

    Point normal = Point(0.0f, -1.0f, 0.0f);

    float texture_radius = 0.5f;
    float texture_center[2] = {0.5f, 0.5f};

    for (int i = 0; i < slices; i++) {
        Point np = Point(radius * sinf(start), 0.0f, radius * cosf(start));
        base.insert(base.begin() + i, np);

        add_point_full(np, normal);
        add_point_full(Point(0.0f, 0.0f, 0.0f), normal);
        start += alpha;
        add_point_full(Point(radius * sinf(start), 0.0f, radius * cosf(start)), normal);

        // normals
        Point vector_a = Point::vector_from_two_points(origin, np);
        Point vector_b = Point::vector_from_two_points(origin, apex);
        Point vector_c = Point::vector_from_two_points(np, apex);
        Point vector_r = Point::cross2(vector_a, vector_b);

        Point edge_normal = Point::cross2(vector_c, vector_r);
        edge_normal.normalize();

        auto position = temp_normals.begin() + i;
        temp_normals.insert(position, edge_normal);
    }

    float h_diff = static_cast<float>(height) / stacks;

    float current_texture_alpha = 0.0f;
    float texture_radius_delta = texture_radius / stacks;

    // Faces
    for (int j = 0; j < slices; j++) {
        Point p1 = base.at(j);
        Point normal1 = temp_normals.at(j);
        int nj = j + 1;

        if (nj == slices) 
            nj = 0;
        Point p2 = base.at(nj);
        Point normal2 = temp_normals.at(nj);
        
        float current_texture_radius = 0.5f;
 
        float b1x_diff = p1.x / stacks; // Diferença entre a coordenada X e 0 do p1
        float b1z_diff = p1.z / stacks; // Diferença entre a coordenada Z e 0 do p1

        float b2x_diff = p2.x / stacks; // Diferença entre a coordenada X e 0 do p2
        float b2z_diff = p2.z / stacks; // Diferença entre a coordenada Z e 0 do p2

        Point l_p1 = p1;
        Point l_p2 = p2;

        // Para cada stack da face
        for (int i = 0; i < stacks - 1; i++) {
            // Triangulo da esquerda
            // 1
            // 1  2
            add_point_full(l_p1, normal1, Point::new_sph_point2(texture_center, current_texture_alpha, current_texture_radius));
            add_point_full(l_p2, normal2, Point::new_sph_point2(texture_center, current_texture_alpha + alpha, current_texture_radius));
            l_p1 = Point(l_p1.x - b1x_diff, l_p1.y + h_diff, l_p1.z - b1z_diff);
            add_point_full(l_p1, normal1, Point::new_sph_point2(texture_center, current_texture_alpha, current_texture_radius - texture_radius_delta));

            // Triangulo da direita
            //    2
            // 1  2
            add_point_full(l_p2, normal2, Point::new_sph_point2(texture_center, current_texture_alpha + alpha, current_texture_radius));
            l_p2 = Point(l_p2.x - b2x_diff, l_p2.y + h_diff, l_p2.z - b2z_diff);
            add_point_full(l_p2, normal2, Point::new_sph_point2(texture_center, current_texture_alpha + alpha, current_texture_radius - texture_radius_delta));
            add_point_full(l_p1, normal1, Point::new_sph_point2(texture_center, current_texture_alpha, current_texture_radius - texture_radius_delta));

            current_texture_radius -= texture_radius_delta;
        }

        // Construir triangulo do topo.
        add_point_full(l_p1, normal1, Point::new_sph_point2(texture_center, current_texture_alpha, current_texture_radius));
        add_point_full(l_p2, normal2, Point::new_sph_point2(texture_center, current_texture_alpha + alpha, current_texture_radius));
        add_point_full(Point(0.0f, static_cast<float>(height), 0.0f), Point(0.0f, 1.0f, 0.0f), Point(texture_center[0], texture_center[1], 0.0f));

        current_texture_alpha += alpha;
    }

    base.clear();
    temp_normals.clear();

}

Figure::FigureType Cone::get_type() {
	return Figure::FigureType::CONE;
}
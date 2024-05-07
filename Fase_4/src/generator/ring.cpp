#include "ring.hpp"

Ring::Ring(
    int iRadius, 
    int eRadius, 
    int slices, 
    const std::vector<Point>& points, 
    const std::vector<Point>& normals, 
    const std::vector<Point>& texture_coords
) : iRadius(iRadius), eRadius(eRadius), slices(slices), Figure(points, normals, texture_coords) {}

Ring::~Ring() {}

void Ring::generate_points() {
    points.clear();
    float a = 0, delta = (2 * PI) / slices;

    float f_iRadius = static_cast<float>(iRadius);
    float f_eRadius = static_cast<float>(eRadius);

    Point top_normal = Point(0.0f, 1.0f, 0.0f);
    Point bottom_normal = Point(0.0f, -1.0f, 0.0f);

    for (int i = 0; i < slices; i++, a += delta) {
            add_point_full(Point::new_sph_point(a, 0.0f, f_iRadius), top_normal);
            add_point_full(Point::new_sph_point(a, 0.0f, f_eRadius), top_normal);
            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_iRadius), top_normal);

            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_iRadius), top_normal);
            add_point_full(Point::new_sph_point(a, 0.0f, f_eRadius), top_normal);
            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_eRadius), top_normal);

            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_iRadius), bottom_normal);
            add_point_full(Point::new_sph_point(a, 0.0f, f_eRadius), bottom_normal);
            add_point_full(Point::new_sph_point(a, 0.0f, f_iRadius), bottom_normal);

            add_point_full(Point::new_sph_point(a, 0.0f, f_eRadius), bottom_normal);
            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_iRadius), bottom_normal);
            add_point_full(Point::new_sph_point(a + delta, 0.0f, f_eRadius), bottom_normal);
    }
}

Figure::FigureType Ring::get_type() {
    return Figure::FigureType::RING;
}
#include "ring.hpp"

Ring::Ring(int iRadius, int eRadius, int slices, const std::vector<Point>& points) : iRadius(iRadius), eRadius(eRadius), slices(slices), Figure(points) {}
Ring::~Ring() {}

void Ring::generate_points() {
    points.clear();
    float a = 0, delta = (2 * PI) / slices;
    for (int i = 0; i < slices; i++, a += delta) {
            add_point(Point::new_sph_point(a, 0.0f, iRadius));
            add_point(Point::new_sph_point(a, 0.0f, eRadius));
            add_point(Point::new_sph_point(a + delta, 0.0f, iRadius));

            add_point(Point::new_sph_point(a + delta, 0.0f, iRadius));
            add_point(Point::new_sph_point(a, 0.0f, eRadius));
            add_point(Point::new_sph_point(a + delta, 0.0f, eRadius));

            add_point(Point::new_sph_point(a + delta, 0.0f, iRadius));
            add_point(Point::new_sph_point(a, 0.0f, eRadius));
            add_point(Point::new_sph_point(a, 0.0f, iRadius));

            add_point(Point::new_sph_point(a, 0.0f, eRadius));
            add_point(Point::new_sph_point(a + delta, 0.0f, iRadius));
            add_point(Point::new_sph_point(a + delta, 0.0f, eRadius));
    }
}

Figure::FigureType Ring::get_type() {
    return Figure::FigureType::RING;
}
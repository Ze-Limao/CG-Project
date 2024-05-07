#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>
#include <cmath>
constexpr float PI = 3.14159265358979323846f;

#include <vector>
#include "point.hpp"

class Figure {
public:
    Figure();
    Figure(
        const std::vector<Point>& points = {},
        const std::vector<Point>& normals = {}, 
        const std::vector<Point>& texture_coords = {}
    );
    ~Figure();

    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<Point> texture_coords;

    std::string texture_file;
    vector<float> diffuse  = { 200.0f, 200.0f, 200.0f};
    vector<float> ambient  = { 50.0f, 50.0f, 50.f };
    vector<float> specular = { 0.0f, 0.0f, 0.0f };
    vector<float> emissive = { 0.0f, 0.0f, 0.0f };
    float shininess = 0;

    std::string to_string() const;
    vector<float> to_vector();

    enum FigureType { FIGURE = 0, BOX = 1, CONE = 2, PLANE = 3, SPHERE = 4, RING = 5, BEZIER = 6 };

    void add_point(const Point& point);
    void add_point_full(const Point& point, Point& normal, const Point& texture_coord);
    void add_point_full(const Point& point, Point& normal);

    void to_file(const std::string& path, const std::vector<int>& args, FigureType type);
    static Figure* from_file(const std::string& path);
    
    virtual void generate_points() = 0;    
    virtual FigureType get_type() { return FigureType::FIGURE; }
};

#endif // FIGURE_HPP

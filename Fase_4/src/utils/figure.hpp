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
    Figure(const std::vector<Point>& points);
    ~Figure();

    std::vector<Point> points;

    std::string texture_file;
    vector<float> diffuse  = { 200.0f, 200.0f, 200.0f};
    vector<float> ambient  = { 50.0f, 50.0f, 50.f };
    vector<float> specular = { 0.0f, 0.0f, 0.0f };
    vector<float> emissive = { 0.0f, 0.0f, 0.0f };
    float shininess = 0;

    enum FigureType { FIGURE = 0, BOX = 1, CONE = 2, PLANE = 3, SPHERE = 4, RING = 5, BEZIER = 6 };

    void add_point(const Point& point);
    void to_file(const std::string& path, const std::vector<int>& args, FigureType type);
    std::string to_string() const;
    vector<float> to_vector();
    static Figure* from_file(const std::string& path);
    
    virtual void generate_points() = 0;    
    virtual FigureType get_type() { return FigureType::FIGURE; }
};

#endif // FIGURE_HPP

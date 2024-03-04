#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>
#include <cmath>
constexpr float PI = 3.14159265358979323846f;

#include <vector>
#include "point.hpp"

class Figure {
public:
    std::vector<Point> points;
    Figure();
    Figure(const std::vector<Point>& points);
    ~Figure();
    void add_point(const Point& point);
    void to_file(const std::string& path, const std::vector<int>& args);
    virtual void generate_points() = 0;
};

#endif // FIGURE_HPP

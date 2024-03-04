#include <fstream>
#include <iostream>

#include "figure.hpp"

Figure::Figure() {}
Figure::Figure(const std::vector<Point>& points) : points(points) {}
Figure::~Figure() { points.clear(); }

void Figure::add_point(const Point& point) {
    points.push_back(point);
}

void Figure::to_file(const std::string& path, const std::vector<int>& args) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file '" << path << "'\n";
        return;
    }

    file << points.size();
    for (const auto& arg : args) { file << ';' << arg;  }
    file << '\n';

    for (const auto& point : points) {
        file << point.x << ';' << point.y << ';' << point.z << '\n';
    }

    file.close();
}
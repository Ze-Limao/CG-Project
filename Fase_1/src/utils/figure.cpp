#include <fstream>
#include <iostream>

#include "figure.hpp"

Figure::Figure() {}

Figure::~Figure() {
    points.clear();
}

void Figure::add_point(const Point& point) {
    points.push_back(point);
}

void Figure::to_file(const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file '" << path << "'\n";
        return;
    }

    file << points.size() << '\n';
    for (const auto& point : points) {
        file << point.x << ',' << point.y << ',' << point.z << '\n';
    }
}
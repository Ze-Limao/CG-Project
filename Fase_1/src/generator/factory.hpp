#ifndef FIGURE_FACTORY_HPP
#define FIGURE_FACTORY_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <stdexcept>

#include "box.hpp"
#include "cone.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "../utils/figure.hpp"

class Factory {
public:
    template<typename T, typename std::enable_if<std::is_base_of<Figure, T>::value>::type* = nullptr>
    static T* create(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error opening file '" << path << "'" << std::endl;
            return nullptr;
        }

        std::string line;
        std::getline(file, line);
        std::vector<std::string> first_line = Factory::split(line, ';');

        int n_vertices = std::stoi(first_line.at(0));
        std::vector<Point> points(n_vertices);

        while (std::getline(file, line)) {
            std::vector<std::string> tokens = Factory::split(line, ';');
            Point point(std::stof(tokens.at(0)), std::stof(tokens.at(1)), std::stof(tokens.at(2)));
            points.push_back(point);
        }

        std::vector<int> args;
        for (unsigned int i = 1; i < first_line.size(); i++) 
            args.push_back(std::stoi(first_line.at(i)));

        file.close();
        T* instance = nullptr;

        if (std::is_same_v<T, Box> && args.size() >= 2) {
            instance = dynamic_cast<T*>(new Box(args.at(0), args.at(1), points));
        } else if (std::is_same_v<T, Cone> && args.size() >= 4) {
            instance = dynamic_cast<T*>(new Cone(args.at(0), args.at(1), args.at(2), args.at(3), points));
        } else if (std::is_same_v<T, Plane> && args.size() >= 2) {
            instance = dynamic_cast<T*>(new Plane(args.at(0), args.at(1), 0, points));
        } else if (std::is_same_v<T, Sphere> && args.size() >= 3) {
            instance = dynamic_cast<T*>(new Sphere(args.at(0), args.at(1), args.at(2), points));
        } else {
            std::cerr << "Incorrect number of arguments for type T." << std::endl;
        }

        return instance;
    }

private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif // FIGURE_FACTORY_HPP
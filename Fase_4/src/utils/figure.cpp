#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <stdexcept>

#include <map>
#include "figure.hpp"
#include "../generator/box.hpp"
#include "../generator/cone.hpp"
#include "../generator/plane.hpp"
#include "../generator/sphere.hpp"
#include "../generator/ring.hpp"
#include "../generator/bezier.hpp"

Figure::Figure() {}
Figure::Figure(const std::vector<Point>& points) : points(points) {}
Figure::~Figure() { points.clear(); }

void Figure::add_point(const Point& point) {
    points.push_back(point);
}

void Figure::to_file(const std::string& path, const std::vector<int>& args, FigureType type) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file '" << path << "'\n";
        return;
    }

    file << texture_file << '\n';
    file << diffuse.at(0)  << ';' << diffuse.at(1)  << ';' << diffuse.at(2)  << '\n';
    file << ambient.at(0)  << ';' << ambient.at(1)  << ';' << ambient.at(2)  << '\n';
    file << specular.at(0) << ';' << specular.at(1) << ';' << specular.at(2) << '\n';
    file << emissive.at(0) << ';' << emissive.at(1) << ';' << emissive.at(2) << '\n';
    file << shininess << '\n';

    file << static_cast<int>(type) << ';' << points.size();
    for (const auto& arg : args) { file << ';' << arg;  }
    file << '\n';

    for (const auto& point : points) {
        file << point.x << ';' << point.y << ';' << point.z << '\n';
    }

    file.close();
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Figure* Figure::from_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file '" << path << "'" << std::endl;
        return nullptr;
    }

    std::string line;

    std::getline(file, line);
    std::string texture_file = line;

    std::getline(file, line); // Diffuse
    std::vector<std::string> diffuse_str = split(line, ';');
    vector<float> diffuse = { std::stof(diffuse_str[0]), std::stof(diffuse_str[1]), std::stof(diffuse_str[2]) };

    std::getline(file, line); // Ambient
    std::vector<std::string> ambient_str = split(line, ';');
    vector<float>  ambient = { std::stof(ambient_str[0]), std::stof(ambient_str[1]), std::stof(ambient_str[2]) };

    std::getline(file, line); // Specular
    std::vector<std::string> specular_str = split(line, ';');
    vector<float> specular = { std::stof(specular_str[0]), std::stof(specular_str[1]), std::stof(specular_str[2]) };

    std::getline(file, line); // Emissive
    std::vector<std::string> emissive_str = split(line, ';');
    vector<float> emissive = { std::stof(emissive_str[0]), std::stof(emissive_str[1]), std::stof(emissive_str[2]) };

    std::getline(file, line); // Shininess
    float shininess = std::stof(line);

    std::getline(file, line);
    std::vector<std::string> first_line = split(line, ';');

    FigureType type = static_cast<FigureType>(std::stoi(first_line.at(0)));
    int n_vertices = std::stoi(first_line.at(1));
    std::vector<Point> points(n_vertices);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ';');
        Point point(std::stof(tokens.at(0)), std::stof(tokens.at(1)), std::stof(tokens.at(2)));
        points.push_back(point);
    }

    std::vector<int> args;
    for (unsigned int i = 2; i < first_line.size(); i++)
        args.push_back(std::stoi(first_line.at(i)));

    file.close();
    Figure* instance = nullptr;

    if (type == FigureType::BOX && args.size() >= 2) {
        instance = new Box(args.at(0), args.at(1), points);
    } else if (type == FigureType::CONE && args.size() >= 4) {
        instance = new Cone(args.at(0), args.at(1), args.at(2), args.at(3), points);
    } else if (type == FigureType::PLANE && args.size() >= 2) {
        instance = new Plane(args.at(0), args.at(1), 0, points);
    } else if (type == FigureType::SPHERE && args.size() >= 3) {
        instance = new Sphere(args.at(0), args.at(1), args.at(2), points);
    } else if (type == FigureType::RING && args.size() >= 3) {
        instance = new Ring(args.at(0), args.at(1), args.at(2), points);
    } else if (type == FigureType::BEZIER && args.size() >= 1) {
        instance = new Bezier(args.at(0), {}, points);
    } else {
        std::cerr << "Incorrect number of arguments for type T." << std::endl;
        return nullptr;
    }

    instance->texture_file = texture_file;
    instance->ambient = ambient;
    instance->diffuse = diffuse;
    instance->specular = specular;
    instance->emissive = emissive;
    instance->shininess = shininess;

    std::cout << instance->to_string() << std::endl;

    return instance;
}

vector<float> Figure::to_vector() {
    vector<float> result;
    for (Point p : this->points) {
        result.push_back(p.x);
        result.push_back(p.y);
        result.push_back(p.z);
    }
    return result;
}

std::string Figure::to_string() const {
    std::stringstream ss;

    ss << "Texture file: " << texture_file << '\n';
    ss << "Diffuse: " << diffuse[0] << ", " << diffuse[1] << ", " << diffuse[2] << '\n';
    ss << "Ambient: " << ambient[0] << ", " << ambient[1] << ", " << ambient[2] << '\n';
    ss << "Specular: " << specular[0] << ", " << specular[1] << ", " << specular[2] << '\n';
    ss << "Emissive: " << emissive[0] << ", " << emissive[1] << ", " << emissive[2] << '\n';
    ss << "Shininess: " << shininess << '\n';

    ss << "Points: " << '\n';
    for (const auto& point : points) {
        ss << "  (" << point.x << ", " << point.y << ", " << point.z << ")\n";
    }

    return ss.str();
}
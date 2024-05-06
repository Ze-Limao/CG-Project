#include "light.hpp"
#include <sstream>

PointLight::PointLight(const std::vector<float>& position) : pos(position) {}

Light::Type PointLight::get_type() const {
    return Type::Point;
}

std::string PointLight::to_string() const {
    std::stringstream ss;
    ss << "PointLight { pos: [";
    for (size_t i = 0; i < pos.size(); ++i) {
        ss << pos[i];
        if (i < pos.size() - 1) {
            ss << ", ";
        }
    }
    ss << "] }";
    return ss.str();
}

DirectionalLight::DirectionalLight(const std::vector<float>& direction) : dir(direction) {}

Light::Type DirectionalLight::get_type() const {
    return Type::Directional;
}

std::string DirectionalLight::to_string() const {
    std::stringstream ss;
    ss << "DirectionalLight { dir: [";
    for (size_t i = 0; i < dir.size(); ++i) {
        ss << dir[i];
        if (i < dir.size() - 1) {
            ss << ", ";
        }
    }
    ss << "] }";
    return ss.str();
}

SpotLight::SpotLight(const std::vector<float>& position, const std::vector<float>& direction, float cut_off)
    : pos(position), dir(direction), cutoff(cut_off) {}

Light::Type SpotLight::get_type() const {
    return Type::Spotlight;
}

std::string SpotLight::to_string() const {
    std::stringstream ss;
    ss << "SpotLight { pos: [";
    for (size_t i = 0; i < pos.size(); ++i) {
        ss << pos[i];
        if (i < pos.size() - 1) {
            ss << ", ";
        }
    }
    ss << "], dir: [";
    for (size_t i = 0; i < dir.size(); ++i) {
        ss << dir[i];
        if (i < dir.size() - 1) {
            ss << ", ";
        }
    }
    ss << "], cutoff: " << cutoff << " }";
    return ss.str();
}
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <vector>
#include <string>

class Light {
public:
    enum class Type {
        Point,
        Directional,
        Spotlight
    };

    virtual ~Light() {}
    virtual Type get_type() const = 0;
    virtual std::string to_string() const = 0;
};

class PointLight : public Light {
private:
    std::vector<float> pos;
public:
    PointLight(const std::vector<float>& position);
    Type get_type() const override;
    std::string to_string() const override;
};

class DirectionalLight : public Light {
private:
    std::vector<float> dir;
public:
    DirectionalLight(const std::vector<float>& direction);
    Type get_type() const override;
    std::string to_string() const override;
};

class SpotLight : public Light {
private:
    std::vector<float> pos;
    std::vector<float> dir;
    float cutoff;
public:
    SpotLight(const std::vector<float>& position, const std::vector<float>& direction, float cut_off);
    Type get_type() const override;
    std::string to_string() const override;
};

#endif // LIGHT_HPP
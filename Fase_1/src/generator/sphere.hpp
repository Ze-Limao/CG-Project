#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../utils/figure.hpp"

class Sphere : public Figure {
public:
    Sphere(int radius, int slices, int stacks);

    ~Sphere();

    int radius;
    int slices;
    int stacks;

    virtual void generate_points() override;
};

#endif // SPHERE_HPP

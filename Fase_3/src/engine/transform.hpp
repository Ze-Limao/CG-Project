#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../utils/point.hpp"
#include <vector>

class Transform {
public:
    enum TransformType { TRANSLATE = 1, SCALE = 2, ROTATE = 3 };

    Transform(float x, float y, float z, float angle, TransformType type);
    ~Transform();

    bool is_dynamic = false;
    float x, y, z, angle;
    TransformType type;
};

class DynamicTransform : public Transform{
public:
    DynamicTransform(float x, float y, float z, TransformType type, float time, bool align, std::vector<Point>& points, float *axis);

    bool align;
    float time;
    std::vector<Point> points;
    float axis[3];
};

#endif // TRANSFORM_HPP

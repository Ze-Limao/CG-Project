#include "transform.hpp"

#include <vector>

Transform::Transform(float x, float y, float z, float angle, TransformType type) : x(x), y(y), z(z), angle(angle), type(type) {}
Transform::~Transform() {}

DynamicTransform::DynamicTransform(float x, float y, float z, TransformType type, float time, bool align, std::vector<Point>& points, float* axis) :
	Transform(x, y, z, 0, type), time(time), align(align), points(points) {
	std::copy(axis, axis + 3, this->axis);
	this->is_dynamic = true;
}
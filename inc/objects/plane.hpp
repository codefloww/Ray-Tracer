//
// Created by paul on 3/31/23.
//

#ifndef RAY_TRACER_PLANE_HPP
#define RAY_TRACER_PLANE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "objects/object.hpp"

class Plane : public Object {
public:
    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const override;
};

#endif //RAY_TRACER_PLANE_HPP

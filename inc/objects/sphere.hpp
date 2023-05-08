//
// Created by paul on 3/12/23.
//

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "transformation.hpp"
#include "objects/object.hpp"

class Sphere : public Object {
private:
    glm::vec3 center_m {0.0f, 0.0f, 0.0f};
    float radius_m = 1.0f;
public:
    explicit Sphere(glm::vec3 center, float radius);

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const override;
};

#endif //RAY_TRACER_SPHERE_HPP

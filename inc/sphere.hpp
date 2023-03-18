//
// Created by paul on 3/12/23.
//

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Sphere {

    double radius_m = 1.0f;
    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);


public:
    Sphere() = default;

    ~Sphere() = default;

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, const glm::vec3 &loc_normal, glm::vec3 loc_color) const;
};


#endif //RAY_TRACER_SPHERE_HPP

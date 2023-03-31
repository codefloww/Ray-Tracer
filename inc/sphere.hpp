//
// Created by paul on 3/12/23.
//

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "transformation.hpp"

class Sphere {
public:

    Transformation transformation_m;
    glm::vec3 base_color_m = glm::vec3(255.0f, 0.0f, 0.0f);
public:
    Sphere() = default;

    ~Sphere() = default;

    void setTransformation(const Transformation &transformation);

    void setColor(const glm::vec3 &color);

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 &loc_color) const;
};


#endif //RAY_TRACER_SPHERE_HPP

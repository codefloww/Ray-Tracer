//
// Created by andrew on 18/04/23.
//

#ifndef RAY_TRACER_OBJECT_HPP
#define RAY_TRACER_OBJECT_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "transformation.hpp"

class Object {
public:
    Transformation transformation_m;
    glm::vec3 base_color_m = glm::vec3(255.0f, 0.0f, 0.0f);

public:
    Object() = default;

    ~Object() = default;

    void setTransformation(const Transformation &transformation);

    void setColor(const glm::vec3 &color);

    virtual bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 &loc_color) const = 0;
};
#endif //RAY_TRACER_OBJECT_HPP

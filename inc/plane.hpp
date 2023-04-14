//
// Created by paul on 3/31/23.
//

#ifndef RAY_TRACER_PLANE_HPP
#define RAY_TRACER_PLANE_HPP

#include <glm/glm.hpp>
#include "transformation.hpp"

class Plane {
public:
    glm::vec3 color_m = glm::vec3(128.0f, 128.0f, 128.0f);
    Transformation transformation_m = Transformation();

public:
    Plane() = default;

    ~Plane() = default;

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 &loc_color) const;

    void setTransformation(const Transformation &transformation);

    void setColor(const glm::vec3 &color);
};

#endif //RAY_TRACER_PLANE_HPP

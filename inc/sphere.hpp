//
// Created by paul on 3/12/23.
//

#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Sphere {
    glm::vec3 m_center;
    double m_radius;

public:
    Sphere();

    ~Sphere();

    bool TestIntersections(const Ray &castRay, glm::vec3 &intPoint, glm::vec3 &locNormal, glm::vec3 locColor) const;

};


#endif //RAY_TRACER_SPHERE_HPP

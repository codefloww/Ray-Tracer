//
// Created by paul on 3/12/23.
//

#include "../inc/sphere.hpp"
#include <cmath>

Sphere::Sphere() {
    m_center = glm::vec3(0.0f, 0.0f, 0.0f);
    m_radius = 1.0f;
}

Sphere::~Sphere() {}


bool
Sphere::TestIntersections(const Ray &castRay, glm::vec3 &intPoint, glm::vec3 &locNormal, glm::vec3 locColor) const {
    glm::vec3 vhat = castRay.GetDirection();
    double b = 2.0 * glm::dot(vhat, castRay.GetOrigin() - m_center);
    double c = glm::dot(castRay.GetOrigin() - m_center, castRay.GetOrigin() - m_center) - m_radius * m_radius;
    double discriminant = b * b - 4.0 * c;
    if (discriminant < 0.0) {
        return false;
    } else {
        double numSqrt = sqrt(discriminant);
        double t1 = (-b + numSqrt) / 2.0;
        double t2 = (-b - numSqrt) / 2.0;
        if ((t1 < 0.0) || (t2 < 0.0)) {
            return false;
        } else {
            if (t1 < t2) {
                intPoint = castRay.GetOrigin() + vhat * static_cast<float>(t1);
            } else {
                intPoint = castRay.GetOrigin() + vhat * static_cast<float>(t2);
            }
            return true;
        }
    }
}

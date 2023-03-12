//
// Created by paul on 3/11/23.
//

#include "../inc/ray.hpp"

Ray::Ray() : m_origin(glm::vec3(0.0f, 0.0f, 0.0f)),
             m_direction(glm::vec3(0.0f, 0.0f, 1.0f)) {}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) : m_origin(origin),
                                                                m_direction(glm::normalize(direction)) {}

glm::vec3 Ray::GetOrigin() const {
    return m_origin;
}

glm::vec3 Ray::GetDirection() const {
    return m_direction;
}

glm::vec3 Ray::GetPoint(double t) const {
    return m_origin + m_direction * static_cast<float>(t);
}

Ray Ray::GetRayFromPoints(const glm::vec3 &origin, const glm::vec3 &destination) {
    return Ray{origin, glm::normalize(destination - origin)};
}

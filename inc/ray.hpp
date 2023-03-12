//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_RAY_HPP
#define RAY_TRACER_RAY_HPP

#include <glm/glm.hpp>

class Ray {
    glm::vec3 m_origin;
    glm::vec3 m_direction;

public:
    Ray();

    Ray(const glm::vec3 &origin, const glm::vec3 &direction);

    ~Ray() = default;

    glm::vec3 GetOrigin() const;

    glm::vec3 GetDirection() const;

    glm::vec3 GetPoint(double t) const;

    static Ray GetRayFromPoints(const glm::vec3 &origin, const glm::vec3 &destination);
};


#endif //RAY_TRACER_RAY_HPP

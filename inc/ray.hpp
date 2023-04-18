//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_RAY_HPP
#define RAY_TRACER_RAY_HPP

#include <glm/glm.hpp>

class Ray {
    glm::vec3 origin_m;
    glm::vec3 direction_m;

public:
    Ray();

    Ray(const glm::vec3 &origin, const glm::vec3 &direction);

    [[nodiscard]] glm::vec3 getOrigin() const;

    [[nodiscard]] glm::vec3 getDirection() const;

    [[nodiscard]] glm::vec3 getPoint(double t) const;

    static Ray getRayFromPoints(const glm::vec3 &origin, const glm::vec3 &destination);
};

#endif //RAY_TRACER_RAY_HPP

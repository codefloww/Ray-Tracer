//
// Created by paul on 3/11/23.
//

#include "ray.hpp"

Ray::Ray() : origin_m(glm::vec3(0.0f, 0.0f, 0.0f)),
             direction_m(glm::vec3(0.0f, 0.0f, 1.0f)) {}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) : origin_m(origin),
                                                                direction_m(glm::normalize(direction)) {}

glm::vec3 Ray::getOrigin() const {
    return origin_m;
}

glm::vec3 Ray::getDirection() const {
    return direction_m;
}

glm::vec3 Ray::getPoint(double t) const {
    return origin_m + direction_m * static_cast<float>(t);
}

Ray Ray::getRayFromPoints(const glm::vec3 &origin, const glm::vec3 &destination) {
    return Ray{origin, glm::normalize(destination - origin)};
}

//
// Created by paul on 3/31/23.
//

#include "objects/plane.hpp"

constexpr double kEpsilon = 0.0001f;

bool
Plane::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 &loc_color) const {
    Ray local_ray = transformation_m.applyTransform(cast_ray, Direction::BACKWARD);
    glm::vec3 k = local_ray.getDirection();

    if (fabs(k.z) < kEpsilon) {
        return false;
    }

    double t = -local_ray.getOrigin().z / k.z;
    if (t < 0.0) {
        return false;
    }

    glm::vec3 local_int_point = local_ray.getPoint(t);
    if ((local_int_point.x < -1.0f) || (local_int_point.x > 1.0f) || (local_int_point.y < -1.0f) ||
        (local_int_point.y > 1.0f)) {
        return false;
    }

    int_point = transformation_m.applyTransform(local_int_point, Direction::FORWARD);
    glm::vec3 plane_origin = transformation_m.applyTransform(glm::vec3(0.0f, 0.0f, 0.0f), Direction::FORWARD);
    loc_normal = transformation_m.applyTransform(glm::vec3(0.0f, 0.0f, 1.0f), Direction::FORWARD) - plane_origin;
    loc_normal = glm::normalize(loc_normal);
    loc_color = base_color_m;
    return true;
}

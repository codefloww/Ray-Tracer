//
// Created by paul on 3/12/23.
//

#include "objects/sphere.hpp"
#include <cmath>

Sphere::Sphere() = default;

bool Sphere::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const {
    Ray local_ray = transformation_m.applyTransform(cast_ray, Direction::BACKWARD);
    auto ray_origin = local_ray.getOrigin();
    float b = 2.0f * glm::dot(ray_origin, local_ray.getDirection());
    float c = glm::dot(ray_origin, ray_origin) - 1.0f;
    float discriminant = b * b - 4.0 * c;

    glm::vec3 loc_int_point;

    if (discriminant < 0.0) {
        return false;
    }

    float num_sqrt = sqrt(discriminant);

    float t1 = (-b + num_sqrt) / 2.0;
    if (t1 < 0.0f) {
        return false;
    }

    float t2 = (-b - num_sqrt) / 2.0;

    if (t2 < 0.0f) {
        loc_int_point = local_ray.getPoint(t1);
        loc_normal = -glm::normalize(loc_int_point);
    } else {
        loc_int_point = local_ray.getPoint(t2);
        loc_normal = glm::normalize(loc_int_point);
    }

    int_point = transformation_m.applyTransform(loc_int_point, Direction::FORWARD);
    return true;
}







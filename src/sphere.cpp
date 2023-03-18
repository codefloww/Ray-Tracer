//
// Created by paul on 3/12/23.
//

#include "../inc/sphere.hpp"
#include <cmath>

Sphere::Sphere(const glm::vec3 &position, double radius) : position_m(position), radius_m(radius) {}

bool
Sphere::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 loc_color) const {
    glm::vec3 vhat = cast_ray.getDirection();
    double b = 2.0 * glm::dot(vhat, cast_ray.getOrigin() - position_m);
    double c = glm::dot(cast_ray.getOrigin() - position_m, cast_ray.getOrigin() - position_m) - radius_m * radius_m;
    double discriminant = b * b - 4.0 * c;

    if (discriminant < 0.0) {
        return false;
    } else {
        double num_sqrt = sqrt(discriminant);
        double t1 = (-b + num_sqrt) / 2.0;
        double t2 = (-b - num_sqrt) / 2.0;
        if ((t1 < 0.0) || (t2 < 0.0)) {
            return false;
        } else {
            if (t1 < t2) {
                int_point = cast_ray.getOrigin() + vhat * static_cast<float>(t1);
            } else {
                int_point = cast_ray.getOrigin() + vhat * static_cast<float>(t2);
            }
            loc_normal = glm::normalize(int_point - position_m);
            return true;
        }
    }
}

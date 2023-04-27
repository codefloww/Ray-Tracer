//
// Created by paul on 3/12/23.
//

#include "objects/sphere.hpp"
#include <cmath>

bool Sphere::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal,
                               glm::vec3 &loc_color) const {
    // Copy the ray and transform it into the local coordinate system of the sphere
    Ray local_ray = transformation_m.applyTransform(cast_ray, Direction::BACKWARD);

    glm::vec3 v_hat = local_ray.getDirection();
    double b = 2.0 * glm::dot(local_ray.getOrigin(), v_hat);
    double c = glm::dot(local_ray.getOrigin(), local_ray.getOrigin()) - 1.0f;
    double discriminant = b * b - 4.0 * c;

    glm::vec3 loc_int_point;

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
                loc_int_point = local_ray.getOrigin() + v_hat * static_cast<float>(t1);
            } else {
                loc_int_point = local_ray.getOrigin() + v_hat * static_cast<float>(t2);
            }

            // Transform the intersection point back into the world coordinate system
            int_point = transformation_m.applyTransform(loc_int_point, Direction::FORWARD);
            glm::vec3 sphere_origin = transformation_m.applyTransform(glm::vec3(0.0f, 0.0f, 0.0f), Direction::FORWARD);
            loc_normal = glm::normalize(int_point - sphere_origin);

            loc_color = base_color_m;
            return true;
        }
    }
}

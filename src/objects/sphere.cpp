//
// Created by paul on 3/12/23.
//

#include "objects/sphere.hpp"
#include <cmath>

Sphere::Sphere(glm::vec3 center, float radius): center_m(center), radius_m(radius){};

bool Sphere::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const {
    glm::vec3 to_ray = cast_ray.getOrigin() - center_m;
    float a = length(cast_ray.getDirection());
    float half_b = dot(to_ray, cast_ray.getDirection());
    float c = std::pow(length(to_ray), 2) - radius_m * radius_m;
    float discriminant = half_b*half_b - a*c;

    if (discriminant < 0.0) {
        return false;
    }

    float num_sqrt = sqrt(discriminant);
    float t1 = (-half_b + num_sqrt) / a;

    if (t1 < 0.0) { // t1 always bigger than t2, so we can check only it first.
        return false;
    }

    float t2 = (-half_b - num_sqrt) / a;

    if (t2 < 0.0){
        // We're inside the sphere
        int_point = cast_ray.getPoint(t1);
        loc_normal = -glm::normalize(int_point - center_m);
    }
    else{
        // We're outside
        int_point = cast_ray.getPoint(t2);
        loc_normal = glm::normalize(int_point - center_m);
    }

    return true;
}

#include "objects/triangle.hpp"

Triangle::Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    vertices_m[0] = v1;
    vertices_m[1] = v2;
    vertices_m[2] = v3;

    e1_m = vertices_m[1].position - vertices_m[0].position;
    e2_m = vertices_m[2].position - vertices_m[0].position;
    normal_m = glm::normalize(glm::cross(e1_m, e2_m));
}

bool Triangle::testIntersections(const Ray &cast_ray, glm::vec3 &loc_normal, float &distance) const {
    constexpr float kEpsilon = 0.0001f;

    glm::vec3 p_vec = glm::cross(cast_ray.getDirection(), e2_m);
    float determinant = glm::dot(e1_m, p_vec);

    if (determinant < kEpsilon) {
        return false;
    }

    float invDeterminant = 1 / determinant;

    glm::vec3 t_vec = cast_ray.getOrigin() - vertices_m[0].position;

    float u = glm::dot(t_vec, p_vec) * invDeterminant;
    if (u < 0 || u > 1) {
        return false;
    }

    glm::vec3 q_vec = glm::cross(t_vec, e1_m);

    float v = glm::dot(cast_ray.getDirection(), q_vec) * invDeterminant;
    if (v < 0 || u + v > 1) {
        return false;
    }

    distance = glm::dot(e2_m, q_vec) * invDeterminant;

    if (distance < 0.0f) {
        return false;
    }

    if (glm::dot(normal_m, cast_ray.getDirection()) >= 0.0f) {
        // TODO: probably there is a more optimized way to find appropriate direction
        loc_normal = -normal_m;
    } else {
        loc_normal = normal_m;
    }
    return true;
}

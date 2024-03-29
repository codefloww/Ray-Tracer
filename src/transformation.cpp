#include <iostream>
#include <glm/gtx/transform.hpp>
#include "transformation.hpp"

Transformation::Transformation(const glm::mat4 &forw_transform, const glm::mat4 &back_transform) {
    forw_transform_m = forw_transform;
    back_transform_m = back_transform;
}

void Transformation::setTransform(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale) {
    // apply translation
    forw_transform_m = glm::translate(forw_transform_m, translation);

    // apply rotation
    forw_transform_m = glm::rotate(forw_transform_m, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    forw_transform_m = glm::rotate(forw_transform_m, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    forw_transform_m = glm::rotate(forw_transform_m, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    // apply scale
    forw_transform_m = glm::scale(forw_transform_m, scale);

    // calculate back transform
    back_transform_m = glm::inverse(forw_transform_m);
}

glm::mat4x4 Transformation::getForwTransform() const {
    return forw_transform_m;
}

glm::mat4x4 Transformation::getBackTransform() const {
    return back_transform_m;
}

Ray Transformation::applyTransform(const Ray &ray, Direction dir) const {
    glm::vec3 new_origin = applyTransform(ray.getOrigin(), dir);
    glm::vec3 new_dir = applyTransform(ray.getOrigin() + ray.getDirection(), dir);
    return Ray{new_origin, new_dir - new_origin};
}

glm::vec3 Transformation::applyTransform(const glm::vec3 &vec, Direction dir) const {
    auto new_vec = glm::vec4(vec, 1.0f);
    if (dir == Direction::FORWARD) {
        new_vec = forw_transform_m * new_vec;
    } else {
        new_vec = back_transform_m * new_vec;
    }
    return glm::vec3{new_vec};
}

glm::vec3 Transformation::applyLinearTransform(const glm::vec3 &vec,
                                               Direction dir) const { // Apply transformation without its "affine part". Usable for directions - normals, for instance.
    auto new_vec = glm::vec4(vec, 0.0f);
    if (dir == Direction::FORWARD) {
        new_vec = forw_transform_m * new_vec;
    } else {
        new_vec = back_transform_m * new_vec;
    }
    return new_vec;
}

void Transformation::printTransform(Direction dir) const {
    if (dir == Direction::FORWARD) {
        printMatrix(forw_transform_m);
    } else {
        printMatrix(back_transform_m);
    }
}

void Transformation::printMatrix(const glm::mat4x4 &mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Transformation::printVector(const glm::vec3 &vec) {
    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
}

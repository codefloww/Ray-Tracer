//
// Created by paul on 3/31/23.
//

#include <iostream>
#include "../inc/transformation.hpp"

Transformation::Transformation() {
    // set forw and back transform to identity matrix
    forw_transform_m = glm::mat4(1.0f);
    back_transform_m = glm::mat4(1.0f);
}

Transformation::Transformation(const glm::mat4 &forw_transform, const glm::mat4 &back_transform) {
    forw_transform_m = forw_transform;
    back_transform_m = back_transform;
}

void Transformation::setTransform(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale) {
    // set forw and back transform to identity matrix
    forw_transform_m = glm::mat4(1.0f);
    back_transform_m = glm::mat4(1.0f);

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

glm::mat4x4 Transformation::getForwTransform() const{
    return forw_transform_m;
}

glm::mat4x4 Transformation::getBackTransform() const{
    return back_transform_m;
}

Ray Transformation::applyTransform(const Ray &ray, bool dir_flag) const {
    glm::vec3 new_origin = applyTransform(ray.getOrigin(), dir_flag);
    glm::vec3 new_dir = applyTransform(ray.getOrigin() + ray.getDirection(), dir_flag);
    return Ray{new_origin, new_dir - new_origin};
}

glm::vec3 Transformation::applyTransform(const glm::vec3 &vec, bool dir_flag) const {
    auto new_vec = glm::vec4(vec, 1.0f);
    if (dir_flag) {
        new_vec = forw_transform_m * new_vec;
    } else {
        new_vec = back_transform_m * new_vec;
    }
    return glm::vec3{new_vec};
}

void Transformation::printTransform(bool dir_flag) const {
    if (dir_flag) {
        printMat(forw_transform_m);
    } else {
        printMat(back_transform_m);
    }
}

void Transformation::printMat(const glm::mat4x4 &mat) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Transformation::printVec(const glm::vec3 &vec) {
    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
}



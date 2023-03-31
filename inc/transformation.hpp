//
// Created by paul on 3/31/23.
//

#ifndef RAY_TRACER_TRANSFORMATION_HPP
#define RAY_TRACER_TRANSFORMATION_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ray.hpp"

constexpr bool kForwTransform = true;
constexpr bool kBackTransform = false;

class Transformation {
    glm::mat4x4 forw_transform_m;
    glm::mat4x4 back_transform_m;


public:
    Transformation();

    ~Transformation() = default;

    Transformation(const glm::mat4x4 &forw_transform, const glm::mat4x4 &back_transform);

    void setTransform(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

    glm::mat4x4 getForwTransform() const;

    glm::mat4x4 getBackTransform() const;

    [[nodiscard]] Ray applyTransform(const Ray &ray, bool dir_flag) const;

    [[nodiscard]] glm::vec3 applyTransform(const glm::vec3 &vec, bool dir_flag) const;

    Transformation &operator=(const Transformation &rhs) = default;

    void printTransform(bool dir_flag) const;

    void printMat(const glm::mat4x4 &mat) const;

    static void printVec(const glm::vec3 &vec);


};

#endif //RAY_TRACER_TRANSFORMATION_HPP

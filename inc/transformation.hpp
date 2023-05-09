#ifndef RAY_TRACER_TRANSFORMATION_HPP
#define RAY_TRACER_TRANSFORMATION_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

enum class Direction {
    FORWARD,
    BACKWARD,
};

class Transformation {
    glm::mat4x4 forw_transform_m = glm::mat4(1.0f);
    glm::mat4x4 back_transform_m = glm::mat4(1.0f);

public:
    Transformation() = default;

    Transformation(const glm::mat4x4 &forw_transform, const glm::mat4x4 &back_transform);

    Transformation &operator=(const Transformation &rhs) = default;

    void setTransform(const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);

    [[nodiscard]] glm::mat4x4 getForwTransform() const;

    [[nodiscard]] glm::mat4x4 getBackTransform() const;

    [[nodiscard]] Ray applyTransform(const Ray &ray, Direction dir) const;

    [[nodiscard]] glm::vec3 applyTransform(const glm::vec3 &vec, Direction dir) const;

    [[nodiscard]] glm::vec3 applyLinearTransform(const glm::vec3 &vec, Direction dir) const;

    void printTransform(Direction dir) const;

    static void printMatrix(const glm::mat4x4 &mat);

    static void printVector(const glm::vec3 &vec);
};

#endif //RAY_TRACER_TRANSFORMATION_HPP

//
// Created by andrew on 28/04/23.
//

#ifndef RAY_TRACER_TRIANGLE_HPP
#define RAY_TRACER_TRIANGLE_HPP

#include <glm/glm.hpp>
#include <array>
#include "ray.hpp"
#include "object.hpp"

struct Vertex {
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Triangle : public Object {
private:
    std::array<Vertex, 3> vertices_m{};
    glm::vec3 e1_m{};
    glm::vec3 e2_m{};
    glm::vec3 normal_m{};

public:
    Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);

    /**
     * @warning For the triangle class, the transformation of cast ray into object space and back
     * relies exclusively on the caller method.
     */
    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal,
                           glm::vec3 &loc_color) const override;
};

#endif //RAY_TRACER_TRIANGLE_HPP

//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include <vector>
#include "light_source.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "ray.hpp"

class PointLight : public LightSource {
public:
    PointLight();

    bool computeDiffIllum(const glm::vec3 &int_point, const glm::vec3 &loc_normal,
                          const std::vector<std::shared_ptr<Object>> &object_list,
                          const std::shared_ptr<Object> &current_object,
                          glm::vec3 &color, double &intensity) const;

    [[nodiscard]] glm::vec3
    computeSpecIllum(const Ray &camera_ray, const glm::vec3 &int_point, const glm::vec3 &loc_normal) const;
};

#endif //RAY_TRACER_POINT_LIGHT_HPP

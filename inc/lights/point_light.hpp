//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include <vector>
#include "light_source.hpp"
#include "ray.hpp"

extern float POINT_ATTENUATION_CONSTANT_MEMBER;
extern float POINT_ATTENUATION_LINEAR_MEMBER;
extern float POINT_ATTENUATION_QUADRATIC_MEMBER;

class PointLight : public LightSource {
public:
    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);

    explicit PointLight(glm::vec3 position);

    void computeIllumination(const glm::vec3 &int_point,
                             const glm::vec3 &loc_normal,
                             const std::vector<std::shared_ptr<Object>> &object_list,
                             const std::shared_ptr<Object> &current_object,
                             const glm::vec3 &view_dir,
                             glm::vec3 &diffuse_component,
                             std::pair<glm::vec3, float> &specular_component,
                             glm::vec3 &ambient_component) const override;

    [[nodiscard]] bool testIlluminationPresence(const glm::vec3 &int_point,
                                                const std::vector<std::shared_ptr<Object>> &object_list,
                                                const std::shared_ptr<Object> &current_object,
                                                const Ray &light_ray) const override;

    [[nodiscard]] glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                        const glm::vec3 &loc_normal,
                                                        const Ray &light_ray) const override;

    [[nodiscard]] float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                      const Ray &light_ray,
                                                      const glm::vec3 &view_dir) const override;

    [[nodiscard]] double getAttenuation(const glm::vec3 &int_point) const override;
};

#endif //RAY_TRACER_POINT_LIGHT_HPP

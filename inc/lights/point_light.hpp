//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include "light_source.hpp"


class PointLight : public LightSource {
private:
    static constexpr float kAttenConst = 1.0f;
    static constexpr float kAttenLin = 0.09f;
    static constexpr float kAttenQuad = 0.032f;

    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);

    [[nodiscard]] static bool testIlluminationPresence(const glm::vec3 &int_point,
                                                              const glm::vec3 &to_light_unnormalized,
                                                              const std::vector<Object *> &object_list,
                                                              const Object * current_object,
                                                              const Ray &light_ray);

    [[nodiscard]] glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const override;

    [[nodiscard]] float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                  const Ray &light_ray,
                                                  const glm::vec3 &view_dir) const override;

    [[nodiscard]] float getAttenuation(const glm::vec3 &int_point) const override;
public:
    explicit PointLight(glm::vec3 position);

    void computeIllumination(const glm::vec3 &int_point,
                             const glm::vec3 &loc_normal,
                             const std::vector<Object *> &object_list,
                             const Object * current_object,
                             const glm::vec3 &view_dir,
                             glm::vec3 &diffuse_component,
                             glm::vec3 &specular_component,
                             glm::vec3 &ambient_component) const override;

    ~PointLight() override = default;
};

#endif //RAY_TRACER_POINT_LIGHT_HPP

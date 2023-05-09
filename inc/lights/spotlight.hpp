#ifndef RAY_TRACER_SPOTLIGHT_HPP
#define RAY_TRACER_SPOTLIGHT_HPP

#include "light_source.hpp"


class Spotlight : public LightSource {
private:
    static constexpr float kAttenConst = 1.0f;
    static constexpr float kAttenLin = 0.045f;
    static constexpr float kAttenQuad = 0.0075f;

    glm::vec3 position_m;
    glm::vec3 spot_direction_m;
    float inner_cone_angle_m;
    float inner_cone_cos_m;
    float outer_cone_angle_m;
    float outer_cone_cos_m;
    float epsilon_m; // Cos difference between outer and inner cone angles.


    [[nodiscard]] static bool testIlluminationPresence(const glm::vec3 &int_point,
                                                       const glm::vec3 &to_light_unnormalized,
                                                       const std::vector<Object *> &object_list,
                                                       const Object *current_object,
                                                       const Ray &light_ray);

    [[nodiscard]] glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const override;

    [[nodiscard]] float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                  const Ray &light_ray,
                                                  const glm::vec3 &view_dir) const override;

    [[nodiscard]] float getAttenuation(const glm::vec3 &int_point) const override;

    [[nodiscard]] bool testIfInCone(float angle_cos) const;

public:
    Spotlight(const glm::vec3 &position, const glm::vec3 &direction, float inner_angle, float outer_angle);

    void computeIllumination(const glm::vec3 &int_point,
                             const glm::vec3 &loc_normal,
                             const std::vector<Object *> &object_list,
                             const Object *current_object,
                             const glm::vec3 &view_dir,
                             glm::vec3 &diffuse_component,
                             glm::vec3 &specular_component,
                             glm::vec3 &ambient_component) const override;
};

#endif //RAY_TRACER_SPOTLIGHT_HPP

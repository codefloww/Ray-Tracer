#ifndef RAY_TRACER_DIRECTIONAL_LIGHT_H
#define RAY_TRACER_DIRECTIONAL_LIGHT_H

#include "light_source.hpp"

class DirectionalLight : public LightSource {
private:
    static constexpr float kAttenConst = 1.0f;
    static constexpr float kAttenLin = 0.0f;
    static constexpr float kAttenQuad = 0.0f;

    glm::vec3 direction_m {1.0f, 1.0f, 1.0f};
    float m_distance = 1000.0f;
    glm::vec3 color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    float intensity_m = 1.0f;
    float spec_intensity_m = 0.2f;
    float ambient_intensity_m = 0.005f;

    [[nodiscard]] static bool testIlluminationPresence(const std::vector<Object *> &object_list,
                                                              const Object * current_object,
                                                              const Ray &light_ray) ;

    [[nodiscard]] glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const override;

    [[nodiscard]] float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                  const Ray &light_ray,
                                                  const glm::vec3 &view_dir) const override;

    [[nodiscard]] float getAttenuation(const glm::vec3 &int_point) const override;
public:
    explicit DirectionalLight(glm::vec3 direction);

    void computeIllumination(const glm::vec3 &int_point,
                             const glm::vec3 &loc_normal,
                             const std::vector<Object *> &object_list,
                             const Object * current_object,
                             const glm::vec3 &view_dir,
                             glm::vec3 &diffuse_component,
                             glm::vec3 &specular_component,
                             glm::vec3 &ambient_component) const override;

    ~DirectionalLight() override = default;
};


#endif //RAY_TRACER_DIRECTIONAL_LIGHT_H

#ifndef RAY_TRACER_DIRECTIONAL_LIGHT_H
#define RAY_TRACER_DIRECTIONAL_LIGHT_H

#include "light_source.hpp"

class DirectionalLight : public LightSource {
private:
    static constexpr float M_ATTENUATION_CONSTANT_MEMBER = 1.0f;
    static constexpr float M_ATTENUATION_LINEAR_MEMBER = 0.0f;
    static constexpr float M_ATTENUATION_QUADRATIC_MEMBER = 0.0f;

    glm::vec3 m_direction {1.0f, 1.0f, 1.0f};
    float m_distance = 1000.0f;

    [[nodiscard]] static inline bool testIlluminationPresence(const std::vector<Object *> &object_list,
                                                              const Object * current_object,
                                                              const Ray &light_ray) ;

    [[nodiscard]] inline glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const override;

    [[nodiscard]] inline float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                  const Ray &light_ray,
                                                  const glm::vec3 &view_dir) const override;

    [[nodiscard]] inline double getAttenuation(const glm::vec3 &int_point) const override;
public:
    explicit DirectionalLight(glm::vec3 direction);

    void computeIllumination(const glm::vec3 &int_point,
                             const glm::vec3 &loc_normal,
                             const std::vector<Object *> &object_list,
                             const Object * current_object,
                             const glm::vec3 &view_dir,
                             glm::vec3 &diffuse_component,
                             std::pair<glm::vec3, float> &specular_component,
                             glm::vec3 &ambient_component) const override;

    ~DirectionalLight() override = default;
};


#endif //RAY_TRACER_DIRECTIONAL_LIGHT_H

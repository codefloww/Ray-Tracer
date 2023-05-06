#ifndef RAY_TRACER_DIRECTIONAL_LIGHT_H
#define RAY_TRACER_DIRECTIONAL_LIGHT_H

#include "light_source.hpp"

extern float DIRECTIONAL_ATTENUATION_CONSTANT_MEMBER;
extern float DIRECTIONAL_ATTENUATION_LINEAR_MEMBER;
extern float DIRECTIONAL_ATTENUATION_QUADRATIC_MEMBER;

class DirectionalLight : public LightSource {
private:
    glm::vec3 m_direction {1.0f, 1.0f, 1.0f};

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
public:
    explicit DirectionalLight(glm::vec3 direction);

    void computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<std::shared_ptr<Object>> &object_list,
                                     const std::shared_ptr<Object> &current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     std::pair<glm::vec3, float> &specular_component,
                                     glm::vec3 &ambient_component) const override;
};


#endif //RAY_TRACER_DIRECTIONAL_LIGHT_H

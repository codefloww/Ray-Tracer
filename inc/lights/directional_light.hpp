#ifndef RAY_TRACER_DIRECTIONAL_LIGHT_H
#define RAY_TRACER_DIRECTIONAL_LIGHT_H

#include <vector>
#include "light_source.hpp"
#include "ray.hpp"

extern float ATTENUATION_CONSTANT_MEMBER;
extern float ATTENUATION_LINEAR_MEMBER;
extern float ATTENUATION_QUADRATIC_MEMBER;

class DirectionalLight : public LightSource {
public:
    DirectionalLight();

    [[nodiscard]] bool testIlluminationPresence(const glm::vec3 &int_point,
                                                const std::vector<std::shared_ptr<Object>> &object_list,
                                                const std::shared_ptr<Object> &current_object) const override;

    [[nodiscard]] glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray,
                                                       glm::vec3 &color) const override;

    [[nodiscard]] glm::vec3 computeSpecularIllumination(const glm::vec3 &int_point,
                                                        const glm::vec3 &loc_normal,
                                                        const Ray &light_ray,
                                                        const glm::vec3 &view_dir,
                                                        float shininess) const override;

    [[nodiscard]] double getAttenuation(const glm::vec3 &int_point) const override;
};

#endif //RAY_TRACER_DIRECTIONAL_LIGHT_H

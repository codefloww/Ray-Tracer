//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include "objects/object.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>

class LightSource {
protected:
    glm::vec3 color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    float intensity_m = 1.0f;
    float m_spec_intensity;

public:
    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);

    void setPosition(const glm::vec3 &position);

    void setColor(const glm::vec3 &color);

    [[nodiscard]] glm::vec3 getColor() const;

    void setIntensity(float intensity);

    [[nodiscard]] virtual bool testIlluminationPresence(const glm::vec3 &int_point,
                                                        const std::vector<std::shared_ptr<Object>> &object_list,
                                                        const std::shared_ptr<Object> &current_object) const = 0;

    [[nodiscard]] virtual glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                                const glm::vec3 &loc_normal,
                                                                const Ray &light_ray,
                                                                glm::vec3 &color) const = 0;

    [[nodiscard]] virtual glm::vec3 computeSpecularIllumination(const glm::vec3 &int_point,
                                                                const glm::vec3 &loc_normal,
                                                                const Ray &light_ray,
                                                                const glm::vec3 &view_dir,
                                                                float shininess) const = 0;

    [[nodiscard]] virtual double getAttenuation(const glm::vec3 &int_point) const = 0;
};

#endif //RAY_TRACER_LIGHT_SOURCE_HPP

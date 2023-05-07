#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include "objects/object.hpp"
#include "ray.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <algorithm>

class LightSource {
private:
    static constexpr float M_ATTENUATION_CONSTANT_MEMBER = 1.0f;
    static constexpr float M_ATTENUATION_LINEAR_MEMBER = 0.0f;
    static constexpr float M_ATTENUATION_QUADRATIC_MEMBER = 0.0f;

    [[nodiscard]] virtual glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                               const glm::vec3 &loc_normal,
                                                               const Ray &light_ray) const = 0;

    [[nodiscard]] virtual float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                          const Ray &light_ray,
                                                          const glm::vec3 &view_dir) const = 0;

    [[nodiscard]] virtual double getAttenuation(const glm::vec3 &int_point) const = 0;

protected:
    glm::vec3 color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    float intensity_m = 1.0f;
    float m_spec_intensity;
    float m_ambient_intensity;

public:
    void setColor(const glm::vec3 &color);

    [[nodiscard]] glm::vec3 getColor() const;

    void setIntensity(float intensity);

    virtual void computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<std::shared_ptr<Object>> &object_list,
                                     const std::shared_ptr<Object> &current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     std::pair<glm::vec3, float> &specular_component,
                                     glm::vec3 &ambient_component) const = 0;
};

#endif //RAY_TRACER_LIGHT_SOURCE_HPP

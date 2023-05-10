#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include "objects/object.hpp"
#include "ray.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <algorithm>

class LightSource {

    [[nodiscard]] virtual glm::vec3 computeDiffuseIllumination(const glm::vec3 &int_point,
                                                               const glm::vec3 &loc_normal,
                                                               const Ray &light_ray) const = 0;

    [[nodiscard]] virtual float computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                                          const Ray &light_ray,
                                                          const glm::vec3 &view_dir) const = 0;

    [[nodiscard]] virtual float getAttenuation(const glm::vec3 &int_point) const = 0;

protected:
    glm::vec3 color_m;
    float intensity_m;
    float spec_intensity_m;
    float ambient_intensity_m;

public:
    void setColor(const glm::vec3 &color);

    [[nodiscard]] glm::vec3 getColor() const;

    void setIntensity(float intensity);

    virtual void computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<Object *> &object_list,
                                     const Object *current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     glm::vec3 &specular_component,
                                     glm::vec3 &ambient_component) const = 0;

    virtual ~LightSource() = default;
};

#endif //RAY_TRACER_LIGHT_SOURCE_HPP

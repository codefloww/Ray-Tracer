#include <iostream>
#include "lights/directional_light.hpp"

DirectionalLight::DirectionalLight(glm::vec3 direction) : LightSource() {
    m_direction = normalize(direction);
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.2f;
    m_ambient_intensity = 0.005f;
}

void DirectionalLight::computeIllumination(const glm::vec3 &int_point,
                                           const glm::vec3 &loc_normal,
                                           const std::vector<Object *> &object_list,
                                           const Object * current_object,
                                           const glm::vec3 &view_dir,
                                           glm::vec3 &diffuse_component,
                                           std::pair<glm::vec3, float> &specular_component,
                                           glm::vec3 &ambient_component) const {
    Ray light_ray(int_point, -m_direction);
    if (testIlluminationPresence(object_list, current_object, light_ray)){
        auto attenuation = static_cast<float>(getAttenuation(int_point));
        diffuse_component = attenuation * computeDiffuseIllumination(int_point, loc_normal, light_ray);
        specular_component.first = attenuation * m_spec_intensity * color_m * intensity_m;
        specular_component.second = computeSpecularMultiplier(loc_normal, light_ray, view_dir);
    }
    else{
        diffuse_component = {0, 0, 0};
        specular_component = {{0, 0, 0}, 0};
    }

    ambient_component = m_ambient_intensity * color_m;
}

bool DirectionalLight::testIlluminationPresence(const std::vector<Object *> &object_list,
                                                const Object * current_object,
                                                const Ray &light_ray) {
    glm::vec3 test_int_point;
    glm::vec3 test_loc_normal;
    for (const auto &object: object_list) {
        if (object == current_object) {
            continue;
        }
        if (object->testIntersections(light_ray, test_int_point, test_loc_normal)) {
            return false;
        }
    }
    return true;
}

glm::vec3 DirectionalLight::computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const {
    float angle_cos = glm::max(glm::dot(loc_normal, -m_direction), 0.0f); //TODO: check normal directions: inner or not
    return angle_cos * intensity_m * color_m;
}

float DirectionalLight::computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                            const Ray &light_ray,
                                            const glm::vec3 &view_dir) const {
    glm::vec3 light_dir = light_ray.getDirection();
    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    return glm::max(glm::dot(loc_normal, halfway_dir), 0.0f);
}

double DirectionalLight::getAttenuation(const glm::vec3 &int_point) const {
    return 1.0f / (M_ATTENUATION_CONSTANT_MEMBER + M_ATTENUATION_LINEAR_MEMBER * m_distance + M_ATTENUATION_QUADRATIC_MEMBER * m_distance * m_distance);
}




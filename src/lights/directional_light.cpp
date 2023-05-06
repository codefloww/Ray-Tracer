#include "lights/directional_light.hpp"

float DIRECTIONAL_ATTENUATION_CONSTANT_MEMBER = 1.0f;
float DIRECTIONAL_ATTENUATION_LINEAR_MEMBER = 0.0f;
float DIRECTIONAL_ATTENUATION_QUADRATIC_MEMBER = 0.0f;

DirectionalLight::DirectionalLight(glm::vec3 direction) : LightSource() {
    m_direction = normalize(direction);
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.5f;
}

void DirectionalLight::computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<std::shared_ptr<Object>> &object_list,
                                     const std::shared_ptr<Object> &current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     std::pair<glm::vec3, float> &specular_component,
                                     glm::vec3 &ambient_component) const {
    Ray light_ray(int_point, m_direction);
    if (testIlluminationPresence(int_point, object_list, current_object, light_ray)){
        auto attenuation = static_cast<float>(getAttenuation(int_point));
        diffuse_component = attenuation * computeDiffuseIllumination(int_point, loc_normal, light_ray);
        specular_component.first = attenuation * m_spec_intensity * color_m * intensity_m;
        specular_component.second = computeSpecularMultiplier(loc_normal, light_ray, view_dir);
        ambient_component = m_ambient_intensity * color_m;
    }
}

bool DirectionalLight::testIlluminationPresence(const glm::vec3 &int_point,
                                          const std::vector<std::shared_ptr<Object>> &object_list,
                                          const std::shared_ptr<Object> &current_object,
                                          const Ray &light_ray) const {
    glm::vec3 between_int_point;
    glm::vec3 between_loc_normal;
    for (const auto &object: object_list) {
        if (object == current_object) {
            continue;
        }
        if (object->testIntersections(light_ray, between_int_point, between_loc_normal)) {
            return false;
        }
    }
    return true;
}

glm::vec3 DirectionalLight::computeDiffuseIllumination(const glm::vec3 &int_point,
                                                       const glm::vec3 &loc_normal,
                                                       const Ray &light_ray) const {
    float angle = glm::max(glm::dot(loc_normal, m_direction), 0.0f); //TODO: check normal directions: inner or not
    return angle * intensity_m * color_m;
}

float DirectionalLight::computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                            const Ray &light_ray,
                                            const glm::vec3 &view_dir) const {
    glm::vec3 light_dir = light_ray.getDirection();
    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    return glm::max(glm::dot(loc_normal, halfway_dir), 0.0f);
}

double DirectionalLight::getAttenuation(const glm::vec3 &int_point) const {
    //double distance = glm::length((position_m - int_point));
    //return 1.0f / (DIRECTIONAL_ATTENUATION_CONSTANT_MEMBER + DIRECTIONAL_ATTENUATION_LINEAR_MEMBER * distance + DIRECTIONAL_ATTENUATION_QUADRATIC_MEMBER * distance * distance);
    return 1.0f;
}




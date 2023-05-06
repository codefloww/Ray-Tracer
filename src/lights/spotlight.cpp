#include <iostream>
#include "lights/spotlight.hpp"

float SPOTLIGHT_ATTENUATION_CONSTANT_MEMBER = 1.0f;
float SPOTLIGHT_ATTENUATION_LINEAR_MEMBER = 0.045f;
float SPOTLIGHT_ATTENUATION_QUADRATIC_MEMBER = 0.0075f;

Spotlight::Spotlight(glm::vec3 position, glm::vec3 direction, float inner_angle, float outer_angle) :
    LightSource(), position_m(position), spot_direction_m(normalize(direction)), inner_cone_angle_m(inner_angle),
    outer_cone_angle_m(outer_angle){

    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.5f;
    m_ambient_intensity = 0.005f;

    inner_cone_cos_m = cos(glm::radians(inner_cone_angle_m));
    outer_cone_cos_m = cos(glm::radians(outer_cone_angle_m));
    epsilon_m = inner_cone_cos_m - outer_cone_cos_m;
}

void Spotlight::computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<std::shared_ptr<Object>> &object_list,
                                     const std::shared_ptr<Object> &current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     std::pair<glm::vec3, float> &specular_component,
                                     glm::vec3 &ambient_component) const {
    Ray light_ray(int_point, position_m - int_point); // From the intersection point to the light point
    float theta = glm::dot(light_ray.getDirection(), -spot_direction_m); // theta - angle between (int_point -> spotlight position) and (reversed spotlight direction)
    if (testIfInCone(theta) && testIlluminationPresence(int_point, object_list, current_object, light_ray)){
        float spotlightCoefficient = std::clamp(((theta - outer_cone_cos_m) / epsilon_m), 0.0f, 1.0f);
        auto attenuation = static_cast<float>(getAttenuation(int_point));
        diffuse_component = spotlightCoefficient * attenuation * computeDiffuseIllumination(int_point, loc_normal, light_ray);
        specular_component.first = spotlightCoefficient * attenuation * m_spec_intensity * color_m * intensity_m;
        specular_component.second = computeSpecularMultiplier(loc_normal, light_ray, view_dir);
    }
    else{
        diffuse_component = {0, 0, 0};
        specular_component = {{0, 0, 0}, 0};
    }
    ambient_component = m_ambient_intensity * color_m;
}

bool Spotlight::testIlluminationPresence(const glm::vec3 &int_point,
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

glm::vec3 Spotlight::computeDiffuseIllumination(const glm::vec3 &int_point,
                                                 const glm::vec3 &loc_normal,
                                                 const Ray &light_ray) const {
    float angle = glm::max(glm::dot(loc_normal, light_ray.getDirection()), 0.0f); //TODO: check normal directions: inner or not
    return angle * intensity_m * color_m;
}

float Spotlight::computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                            const Ray &light_ray,
                                            const glm::vec3 &view_dir) const {
    glm::vec3 light_dir = light_ray.getDirection();
    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    return glm::max(glm::dot(loc_normal, halfway_dir), 0.0f);
}

double Spotlight::getAttenuation(const glm::vec3 &int_point) const {
    double distance = glm::length((position_m - int_point));
    return 1.0f / (SPOTLIGHT_ATTENUATION_CONSTANT_MEMBER + SPOTLIGHT_ATTENUATION_LINEAR_MEMBER * distance + SPOTLIGHT_ATTENUATION_QUADRATIC_MEMBER * distance * distance);
}



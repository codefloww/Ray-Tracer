//
// Created by paul on 3/18/23.
//

#include <iostream>
#include "lights/point_light.hpp"

float POINT_ATTENUATION_CONSTANT_MEMBER = 1.0f;
float POINT_ATTENUATION_LINEAR_MEMBER = 0.09f;
float POINT_ATTENUATION_QUADRATIC_MEMBER = 0.032f;

PointLight::PointLight(glm::vec3 position) : LightSource(), position_m(position) {
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.5f;
    m_ambient_intensity = 0.005f;
}

void PointLight::computeIllumination(const glm::vec3 &int_point,
                         const glm::vec3 &loc_normal,
                         const std::vector<std::shared_ptr<Object>> &object_list,
                         const std::shared_ptr<Object> &current_object,
                         const glm::vec3 &view_dir,
                         glm::vec3 &diffuse_component,
                         std::pair<glm::vec3, float> &specular_component,
                         glm::vec3 &ambient_component) const {
    Ray light_ray(int_point, position_m - int_point); // From the intersection point to the light point
    if (testIlluminationPresence(int_point, object_list, current_object, light_ray)){
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

bool PointLight::testIlluminationPresence(const glm::vec3 &int_point,
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

glm::vec3 PointLight::computeDiffuseIllumination(const glm::vec3 &int_point,
                                                 const glm::vec3 &loc_normal,
                                                 const Ray &light_ray) const {
    float angle = glm::max(glm::dot(loc_normal, light_ray.getDirection()), 0.0f); //TODO: check normal directions: inner or not
    return angle * intensity_m * color_m;
}

float PointLight::computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                            const Ray &light_ray,
                                            const glm::vec3 &view_dir) const {
    glm::vec3 light_dir = light_ray.getDirection();
    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    return glm::max(glm::dot(loc_normal, halfway_dir), 0.0f);
}

double PointLight::getAttenuation(const glm::vec3 &int_point) const {
    double distance = glm::length((position_m - int_point));
    return 1.0f / (POINT_ATTENUATION_CONSTANT_MEMBER + POINT_ATTENUATION_LINEAR_MEMBER * distance + POINT_ATTENUATION_QUADRATIC_MEMBER * distance * distance);
}


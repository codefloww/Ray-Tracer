//
// Created by paul on 3/18/23.
//

#include <iostream>
#include "lights/point_light.hpp"

float ATTENUATION_CONSTANT_MEMBER = 1.0f;
float ATTENUATION_LINEAR_MEMBER = 0.09f;
float ATTENUATION_QUADRATIC_MEMBER = 0.032f;

PointLight::PointLight() : LightSource() {
    position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.5f;
}

bool PointLight::testIlluminationPresence(const glm::vec3 &int_point,
                                          const std::vector<std::shared_ptr<Object>> &object_list,
                                          const std::shared_ptr<Object> &current_object) const {
    Ray light_ray(int_point, position_m - int_point);
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
                                                 const Ray &light_ray,
                                                 glm::vec3 &color) const {
    float angle = glm::max(glm::dot(loc_normal, light_ray.getDirection()), 0.0f); //TODO: check normal directions: inner or not
    return angle * intensity_m * color_m;
}

glm::vec3 PointLight::computeSpecularIllumination(const glm::vec3 &int_point,
                                                  const glm::vec3 &loc_normal,
                                                  const Ray &light_ray,
                                                  const glm::vec3 &view_dir,
                                                  float shininess) const {
    glm::vec3 temp = -light_ray.getDirection();
    glm::vec3 light_reflect_dir{temp - 2.0f * dot(temp, loc_normal) * loc_normal}; // Always normalized(no)
//    glm::vec3 light_dir = glm::normalize(position_m - int_point);
//    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    float spec = std::pow(glm::max(glm::dot(view_dir, light_reflect_dir), 0.0f), shininess);
    return m_spec_intensity * spec * color_m;
}

double PointLight::getAttenuation(const glm::vec3 &int_point) const {
    double distance = glm::length((position_m - int_point));
    return 1.0f / (ATTENUATION_CONSTANT_MEMBER + ATTENUATION_LINEAR_MEMBER * distance + ATTENUATION_QUADRATIC_MEMBER * distance * distance);
}


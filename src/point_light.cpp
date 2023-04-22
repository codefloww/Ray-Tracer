//
// Created by paul on 3/18/23.
//

#include "point_light.hpp"

PointLight::PointLight() : LightSource() {
    position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
}

bool PointLight::computeDiffIllum(const glm::vec3 &int_point, const glm::vec3 &loc_normal,
                                  const std::vector<std::shared_ptr<Object>> &object_list,
                                  const std::shared_ptr<Object> &current_object, glm::vec3 &color,
                                  double &intensity) const {

    Ray light_ray(int_point, position_m - int_point);
    glm::vec3 betweeen_int_point;
    glm::vec3 between_loc_normal;
    glm::vec3 between_loc_color;
    for (const auto &object: object_list) {
        if (object == current_object) {
            continue;
        }
        if (object->testIntersections(light_ray, betweeen_int_point, between_loc_normal, between_loc_color)) {
            color = color_m;
            intensity = 0.0;
            return false;
        }
    }

    double angle = glm::acos(glm::dot(loc_normal, light_ray.getDirection()));
    if (angle > glm::half_pi<decltype(angle)>()) {
        color = color_m;
        intensity = 0.0;
        return false;
    } else {
        color = color_m;
        intensity = intensity_m * (1.0 - (angle / glm::half_pi<decltype(angle)>()));
        return true;
    }
}

glm::vec3
PointLight::computeSpecIllum(const Ray &camera_ray, const glm::vec3 &int_point, const glm::vec3 &loc_normal) const {
    float spec_intensity = 0.5f;
    glm::vec3 view_dir = glm::normalize(camera_ray.getOrigin() - int_point);
    glm::vec3 light_dir = glm::normalize(position_m - int_point);
    glm::vec3 reflect_dir = glm::reflect(-light_dir, loc_normal);
    float spec_angle = std::pow(glm::max(glm::dot(view_dir, reflect_dir), 0.0f), 16);
    return spec_intensity * spec_angle * color_m;
}


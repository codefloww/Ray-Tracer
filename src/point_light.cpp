//
// Created by paul on 3/18/23.
//

#include "point_light.hpp"

PointLight::PointLight() : LightSource() {
    position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
}

bool PointLight::computeIllumination(const glm::vec3 &int_point, const glm::vec3 &loc_normal,
                                     const std::vector<std::shared_ptr<Object>> &object_list,
                                     const std::shared_ptr<Object> &current_object, glm::vec3 &color,
                                     double &intensity) const {
    glm::vec3 light_dir = glm::normalize(position_m - int_point);
    double angle = glm::acos(glm::dot(loc_normal, light_dir));

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

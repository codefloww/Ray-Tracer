//
// Created by paul on 3/18/23.
//

#include <iostream>
#include "lights/point_light.hpp"


PointLight::PointLight(glm::vec3 position) : LightSource(), position_m(position) {
    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    m_spec_intensity = 0.5f;
    m_ambient_intensity = 0.005f;
}

void PointLight::computeIllumination(const glm::vec3 &int_point,
                                     const glm::vec3 &loc_normal,
                                     const std::vector<Object *> &object_list,
                                     const Object * const current_object,
                                     const glm::vec3 &view_dir,
                                     glm::vec3 &diffuse_component,
                                     std::pair<glm::vec3, float> &specular_component,
                                     glm::vec3 &ambient_component) const {
    glm::vec3 to_light_unnormalized(position_m - int_point);
    Ray light_ray(int_point, to_light_unnormalized); // From the intersection point to the light point
    if (testIlluminationPresence(int_point, to_light_unnormalized, object_list, current_object, light_ray)){
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
                                          const glm::vec3 &to_light_unnormalized,
                                          const std::vector<Object *> &object_list,
                                          const Object * const current_object,
                                          const Ray &light_ray) {
    glm::vec3 test_int_point;
    glm::vec3 test_loc_normal;
    glm::vec3 test_vector;
    for (const auto &object: object_list) {
        if (object == current_object) {
            continue;
        }
        if (object->testIntersections(light_ray, test_int_point, test_loc_normal)) {
            // Probably point light is closer than intersected object.
            test_vector = test_int_point - int_point;
            /* Unfortunately, we should check all three axis, because in the opposite case
             * due to a floating point calculation errors we will get some undesired lines of light, where they shouldn't be.
             * */
            if (test_vector.x / to_light_unnormalized.x < 1.0 ||
                test_vector.y / to_light_unnormalized.y < 1.0 ||
                test_vector.z / to_light_unnormalized.z < 1.0){
                // Intersected object yet closer
                return false;
            }
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
    return 1.0f / (M_ATTENUATION_CONSTANT_MEMBER + M_ATTENUATION_LINEAR_MEMBER * distance + M_ATTENUATION_QUADRATIC_MEMBER * distance * distance);
}


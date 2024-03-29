#include "lights/spotlight.hpp"


Spotlight::Spotlight(const glm::vec3 &position, const glm::vec3 &direction, float inner_angle, float outer_angle) :
        LightSource(), position_m(position), spot_direction_m(normalize(direction)), inner_cone_angle_m(inner_angle),
        outer_cone_angle_m(outer_angle) {

    color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    intensity_m = 1.0f;
    spec_intensity_m = 0.5f;
    ambient_intensity_m = 0.1f;

    inner_cone_cos_m = std::cos(glm::radians(inner_cone_angle_m));
    outer_cone_cos_m = std::cos(glm::radians(outer_cone_angle_m));
    epsilon_m = inner_cone_cos_m - outer_cone_cos_m;
}

void Spotlight::computeIllumination(const glm::vec3 &int_point,
                                    const glm::vec3 &loc_normal,
                                    const std::vector<Object *> &object_list,
                                    const Object *current_object,
                                    const glm::vec3 &view_dir,
                                    glm::vec3 &diffuse_component,
                                    glm::vec3 &specular_component,
                                    glm::vec3 &ambient_component) const {
    glm::vec3 to_light_unnormalized(position_m - int_point);
    Ray light_ray(int_point, to_light_unnormalized); // From the intersection point to the light point

    // theta - angle between (int_point -> spotlight position) and (reversed spotlight direction)
    float theta = glm::dot(light_ray.getDirection(), -spot_direction_m);
    bool illuminated = testIlluminationPresence(int_point, to_light_unnormalized, object_list, current_object,
                                                light_ray);

    if (testIfInCone(theta) && illuminated) {
        float spotlightCoefficient = std::clamp(((theta - outer_cone_cos_m) / epsilon_m), 0.0f, 1.0f);
        auto attenuation = getAttenuation(int_point);

        diffuse_component =
                spotlightCoefficient * attenuation * computeDiffuseIllumination(int_point, loc_normal, light_ray);

        specular_component = attenuation * spec_intensity_m * color_m * intensity_m *
                             std::pow(computeSpecularMultiplier(loc_normal, light_ray, view_dir),
                                      current_object->getMaterial().getShininess());
    } else {
        diffuse_component = {0, 0, 0};
        specular_component = {0, 0, 0};
    }
    ambient_component = ambient_intensity_m * color_m;
}

bool Spotlight::testIlluminationPresence(const glm::vec3 &int_point,
                                         const glm::vec3 &to_light_unnormalized,
                                         const std::vector<Object *> &object_list,
                                         const Object *current_object,
                                         const Ray &light_ray) {
    glm::vec3 test_int_point;
    glm::vec3 test_loc_normal;
    glm::vec3 test_vector;
    for (const auto &object: object_list) {
        if (object == current_object) {
            continue;
        }
        if (object->testIntersections(light_ray, test_int_point, test_loc_normal)) {
            // Probably spotlight is closer than intersected object.
            test_vector = test_int_point - int_point;
            /* Unfortunately, we should check all three axis, because in the opposite case
             * due to a floating point calculation errors we will get some undesired lines of light, where they shouldn't be.
             * */
            if (test_vector.x / to_light_unnormalized.x < 1.0 ||
                test_vector.y / to_light_unnormalized.y < 1.0 ||
                test_vector.z / to_light_unnormalized.z < 1.0) {
                // Intersected object yet closer
                return false;
            }
        }
    }
    return true;
}

glm::vec3 Spotlight::computeDiffuseIllumination(const glm::vec3 &int_point,
                                                const glm::vec3 &loc_normal,
                                                const Ray &light_ray) const {
    float angle = glm::max(glm::dot(loc_normal, light_ray.getDirection()),
                           0.0f); //TODO: check normal directions: inner or not
    return angle * intensity_m * color_m;
}

float Spotlight::computeSpecularMultiplier(const glm::vec3 &loc_normal,
                                           const Ray &light_ray,
                                           const glm::vec3 &view_dir) const {
    glm::vec3 light_dir = light_ray.getDirection();
    glm::vec3 halfway_dir = glm::normalize(light_dir + view_dir);
    return glm::max(glm::dot(loc_normal, halfway_dir), 0.0f);
}

bool Spotlight::testIfInCone(const float angle_cos) const {
    if (angle_cos < outer_cone_cos_m) {
        return false;
    }
    return true;
}

float Spotlight::getAttenuation(const glm::vec3 &int_point) const {
    float distance = glm::length((position_m - int_point));
    return 1.0f / (kAttenConst + kAttenLin * distance + kAttenQuad * distance * distance);
}



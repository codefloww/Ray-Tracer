//
// Created by paul on 3/11/23.
//

#include "app/scene.hpp"
#include "objects/trianglemesh.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/blocked_range2d.h>

Scene::Scene() {
    camera_movement_speed_m = 7.5f;
    camera_rotation_speed_m = 7.5f;

    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(std::make_shared<PointLight>());
    light_list_m[0]->setPosition(glm::vec3(-0.0f, -10.0f, 25.0f));
    light_list_m[0]->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

    object_list_m.emplace_back(std::make_shared<Sphere>());
    Transformation transformation5;
    transformation5.setTransform(glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(1.0f, 1.0f, 1.0f));
    object_list_m[0]->setTransformation(transformation5);
    Material material1;
    material1.setupMaterial(glm::vec3(0.8f, 0.2f, 0.3f),
                            glm::vec3(0.4f, 0.5f, 0.9f),
                            glm::vec3(1.0f, 1.0f, 1.0f),
                            128.0f);
    object_list_m[0]->setMaterial(material1);
}

void Scene::render(Image &output_image) const {
    namespace tbb = oneapi::tbb;
    using range_t = tbb::blocked_range2d<int>;

    const int width = output_image.getWidth();
    const int height = output_image.getHeight();

    tbb::parallel_for(range_t{0, height, 0, width},
                      [&](const range_t &range) {
                          for (int y = range.rows().begin(); y < range.rows().end(); ++y) {
                              for (int x = range.cols().begin(); x < range.cols().end(); ++x) {
                                  Ray camera_ray;
                                  glm::vec3 int_point;
                                  glm::vec3 loc_normal;
                                  float x_factor = 2 / (static_cast<float>(width));
                                  float y_factor = 2 / (static_cast<float>(height));
                                  float norm_x = static_cast<float>(x) * x_factor - 1;
                                  float norm_y = static_cast<float>(y) * y_factor - 1;
                                  camera_m.createRay(norm_x, norm_y, camera_ray);
                                  internalRender(x, y, camera_ray, output_image, int_point, loc_normal);
                              }
                          }
                      }
    );
}

void Scene::internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point,
                           glm::vec3 &loc_normal) const {
    bool blank = true;
    std::shared_ptr<Object> closest_object;
    glm::vec3 closest_int_point;
    glm::vec3 closest_loc_normal;
    float min_distance = std::numeric_limits<float>::max();

    for (const auto &object_m: object_list_m) {
        bool valid_intersection = object_m->testIntersections(camera_ray,
                                                              int_point,
                                                              loc_normal);
        if (valid_intersection) {
            blank = false;
            float distance = glm::length(camera_ray.getOrigin() - int_point);
            if (distance < min_distance) {
                min_distance = distance;
                closest_object = object_m;
                closest_int_point = int_point;
                closest_loc_normal = loc_normal;
            }
        }
    }

    if (!blank) {
        glm::vec3 output_color = computeColor(camera_ray,
                                              closest_object,
                                              closest_int_point,
                                              closest_loc_normal);

        output_image.setPixel(x, y, output_color);
    } else {
        output_image.setPixel(x, y, output_image.getBgColor());
    }
}

glm::vec3 Scene::computeColor(const Ray &camera_ray, const std::shared_ptr<Object> &current_object,
                              const glm::vec3 &int_point, const glm::vec3 &loc_normal) const {
    float ambient_intensity = 0.05f;
    float intensity{};
    glm::vec3 color{};
    glm::vec3 output_color{};
    glm::vec3 ambient_color{};
    glm::vec3 specular_color{};
    glm::vec3 diffuse_color{};

    bool valid_illumination;
    bool illuminated = false;
    for (const auto &light_m: light_list_m) {
        valid_illumination = light_m->computeDiffIllum(int_point, loc_normal,
                                                       object_list_m,
                                                       current_object, color, intensity);
        specular_color += light_m->computeSpecIllum(camera_ray, object_list_m, current_object, int_point, loc_normal);
        ambient_color += ambient_intensity * light_m->getColor();

        if (valid_illumination) {
            illuminated = true;
            diffuse_color += color * intensity;
        }
    }

    auto ambient_term = ambient_color / static_cast<float>(light_list_m.size());
    if (illuminated) {
        output_color = ambient_term * current_object->getMaterial().getAmbient() +
                       diffuse_color * current_object->getMaterial().getDiffuse() +
                       specular_color * current_object->getMaterial().getSpecular();
    } else {
        output_color = current_object->getMaterial().getAmbient() * ambient_term;
    }

    return output_color;
}

void Scene::moveCamera(CameraMovement direction) {
    switch (direction) {
        case CameraMovement::FORWARD:
            camera_m.moveForward(camera_movement_speed_m * update_time_m);
            break;
        case CameraMovement::BACKWARD:
            camera_m.moveBackward(camera_movement_speed_m * update_time_m);
            break;
        case CameraMovement::LEFT:
            camera_m.moveLeft(camera_movement_speed_m * update_time_m);
            break;
        case CameraMovement::RIGHT:
            camera_m.moveRight(camera_movement_speed_m * update_time_m);
            break;
        case CameraMovement::UP:
            camera_m.moveUp(camera_movement_speed_m * update_time_m);
            break;
        case CameraMovement::DOWN:
            camera_m.moveDown(camera_movement_speed_m * update_time_m);
            break;
    }

    camera_m.updateCameraGeometry();
}

void Scene::rotateCamera(CameraRotation direction) {
    switch (direction) {
        case CameraRotation::LEFT:
            camera_m.rotateLeft(0.1f * camera_rotation_speed_m * update_time_m);
            break;
        case CameraRotation::RIGHT:
            camera_m.rotateRight(0.1f * camera_rotation_speed_m * update_time_m);
            break;
        case CameraRotation::UP:
            camera_m.rotateUp(0.1f * camera_rotation_speed_m * update_time_m);
            break;
        case CameraRotation::DOWN:
            camera_m.rotateDown(0.1f * camera_rotation_speed_m * update_time_m);
            break;
    }

    camera_m.updateCameraGeometry();
}

#include "app/scene.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "lights/point_light.hpp"
#include "lights/directional_light.hpp"
#include "lights/spotlight.hpp"
#include "objects/trianglemesh.hpp"
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/blocked_range2d.h>


Scene::Scene(): background_color_m{0.01, 0.01, 0.01} {

    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(new PointLight(glm::vec3(-25.0f, -10.0f, 25.0f)));
    light_list_m.back()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    light_list_m.emplace_back(new PointLight(glm::vec3(25.0f, -10.0f, 25.0f)));
    light_list_m.back()->setColor(glm::vec3(1.0f, 1.0f, 0.8f));

    object_list_m.emplace_back(new TriangleMesh("../models/suzanne.obj"));

    Transformation suzanneTransform;
    suzanneTransform.setTransform(glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(glm::half_pi<float>(), 0.0f, 0.0f),
                                 glm::vec3(1.0f, 1.0f, 1.0f));
    object_list_m.back()->setTransformation(suzanneTransform);

//    object_list_m.emplace_back(new Sphere());
//    Transformation transformation1;
//    transformation1.setTransform(glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(1.0f, 1.0f, 1.0f));
//
//    object_list_m.back()->setTransformation(transformation1);
    Material material;
    material.setupMaterial(glm::vec3(1.0f, 1.0f, 0.0f),
                           glm::vec3(1.0f, 1.0f, 0.0f),
                           glm::vec3(1.0f, 1.0f, 0.0f),
                           256.0f);
    object_list_m.back()->setMaterial(material);

//    for (int i = 0; i < 100; i++){
//        object_list_m.emplace_back(new Sphere(glm::vec3(0.0f, 3.0f+i*10, 0.0f), 1));
//        object_list_m.back()->setMaterial(material);
//    }
}

void Scene::render(Image &output_image) {
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
                                  double x_factor = 1.0 / (static_cast<double>(width) / 2.0);
                                  double y_factor = 1.0 / (static_cast<double>(height) / 2.0);
                                  double norm_x = static_cast<double>(x) * x_factor - 1.0;
                                  double norm_y = static_cast<double>(y) * y_factor - 1.0;
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
    Object *closest_object;
    glm::vec3 closest_int_point;
    glm::vec3 closest_loc_normal;
    float min_distance = std::numeric_limits<float>::max();

    for (const auto object_m: object_list_m) {
        if (object_m->testIntersections(camera_ray, int_point, loc_normal)) {
            float distance = glm::length(camera_ray.getOrigin() - int_point);
            if (distance < min_distance) {
                blank = false;
                min_distance = distance;
                closest_object = object_m;
                closest_int_point = int_point;
                closest_loc_normal = loc_normal;
            }
        }
    }

    glm::vec3 output_color;
    if (!blank) {
        output_color = computeColor(camera_ray, closest_object, closest_int_point, closest_loc_normal);
    } else {
        output_color = background_color_m;
    }

    output_image.setPixel(x, y, Image::postProcess(output_image.convertColor(glm::vec4 {output_color, 1.0})));
}

glm::vec3
Scene::computeColor(const Ray &camera_ray, const Object* const current_object, const glm::vec3 &int_point,
                    const glm::vec3 &loc_normal) const {
    glm::vec3 diffuse_color{};
    glm::vec3 specular_color{};
    glm::vec3 ambient_color{};
    glm::vec3 output_color{};
    glm::vec3 view_dir{normalize(camera_ray.getOrigin() - int_point)};

    glm::vec3 diffuse_component{};
    glm::vec3 specular_component{};
    glm::vec3 ambient_component{};

    for (const auto light_m: light_list_m) {
        // It is assumed that diffuse_color, specular_color and ambient_color will be reset in the computeIllumination().
        light_m->computeIllumination(int_point, loc_normal, object_list_m, current_object,
                                     view_dir, diffuse_component, specular_component, ambient_component);
        diffuse_color += diffuse_component;
        specular_color += specular_component;
        ambient_color += ambient_component;
    }

    output_color = ambient_color * current_object->getMaterial().getAmbient() +
                   diffuse_color * current_object->getMaterial().getDiffuse() +
                   specular_color * current_object->getMaterial().getSpecular();

    return output_color;
}

void Scene::moveCamera(CameraMovement direction) {
    switch (direction) {
        case CameraMovement::FORWARD:
            camera_m.setPosition(camera_m.getPosition() + camera_m.getDirection() * 0.1f);
            break;
        case CameraMovement::BACKWARD:
            camera_m.setPosition(camera_m.getPosition() - camera_m.getDirection() * 0.1f);
            break;
        case CameraMovement::LEFT:
            camera_m.setPosition(
                    camera_m.getPosition() +
                    glm::normalize(glm::cross(camera_m.getUp(), camera_m.getDirection())) * 0.1f);
            break;
        case CameraMovement::RIGHT:
            camera_m.setPosition(
                    camera_m.getPosition() +
                    glm::normalize(glm::cross(camera_m.getDirection(), camera_m.getUp())) * 0.1f);
            break;
        case CameraMovement::UP:
            camera_m.setPosition(camera_m.getPosition() + camera_m.getUp() * 0.1f);
            break;
        case CameraMovement::DOWN:
            camera_m.setPosition(camera_m.getPosition() - camera_m.getUp() * 0.1f);
            break;
    }

    camera_m.updateCameraGeometry();
}

void Scene::rotateCamera(const glm::vec2 &rotation) {
    glm::vec3 x_axis = glm::normalize(glm::cross(camera_m.getDirection(), camera_m.getUp()));
    camera_m.setDirection(glm::rotate(camera_m.getDirection(), rotation.x, camera_m.getUp()));

    camera_m.setDirection(glm::rotate(camera_m.getDirection(), rotation.y, x_axis));
    camera_m.setUp(glm::rotate(camera_m.getUp(), rotation.y, x_axis));
    camera_m.updateCameraGeometry();
}

Scene::~Scene() {
    for(const auto object_ptr: object_list_m){
        delete object_ptr;
    }
    for(const auto light_ptr: light_list_m){
        delete light_ptr;
    }
}


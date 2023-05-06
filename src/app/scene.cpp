//
// Created by paul on 3/11/23.
//

#include "app/scene.hpp"

Scene::Scene() {
    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(std::make_shared<PointLight>(glm::vec3(-0.0f, -10.0f, 25.0f)));
    light_list_m.back()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    light_list_m.emplace_back(std::make_shared<DirectionalLight>(glm::vec3(1.0f, -2.0f, -1.0f)));
    light_list_m.back()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    light_list_m.back()->setIntensity(0.01f);
//    light_list_m.emplace_back(std::make_shared<PointLight>());
//    light_list_m[0]->setPosition(glm::vec3(25.0f, -10.0f, 25.0f));
//    light_list_m[0]->setColor(glm::vec3(1.0f, 1.0f, 0.8f));
//    light_list_m.emplace_back(std::make_shared<PointLight>());
//    light_list_m[0]->setPosition(glm::vec3(0.0f, -2.0f, 0.0f));
//    light_list_m[0]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

    object_list_m.emplace_back(std::make_shared<Sphere>());
    Transformation transformation1;
    transformation1.setTransform(glm::vec3(-1.5f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.5f, 0.5f, 0.5f));
    Material material1;
    material1.setupMaterial(glm::vec3(0.0f, 1.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f),
                            glm::vec3(1.0f, 1.0f, 1.0f),
                            128.0f);
    object_list_m[0]->setMaterial(material1);
    object_list_m[0]->setTransformation(transformation1);

    object_list_m.emplace_back(std::make_shared<Sphere>());
    Transformation transformation5;
    transformation5.setTransform(glm::vec3(1.5f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.5f, 0.5f, 0.5f));
    Material material5;
    material5.setupMaterial(glm::vec3(0.0f, 1.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f),
                            glm::vec3(1.0f, 1.0f, 1.0f),
                            128.0f);
    object_list_m[1]->setMaterial(material5);
    object_list_m[1]->setTransformation(transformation5);

//    object_list_m.emplace_back(std::make_shared<Plane>());
//    Transformation transplane;
//    transplane.setTransform(glm::vec3(0.0f, 0.0f, -1.0f),
//                            glm::vec3(0.0f, 0.0f, 0.0f),
//                            glm::vec3(50.0f, 50.0f, 1.0f));
//
//    Material material2;
//    material2.setupMaterial(glm::vec3(0.0f, 0.0f, 1.0f),
//                            glm::vec3(0.0f, 0.0f, 1.0f),
//                            glm::vec3(0.0f, 0.0f, 1.0f),
//                            128.0f);
//    object_list_m[1]->setTransformation(transplane);
//    object_list_m[1]->setMaterial(material2);
//    object_list_m[1]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

//    Transformation transformation2;
//    transformation2.setTransform(glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(0.75f, 0.5f, 0.5f));
//    Transformation transformation3;
//    transformation3.setTransform(glm::vec3(1.5f, 0.0f, 0.0f),
//                                 glm::vec3(0.0f, 0.0f, 0.0f),
//                                 glm::vec3(0.75f, 0.75f, 0.75f));
//
//    object_list_m[1]->setTransformation(transformation2);
//    object_list_m[2]->setTransformation(transformation3);
//
//    object_list_m[0]->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
//    object_list_m[1]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
//    object_list_m[2]->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
//
//    object_list_m.emplace_back(std::make_shared<Plane>());
//    Transformation transformation4;
//    transformation4.setTransform(glm::vec3(0.0f, 1.0f, -1.0f),
//                                 glm::vec3(0.1f, 0.0f, 0.0f),
//                                 glm::vec3(5.0f, 5.0f, 1.0f));
//    object_list_m[3]->setTransformation(transformation4);
//    object_list_m[3]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

//    object_list_m.emplace_back(std::make_shared<TriangleMesh>("../models/suzanne.obj"));
//    object_list_m.emplace_back(std::make_shared<TriangleMesh>("../models/cube.obj"));
//
//    Transformation dda1;
//    dda1.setTransform(glm::vec3(4.0f, 0.0f, 2.0f),
//                      glm::vec3(glm::half_pi<float>(), 0.0f, 0.0f),
//                      glm::vec3(2.0f, 2.0f, 2.0f));
//    object_list_m[2]->setTransformation(dda1);
//    Material material3;
//    material3.setupMaterial(glm::vec3(0.8f, 0.2f, 0.3f),
//                            glm::vec3(1.0f, 0.5f, 0.5f),
//                            glm::vec3(1.0f, 1.0f, 1.0f),
//                            256.0f);
//    object_list_m[2]->setMaterial(material3);
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
    std::shared_ptr<Object> closest_object;
    glm::vec3 closest_int_point;
    glm::vec3 closest_loc_normal;
    double min_distance = std::numeric_limits<double>::max();

    for (const auto &object_m: object_list_m) {
        bool valid_intersection = object_m->testIntersections(camera_ray,
                                                              int_point,
                                                              loc_normal);
        if (valid_intersection) {
            blank = false;
            double distance = glm::length(camera_ray.getOrigin() - int_point);
            if (distance < min_distance) {
                min_distance = distance;
                closest_object = object_m;
                closest_int_point = int_point;
                closest_loc_normal = loc_normal;
            }
        }
    }

    closest_loc_normal = glm::normalize(closest_loc_normal);
    if (!blank) {
        glm::vec3 output_color = computeColor(camera_ray,
                                              closest_object,
                                              closest_int_point,
                                              closest_loc_normal);
        //std::cout << output_color.r << " " << output_color.g << " " << output_color.b << " " <<std::endl;
        output_image.setPixel(x, y, output_color.r, output_color.g, output_color.b, 1.0);
    } else {
        output_image.setPixel(x, y, 0.01, 0.01, 0.01, 1.0);
    }
}

glm::vec3
Scene::computeColor(const Ray &camera_ray, const std::shared_ptr<Object> &current_object, const glm::vec3 &int_point,
                    const glm::vec3 &loc_normal) const {
    glm::vec3 color{};
    glm::vec3 diffuse_color{};
    glm::vec3 specular_color{};
    glm::vec3 ambient_color{};
    glm::vec3 output_color{};
    glm::vec3 view_dir{normalize(camera_ray.getOrigin() - int_point)};
    glm::vec3 reflect_dir{view_dir - 2.0f * dot(view_dir, loc_normal)}; // Always normalized
    Ray light_ray;

    glm::vec3 diffuse_component{};
    std::pair<glm::vec3, float> specular_component{};
    glm::vec3 ambient_component{};

    float shininess = current_object->getMaterial().getShininess();

    for (const auto &light_m: light_list_m) {
        light_m->computeIllumination(int_point, loc_normal, object_list_m, current_object,
                                     view_dir, diffuse_component, specular_component, ambient_component);
        diffuse_color += diffuse_component;
        float spec = std::pow(specular_component.second, shininess);
        specular_color += spec * specular_component.first;
        ambient_color += ambient_component;
    }
    auto ambient_term = ambient_color / static_cast<float>(light_list_m.size());

    output_color = ambient_term * current_object->getMaterial().getAmbient() +
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

//
// Created by paul on 3/11/23.
//

#include <glm/gtx/rotate_vector.hpp>
#include "scene.hpp"

Scene::Scene() {
    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(std::make_shared<PointLight>());
    light_list_m[0]->setPosition(glm::vec3(250.0f, -100.0f, 250.0f));
    light_list_m[0]->setColor(glm::vec3(255.0f, 255.0f, 255.0f));

    object_list_m.emplace_back(std::make_shared<Sphere>());
    object_list_m.emplace_back(std::make_shared<Sphere>());
    object_list_m.emplace_back(std::make_shared<Sphere>());

    Transformation transformation1;
    transformation1.setTransform(glm::vec3(-1.5f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.5f, 0.5f, 0.75f));
    Transformation transformation2;
    transformation2.setTransform(glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.75f, 0.5f, 0.5f));
    Transformation transformation3;
    transformation3.setTransform(glm::vec3(1.5f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.75f, 0.75f, 0.75f));

    object_list_m[0]->setTransformation(transformation1);
    object_list_m[1]->setTransformation(transformation2);
    object_list_m[2]->setTransformation(transformation3);

    object_list_m[0]->setColor(glm::vec3(0.0f, 255.0f, 0.0f));
    object_list_m[1]->setColor(glm::vec3(255.0f, 0.0f, 0.0f));
    object_list_m[2]->setColor(glm::vec3(0.0f, 0.0f, 255.0f));

//    plane_list_m.emplace_back(std::make_shared<Plane>());
//    Transformation transformation;
//    transformation.setTransform(glm::vec3(1.0f, 0.0f, 0.0f),
//                                glm::vec3(2.0f, 1.0f, 1.0f),
//                                glm::vec3(2.0f, 1.0f, 1.0f));
//    plane_list_m[0]->setTransformation(transformation);
//    plane_list_m[0] ->setColor(glm::vec3(255.0f, 0.0f, 0.0f));

}


bool Scene::render(Image &output_image) {
    int width = output_image.getWidth();
    int height = output_image.getHeight();

    Ray camera_ray;
    glm::vec3 int_point;
    glm::vec3 loc_normal;
    glm::vec3 loc_color;
    double x_factor = 1.0 / (static_cast<double>(width) / 2.0);
    double y_factor = 1.0 / (static_cast<double>(height) / 2.0);


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double norm_x = static_cast<double>(x) * x_factor - 1.0;
            double norm_y = static_cast<double>(y) * y_factor - 1.0;
            camera_m.createRay(norm_x, norm_y, camera_ray);
            bool blank = internalRender(x, y, camera_ray, output_image, int_point, loc_normal, loc_color);
            if (blank) {
                output_image.setPixel(x, y, 64.0, 64.0, 64.0, 255.0);
            }
        }
    }
    return true;
}

bool Scene::internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point,
                           glm::vec3 &loc_normal, glm::vec3 &loc_color) {
    bool blank = true;
    for (auto &sphere_m: object_list_m) {
        bool valid_intersection = sphere_m->testIntersections(camera_ray, int_point, loc_normal, loc_color);
        if (valid_intersection) {
            blank = false;
            double intensity = 0.0;
            glm::vec3 color;
            bool valid_illumination;
            for (auto &light_m: light_list_m) {
                valid_illumination = light_m->computeIllumination(int_point, loc_normal, object_list_m,
                                                                  sphere_m, color, intensity);
                if (valid_illumination) {
                    output_image.setPixel(x, y, loc_color.r * intensity, loc_color.g * intensity,
                                          loc_color.b * intensity, 255.0);
                } else {
                    output_image.setPixel(x, y, 0.0, 0.0, 0.0, 255.0);
                }
            }
        }
    }

    return blank;
}

void Scene::moveCamera(CameraMovement direction) {
    switch (direction) {
        case CameraMovement::FORWARD:
            camera_m.setPosition(camera_m.getPosition() + camera_m.getDirection());
            break;
        case CameraMovement::BACKWARD:
            camera_m.setPosition(camera_m.getPosition() - camera_m.getDirection());
            break;
        case CameraMovement::LEFT:
            camera_m.setPosition(
                    camera_m.getPosition() + glm::normalize(glm::cross(camera_m.getUp(), camera_m.getDirection())));
            break;
        case CameraMovement::RIGHT:
            camera_m.setPosition(
                    camera_m.getPosition() + glm::normalize(glm::cross(camera_m.getDirection(), camera_m.getUp())));
            break;
        case CameraMovement::UP:
            camera_m.setPosition(camera_m.getPosition() + camera_m.getUp());
            break;
        case CameraMovement::DOWN:
            camera_m.setPosition(camera_m.getPosition() - camera_m.getUp());
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

//
// Created by paul on 3/11/23.
//

#include <glm/gtx/rotate_vector.hpp>
#include "app/scene.hpp"

unsigned int constexpr THREADS_NUMBER = 16;

Scene::Scene(): thread_pool_m{THREADS_NUMBER}{
    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(std::make_shared<PointLight>());
    light_list_m[0]->setPosition(glm::vec3(-25.0f, -10.0f, 25.0f));
    light_list_m[0]->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    light_list_m.emplace_back(std::make_shared<PointLight>());
    light_list_m[1]->setPosition(glm::vec3(25.0f, -10.0f, 25.0f));
    light_list_m[1]->setColor(glm::vec3(1.0f, 1.0f, 0.8f));

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

    object_list_m[0]->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    object_list_m[1]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    object_list_m[2]->setColor(glm::vec3(0.0f, 0.0f, 1.0f));

    object_list_m.emplace_back(std::make_shared<Plane>());
    Transformation transformation4;
    transformation4.setTransform(glm::vec3(0.0f, 1.0f, -1.0f),
                                 glm::vec3(0.1f, 0.0f, 0.0f),
                                 glm::vec3(5.0f, 5.0f, 1.0f));
    object_list_m[3]->setTransformation(transformation4);
    object_list_m[3]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
}


bool Scene::render(Image &output_image) {
    int width = output_image.getWidth();
    int height = output_image.getHeight();

    unsigned int whole_part = height / THREADS_NUMBER; // make height unsigned in future
    unsigned int remainder = height % THREADS_NUMBER;
    unsigned int current_step = 0;
    unsigned int next_step = (remainder > 0) ? whole_part + 1 : whole_part;
    remainder = (remainder > 0) ? remainder - 1 : remainder;

    std::vector<std::future<bool>> responses;

    for (unsigned int thread_number = 0; thread_number < THREADS_NUMBER; thread_number++){
        std::pair<int, int> image_part {current_step, next_step};
        current_step = next_step;
        next_step += (remainder > 0) ? whole_part + 1 : whole_part;
        remainder = (remainder > 0) ? remainder - 1 : remainder;
        std::packaged_task<bool()> task([this, image_part, &output_image]
                                        { return renderImagePart(image_part, output_image); });
        responses.push_back(boost::asio::post(thread_pool_m, std::move(task)));
    }

    for (auto &future_response: responses){
        auto response = future_response.get();
        if (!response){
            return false;
        }
    }
    return true;
}

bool Scene::renderImagePart(std::pair<int, int> boundaries, Image &output_image){
    auto [lower_bound, upper_bound] = boundaries;
    int width = output_image.getWidth();
    int height = output_image.getHeight();

    Ray camera_ray;
    glm::vec3 int_point;
    glm::vec3 loc_normal;
    glm::vec3 loc_color;
    double x_factor = 1.0 / (static_cast<double>(width) / 2.0);
    double y_factor = 1.0 / (static_cast<double>(height) / 2.0);
    for (int y = lower_bound; y < upper_bound; y++) {
        for (int x = 0; x < width; x++) {
            double norm_x = static_cast<double>(x) * x_factor - 1.0;
            double norm_y = static_cast<double>(y) * y_factor - 1.0;
            camera_m.createRay(norm_x, norm_y, camera_ray);
            internalRender(x, y, camera_ray, output_image, int_point, loc_normal, loc_color);
        }
    }
    return true;
}

void Scene::internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point,
                           glm::vec3 &loc_normal, glm::vec3 &loc_color) const{
    bool blank = true;
    std::shared_ptr<Object> closest_object;
    glm::vec3 closest_int_point;
    glm::vec3 closest_loc_normal;
    glm::vec3 closest_loc_color;
    double min_distance = std::numeric_limits<double>::max();
    // intersection part
    for (const auto &object_m: object_list_m) {
        bool valid_intersection = object_m->testIntersections(camera_ray, int_point, loc_normal, loc_color);
        if (valid_intersection) {
            blank = false;
            double distance = glm::length(camera_ray.getOrigin() - int_point);
            if (distance < min_distance) {
                min_distance = distance;
                closest_object = object_m;
                closest_int_point = int_point;
                closest_loc_normal = loc_normal;
                closest_loc_color = loc_color;
            }
        }
    }
    // illumination part
    if (!blank) {
        glm::vec3 output_color = computeColor(camera_ray, closest_object, closest_int_point, closest_loc_normal, closest_loc_color);
        output_image.setPixel(x, y, output_color.r, output_color.g, output_color.b, 1.0);
    }else{
        output_image.setPixel(x, y, 0.2, 0.2, 0.2, 1.0);
    }
}

glm::vec3 Scene::computeColor(const Ray &camera_ray, const std::shared_ptr<Object>& current_object, const glm::vec3 &int_point,
                              const glm::vec3 &loc_normal, const glm::vec3 &loc_color) const{
    float ambient_intensity = 0.05f;
    double intensity{};
    glm::vec3 color{};
    glm::vec3 output_color{};
    glm::vec3 ambient_color{};
    glm::vec3 specular_color{};
    glm::vec3 diffuse_color{};

    bool valid_illumination = false;
    bool illuminated = false;
    for (const auto &light_m: light_list_m) {
        valid_illumination = light_m->computeDiffIllum(int_point, loc_normal,
                                                       object_list_m,
                                                       current_object, color, intensity);
        // specular part of illumination
        specular_color += light_m->computeSpecIllum(camera_ray, int_point, loc_normal);
        // ambient part of illumination
        ambient_color += ambient_intensity * light_m->getColor();

        if (valid_illumination) {
            illuminated = true;
            diffuse_color += color * static_cast<float>(intensity);
        }
    }
    if (illuminated) {
        output_color = loc_color * (ambient_color / static_cast<float>(light_list_m.size()) + diffuse_color + specular_color);
    } else {
        output_color = loc_color * ambient_color / static_cast<float>(light_list_m.size());
    }
    return output_color;

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

Scene::~Scene(){
    thread_pool_m.join();
    thread_pool_m.~thread_pool();
};
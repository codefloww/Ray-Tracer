//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <glm/gtx/rotate_vector.hpp>
#include <memory>
#include "app/image.hpp"
#include "app/camera.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "lights/point_light.hpp"

class Scene {
    std::vector<std::shared_ptr<Object>> object_list_m;
    std::vector<std::shared_ptr<PointLight>> light_list_m;

public:
    Camera camera_m;

    float update_time_m{};
    float camera_movement_speed_m;
    float camera_rotation_speed_m;

    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum class CameraRotation {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Scene();

    void render(Image &output_image) const;

    void internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point,
                        glm::vec3 &loc_normal) const;

    [[nodiscard]] glm::vec3
    computeColor(const Ray &camera_ray, const std::shared_ptr<Object> &current_object, const glm::vec3 &int_point,
                 const glm::vec3 &loc_normal) const;

    void moveCamera(CameraMovement direction);

    void rotateCamera(CameraRotation direction);
};

#endif //RAY_TRACER_SCENE_HPP

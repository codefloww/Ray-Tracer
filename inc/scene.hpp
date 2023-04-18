//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <memory>
#include "image.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "point_light.hpp"

class Scene {

    Camera camera_m;
    std::vector<std::shared_ptr<Object>> object_list_m;
    std::vector<std::shared_ptr<PointLight>> light_list_m;

public:

    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Scene();

    ~Scene() = default;

    bool render(Image &output_image) const;

    void move_camera(CameraMovement direction);

    // rotation about the up and left to right camera axis
    void rotate_camera(const glm::vec2 &rotation);
};

#endif //RAY_TRACER_SCENE_HPP

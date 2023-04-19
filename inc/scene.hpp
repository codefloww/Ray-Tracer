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
#include "image.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "point_light.hpp"
#include "threadpool/thread_pool.h"

class Scene {
    Camera camera_m;
    std::vector<std::shared_ptr<Object>> object_list_m;
    std::vector<std::shared_ptr<PointLight>> light_list_m;
    thread_pool thread_pool_m;

public:
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Scene();

    bool render(Image &output_image);

    bool internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point, glm::vec3 &loc_normal, glm::vec3 &loc_color);

    void moveCamera(CameraMovement direction);

    void rotateCamera(const glm::vec2 &rotation);

    bool renderImagePart(std::pair<int, int> boundaries, Image &output_image);
};

#endif //RAY_TRACER_SCENE_HPP

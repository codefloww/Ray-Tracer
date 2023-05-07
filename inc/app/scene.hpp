//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include "app/image.hpp"
#include "app/camera.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "lights/point_light.hpp"
#include "lights/directional_light.hpp"
#include "lights/spotlight.hpp"
#include "objects/trianglemesh.hpp"
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/blocked_range2d.h>
#include <oneapi/tbb/enumerable_thread_specific.h>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <glm/gtx/rotate_vector.hpp>
#include <memory>


class Scene {
    Camera camera_m;
    std::vector<std::shared_ptr<Object>> object_list_m;
    std::vector<std::shared_ptr<LightSource>> light_list_m;
    glm::vec3 background_color_m;

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

    void render(Image &output_image);

    void internalRender(int x, int y, const Ray &camera_ray, Image &output_image, glm::vec3 &int_point,
                        glm::vec3 &loc_normal) const;

    [[nodiscard]] glm::vec3
    computeColor(const Ray &camera_ray, const std::shared_ptr<Object> &current_object, const glm::vec3 &int_point,
                 const glm::vec3 &loc_normal) const;

    void moveCamera(CameraMovement direction);

    void rotateCamera(const glm::vec2 &rotation);

    inline static void accumulateColors(glm::vec3 diffuse_component,
                                 std::pair<glm::vec3, float> specular_component,
                                 glm::vec3 ambient_component,
                                 glm::vec3 &diffuse_color,
                                 glm::vec3 &specular_color,
                                 glm::vec3 &ambient_color,
                                 float shininess);
};

#endif //RAY_TRACER_SCENE_HPP

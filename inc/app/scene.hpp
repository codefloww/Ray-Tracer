#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include "app/image.hpp"
#include "app/camera.hpp"
#include "lights/light_source.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>


class Scene {
    Camera camera_m;
    std::vector<Object *> object_list_m;
    std::vector<LightSource *> light_list_m;
    glm::vec3 background_color_m;

public:
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
    computeColor(const Ray &camera_ray, const Object *current_object, const glm::vec3 &int_point,
                 const glm::vec3 &loc_normal) const;

    void moveCamera(CameraMovement direction);

    void rotateCamera(CameraRotation direction);

    ~Scene();
};

#endif //RAY_TRACER_SCENE_HPP

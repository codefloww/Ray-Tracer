//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_SCENE_HPP
#define RAY_TRACER_SCENE_HPP

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "sphere.hpp"

class Scene {

    Camera camera_m;
    Sphere sphere_m;

public:
    Scene();

    ~Scene() = default;

    bool render(Image &output_image) const;
};

#endif //RAY_TRACER_SCENE_HPP

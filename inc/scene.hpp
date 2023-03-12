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

private:
    Camera m_camera;
    Sphere m_sphere;

public:
    Scene();

    ~Scene() = default;

    bool Render(Image &outputImage) const;

};

#endif //RAY_TRACER_SCENE_HPP

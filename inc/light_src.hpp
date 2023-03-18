//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_LIGHT_SRC_HPP
#define RAY_TRACER_LIGHT_SRC_HPP

#include <glm/glm.hpp>
#include <memory>


class LightSrc {
public:
    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    double intensity_m = 1.0f;

    LightSrc();
    ~LightSrc() = default;
};

#endif //RAY_TRACER_LIGHT_SRC_HPP

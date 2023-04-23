//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_LIGHT_SOURCE_HPP
#define RAY_TRACER_LIGHT_SOURCE_HPP

#include <glm/glm.hpp>
#include <memory>

class LightSource {
protected:
    glm::vec3 position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 color_m = glm::vec3(1.0f, 1.0f, 1.0f);
    double intensity_m = 1.0f;

public:
    void setPosition(const glm::vec3 &position);

    void setColor(const glm::vec3 &color);

    [[nodiscard]] glm::vec3 getColor() const;

    void setIntensity(double intensity);
};

#endif //RAY_TRACER_LIGHT_SOURCE_HPP

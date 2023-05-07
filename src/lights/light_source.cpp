//
// Created by paul on 3/18/23.
//

#include "lights/light_source.hpp"

void LightSource::setPosition(const glm::vec3 &position) {
    position_m = position;
}

void LightSource::setColor(const glm::vec3 &color) {
    color_m = color;
}

void LightSource::setIntensity(float intensity) {
    intensity_m = intensity;
}

glm::vec3 LightSource::getColor() const {
    return color_m;
}

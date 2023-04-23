//
// Created by andrew on 18/04/23.
//

#include "objects/object.hpp"

void Object::setTransformation(const Transformation &transformation) {
    transformation_m = transformation;
}

Transformation Object::getTransformation() const {
    return transformation_m;
}

void Object::setColor(const glm::vec3 &color) {
    base_color_m = color;
}

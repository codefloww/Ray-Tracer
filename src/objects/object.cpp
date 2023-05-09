#include "objects/object.hpp"

void Object::setTransformation(const Transformation &transformation) {
    transformation_m = transformation;
}

Transformation Object::getTransformation() const {
    return transformation_m;
}

Material Object::getMaterial() const {
    return material_m;
}

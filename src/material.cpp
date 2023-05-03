//
// Created by paul on 5/3/23.
//

#include "material.hpp"

glm::vec3 Material::getAmbient() const {
    return ambient_m;
}

glm::vec3 Material::getDiffuse() const {
    return diffuse_m;
}

glm::vec3 Material::getSpecular() const {
    return specular_m;
}

float Material::getShininess() const {
    return shininess_m;
}

void Material::setAmbient(const glm::vec3 &ambient) {
    ambient_m = ambient;
}

void Material::setDiffuse(const glm::vec3 &diffuse) {
    diffuse_m = diffuse;
}

void Material::setSpecular(const glm::vec3 &specular) {
    specular_m = specular;
}

void Material::setShininess(float shininess) {
    shininess_m = shininess;
}

void Material::setupMaterial(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                             float shininess) {
    ambient_m = ambient;
    diffuse_m = diffuse;
    specular_m = specular;
    shininess_m = shininess;
}

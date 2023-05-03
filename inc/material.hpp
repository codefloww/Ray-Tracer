//
// Created by paul on 5/3/23.
//

#ifndef RAY_TRACER_MATERIAL_HPP
#define RAY_TRACER_MATERIAL_HPP

#include <glm/glm.hpp>

class Material{
    glm::vec3 ambient_m{};
    glm::vec3 diffuse_m{};
    glm::vec3 specular_m{};
    double shininess_m{};

public:
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    double getShininess() const;

    void setAmbient(const glm::vec3 &ambient);
    void setDiffuse(const glm::vec3 &diffuse);
    void setSpecular(const glm::vec3 &specular);
    void setShininess(double shininess);

    void setupMaterial(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, double shininess);
};

#endif //RAY_TRACER_MATERIAL_HPP

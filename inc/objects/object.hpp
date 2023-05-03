//
// Created by andrew on 18/04/23.
//

#ifndef RAY_TRACER_OBJECT_HPP
#define RAY_TRACER_OBJECT_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "transformation.hpp"
#include "material.hpp"

class Object {
protected:
    Transformation transformation_m;
    Material material_m;

public:
    void setTransformation(const Transformation &transformation);

    Transformation &getTransformation();

    Material &getMaterial();

    virtual void setMaterial(const Material &material) {
        material_m = material;
    };

    virtual bool
    testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const = 0;

    virtual ~Object() = default;
};

#endif //RAY_TRACER_OBJECT_HPP

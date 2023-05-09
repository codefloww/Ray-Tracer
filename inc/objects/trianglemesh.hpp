//
// Created by andrew on 29/04/23.
//

#ifndef RAY_TRACER_TRIANGLEMESH_HPP
#define RAY_TRACER_TRIANGLEMESH_HPP

#include "triangle.hpp"
#include "obj_loader/tiny_obj_loader.h"
#include <vector>
#include <memory>

class TriangleMesh : public Object {
public:
    explicit TriangleMesh(const std::string &filename);

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const override;

    void setMaterial(const Material &material) override;

public:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<Triangle *> triangles;
};

#endif //RAY_TRACER_TRIANGLEMESH_HPP

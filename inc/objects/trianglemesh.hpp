//
// Created by andrew on 29/04/23.
//

#ifndef RAY_TRACER_TRIANGLEMESH_HPP
#define RAY_TRACER_TRIANGLEMESH_HPP

#include "triangle.hpp"
#include "obj_loader/tiny_obj_loader.h"
#include <iostream>
#include <vector>
#include <memory>

class TriangleMesh : public Object {
public:
    explicit TriangleMesh(const std::string &filename);

    bool testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal,
                           glm::vec3 &loc_color) const override;

public:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<std::shared_ptr<Triangle>> triangles;
};

#endif //RAY_TRACER_TRIANGLEMESH_HPP
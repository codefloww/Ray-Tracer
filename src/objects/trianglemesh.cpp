#include "objects/trianglemesh.hpp"
#include <iostream>

TriangleMesh::TriangleMesh(const std::string &file_path) {
    std::string mtl_base = file_path.substr(0, file_path.find_last_of('/') + 1);

    tinyobj::attrib_t attributes;
    std::vector<Vertex> vertices;

    std::string warnings;
    std::string errors;

    bool open = tinyobj::LoadObj(&attributes,
                                 &shapes,
                                 &materials,
                                 &warnings,
                                 &errors,
                                 file_path.c_str(),
                                 mtl_base.c_str());

    if (!warnings.empty()) {
        std::cout << "[OBJ Loader] Warning: " << warnings << std::endl;
    }
    if (!errors.empty()) {
        std::cerr << "[OBJ Loader] Error: " << errors << std::endl;
    }
    if (!open) {
        std::cerr << "[OBJ Loader] Failed to open file: " << file_path << std::endl;
        exit(1);
    }

    for (const auto &shape: shapes) {
        size_t offset = 0;
        for (const auto &vertex: shape.mesh.num_face_vertices) {
            for (size_t v = 0; v < vertex; ++v) {
                tinyobj::index_t idx = shape.mesh.indices[offset + v];
                tinyobj::real_t vx = attributes.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attributes.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attributes.vertices[3 * idx.vertex_index + 2];

                tinyobj::real_t nx = attributes.normals[3 * idx.normal_index + 0];
                tinyobj::real_t ny = attributes.normals[3 * idx.normal_index + 1];
                tinyobj::real_t nz = attributes.normals[3 * idx.normal_index + 2];

                tinyobj::real_t tx = attributes.texcoords[2 * idx.texcoord_index + 0];
                tinyobj::real_t ty = attributes.texcoords[2 * idx.texcoord_index + 1];

                // emplace_back causes a compilation error with clang
                vertices.push_back({glm::vec3{vx, vy, vz},
                                    glm::vec3{nx, ny, nz},
                                    glm::vec2{tx, ty}}
                );
            }
            offset += vertex;
        }
    }

    for (int i = 0; i < vertices.size() / 3; ++i) {
        triangles.push_back(new Triangle(
                vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
    }
}

// override setMaterial to set the material of all the triangles
void TriangleMesh::setMaterial(const Material &material) {
    material_m = material;
    for (auto &part_material: materials) {
        part_material.ambient[0] = material_m.getAmbient()[0];
        part_material.ambient[1] = material_m.getAmbient()[1];
        part_material.ambient[2] = material_m.getAmbient()[2];

        part_material.diffuse[0] = material_m.getDiffuse()[0];
        part_material.diffuse[1] = material_m.getDiffuse()[1];
        part_material.diffuse[2] = material_m.getDiffuse()[2];

        part_material.specular[0] = material_m.getSpecular()[0];
        part_material.specular[1] = material_m.getSpecular()[1];
        part_material.specular[2] = material_m.getSpecular()[2];

        part_material.shininess = material_m.getShininess();
    }
}

bool TriangleMesh::testIntersections(const Ray &cast_ray, glm::vec3 &int_point, glm::vec3 &loc_normal) const {
    bool hit = false;
    float closest_hit = std::numeric_limits<float>::max();
    Ray local_ray = transformation_m.applyTransform(cast_ray, Direction::BACKWARD);
    glm::vec3 tri_loc_normal;
    float distance;

    for (const auto &tri: triangles) {
        if (tri->testIntersections(local_ray, tri_loc_normal, distance)) {
            if (distance < closest_hit) {
                closest_hit = distance;
                int_point = local_ray.getPoint(distance);
                loc_normal = tri_loc_normal;
                hit = true;
            }
        }
    }
    if (hit) {
        loc_normal = glm::normalize(transformation_m.applyLinearTransform(loc_normal, Direction::FORWARD));
        int_point = transformation_m.applyTransform(int_point, Direction::FORWARD);
    }

    return hit;
}

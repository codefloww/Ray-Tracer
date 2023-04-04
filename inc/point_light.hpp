//
// Created by paul on 3/18/23.
//

#ifndef RAY_TRACER_POINT_LIGHT_HPP
#define RAY_TRACER_POINT_LIGHT_HPP

#include <vector>
#include "light_src.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "ray.hpp"


class PointLight : public LightSrc {
public:
    PointLight();
    ~PointLight() = default;
    bool compute_illumination(const glm::vec3 &int_point, const glm::vec3 &loc_normal,
                              const std::vector<std::shared_ptr<Sphere>> &sphere_list,
                              const std::shared_ptr<Sphere> &current_sphere,
                              glm::vec3 &color, double &intensity) const;
            ;

    bool compute_illumination(const glm::vec3 &int_point, const glm::vec3 &loc_normal,
                              const std::vector<std::shared_ptr<Plane>> &plane_list,
                              const std::shared_ptr<Plane> &current_plane,
                              glm::vec3 &color, double &intensity) const;
            ;
};
#endif //RAY_TRACER_POINT_LIGHT_HPP

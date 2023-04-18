//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera {
    glm::vec3 position_m{};
    glm::vec3 direction_m{};
    glm::vec3 screen_up_m{};
    glm::vec3 screen_u_m{};
    glm::vec3 screen_v_m{};
    glm::vec3 screen_center_m{};
    double lens_distance_m;
    double width_m;
    double aspect_ratio_m;

public:
    Camera();

    void setPosition(const glm::vec3 &new_position);

    void setDirection(const glm::vec3 &new_direction);

    void setUp(const glm::vec3 &new_up);

    void setLensDistance(const double &new_lens_distance);

    void setWidth(const double &new_width);

    void setAspectRatio(const double &new_aspect_ratio);

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] glm::vec3 getDirection() const;

    [[nodiscard]] glm::vec3 getUp() const;

    [[nodiscard]] glm::vec3 getU() const;

    [[nodiscard]] glm::vec3 getV() const;

    [[nodiscard]] glm::vec3 getScreenCenter() const;

    [[nodiscard]] double getLensDistance() const;

    [[nodiscard]] double getWidth() const;

    bool getRayFromScreenPoint(double x, double y, Ray &camera_ray) const;

    void updateCameraGeometry();
};

#endif //RAY_TRACER_CAMERA_HPP

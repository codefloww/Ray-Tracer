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
    float lens_distance_m;
    float width_m;
    float aspect_ratio_m;

public:
    Camera();

    void setPosition(const glm::vec3 &new_position);

    void setDirection(const glm::vec3 &new_direction);

    void setUp(const glm::vec3 &new_up);

    void setLensDistance(const float new_lens_distance);

    void setWidth(const float new_width);

    void setAspectRatio(const float new_aspect_ratio);

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] glm::vec3 getDirection() const;

    [[nodiscard]] glm::vec3 getUp() const;

    [[nodiscard]] glm::vec3 getU() const;

    [[nodiscard]] glm::vec3 getV() const;

    [[nodiscard]] glm::vec3 getScreenCenter() const;

    [[nodiscard]] double getLensDistance() const;

    [[nodiscard]] float getLensDistance() const;

    [[nodiscard]] float getWidth() const;

    bool createRay(float x, float y, Ray &camera_ray) const;

    void updateCameraGeometry();
};

#endif //RAY_TRACER_CAMERA_HPP

//
// Created by paul on 3/11/23.
//

#ifndef RAY_TRACER_CAMERA_HPP
#define RAY_TRACER_CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera {

private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;
    glm::vec3 m_screenU;
    glm::vec3 m_screenV;
    glm::vec3 m_screenCenter;
    double m_lensDistance;
    double m_width;
    double m_aspectRatio;

public:
    Camera();

    void SetPosition(const glm::vec3 &newPosition);

    void SetDirection(const glm::vec3 &newDirection);

    void SetUp(const glm::vec3 &newUp);

    void SetLensDistance(const double &newLensDistance);

    void SetWidth(const double &newWidth);

    void SetAspectRatio(const double &newAspectRatio);

    glm::vec3 GetPosition() const;

    glm::vec3 GetDirection() const;

    glm::vec3 GetUp() const;

    glm::vec3 GetU() const;

    glm::vec3 GetV() const;

    glm::vec3 GetScreenCenter() const;

    double GetLensDistance() const;

    double GetWidth() const;

    double GetAspectRatio() const;

    bool GetRayFromScreenPoint(double x, double y, Ray &cameraRay) const;

    void UpdateCameraGeometry();

};

#endif //RAY_TRACER_CAMERA_HPP

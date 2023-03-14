//
// Created by paul on 3/11/23.
//

#include "../inc/camera.hpp"

Camera::Camera() {
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    m_up = glm::vec3(0.0f, 0.0f, 1.0f);
    m_lensDistance = 1.0f;
    m_width = 1.0f;
    m_aspectRatio = 1.0f;
}

void Camera::SetPosition(const glm::vec3 &newPosition) {
    m_position = newPosition;
}

void Camera::SetDirection(const glm::vec3 &newDirection) {
    m_direction = glm::normalize(newDirection);
}

void Camera::SetUp(const glm::vec3 &newUp) {
    m_up = glm::normalize(newUp);
}

void Camera::SetLensDistance(const double &newLensDistance) {
    m_lensDistance = newLensDistance;
}

void Camera::SetWidth(const double &newWidth) {
    m_width = newWidth;
}

void Camera::SetAspectRatio(const double &newAspectRatio) {
    m_aspectRatio = newAspectRatio;
}

glm::vec3 Camera::GetPosition() const {
    return m_position;
}

glm::vec3 Camera::GetDirection() const {
    return m_direction;
}

glm::vec3 Camera::GetUp() const {
    return m_up;
}

double Camera::GetLensDistance() const {
    return m_lensDistance;
}

double Camera::GetWidth() const {
    return m_width;
}

glm::vec3 Camera::GetU() const {
    return m_screenU;
}

glm::vec3 Camera::GetV() const {
    return m_screenV;
}

glm::vec3 Camera::GetScreenCenter() const {
    return m_screenCenter;
}

void Camera::UpdateCameraGeometry() {
    m_screenU = glm::normalize(glm::cross(m_direction, m_up));
    m_screenV = glm::normalize(glm::cross(m_direction, m_screenU));
    m_screenCenter = m_position + m_direction * static_cast<float>(m_lensDistance);
    m_screenU *= static_cast<float>(m_width);
    m_screenV *= static_cast<float>(m_width / m_aspectRatio);
}

bool Camera::GetRayFromScreenPoint(double x, double y, Ray &cameraRay) const {
    glm::vec3 pointOnScreen = m_screenCenter + m_screenU * static_cast<float>(x) + m_screenV * static_cast<float>(y);
    cameraRay = Ray::GetRayFromPoints(m_position, pointOnScreen);
    return true;
}

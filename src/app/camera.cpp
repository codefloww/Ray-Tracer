//
// Created by paul on 3/11/23.
//

#include "app/camera.hpp"
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera() {
    position_m = glm::vec3(0.0f, 0.0f, 0.0f);
    direction_m = glm::vec3(0.0f, 1.0f, 0.0f);
    screen_up_m = glm::vec3(0.0f, 0.0f, 1.0f);
    lens_distance_m = 1.0f;
    width_m = 1.0f;
    aspect_ratio_m = 1.0f;
}

void Camera::setPosition(const glm::vec3 &new_position) {
    position_m = new_position;
}

void Camera::setDirection(const glm::vec3 &new_direction) {
    direction_m = glm::normalize(new_direction);
}

void Camera::moveUp(const float speed) {
    position_m += speed * screen_up_m;
}

void Camera::moveDown(const float speed) {
    position_m -= speed * screen_up_m;
}

void Camera::moveLeft(const float speed) {
    position_m += speed * glm::cross(screen_up_m, direction_m);
}

void Camera::moveRight(const float speed) {
    position_m += speed * glm::cross(direction_m, screen_up_m);
}

void Camera::moveForward(const float speed) {
    position_m += speed * direction_m;
}

void Camera::moveBackward(const float speed) {
    position_m -= speed * direction_m;
}

void Camera::rotateUp(const float speed) {
    setDirection(glm::rotate(direction_m, speed, getXAxis()));
    setUp(glm::rotate(screen_up_m, speed, getXAxis()));
}

void Camera::rotateDown(const float speed) {
    setDirection(glm::rotate(direction_m, -speed, getXAxis()));
    setUp(glm::rotate(screen_up_m, -speed, getXAxis()));
}

void Camera::rotateLeft(const float speed) {
    setDirection(glm::rotate(direction_m, speed, screen_up_m));
}

void Camera::rotateRight(const float speed) {
    setDirection(glm::rotate(direction_m, -speed, screen_up_m));
}

void Camera::setUp(const glm::vec3 &new_up) {
    screen_up_m = glm::normalize(new_up);
}

void Camera::setLensDistance(const float new_lens_distance) {
    lens_distance_m = new_lens_distance;
}

void Camera::setWidth(const float new_width) {
    width_m = new_width;
}

void Camera::setAspectRatio(const float new_aspect_ratio) {
    aspect_ratio_m = new_aspect_ratio;
}

glm::vec3 Camera::getPosition() const {
    return position_m;
}

glm::vec3 Camera::getDirection() const {
    return direction_m;
}

glm::vec3 Camera::getUp() const {
    return screen_up_m;
}

float Camera::getLensDistance() const {
    return lens_distance_m;
}

float Camera::getWidth() const {
    return width_m;
}

glm::vec3 Camera::getU() const {
    return screen_u_m;
}

glm::vec3 Camera::getV() const {
    return screen_v_m;
}

glm::vec3 Camera::getScreenCenter() const {
    return screen_center_m;
}

glm::vec3 Camera::getXAxis() const {
    return glm::cross(direction_m, screen_up_m);
}

void Camera::updateCameraGeometry() {
    screen_u_m = glm::cross(direction_m, screen_up_m);
    screen_v_m = glm::cross(direction_m, screen_u_m);
    screen_center_m = position_m + direction_m * static_cast<float>(lens_distance_m);
    screen_u_m *= static_cast<float>(width_m);
    screen_v_m *= static_cast<float>(width_m / aspect_ratio_m);
}

bool Camera::createRay(float x, float y, Ray &camera_ray) const {
    glm::vec3 point_on_screen =
            screen_center_m + screen_u_m * static_cast<float>(x) + screen_v_m * static_cast<float>(y);
    camera_ray = Ray::getRayFromPoints(position_m, point_on_screen);
    return true;
}

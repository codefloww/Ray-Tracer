//
// Created by paul on 3/11/23.
//

#include "../inc/scene.hpp"

Scene::Scene() {
    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.0f, 1.0f, 0.1f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();
}

bool Scene::render(Image &output_image) const {
    int width = output_image.getWidth();
    int height = output_image.getHeight();

    Ray camera_ray;
    glm::vec3 int_point;
    glm::vec3 loc_normal;
    glm::vec3 loc_color;
    double x_factor = 1.0 / (static_cast<double>(width) / 2.0);
    double y_factor = 1.0 / (static_cast<double>(height) / 2.0);


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double norm_x = static_cast<double>(x) * x_factor - 1.0;
            double norm_y = static_cast<double>(y) * y_factor - 1.0;
            camera_m.getRayFromScreenPoint(norm_x, norm_y, camera_ray);
            bool valid_intersection = sphere_m.testIntersections(camera_ray, int_point, loc_normal, loc_color);
            if (valid_intersection) {
                double dist = glm::length(int_point - camera_m.getPosition());
                output_image.setPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255, 0.0, 0.0, 255.0);
            } else {
                output_image.setPixel(x, y, 0.0, 0.0, 0.0, 255.0);
            }
        }
    }
    return true;
}

//
// Created by paul on 3/11/23.
//

#include "../inc/scene.hpp"

Scene::Scene() {
    camera_m.setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    camera_m.setDirection(glm::vec3(0.1f, 1.0f, 0.0f));
    camera_m.setUp(glm::vec3(0.0f, 0.0f, 1.0f));
    camera_m.setWidth(0.25f);
    camera_m.setAspectRatio(4.0 / 3.0);
    camera_m.updateCameraGeometry();

    light_list_m.emplace_back(std::make_shared<PointLight>());
    light_list_m[0]->position_m = glm::vec3(5.0f, -10.0f, 5.0f);
    light_list_m[0]->color_m = glm::vec3(255.0f, 255.0f, 255.0f);
    sphere_list_m.emplace_back(std::make_shared<Sphere>(glm::vec3(3.0f, 7.0f, 0.0f), 1.4f));
    sphere_list_m.emplace_back(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));

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

            for (auto &sphere_m : sphere_list_m){
                bool valid_intersection = sphere_m->testIntersections(camera_ray, int_point, loc_normal, loc_color);
                if (valid_intersection) {
                    double intensity = 0.0;
                    glm::vec3 color;
                    bool valid_illumination;
                    for (auto &light_m : light_list_m) {
                        valid_illumination = light_m->compute_illumination(int_point, loc_normal, sphere_list_m, sphere_m, color, intensity);
                        if (valid_illumination) {
                            output_image.setPixel(x, y, color.r * intensity, 0.0, 0.0, 255.0);
                        }
                        else {
                            output_image.setPixel(x, y, 0.0, 0.0, 0.0, 255.0);
                        }
                    }
                }
            }
        }
    }
    return true;
}

//
// Created by paul on 3/11/23.
//

#include "../inc/scene.hpp"

Scene::Scene() {
    m_camera.SetPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    m_camera.SetDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    m_camera.SetUp(glm::vec3(0.0f, 0.0f, 1.0f));
    m_camera.SetWidth(0.25f);
    m_camera.SetAspectRatio(4.0 / 3.0);
    m_camera.UpdateCameraGeometry();
}

bool Scene::Render(Image &outputImage) const {
    int width = outputImage.GetWidth();
    int height = outputImage.GetHeight();

    Ray cameraRay;
    glm::vec3 intPoint;
    glm::vec3 locNormal;
    glm::vec3 locColor;
    double xFactor = 1.0 / (static_cast<double>(width) / 2.0);
    double yFactor = 1.0 / (static_cast<double>(height) / 2.0);


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double normX = static_cast<double>(x) * xFactor - 1.0;
            double normY = static_cast<double>(y) * yFactor - 1.0;
            m_camera.GetRayFromScreenPoint(normX, normY, cameraRay);
            bool validIntersection = m_sphere.TestIntersections(cameraRay, intPoint, locNormal, locColor);
            if (validIntersection) {
                double dist = glm::length(intPoint - m_camera.GetPosition());
                outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255, 0.0, 0.0, 255.0);
            } else {
                outputImage.SetPixel(x, y, 0.0, 0.0, 0.0, 255.0);
            }

        }
    }
    return true;
}

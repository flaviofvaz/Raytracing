#include "raytracer.h"
#include "camera.h"
#include "film.h"
#include "scene.h"
#include "light.h"
#include "instance.h"
#include "material.h"
#include "shape.h"
#include "glm/glm.hpp"
#include <iostream>
#include <memory>

int main() {
    try {
        // Create film (image plane)
        const int width = 800;
        const int height = 600;
        auto film = std::make_unique<Film>(glm::ivec2(width, height));

        // Create camera
        glm::vec3 eye(2.775f, 2.775f, 8.0f);    // Camera position (moved closer and lower)
        glm::vec3 lookAt(2.775, 2.775, 2.775);  // Look at point
        glm::vec3 up(0, 1, 0);      // Up vector
        float fov = 60.0f;          // Increased field of view
        float focalDistance = 5.225f; // Distance from camera to look-at point
        auto camera = std::make_unique<Camera>(eye, lookAt, up, fov, focalDistance, width, height);

        // Create scene
        auto scene = std::make_unique<Scene>();
        scene->setAmbientLight(glm::vec3(0.2, 0.2, 0.2));

        // Create materials
        auto redMaterial = std::make_unique<Phong>(
            glm::vec3(0.8f, 0.2f, 0.2f),  // diffuse
            glm::vec3(0.5f, 0.5f, 0.5f),  // glossy
            glm::vec3(0.1f, 0.1f, 0.1f),  // ambient
            32.0f                         // shininess
        );

        auto greenMaterial = std::make_unique<Phong>(
            glm::vec3(0.2f, 0.8f, 0.2f),  // diffuse
            glm::vec3(0.5f, 0.5f, 0.5f),  // glossy
            glm::vec3(0.1f, 0.1f, 0.1f),  // ambient
            32.0f                         // shininess
        );

        auto greyMaterial = std::make_unique<Phong>(
            glm::vec3(0.4f, 0.4f, 0.4f),  // diffuse
            glm::vec3(0.3f, 0.3f, 0.3f),  // glossy
            glm::vec3(0.1f, 0.1f, 0.1f),  // ambient
            32.0f                         // shininess
        );

        auto whiteMaterial = std::make_unique<Phong>(
            glm::vec3(0.0f, 0.0f, 0.0f),  // diffuse
            glm::vec3(0.3f, 0.3f, 0.3f),  // glossy
            glm::vec3(0.1f, 0.1f, 0.1f),  // ambient
            32.0f                         // shininess
        );

        // Add lights to the scene
        auto light1 = std::make_unique<PointLight>(
            glm::vec3(2.775, 4.0, 2.775),     // position
            glm::vec3(100.0, 100.0, 100.0)    // increased power
        );

        // Create shapes
        //auto largeBox = std::make_unique<Box>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.65, 3.30, 1.65));
        //auto smallBox = std::make_unique<Box>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.65, 1.65, 0.30));
        auto sphere = std::make_unique<Sphere>(glm::vec3(2.775, -1.0, 0.1), 0.1);
        auto sphere2 = std::make_unique<Sphere>(glm::vec3(2.775, 3.0, 1.0), 0.1);

        // Create floor (adjusted dimensions)
        auto floorBox = std::make_unique<Box>(glm::vec3(-0.1, -0.1, -0.1), glm::vec3(5.65, 0.0, 5.65));

        // // Create ceiling (adjusted dimensions)
        // auto ceilingBox = std::make_unique<Box>(glm::vec3(-0.1, 5.55, -0.1), glm::vec3(5.65, 5.65, 5.65));

        // // Create left wall (adjusted dimensions)
        // auto leftWallBox = std::make_unique<Box>(glm::vec3(-0.1, -0.1, -0.1), glm::vec3(0.0, 5.65, 5.65));

        // // Create right wall (adjusted dimensions)
        // auto rightWallBox = std::make_unique<Box>(glm::vec3(5.55, -0.1, -0.1), glm::vec3(5.65, 5.65, 5.65));

        // // Create back wall (adjusted dimensions)
        // auto backWallBox = std::make_unique<Box>(glm::vec3(-0.1, -0.1, -0.1), glm::vec3(5.65, 5.65, 0.0));

        // Create sphere lights
        auto sphereLightInstance = std::make_unique<Instance>(std::move(sphere));
        sphereLightInstance->setLight(light1.get());

        auto sphereInstance = std::make_unique<Instance>(std::move(sphere2));
        sphereInstance->setMaterial(redMaterial.get());
        
        // Create instances with materials
        // auto leftWallInstance = std::make_unique<Instance>(std::move(leftWallBox));
        // leftWallInstance->setMaterial(greenMaterial.get());

        // auto rightWallInstance = std::make_unique<Instance>(std::move(rightWallBox));
        // rightWallInstance->setMaterial(redMaterial.get());

        // auto backWallInstance = std::make_unique<Instance>(std::move(backWallBox));
        // backWallInstance->setMaterial(greyMaterial.get());

        auto floorInstance = std::make_unique<Instance>(std::move(floorBox));
        floorInstance->setMaterial(whiteMaterial.get());

        // auto ceilingInstance = std::make_unique<Instance>(std::move(ceilingBox));
        // ceilingInstance->setMaterial(greyMaterial.get());

        // auto largeBoxInstance = std::make_unique<Instance>(std::move(largeBox));
        // largeBoxInstance->setMaterial(greyMaterial.get());
        
        // auto smallBoxInstance = std::make_unique<Instance>(std::move(smallBox));
        // smallBoxInstance->setMaterial(greyMaterial.get());

        // Add objects to scene
        // scene->addObject(std::move(leftWallInstance));
        // scene->addObject(std::move(rightWallInstance));
        // scene->addObject(std::move(backWallInstance));
        scene->addObject(std::move(floorInstance));
        // scene->addObject(std::move(ceilingInstance));
        // scene->addObject(std::move(largeBoxInstance));
        // scene->addObject(std::move(smallBoxInstance));
        scene->addObject(std::move(sphereLightInstance));
        scene->addObject(std::move(sphereInstance));

        // Create and run raytracer
        RayTracer raytracer;
        raytracer.render(film.get(), camera.get(), scene.get());

        // Save the rendered image
        if (!film->savePPM("output.ppm")) {
            std::cerr << "Failed to save image" << std::endl;
            return 1;
        }

        std::cout << "Rendering completed successfully!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 
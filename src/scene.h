#ifndef SCENE_H
#define SCENE_H

#include "ray.h"
#include "hit.h"
#include "light.h"
#include "instance.h"

class Scene
{
    public:
        Scene();
        Hit* computeIntersection(Ray* ray);
        glm::vec3 traceRay(Ray* ray);
        std::vector<Light*> lightSources;
        std::vector<Instance*> sceneObjects;
        void addLight(Light* lightSource) {this->lightSources.push_back(lightSource);};
        void addObjects(Instance* sceneObject) {this->sceneObjects.push_back(sceneObject);};
};
#endif
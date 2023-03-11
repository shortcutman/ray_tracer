//
//  world.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 12/2/2023.
//

#include "world.hpp"

#include "lighting.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "transformations.hpp"

#include <algorithm>

using namespace rtlib;

std::vector<LightPtr> World::lights() const {
    return _lights;
}

void World::addLight(LightPtr light) {
    _lights.push_back(light);
}

std::vector<ObjectPtr> World::objects() const {
    return _objects;
}

void World::addObject(ObjectPtr object) {
    _objects.push_back(object);
}

Colour World::colourAt(const Ray &ray) const {
    auto intersects = this->intersects(ray);
    auto rayHit = getFirstHit(intersects);
    if (rayHit) {
        auto values = IntersectValues(*rayHit, ray);
        auto colour = shadeHits(values);
        return colour;
    } else {
        return Colour();
    }
}

Colour World::reflectedColourAt(const IntersectValues &values) const {
    if (values.intersect.object->material()._reflective == 0.0) {
        return Colour(0.0, 0.0, 0.0);
    }
    
    auto reflectRay = Ray(values.overPoint, values.reflectionVector);
    auto colour = colourAt(reflectRay);
    auto reflectColour = colour * values.intersect.object->material()._reflective;
    
    return reflectColour;
}

Intersections World::intersects(const Ray& ray) const {
    Intersections allHits;
    
    for (auto obj : _objects) {
        auto hits = obj->intersects(ray);
        allHits.insert(std::end(allHits), std::begin(hits), std::end(hits));
    }
    
    std::sort(allHits.begin(), allHits.end(),
        [](const Intersect& a, const Intersect& b) -> bool {
            return a.t < b.t;
        });
    
    return allHits;
}

Colour World::shadeHits(IntersectValues values) const {
    auto colour = _lights.front()->lightPoint(values.intersect.object, values.point, values.vectorToEye, values.normal, isShadowed(values.overPoint));
    return colour;
}

bool World::isShadowed(const Tuple &point) const {
    if (_lights.size() > 1) {
        throw std::runtime_error("only 1 light supported");
    } else if (_lights.size() == 0) {
        return false;
    }
    
    auto pointToLightVector = _lights.front()->origin() - point;
    auto distancePointToLight = pointToLightVector.magnitude();
    auto normalisedPointToLightVector = pointToLightVector.normalised();
    auto ray = Ray(point, normalisedPointToLightVector);
    
    auto intersections = intersects(ray);
    auto hit = rtlib::getFirstHit(intersections);
    
    return hit && hit->t < distancePointToLight;
}

World World::defaultWorld() {
    World w;
    
    auto light = std::make_shared<Light>(create_point(-10, 10, -10),
                                         Colour(1.0, 1.0, 1.0));
    w._lights.push_back(light);
    
    auto sphere1 = std::make_shared<Sphere>();
    sphere1->setMaterial({
        nullptr,
        Colour(0.8, 1.0, 0.6),
        0.1,
        0.7,
        0.2,
        200.0
    });
    w._objects.push_back(sphere1);
    
    auto sphere2 = std::make_shared<Sphere>();
    sphere2->setTransform(scaling(0.5, 0.5, 0.5));
    w._objects.push_back(sphere2);
    
    return w;
}

//
//  world.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 12/2/2023.
//

#include "world.hpp"

#include "lighting.hpp"
#include "object.hpp"
#include "transformations.hpp"

#include <algorithm>

using namespace rtlib;

std::vector<LightPtr> World::lights() const {
    return _lights;
}

std::vector<ObjectPtr> World::objects() const {
    return _objects;
}

Object::IntersectHits World::intersects(const Ray& ray) const {
    Object::IntersectHits allHits;
    
    for (auto obj : _objects) {
        auto hits = obj->intersects(ray);
        allHits.insert(std::end(allHits), std::begin(hits), std::end(hits));
    }
    
    std::sort(allHits.begin(), allHits.end(),
        [](const Object::Intersect& a, const Object::Intersect& b) -> bool {
            return a.t < b.t;
        });
    
    return allHits;
}

Colour World::shadeHits(IntersectValues values) {
    auto colour = _lights.front()->lightPoint(values.intersect.object->material(), values.point, values.vectorToEye, values.normal);
    return colour;
}

World World::defaultWorld() {
    World w;
    
    auto light = std::make_shared<Light>(create_point(-10, 10, -10),
                                         Colour(1.0, 1.0, 1.0));
    w._lights.push_back(light);
    
    auto sphere1 = std::make_shared<Sphere>();
    sphere1->setMaterial({
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

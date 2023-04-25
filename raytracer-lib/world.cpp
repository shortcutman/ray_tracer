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

Colour World::colourAt(const Ray &ray, unsigned int remaining) const {
    auto intersects = this->intersects(ray);
    auto rayHit = getFirstHit(intersects);
    if (rayHit) {
        auto values = IntersectValues(*rayHit, ray, intersects);
        auto colour = shadeHits(values, remaining);
        return colour;
    } else {
        return Colour();
    }
}

Colour World::reflectedColourAt(const IntersectValues &values, unsigned int remaining) const {
    if (remaining == 0) {
        return Colour(0.0, 0.0, 0.0);
    }
    
    remaining--;
    
    if (values.intersect.object->material()._reflective == 0.0) {
        return Colour(0.0, 0.0, 0.0);
    }
    
    auto reflectRay = Ray(values.overPoint, values.reflectionVector);
    auto colour = colourAt(reflectRay, remaining);
    auto reflectColour = colour * values.intersect.object->material()._reflective;
    
    return reflectColour;
}

Colour World::refractedColourAt(const IntersectValues &values, unsigned int remaining) const {
    if (values.intersect.object->material()._transparency == 0.0 ||
        remaining == 0) {
        return Colour(0.0, 0.0, 0.0);
    }
    
    //snells law to determine total internal refraction
    auto nRatio = values.refractiveIndexN1 / values.refractiveIndexN2;
    auto cosI = Tuple::dot(values.vectorToEye, values.normal);
    auto sin2t = nRatio * nRatio * (1 - cosI * cosI);
    if (sin2t > 1.0) {
        return Colour(0.0, 0.0, 0.0);
    }
    
    auto cosT = std::sqrt(1.0 - sin2t);
    auto direction = values.normal * (nRatio * cosI - cosT) - values.vectorToEye * nRatio;
    auto refractRay = Ray(values.underPoint, direction);
    auto colour = colourAt(refractRay, remaining) * values.intersect.object->material()._transparency;
    
    return colour;
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

Colour World::shadeHits(IntersectValues values, unsigned int remaining) const {
    auto surfaceColour = _lights.front()->lightPoint(values.intersect.object, values.point, values.vectorToEye, values.normal, isShadowed(values.overPoint));
    auto reflectedColour = reflectedColourAt(values, remaining);
    auto refractedColour = refractedColourAt(values, remaining);
    
    auto material = values.intersect.object->material();
    if (material._reflective > 0.0 && material._transparency > 0.0) {
        auto reflectance = schlickReflectance(values);
        return surfaceColour + reflectedColour * reflectance + refractedColour * (1 - reflectance);
    } else {
        return surfaceColour + reflectedColour + refractedColour;
    }
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
    w.addLight(light);
    
    auto sphere1 = std::make_shared<Sphere>();
    sphere1->setMaterial({
        nullptr,
        Colour(0.8, 1.0, 0.6),
        0.1,
        0.7,
        0.2,
        200.0
    });
    w.addObject(sphere1);
    
    auto sphere2 = std::make_shared<Sphere>();
    sphere2->setTransform(scaling(0.5, 0.5, 0.5));
    w.addObject(sphere2);
    
    return w;
}

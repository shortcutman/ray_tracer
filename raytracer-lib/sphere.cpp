//
//  sphere.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 19/2/2023.
//

#include "sphere.hpp"

#include "intersection.hpp"

rtlib::Intersections rtlib::Sphere::intersectsImpl(const Ray& ray) const {
    const auto centre = rtlib::create_point(0.0, 0.0, 0.0);
    const auto radius = 1.0;
    const auto sphere_to_ray = ray.origin() - centre;
    
    auto a = rtlib::Tuple::dot(ray.direction(), ray.direction());
    auto b = 2 * rtlib::Tuple::dot(ray.direction(), sphere_to_ray);
    auto c = rtlib::Tuple::dot(sphere_to_ray, sphere_to_ray) - radius;
    
    auto discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return Intersections();
    }
        
    Intersect hit1(this, (-b - std::sqrt(discriminant)) / (2 * a));
    Intersect hit2(this, (-b + std::sqrt(discriminant)) / (2 * a));
    
    Intersections hits;
    hits.push_back(hit1);
    hits.push_back(hit2);
    return hits;
}

rtlib::Tuple rtlib::Sphere::normalAt(const Tuple &point) const {
    auto objectPoint = this->transform().inverse() * point;
    auto objectNormal = objectPoint - rtlib::create_point(0.0, 0.0, 0.0);
    auto worldNormal = this->transform().inverse().transpose() * objectNormal;
    worldNormal.setW(0.0);
    return worldNormal.normalised();
}

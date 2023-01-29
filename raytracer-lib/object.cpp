//
//  object.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#include "object.hpp"

#include "ray.hpp"
#include "tuple.hpp"

#include <cmath>

rtlib::Sphere::IntersectHits rtlib::Sphere::intersects(const Ray& ray) const {
    const auto centre = rtlib::create_point(0.0, 0.0, 0.0);
    const auto radius = 1.0;
    const auto sphere_to_ray = ray.origin() - centre;
    
    auto a = rtlib::Tuple::dot(ray.direction(), ray.direction());
    auto b = 2 * rtlib::Tuple::dot(ray.direction(), sphere_to_ray);
    auto c = rtlib::Tuple::dot(sphere_to_ray, sphere_to_ray) - radius;
    
    auto discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return IntersectHits();
    }
    
    auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    
    IntersectHits hits;
    hits.push_back(t1);
    hits.push_back(t2);
    return hits;
}

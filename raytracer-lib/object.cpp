//
//  object.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 27/1/2023.
//

#include "object.hpp"

#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"

#include <cmath>
#include <numeric>

rtlib::Object::Intersect::Intersect(const Object* obj, double t_) :
object(obj), t(t_) {}

bool rtlib::Object::Intersect::operator==(const Intersect& rhs) const {
    return this->object == rhs.object && this->t == rhs.t;
}

rtlib::Object::Object() :
    _transform(Matrix<4>::identityMatrix())
{}

rtlib::Matrix<4> rtlib::Object::transform() const {
    return _transform;
}

void rtlib::Object::setTransform(rtlib::Matrix<4> matrix) {
    _transform = matrix;
}

std::optional<rtlib::Object::Intersect> rtlib::hit(Object::IntersectHits hits) {
    std::optional<Object::Intersect> result;
    
    for (const Object::Intersect& i : hits) {
        if (i.t < 0.0) {
            continue;
        } else if (!result) {
            result = i;
        } else if (result->t > i.t) {
            result = i;
        }
    }
    
    return result;
}

rtlib::Sphere::IntersectHits rtlib::Sphere::intersects(const Ray& ray) const {
    const auto translatedRay = ray.transform(this->transform().inverse());
    const auto centre = rtlib::create_point(0.0, 0.0, 0.0);
    const auto radius = 1.0;
    const auto sphere_to_ray = translatedRay.origin() - centre;
    
    auto a = rtlib::Tuple::dot(translatedRay.direction(), translatedRay.direction());
    auto b = 2 * rtlib::Tuple::dot(translatedRay.direction(), sphere_to_ray);
    auto c = rtlib::Tuple::dot(sphere_to_ray, sphere_to_ray) - radius;
    
    auto discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return IntersectHits();
    }
        
    Intersect hit1(this, (-b - std::sqrt(discriminant)) / (2 * a));
    Intersect hit2(this, (-b + std::sqrt(discriminant)) / (2 * a));
    
    IntersectHits hits;
    hits.push_back(hit1);
    hits.push_back(hit2);
    return hits;
}

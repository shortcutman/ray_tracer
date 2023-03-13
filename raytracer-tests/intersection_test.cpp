//
//  intersection_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 11/3/2023.
//

#include <gtest/gtest.h>

#include "intersection.hpp"

#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "transformations.hpp"

using namespace rtlib;

namespace {

std::shared_ptr<Sphere> glassSphere() {
    auto sphere = std::make_shared<Sphere>();
    sphere->material()._transparency = 1.0;
    sphere->material()._refractiveIndex = 1.5;
    return sphere;
}

TEST(IntersectionTest, PrecomputeReflectionVector) {
    auto plane = Plane();
    auto ray = Ray(create_point(0.0, 0.0, 0.0), create_vector(0.0, -std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
    auto intersect = Intersect(&plane, std::sqrt(2.0));
    auto intersectValues = IntersectValues(intersect, ray);
    
    EXPECT_EQ(intersectValues.reflectionVector, create_vector(0.0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0));
}

TEST(IntersectionTest, ComputeRefractiveN1andN2AtVariousIntersections) {
    auto sphereA = glassSphere();
    sphereA->setTransform(scaling(2.0, 2.0, 2.0));
    
    auto sphereB = glassSphere();
    sphereB->setTransform(translation(0.0, 0.0, -0.25));
    sphereB->material()._refractiveIndex = 2.0;
    
    auto sphereC = glassSphere();
    sphereC->setTransform(translation(0.0, 0.0, -0.25));
    sphereC->material()._refractiveIndex = 2.5;
    
    auto ray = Ray(create_point(0.0, 0.0, -4.0), create_vector(0.0, 0.0, 1.0));
    auto intersections = Intersections();
    intersections.push_back(Intersect(sphereA.get(), 2.0));
    intersections.push_back(Intersect(sphereB.get(), 2.75));
    intersections.push_back(Intersect(sphereC.get(), 3.25));
    intersections.push_back(Intersect(sphereB.get(), 4.75));
    intersections.push_back(Intersect(sphereC.get(), 5.25));
    intersections.push_back(Intersect(sphereA.get(), 6.0));
    
    auto values = IntersectValues(intersections[0], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 1.0);
    EXPECT_EQ(values.refractiveIndexN2, 1.5);
    
    values = IntersectValues(intersections[1], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 1.5);
    EXPECT_EQ(values.refractiveIndexN2, 2.0);
    
    values = IntersectValues(intersections[2], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 2.0);
    EXPECT_EQ(values.refractiveIndexN2, 2.5);
    
    values = IntersectValues(intersections[3], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 2.5);
    EXPECT_EQ(values.refractiveIndexN2, 2.5);
    
    values = IntersectValues(intersections[4], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 2.5);
    EXPECT_EQ(values.refractiveIndexN2, 1.5);
    
    values = IntersectValues(intersections[5], ray, intersections);
    EXPECT_EQ(values.refractiveIndexN1, 1.5);
    EXPECT_EQ(values.refractiveIndexN2, 1.0);
}

}

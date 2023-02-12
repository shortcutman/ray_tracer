//
//  object_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 27/1/2023.
//

#include <gtest/gtest.h>

#include "object.hpp"
#include "ray.hpp"
#include "transformations.hpp"

#include <cmath>
#include <numbers>

namespace {

TEST(ObjectTest, SphereTransforms) {
    rtlib::Sphere s;

    EXPECT_EQ(s.transform(), rtlib::Matrix4x4::identityMatrix());
    
    auto randomMatrix = rtlib::Matrix4x4::identityMatrix();
    randomMatrix.set(1, 1, 1.0);
    randomMatrix.set(3, 2, 2.0);
    randomMatrix.set(2, 3, 3.0);
    s.setTransform(randomMatrix);
    
    EXPECT_EQ(s.transform(), randomMatrix);
}

TEST(ObjectTest, IntersectSphereThroughMiddle) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, 4.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 6.0);
}

TEST(ObjectTest, IntersectSphereTangent) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 1.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, 5.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 5.0);
}

TEST(ObjectTest, IntersectSphereMiss) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 2.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 0);
}

TEST(ObjectTest, IntersectSphereFromInside) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, 0.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, -1.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, 1.0);
}

TEST(ObjectTest, IntersectSphereBehind) {
    rtlib::Sphere s;
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, 5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).object, &s);
    EXPECT_EQ(result.at(0).t, -6.0);
    EXPECT_EQ(result.at(1).object, &s);
    EXPECT_EQ(result.at(1).t, -4.0);
}

TEST(ObjectTest, HitIntersectionWithAllPositive) {
    rtlib::Sphere s;
    
    rtlib::Object::IntersectHits hits;
    hits.push_back(rtlib::Object::Intersect(&s, 1.0));
    hits.push_back(rtlib::Object::Intersect(&s, 2.0));
    
    auto hit = rtlib::hit(hits);
    EXPECT_TRUE(hit);
    EXPECT_EQ(*hit, rtlib::Object::Intersect(&s, 1.0));
}

TEST(ObjectTest, HitIntersectionWithMix) {
    rtlib::Sphere s;
    
    rtlib::Object::IntersectHits hits;
    hits.push_back(rtlib::Object::Intersect(&s, -1.0));
    hits.push_back(rtlib::Object::Intersect(&s, 1.0));
    
    auto hit = rtlib::hit(hits);
    EXPECT_TRUE(hit);
    EXPECT_EQ(*hit, rtlib::Object::Intersect(&s, 1.0));
}

TEST(ObjectTest, HitIntersectionWithAllNegative) {
    rtlib::Sphere s;
    
    rtlib::Object::IntersectHits hits;
    hits.push_back(rtlib::Object::Intersect(&s, -1.0));
    hits.push_back(rtlib::Object::Intersect(&s, -2.0));
    
    auto hit = rtlib::hit(hits);
    EXPECT_FALSE(hit);
}

TEST(ObjectTest, HitIntersectionIsLowestNonNegative) {
    rtlib::Sphere s;
    
    rtlib::Object::IntersectHits hits;
    hits.push_back(rtlib::Object::Intersect(&s, 5.0));
    hits.push_back(rtlib::Object::Intersect(&s, 7.0));
    hits.push_back(rtlib::Object::Intersect(&s, -3.0));
    hits.push_back(rtlib::Object::Intersect(&s, 2.0));
    
    auto hit = rtlib::hit(hits);
    EXPECT_TRUE(hit);
    EXPECT_EQ(*hit, rtlib::Object::Intersect(&s, 2.0));
}

TEST(ObjectTest, IntersectValues) {
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    rtlib::Sphere s;
    rtlib::Object::Intersect i(&s, 4.0);
    rtlib::IntersectValues v(i, r);
    
    EXPECT_EQ(v.intersect.object, &s);
    EXPECT_EQ(v.intersect.t, 4.0);
    EXPECT_EQ(v.point, rtlib::create_point(0, 0, -1));
    EXPECT_EQ(v.vectorToEye, rtlib::create_vector(0, 0, -1));
    EXPECT_EQ(v.normal, rtlib::create_vector(0, 0, -1));
}


TEST(ObjectTest, IntersectScaledSphere) {
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    rtlib::Sphere s;
    s.setTransform(rtlib::scaling(2.0, 2.0, 2.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0).t, 3.0);
    EXPECT_EQ(result.at(1).t, 7.0);
}

TEST(ObjectTest, IntersectTranslatedSphere) {
    rtlib::Ray r(rtlib::create_point(0.0, 0.0, -5.0),
                 rtlib::create_vector(0.0, 0.0, 1.0));
    rtlib::Sphere s;
    s.setTransform(rtlib::translation(5.0, 0.0, 0.0));
    
    auto result = s.intersects(r);
    EXPECT_EQ(result.size(), 0);
}

TEST(ObjectTest, SphereNormalOnXAxis) {
    rtlib::Sphere s;
    auto normal = s.normalAt(rtlib::create_point(1.0, 0.0, 0.0));
    EXPECT_EQ(normal, rtlib::create_vector(1.0, 0.0, 0.0));
}

TEST(ObjectTest, SphereNormalOnYAxis) {
    rtlib::Sphere s;
    auto normal = s.normalAt(rtlib::create_point(0.0, 1.0, 0.0));
    EXPECT_EQ(normal, rtlib::create_vector(0.0, 1.0, 0.0));
}

TEST(ObjectTest, SphereNormalOnZAxis) {
    rtlib::Sphere s;
    auto normal = s.normalAt(rtlib::create_point(0.0, 0.0, 1.0));
    EXPECT_EQ(normal, rtlib::create_vector(0.0, 0.0, 1.0));
}

TEST(ObjectTest, SphereNormalOnNonaxialPoint) {
    double value = std::sqrt(3.0) / 3.0;
    
    rtlib::Sphere s;
    auto normal = s.normalAt(rtlib::create_point(value, value, value));
    EXPECT_EQ(normal, rtlib::create_vector(value, value, value));
}

TEST(ObjectTest, SphereNormalIsNormalised) {
    double value = std::sqrt(3.0) / 3.0;
    
    rtlib::Sphere s;
    auto normal = s.normalAt(rtlib::create_point(value, value, value));
    EXPECT_EQ(normal, normal.normalised());
}

TEST(ObjectTest, TranslatedSphereNormal) {
    rtlib::Sphere s;
    s.setTransform(rtlib::translation(0.0, 1.0, 0.0));
    auto normal = s.normalAt(rtlib::create_point(0.0, 1.70711, -0.70711));
    EXPECT_EQ(normal, rtlib::create_vector(0.0, 0.70711, -0.70711));
}

TEST(ObjectTest, TransformedSphereNormal) {
    double value = std::sqrt(2.0) / 2.0;
    
    rtlib::Sphere s;
    auto transform = rtlib::scaling(1.0, 0.5, 1.0) *
                     rtlib::rotation_z(std::numbers::pi / 5);
    s.setTransform(transform);
    auto normal = s.normalAt(rtlib::create_point(0.0, value, -value));
    EXPECT_EQ(normal, rtlib::create_vector(0.0, 0.970143, -0.242536));
}

}

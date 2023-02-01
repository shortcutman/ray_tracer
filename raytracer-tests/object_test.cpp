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

namespace {

TEST(ObjectTest, SphereTransforms) {
    rtlib::Sphere s;

    EXPECT_EQ(s.transform(), rtlib::Matrix<4>::identityMatrix());
    
    auto randomMatrix = rtlib::Matrix<4>::identityMatrix();
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

}

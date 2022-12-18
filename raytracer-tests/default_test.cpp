//
//  default_test.cpp
//  raytracer-tests
//
//  Created by Daniel Burke on 18/12/2022.
//

#include <gtest/gtest.h>

#include "raytracer_lib.hpp"

namespace {

TEST(Default, helloWorld) {
    raytracer_lib a;
    
    EXPECT_EQ(a.HelloWorld(), "Hello World!");
}

}

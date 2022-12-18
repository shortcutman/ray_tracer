//
//  main.cpp
//  raytracer
//
//  Created by Daniel Burke on 18/12/2022.
//

#include "raytracer_lib.hpp"

#include <iostream>

int main(int argc, const char * argv[]) {
    
    raytracer_lib lib;

    std::cout << lib.HelloWorld().c_str();
    return 0;
}

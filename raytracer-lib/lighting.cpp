//
//  lighting.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 3/2/2023.
//

#include "lighting.hpp"

#include <cmath>

rtlib::Light::Light(const Tuple &origin, const Colour &intensity) :
    _position(origin),
    _intensity(intensity)
{
}

rtlib::Tuple rtlib::Light::origin() const {
    return _position;
}

rtlib::Colour rtlib::Light::intensity() const {
    return _intensity;
}

rtlib::Colour rtlib::Light::lightPoint(Material material, Tuple point, Tuple camera, Tuple normal) const {
    
    rtlib::Colour ambient, diffuse, specular;
    
    auto effectiveColour = material._colour * this->_intensity;
    auto lightVector = (this->_position - point).normalised();
    ambient = effectiveColour * material._ambient;
    
    auto lightDotNormal = Tuple::dot(lightVector, normal);
    if (lightDotNormal < 0.0) {
        diffuse = rtlib::Colour(0, 0, 0);
        specular = rtlib::Colour(0, 0, 0);
    } else {
        diffuse = effectiveColour * material._diffuse * lightDotNormal;
        auto reflectV = rtlib::Tuple::reflect(-lightVector, normal);
        auto reflectDotEye = Tuple::dot(reflectV, camera);
        
        if (reflectDotEye <= 0.0) {
            specular = rtlib::Colour(0, 0, 0);
        } else {
            auto factor = std::pow(reflectDotEye, material._shininess);
            specular = this->_intensity * material._specular * factor;
        }
    }
    
    return ambient + diffuse + specular;
}

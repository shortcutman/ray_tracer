//
//  lighting.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 3/2/2023.
//

#include "lighting.hpp"

#include "object.hpp"

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

rtlib::Colour rtlib::Light::lightPoint(const Object* object, Tuple point, Tuple vectorToCamera, Tuple normal, bool inShadow) const {
    if (!point.isPoint() || !vectorToCamera.isVector() || !normal.isVector()) {
        throw std::runtime_error("Incorrect parameters supplied");
    }
    
    rtlib::Colour ambient, diffuse, specular;
    
    auto effectiveColour = object->material().colourAt(object, point) * this->_intensity;
    auto lightVector = (this->_position - point).normalised();
    ambient = effectiveColour * object->material()._ambient;
    
    if (!inShadow) {
        auto lightDotNormal = Tuple::dot(lightVector, normal);
        if (lightDotNormal < 0.0) {
            diffuse = rtlib::Colour(0, 0, 0);
            specular = rtlib::Colour(0, 0, 0);
        } else {
            diffuse = effectiveColour * object->material()._diffuse * lightDotNormal;
            auto reflectV = rtlib::Tuple::reflect(-lightVector, normal);
            auto reflectDotEye = Tuple::dot(reflectV, vectorToCamera);
            
            if (reflectDotEye <= 0.0) {
                specular = rtlib::Colour(0, 0, 0);
            } else {
                auto factor = std::pow(reflectDotEye, object->material()._shininess);
                specular = this->_intensity * object->material()._specular * factor;
            }
        }
    }
    
    return ambient + diffuse + specular;
}

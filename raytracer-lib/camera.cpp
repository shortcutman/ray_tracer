//
//  camera.cpp
//  raytracer-lib
//
//  Created by Daniel Burke on 17/2/2023.
//

#include "camera.hpp"

using namespace rtlib;

Camera::Camera(unsigned int horizontalSize, unsigned int verticalSize, double fieldOfView) :
    _horizontalSize(horizontalSize),
    _verticalSize(verticalSize),
    _fieldOfView(fieldOfView),
    _transform(Matrix4x4::identityMatrix())
{
    auto halfView = std::tan(_fieldOfView / 2.0);
    auto aspectRatio = static_cast<double>(_horizontalSize) / static_cast<double>(_verticalSize);
    
    _halfWidth = aspectRatio >= 1 ? halfView : halfView * aspectRatio;
    _halfHeight = aspectRatio >= 1 ? halfView / aspectRatio : halfView;
    
    _pixelSize = (_halfWidth * 2) / _horizontalSize;
}

unsigned int Camera::horizontalSize() const {
    return _horizontalSize;
}

unsigned int Camera::verticalSize() const {
    return _verticalSize;
}

double Camera::fieldOfView() const {
    return _fieldOfView;
}

void Camera::setTransform(Matrix4x4 transform) {
    _transform = transform;
}

Matrix4x4 Camera::transform() const {
    return _transform;
}

double Camera::pixelSize() const {
    return _pixelSize;
}

Ray Camera::rayForPixel(unsigned int x, unsigned int y) const {
    auto xOffset = (static_cast<double >(x) + 0.5) * _pixelSize;
    auto yOffset = (static_cast<double >(y) + 0.5) * _pixelSize;
    
    auto worldX = _halfWidth - xOffset;
    auto worldY = _halfHeight - yOffset;
    
    auto pixel = _transform.inverse() * create_point(worldX, worldY, -1.0);
    auto origin = _transform.inverse() * create_point(0.0, 0.0, 0.0);
    auto direction = (pixel - origin).normalised();
    
    return Ray(origin, direction);
}


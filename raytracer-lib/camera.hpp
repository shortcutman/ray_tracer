//
//  camera.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 17/2/2023.
//

#ifndef camera_hpp
#define camera_hpp

#include "matrix.hpp"
#include "ray.hpp"

namespace rtlib {
    class Camera {
    private:
        unsigned int _horizontalSize;
        unsigned int _verticalSize;
        double _fieldOfView;
        Matrix4x4 _transform;
        double _halfWidth;
        double _halfHeight;
        double _pixelSize;
        
    public:
        Camera(unsigned int horizontalSize, unsigned int verticalSize, double fieldOfView);
                
        unsigned int horizontalSize() const;
        unsigned int verticalSize() const;
        double fieldOfView() const;
        double pixelSize() const;
        
        void setTransform(Matrix4x4 transform);
        Matrix4x4 transform() const;
        
        Ray rayForPixel(unsigned int x, unsigned y) const;
    };
}

#endif /* camera_hpp */

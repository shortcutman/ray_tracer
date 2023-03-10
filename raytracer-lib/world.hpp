//
//  world.hpp
//  raytracer-lib
//
//  Created by Daniel Burke on 12/2/2023.
//

#ifndef world_hpp
#define world_hpp

#include "object.hpp"

#include <vector>
#include <memory>

namespace rtlib {
 
class Light;
typedef std::shared_ptr<Light> LightPtr;
class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class World {
private:
    std::vector<LightPtr> _lights;
    std::vector<ObjectPtr> _objects;
    
public:
    World() {}
    
    std::vector<LightPtr> lights() const;
    void addLight(LightPtr light);
    
    std::vector<ObjectPtr> objects() const;
    void addObject(ObjectPtr object);
    
    Colour colourAt(const Ray& ray, unsigned int remaining = 5) const;
    Colour reflectedColourAt(const IntersectValues& values, unsigned int remaining) const;
    Colour refractedColourAt(const IntersectValues& values, unsigned int remaining);
    
    Intersections intersects(const Ray& ray) const;
    Colour shadeHits(IntersectValues values, unsigned int remaining) const;
    bool isShadowed(const Tuple& point) const;
    
    static World defaultWorld();
};

}

#endif /* world_hpp */

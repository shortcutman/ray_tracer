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
typedef std::unique_ptr<Light> LightPtr;
class Object;
typedef std::unique_ptr<Object> ObjectPtr;

class World {
private:
    std::vector<LightPtr> _lights;
    std::vector<ObjectPtr> _objects;
    
public:
    World() {}
    ~World() {}
    
    std::vector<LightPtr>& lights();
    void addLight(LightPtr light);
    
    std::vector<ObjectPtr>& objects();
    void addObject(ObjectPtr object);
    
    Colour colourAt(const Ray& ray, unsigned int remaining = 5) const;
    Colour reflectedColourAt(const IntersectValues& values, unsigned int remaining) const;
    Colour refractedColourAt(const IntersectValues& values, unsigned int remaining) const;
    
    Intersections intersects(const Ray& ray) const;
    Colour shadeHits(IntersectValues values, unsigned int remaining) const;
    bool isShadowed(const Tuple& point) const;
    
    static std::unique_ptr<World> defaultWorld();
};

}

#endif /* world_hpp */

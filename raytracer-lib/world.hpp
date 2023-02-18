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
    
    Colour colourAt(const Ray& ray) const;
    
    Object::IntersectHits intersects(const Ray& ray) const;
    Colour shadeHits(IntersectValues values) const;
    
    static World defaultWorld();
};

}

#endif /* world_hpp */

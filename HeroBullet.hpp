#ifndef HeroBullet_hpp
#define HeroBullet_hpp

#include "ArmyBullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class HeroBullet : public ArmyBullet {
public:
    explicit HeroBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent);
    void OnExplode(Defense* defense) override;
};


#endif /* HeroBullet_hpp */

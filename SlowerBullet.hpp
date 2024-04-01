#ifndef SlowerBullet_hpp
#define SlowerBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class SlowerBullet : public Bullet {
public:
    explicit SlowerBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

#endif /* SlowerBullet_hpp */
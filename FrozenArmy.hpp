#ifndef FrozenArmy_hpp
#define FrozenArmy_hpp

#include "Army.hpp"

class FrozenArmy : public Army {
public:
    FrozenArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* FrozenArmy_hpp */

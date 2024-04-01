#ifndef HeroArmy_hpp
#define HeroArmy_hpp

#include "Army.hpp"

class HeroArmy : public Army {
public:
    HeroArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* HeroArmy_hpp */

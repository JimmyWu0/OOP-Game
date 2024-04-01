#ifndef GiantArmy_hpp
#define GiantArmy_hpp

#include "Army.hpp"

class GiantArmy : public Army {
public:
    GiantArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* GiantArmy_hpp */

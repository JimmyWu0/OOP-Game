#ifndef SlowerDefense_hpp
#define SlowerDefense_hpp

#include "Defense.hpp"

class SlowerDefense : public Defense {
public:
    SlowerDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* SlowerDefense_hpp */
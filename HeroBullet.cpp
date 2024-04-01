#include <allegro5/base.h>
#include <random>
#include <string>
#include <iostream>
#include "DirtyEffect.hpp"
#include "HeroBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Defense.hpp"
#include "ExplosionEffect.hpp"  //

class Defense;
class Army;  //

int atk;
//ArmyBullet::ArmyBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent)
HeroBullet::HeroBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent) :
    ArmyBullet("play/bullet.png", 400, 5+atk*5, position, forwardDirection, rotation + ALLEGRO_PI / 2, parent) {
    atk++;
    std::cout << atk << "\n";
}

void HeroBullet::OnExplode(Defense* defense) {
    // TODO 3 (1/2): Add a ShootEffect here. Remember you need to include the class.
    getPlayScene()->EffectGroup->AddNewObject(new ShootEffect(defense->Position.x, defense->Position.y));

}
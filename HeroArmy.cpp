#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "HeroArmy.hpp"
#include "AudioHelper.hpp"
//#include "HeroBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "HeroBullet.hpp"

//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
HeroArmy::HeroArmy(int x, int y) : Army("play/turret-1.png", x, y, 20, 1.5, 30, 100, 3, 2 * PlayScene::BlockSize) {  //id=3
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

void HeroArmy::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new HeroBullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}
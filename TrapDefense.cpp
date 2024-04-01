#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "TrapDefense.hpp"
#include "AudioHelper.hpp"
//#include "TrapBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
TrapDefense::TrapDefense(float x, float y) :
    Defense("play/trap.png", x, y, 20, 0.5, -50, 4, 1.5 * PlayScene::BlockSize) {  //TODO, caon data: 20, 1, 50, 2, 425
    // Move center downward, since we the turret head is slightly biased upward.
    Visible = false;  ////
    Anchor.y += 8.0f / GetBitmapHeight();
}

void TrapDefense::CreateBullet(Engine::Point pt) {
    //if(Target->speed>=30)
    //    Target->speed*=0.9;
    /*int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new SlowerBullet(Position, diff, rotation, this));  //
    AudioHelper::PlayAudio("laser.wav");  //*/
}
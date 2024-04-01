#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <iostream>  //
#include "AudioHelper.hpp"
#include "Army.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Defense.hpp"
#include "Collider.hpp"  ////trap


extern ALLEGRO_TIMER* timer;

Defense::Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius) :
    Role(imgDefense, x, y), coolDown(coolDown), id(id), shootRadius(shootRadius) {
    CollisionRadius = radius;
    HP = hp;
}
void Defense::Hit(float damage) {
    HP -= damage;
    if (damage == 0)
    {
        ////ice??
    }
    if (HP <= 0) {
        OnExplode();
        // Remove all armies' reference to target
        for (auto& it : lockedArmies)
            it->Target = nullptr;
        int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
        int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
        getPlayScene()->ClearMapState(x, y);
        getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Defense::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();

    if (al_get_timer_count(timer) >= 2) //2 seconds  ////
    {
        //TODO
        //->Enabled = false;
        Enabled = 1;
        //al_stop_timer(timer);
        //al_set_timer_count(timer, 0);
    }

    if (!Enabled)
        return;

    ////if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, Target->Position, Target->CollisionRadius)) {

    if (HP == -50)
    {
        Army* tgt = nullptr;
        for (auto& it : scene->ArmyGroup->GetObjects())
        {
            tgt = dynamic_cast<Army*>(it);
            //if (it->Position.x == Position.x && it->Position.y == Position.y)
            //if (Position.x - 1 * PlayScene::BlockSize <= it->Position.x && it->Position.x <= Position.x + 1 * PlayScene::BlockSize && Position.y - 1 * PlayScene::BlockSize <= it->Position.y && it->Position.y <= Position.y + 1 * PlayScene::BlockSize)
            if(Engine::Collider::IsCircleOverlap(Position, CollisionRadius, tgt->Position, tgt->CollisionRadius))
            {
                Army* tgt2 = nullptr;
                for (auto& itt : scene->ArmyGroup->GetObjects())
                {
                    //int dis = ManHattanDistance(itt->Position);
                    //if (dis <= (shootRadius / PlayScene::BlockSize)+0.49)  //ie 1.5
                    if(InShootingRange(itt->Position))
                    {
                        tgt2 = dynamic_cast<Army*>(itt);
                        tgt2->Hit(INFINITY);
                    }
                }
                HP = -51;
                break;
            }
        }
    }

    if (HP == -51)  //after the trap is triggered
    {
        for (auto& it : lockedArmies)
            it->Target = nullptr;
        //getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
        //Hit(1);
        OnExplode();
        int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
        int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
        getPlayScene()->ClearMapState(x, y);
        //getPlayScene()->DefenseGroup->RemoveObject(objectIterator);
        Visible = false;
        //AudioHelper::PlayAudio("shockwave.ogg");
        AudioHelper::PlayAudio("explosion.wav");
        HP = -52;
    }

    if (!Target) {
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        int ey;
        for (auto& it : scene->ArmyGroup->GetObjects()) {
            ey = static_cast<int>(floor(it->Position.y / PlayScene::BlockSize));
            if (InShootingRange(it->Position)) {
                Target = dynamic_cast<Army*>(it);
                Target->lockedDefenses.push_back(this);
                lockedDefenseIterator = std::prev(Target->lockedDefenses.end());
                break;
            }
        }
    }
    if (Target  && id != 4) {  ////let TrapDefense not to rotate
        Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (Target->Position - Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime * 2.5;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1) cosTheta = 1;
        else if (cosTheta < -1) cosTheta = -1;
        
        if (cosTheta == -1) Rotation = ALLEGRO_PI;
        else {
            float radian = acos(cosTheta);
            Engine::Point rotation;
            if (abs(radian) <= maxRotateRadian)
                rotation = targetRotation;
            else
                rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
            // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
            Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        }
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet(Target->Position);
        }
    }

    if (id == 4)
    {
        if (!PlayScene::DebugMode || HP==-52)  //traps become invisible, not disappear
            Visible = false;
        else
            Visible = true;
    }

}
void Defense::Draw() const {
    Sprite::Draw();
    //PlayScene* scene = getPlayScene();
    if (PlayScene::DebugMode) {
        // Draw target radius.
        /*if (id == 4)
            Visible = true;*/
        al_draw_circle(Position.x, Position.y, shootRadius, al_map_rgb(0, 0, 255), 2);  ////TODO
    }
    else
    {
        /*if (id == 4)
            Visible = false;*/
    }
}

bool Defense::InShootingRange(Engine::Point obj) {
    float x = Position.x;
    float y = Position.y;
    
    return (pow(abs(x - obj.x), 2) + pow(abs(y - obj.y), 2) <= pow(shootRadius, 2));
}
//
/*int Defense::ManHattanDistance(Engine::Point target) {  ////new added
    int tx = static_cast<int>(floor(target.x / PlayScene::BlockSize));
    int ty = static_cast<int>(floor(target.y / PlayScene::BlockSize));

    int mx = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int my = static_cast<int>(floor(Position.y / PlayScene::BlockSize));

    return abs(tx - mx) + abs(ty - my);
}*/
#include "laser.h"
#include <raylib.h>
#include "ship.h"   // definición completa
#include "enemy.h"
#include <vector>
//using namespace std;

Laser::Laser(const Ship &ship){
    this->color = LASER_INIT_COLOR;
    this->direction = LASER_INIT_DIRECTION;
    this->speed = LASER_INIT_SPEED;
    this->position = {ship.getPosition().x, ship.getPosition().y - LASER_INIT_HEIGHT};
    this->width = LASER_INIT_WIDTH;
    this->height = LASER_INIT_HEIGHT;

    
    this->texture = ship.getLaserTexture();
    this->destroy = false;

    this->laser_box = {this->position.x, this->position.y, (float)this->width, (float)this->height};
}

Laser::~Laser(){}

void Laser::moveLaser(std::vector<Enemy> &enemies){
    checkCollision(enemies);
    float new_position_y = getPosition().y + (getDirection().y * GetFrameTime() * getSpeed());
    setPosition({getPosition().x, new_position_y});
    setLaserBoxPositionY(new_position_y);
}

Color Laser::getColor() const{
    return this->color;
}

void Laser::setColor(const Color &color){
    this->color = color;
}

Vector2 Laser::getPosition() const{
    return this->position;
}

void Laser::setPosition(const Vector2 &position){
    this->position = position;
}

Vector2 Laser::getDirection() const{
    return this->direction;
}

void Laser::setDirection(const Vector2 &direction){
    this->direction = direction;
}

int Laser::getSpeed() const{
    return speed;
}

void Laser::setSpeed(const int &speed) {
    this->speed = speed;
}

Texture2D Laser::getTexture() const{
    return this->texture;
}


void Laser::drawLaser(){
    DrawTextureV(getTexture(), getPosition(), getColor());
    // Uncomment this to draw the hitbox
    //DrawRectangleLinesEx(getLaserBox(), 1.5f, GREEN);
}

int Laser::getWidth() const{
    return this->width;
}

int Laser::getHeight() const{
    return this->height;
}

bool Laser::needDestroy() const{
    return this->destroy;
}

void Laser::setDestroy(const bool &destroy){
    this->destroy = destroy;
}

void Laser::checkCollision(std::vector<Enemy> &enemies){
    if (getPosition().y <= 0){
        setDestroy(true);
    }
    else{
        for (size_t i = 0; i < enemies.size(); i++){
            if (CheckCollisionRecs(getLaserBox(), enemies[i].getEnemyBox())){
                setDestroy(true);
                enemies[i].setDestroy(true);
            }
        }
    }
}

Rectangle Laser::getLaserBox() const{
    return laser_box;
}


void Laser::setLaserBoxPositionY(float y){
    this->laser_box.y = y;
}
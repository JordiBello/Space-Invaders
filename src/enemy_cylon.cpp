#include "enemy_cylon.h"
#include <raylib.h>

Cylon::Cylon(Texture2D texture) : Enemy(texture){
    this->color = ENEMY_CYLON_COLOR;
    this->speed = (float)GetRandomValue(ENEMY_MIN_SPEED, ENEMY_MAX_SPEED);
}

Color Cylon::getColor() const{
    return this->color;
}

void Cylon::setColor(const Color &color){
    this->color = color;
}

int Cylon::getSpeed() const{
    return this->speed;
}

void Cylon::setSpeed(const int &speed) {
    this->speed = speed;
}

float Cylon::getHealth() const{
    return this->health;
}

void Cylon::setHealth(const float &health) {
    this->health = health;
}

void Cylon::drawEnemy(){
    DrawTextureV(getEnemyTexture(), getPosition(), getColor());
    // Uncomment this to draw the hitbox
    // DrawRectangleLinesEx(getEnemyBox(), 1.5f, RED);
}

void Cylon::moveEnemy(){
    float new_position_y = getPosition().y + (getDirection().y * GetFrameTime() * getSpeed());
    setPosition({getPosition().x, new_position_y});
    setEnemyBoxPositionY(new_position_y);
}
#include "enemy_xenomorph.h"
#include <raylib.h>

Xenomorph::Xenomorph(Texture2D texture) : Enemy(texture){
    this->color = ENEMY_XENOMORPH_COLOR;
    this->speed = (float)GetRandomValue(350, 500);
}

Color Xenomorph::getColor() const{
    return this->color;
}

void Xenomorph::setColor(const Color &color){
    this->color = color;
}

int Xenomorph::getSpeed() const{
    return this->speed;
}

void Xenomorph::setSpeed(const int &speed) {
    this->speed = speed;
}

float Xenomorph::getHealth() const{
    return this->health;
}

void Xenomorph::setHealth(const float &health) {
    this->health = health;
}

void Xenomorph::drawEnemy(){
    DrawTextureV(getEnemyTexture(), getPosition(), getColor());
    // Uncomment this to draw the hitbox
    // DrawRectangleLinesEx(getEnemyBox(), 1.5f, RED);
}

void Xenomorph::moveEnemy(){
    float new_position_y = getPosition().y + (getDirection().y * GetFrameTime() * getSpeed());
    setPosition({getPosition().x, new_position_y});
    setEnemyBoxPositionY(new_position_y);
}
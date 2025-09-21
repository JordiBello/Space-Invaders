#include "enemy.h"
#include <raylib.h>
//using namespace std;
Enemy::Enemy(Texture2D texture){
    this->color = ENEMY_INIT_COLOR;
    this->direction = ENEMY_INIT_DIRECTION;
    this->speed = (float)GetRandomValue(ENEMY_MIN_SPEED, ENEMY_MAX_SPEED);
    this->position = {(float)GetRandomValue(0, VIRTUAL_WIDTH - ENEMY_INIT_WIDTH), 50};
    this->width = ENEMY_INIT_WIDTH;
    this->height = ENEMY_INIT_HEIGHT;


    this->enemy_texture = texture;
    this->enemy_box = {this->position.x, this->position.y, ENEMY_INIT_WIDTH, ENEMY_INIT_HEIGHT};

    this->destroy = false;
}

Enemy::~Enemy(){}

void Enemy::moveEnemy(){
    float new_position_y = getPosition().y + (getDirection().y * GetFrameTime() * getSpeed());
    setPosition({getPosition().x, new_position_y});
    setEnemyBoxPositionY(new_position_y);
}

Color Enemy::getColor() const{
    return this->color;
}

void Enemy::setColor(const Color &color){
    this->color = color;
}

Vector2 Enemy::getPosition() const{
    return this->position;
}

void Enemy::setPosition(const Vector2 &position){
    this->position = position;
}

Vector2 Enemy::getDirection() const{
    return this->direction;
}

void Enemy::setDirection(const Vector2 &direction){
    this->direction = direction;
}

int Enemy::getSpeed() const{
    return speed;
}

void Enemy::setSpeed(const int &speed) {
    this->speed = speed;
}

Texture2D Enemy::getEnemyTexture() const{
    return this->enemy_texture;
}


void Enemy::drawEnemy(){
    DrawTextureV(getEnemyTexture(), getPosition(), getColor());
    // Uncomment this to draw the hitbox
    // DrawRectangleLinesEx(getEnemyBox(), 1.5f, RED);
}

int Enemy::getWidth() const{
    return this->width;
}

int Enemy::getHeight() const{
    return this->height;
}

Rectangle Enemy::getEnemyBox() const{
    return this->enemy_box;
}

void Enemy::setEnemyBoxPositionY(float y){
    this->enemy_box.y = y;
}

bool Enemy::needDestroy() const{
    return this->destroy;
}

void Enemy::setDestroy(const bool &destroy){
    this->destroy = destroy;
}
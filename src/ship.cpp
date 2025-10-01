#include "ship.h"
#include <raylib.h>
#include "laser.h"
//using namespace std;
Ship::Ship(){
    this->color = SHIP_INIT_COLOR;
    this->direction = SHIP_INIT_DIRECTION;
    this->speed = SHIP_INIT_SPEED;
    this->position = {(AUX_VIRTUAL_WIDTH/2.0f - SHIP_INIT_WIDTH), SHIP_INIT_POSITION_Y};
    this->width = SHIP_INIT_WIDTH;
    this->height = SHIP_INIT_HEIGHT;

    this->ship_image = LoadImage("assets/ship.png");
    ImageResize(&ship_image, this->width, this->height);
    Texture2D ship_texture = LoadTextureFromImage(ship_image);
    SetTextureFilter(ship_texture, TEXTURE_FILTER_POINT);
    this->ship_texture = ship_texture;
    UnloadImage(ship_image);

    // Laser related

    
    this->laser_image = LoadImage("assets/laser-beam-blue.png");
    ImageResize(&laser_image, LASER_INIT_WIDTH, LASER_INIT_HEIGHT);
    ImageRotate(&laser_image, -90);
    Texture2D laser_texture = LoadTextureFromImage(laser_image);
    SetTextureFilter(laser_texture, TEXTURE_FILTER_POINT);
    this->laser_texture = laser_texture;
    UnloadImage(laser_image);

    std::vector<Laser> ammo;
    this->ammo = ammo;
    this->laser_timer = LASER_INIT_TIMER;

    this->laser_sound_1 = LoadSound("assets/sounds/laserfire01.ogg");
    


}

Ship::~Ship(){
    UnloadSound(laser_sound_1);
    
    UnloadTexture(this->ship_texture);
    UnloadTexture(this->laser_texture);
}

void Ship::moveShip(){
    float direction_y = getDirection().y;

    if (IsKeyDown(KEY_A)){
        setDirection({-1, direction_y});
    }
    else if (IsKeyDown(KEY_D)){
        setDirection({1, direction_y});
    }
    else{
        setDirection({0, direction_y});
    }

    if ((getPosition().x + getWidth() >= VIRTUAL_WIDTH && IsKeyDown(KEY_D)) || (getPosition().x <= 0 && IsKeyDown(KEY_A))){
        setDirection({0, direction_y});
    }
    
    float new_position_x = getPosition().x + (getDirection().x * GetFrameTime() * getSpeed());
    setPosition({new_position_x, getPosition().y});
}

Color Ship::getColor() const{
    return this->color;
}

void Ship::setColor(const Color &color){
    this->color = color;
}

Vector2 Ship::getPosition() const{
    return this->position;
}

void Ship::setPosition(const Vector2 &position){
    this->position = position;
}

Vector2 Ship::getDirection() const{
    return this->direction;
}

void Ship::setDirection(const Vector2 &direction){
    this->direction = direction;
}

int Ship::getSpeed() const{
    return speed;
}

void Ship::setSpeed(const int &speed) {
    this->speed = speed;
}

Texture2D Ship::getShipTexture() const{
    return this->ship_texture;
}


void Ship::drawShip(){
    DrawTextureV(getShipTexture(), getPosition(), getColor());
}

int Ship::getWidth() const{
    return this->width;
}

int Ship::getHeight() const{
    return this->height;
}

Texture2D Ship::getLaserTexture() const{
    return this->laser_texture;
}

void Ship::shootLaser(std::vector<std::unique_ptr<Enemy>> &enemies){
    checkLaser();
    
    float dt = GetFrameTime();
    this->laser_timer += dt;
    if(this->laser_timer >= LASER_COOLDOWN && IsKeyDown(KEY_SPACE)){ // Checks if the cooldown is completed and space key is pressed
        PlaySound(laser_sound_1);
        Laser laser = Laser(*this);
        this->ammo.push_back(laser);
        resetLaserTimer();
    }
    for (unsigned long long i = 0; i < this->ammo.size(); i++){
        this->ammo[i].moveLaser(enemies);
    }
}

// This function checks if any laser has its destroy flag turned true, in that case it's erased from the vector with a simple "swap and pop" algorithm
void Ship::checkLaser(){
    for (unsigned long long i = 0; i < this->ammo.size(); i++){
        if (this->ammo[i].needDestroy()){
            this->ammo[i] = this->ammo.back();
            this->ammo.pop_back();
            i--;
        }
    }
}


void Ship::drawLasers(){
    for (unsigned long long i = 0; i < this->ammo.size(); i++){
        this->ammo[i].drawLaser();
    }
}

void Ship::resetLaserTimer(){
    this->laser_timer = LASER_RESET_TIMER;
}
/*
Vector2 Ship::getTextPosition() const{
    return this->textPosition;
}*/

int Ship::getPoints() const{
    return this->points;
}

void Ship::incrementPoints(){
    this->points++;
}

void Ship::decrementPoints(){
    this->points--;
}

void Ship::setPoints(const int &points){
    this->points = points;
}
/*
void Ship::drawPoints(const Font &font){
    std::string text = "Points: " + std::to_string(getPoints());

    const char* text_converted = text.c_str(); 
    DrawTextEx(font, text_converted, getTextPosition(), float fontSize, float spacing, Color tint);
}*/
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <raylib.h>
#include <vector>
#include "laser.h"
#include <memory>
class Enemy;   // forward declaration

#define SHIP_INIT_SPEED 700
#define SHIP_INIT_POSITION_Y 900
#define SHIP_INIT_COLOR WHITE
#define SHIP_INIT_DIRECTION {0, 0}
#define SHIP_INIT_WIDTH 64
#define SHIP_INIT_HEIGHT 72
#define AUX_VIRTUAL_WIDTH 1980
#define AUX_VIRTUAL_HEIGHT 1080
#define SHIP_INIT_AMMO 100
#define LASER_COOLDOWN 0.1f
#define LASER_INIT_TIMER 0.1f
#define LASER_RESET_TIMER 0.0f
#define VIRTUAL_WIDTH 1980
#define VIRTUAL_HEIGHT 1080

//using namespace std;

class Ship{
    private:
        Texture2D ship_texture;
        Color color;
        Vector2 position;
        Vector2 direction;
        int speed;
        int width;
        int height;
        Image ship_image;
        
        Image laser_image;
        Texture2D laser_texture;
        std::vector<Laser> ammo;
        float laser_timer;
        //std::vector<Sound> laser_sounds;
        Sound laser_sound_1;

        int points;
    public:
        Ship();
        ~Ship();

        void moveShip();

        Color getColor() const;
        void setColor(const Color &color);

        Vector2 getPosition() const;
        void setPosition(const Vector2 &position);

        Vector2 getDirection() const;
        void setDirection(const Vector2 &direction);
        
        int getSpeed() const;
        void setSpeed(const int &speed);

        int getWidth() const;
        int getHeight() const;

        Texture2D getShipTexture() const;

        void drawShip();

        void shootLaser(std::vector<std::unique_ptr<Enemy>> &enemies);

        void checkLaser();

        void drawLasers();

        Texture2D getLaserTexture() const;

        float getLaserTimer() const;
        void resetLaserTimer();

        Vector2 getTextPosition() const;

        int getPoints() const;
        void incrementPoints();
        void decrementPoints();
        void setPoints(const int &points);
        void drawPoints(const Font &font);
};


#endif
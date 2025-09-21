#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <raylib.h>
#include <vector>
#include "laser.h"
//class Laser;   // forward declaration

#define ENEMY_MAX_SPEED 350
#define ENEMY_MIN_SPEED 100
#define ENEMY_INIT_POSITION_Y 900
#define ENEMY_INIT_COLOR WHITE
#define ENEMY_INIT_DIRECTION {0, 1}
#define ENEMY_INIT_WIDTH 64
#define ENEMY_INIT_HEIGHT 72
#define AUX_VIRTUAL_WIDTH 1980
#define AUX_VIRTUAL_HEIGHT 1080
#define VIRTUAL_WIDTH 1980
#define VIRTUAL_HEIGHT 1080
#define ENEMY_COOLDOWN_SPAWN 1.00f
#define ENEMY_INIT_TIMER 0.1f
#define ENEMY_RESET_TIMER 0.0f

//using namespace std;

class Enemy{
    private:
        Rectangle enemy_box;
        Texture2D enemy_texture;
        Color color;
        Vector2 position;
        Vector2 direction;
        int speed;
        int width;
        int height;
        Image enemy_image;
        bool destroy;

    public:
        Enemy(Texture2D texture);
        ~Enemy();

        void moveEnemy();

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

        Texture2D getEnemyTexture() const;

        void drawEnemy();

        Rectangle getEnemyBox() const;
        void setEnemyBoxPositionY(float y);

        bool needDestroy() const;
        void setDestroy(const bool &destroy);
};


#endif
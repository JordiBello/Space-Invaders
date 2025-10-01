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
#define ENEMY_CYLON_COLOR WHITE
#define ENEMY_XENOMORPH_COLOR BLUE
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
        Vector2 position;
        Vector2 direction;
        int width;
        int height;
        Image enemy_image;
        bool destroy;

    public:
        Enemy(Texture2D texture);
        virtual ~Enemy();

        virtual void moveEnemy();



        Vector2 getPosition() const;
        void setPosition(const Vector2 &position);

        Vector2 getDirection() const;
        void setDirection(const Vector2 &direction);
        


        int getWidth() const;
        int getHeight() const;

        Texture2D getEnemyTexture() const;

        

        Rectangle getEnemyBox() const;
        void setEnemyBoxPositionY(float y);

        bool needDestroy() const;
        void setDestroy(const bool &destroy);
        virtual void drawEnemy();

};


#endif
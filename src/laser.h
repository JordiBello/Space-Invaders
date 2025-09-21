#ifndef LASER_H
#define LASER_H

#include <string>
#include <raylib.h>
#include <vector>
class Ship; // declaración adelantada
class Enemy;

#define LASER_INIT_SPEED 500
#define LASER_INIT_POSITION_Y 900
#define LASER_INIT_COLOR WHITE
#define LASER_INIT_DIRECTION {0, -1}
#define LASER_INIT_WIDTH 24
#define LASER_INIT_HEIGHT 15
#define AUX_VIRTUAL_WIDTH 1980
#define AUX_VIRTUAL_HEIGHT 1080

//using namespace std;

class Laser{
    private:
        Texture2D texture;
        Rectangle laser_box;
        Color color;
        Vector2 position;
        Vector2 direction;
        int speed;
        int width;
        int height;
        Image image;
        bool destroy;

    public:
        Laser(const Ship &ship);
        ~Laser();

        void moveLaser(std::vector<Enemy> &enemies);

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

        Texture2D getTexture() const;

        void drawLaser();

        bool needDestroy() const;
        void setDestroy(const bool &destroy);

        void checkCollision(std::vector<Enemy> &enemies);

        Rectangle getLaserBox() const;
        void setLaserBoxPositionY(float y);

};


#endif
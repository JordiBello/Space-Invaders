#include "enemy.h"
class Cylon : public Enemy
{
private:
    Color color;
    int speed;
    float health;
public:
    Cylon(Texture2D texture);

    Color getColor() const;
    void setColor(const Color &color);

    int getSpeed() const;
    void setSpeed(const int &speed);

    float getHealth() const;
    void setHealth(const float &health);
    void drawEnemy() override;
    void moveEnemy() override;
};
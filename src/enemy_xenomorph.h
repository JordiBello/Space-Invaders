#include "enemy.h"
class Xenomorph : public Enemy
{
private:
    Color color;
    int speed;
    float health;
public:
    Xenomorph(Texture2D texture);

    Color getColor() const;
    void setColor(const Color &color);

    int getSpeed() const;
    void setSpeed(const int &speed);

    float getHealth() const;
    void setHealth(const float &health);
    void drawEnemy() override;
    void moveEnemy() override;
};
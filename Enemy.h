#pragma once

class Enemy {
public:
    float x, y;
    float radius;
    float speedX;
    bool isAlive;

    Enemy(float x, float y);

    void Update(float bulletX, float bulletY, bool bulletActive);
    void Draw();
};

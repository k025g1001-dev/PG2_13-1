#pragma once

class Bullet {
public:
    float x, y;
    bool isActive;

    Bullet();

    void Fire(float startX, float startY);
    void Update();
    void Draw();
};

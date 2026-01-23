#include "Enemy.h"
#include <Novice.h>
#include <cmath>

Enemy::Enemy(float x, float y) {
    this->x = x;
    this->y = y;
    radius = 20.0f;
    speedX = 0.5f; 
    isAlive = true;
}

void Enemy::Update(float bulletX, float bulletY, bool bulletActive) {
    if (!isAlive) return;

    // 左右移動
    x += speedX;
    if (x < radius || x > 1280 - radius) {
        speedX *= -1;
    }

    // 当たり判定
    if (bulletActive) {
        float dx = x - bulletX;
        float dy = y - bulletY;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist < radius + 10.0f) {
            isAlive = false;
        }
    }
}

void Enemy::Draw() {
    if (isAlive) {
        Novice::DrawEllipse(
            (int)x, (int)y,
            (int)radius, (int)radius,
            0.0f, RED, kFillModeSolid
        );
    }
}

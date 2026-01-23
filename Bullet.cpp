#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet() {
    x = 0;
    y = 0;
    isActive = false;
}

void Bullet::Fire(float startX, float startY) {
    if (!isActive) {
        x = startX;
        y = startY;
        isActive = true;
    }
}

void Bullet::Update() {
    if (!isActive) return;

    y -= 10.0f;
    if (y < 0) {
        isActive = false;
    }
}

void Bullet::Draw() {
    if (isActive) {
        Novice::DrawEllipse(
            (int)x, (int)y,
            10, 10,
            0.0f, WHITE, kFillModeSolid
        );
    }
}

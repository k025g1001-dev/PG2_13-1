#include <Novice.h>
#include <cstring>
#include "Enemy.h"
#include "Bullet.h"

const char kWindowTitle[] = "GC1C_01_ウエキ_ユウト_タイトル";

// 定数
const int kBulletMax = 10;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // プレイヤー
    float playerX = 640;
    float playerY = 600;

    // 弾
    Bullet bullets[kBulletMax];

    // 敵
    Enemy enemyA(400, 250);
    Enemy enemyB(800, 350);

    while (Novice::ProcessMessage() == 0) {

        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // プレイヤー移動
        if (keys[DIK_A]) playerX -= 5;
        if (keys[DIK_D]) playerX += 5;
        if (keys[DIK_W]) playerY -= 5;
        if (keys[DIK_S]) playerY += 5;

        // 弾発射（スペース1回で1発）
        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            for (int i = 0; i < kBulletMax; i++) {
                if (!bullets[i].isActive) {
                    bullets[i].Fire(playerX, playerY);
                    break;
                }
            }
        }

        // 弾更新
        for (int i = 0; i < kBulletMax; i++) {
            bullets[i].Update();
        }

        // 敵更新
        for (int i = 0; i < kBulletMax; i++) {
            enemyA.Update(bullets[i].x, bullets[i].y, bullets[i].isActive);
            enemyB.Update(bullets[i].x, bullets[i].y, bullets[i].isActive);
        }

        // リセット
        if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
            enemyA.isAlive = true;
            enemyB.isAlive = true;

            for (int i = 0; i < kBulletMax; i++) {
                bullets[i].isActive = false;
            }
        }

        // 描画
        Novice::DrawEllipse(
            (int)playerX, (int)playerY,
            20, 20,
            0.0f, GREEN, kFillModeSolid
        );

        for (int i = 0; i < kBulletMax; i++) {
            bullets[i].Draw();
        }

        enemyA.Draw();
        enemyB.Draw();

        // デバッグ表示
        Novice::ScreenPrintf(20, 20, "enemyA isAlive = %d", enemyA.isAlive);
        Novice::ScreenPrintf(20, 40, "enemyB isAlive = %d", enemyB.isAlive);
        Novice::ScreenPrintf(20, 60, "WASD : Move");
        Novice::ScreenPrintf(20, 80, "SPACE : Shot");
        Novice::ScreenPrintf(20, 100, "R : Reset");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE]) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}

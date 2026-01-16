#include <Novice.h>
#include <cmath>
#include <cstring>

const char kWindowTitle[] = "GC1C_01_ウエキ_ユウト_タイトル";

// 定数
const int kBulletMax = 10;

// Enemyクラス
class Enemy {
public:
    static bool isAllDead;

    float x, y;
    float radius;
    float speedX;
    bool isAlive;

    Enemy(float x, float y) {
        this->x = x;
        this->y = y;
        radius = 20.0f;
        speedX = 1.0f;
        isAlive = true;
    }

    void Update(float bulletX, float bulletY, bool bulletActive) {
        if (!isAlive || isAllDead) return;

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
                isAllDead = true;
            }
        }
    }

    void Draw() {
        if (isAlive && !isAllDead) {
            Novice::DrawEllipse(
                (int)x, (int)y,
                (int)radius, (int)radius,
                0.0f, RED, kFillModeSolid
            );
        }
    }
};

bool Enemy::isAllDead = false;

// 弾構造体
struct Bullet {
    float x, y;
    bool isActive;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // プレイヤー
    float playerX = 640;
    float playerY = 600;

    // 弾
    Bullet bullets[kBulletMax] = {};

    // 敵
    Enemy enemyA(400, 250);
    Enemy enemyB(800, 350);

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///
         // プレイヤー移動
        if (keys[DIK_A]) playerX -= 5;
        if (keys[DIK_D]) playerX += 5;
        if (keys[DIK_W]) playerY -= 5;
        if (keys[DIK_S]) playerY += 5;

        // 弾発射
        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            for (int i = 0; i < kBulletMax; i++) {
                if (!bullets[i].isActive) {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY;
                    bullets[i].isActive = true;
                    break;
                }
            }
        }

        // 弾更新
        for (int i = 0; i < kBulletMax; i++) {
            if (bullets[i].isActive) {
                bullets[i].y -= 10;
                if (bullets[i].y < 0) {
                    bullets[i].isActive = false;
                }
            }
        }

        // 敵更新
        for (int i = 0; i < kBulletMax; i++) {
            enemyA.Update(bullets[i].x, bullets[i].y, bullets[i].isActive);
            enemyB.Update(bullets[i].x, bullets[i].y, bullets[i].isActive);
        }

        // リセット
        if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
            Enemy::isAllDead = false;
            enemyA.isAlive = true;
            enemyB.isAlive = true;

            for (int i = 0; i < kBulletMax; i++) {
                bullets[i].isActive = false;
            }
        }
        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
        // プレイヤー
        Novice::DrawEllipse(
            (int)playerX, (int)playerY,
            20, 20, 0.0f, GREEN, kFillModeSolid
        );

        // 弾
        for (int i = 0; i < kBulletMax; i++) {
            if (bullets[i].isActive) {
                Novice::DrawEllipse(
                    (int)bullets[i].x, (int)bullets[i].y,
                    10, 10, 0.0f, WHITE, kFillModeSolid
                );
            }
        }

        // 敵
        enemyA.Draw();
        enemyB.Draw();

        ///
        /// ↑描画処理ここまで
        ///
       
        // デバッグ表示
        Novice::ScreenPrintf(20, 20, "enemyA isAlive = %d", enemyA.isAlive);
        Novice::ScreenPrintf(20, 40, "enemyB isAlive = %d", enemyB.isAlive);
        Novice::ScreenPrintf(20, 60, "WASD : Move");
        Novice::ScreenPrintf(20, 80, "SPACE : Shot");
        Novice::ScreenPrintf(20, 100, "R : Reset");
        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}



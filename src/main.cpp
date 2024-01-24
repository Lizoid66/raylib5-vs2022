#include "raylib.h"
#include "Math.h"
#include <vector> // Same as List<> in C#

const int screenWidth = 1280;
const int screenHeight = 720;
// TODO figue it otu
struct Enemy
{
    Vector2 position{};
    float radius = 75.0f;
    Color color = BURGUNDY;
    float speed = 300.0f;

    static void CreateEnemies()
    {
        enemies.push_back({});
        enemies.push_back({});
        enemies.push_back({});
        enemies.push_back({});

        enemies[0].position = Vector2{ screenWidth * 0.1f, screenHeight * 0.1f };
        enemies[1].position = Vector2{ screenWidth * 0.9f, screenHeight * 0.1f };
        enemies[2].position = Vector2{ screenWidth * 0.9f, screenHeight * 0.9f };
        enemies[3].position = Vector2{ screenWidth * 0.1f, screenHeight * 0.9f };

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].radius = baseRadius + Random(-25.0f, 25.0f);
            enemies[i].speed = baseSpeed + Random(-250.0f, 250.0f);
        }
    }

    static void Update(Vector2 targetPosition, float targetRadius, float dt)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].Move(targetPosition, targetRadius, dt);
        }
    }

    static void Render(unsigned char a)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].color.a = a;
            DrawCircleV(enemies[i].position, enemies[i].radius, enemies[i].color);
        }
    }

    void Move(Vector2 targetPosition, float targetRadius, float dt)
    {
        bool collision = CheckCollisionCircles(position, radius * 3.0f, targetPosition, targetRadius);
        if (collision)
        {
            //AB = B - A
            position = position + Normalize(targetPosition - position)* speed * dt;
        }
    }

    static float baseRadius;
    static float baseSpeed;
    static std::vector<Enemy> enemies;
};

float Enemy::baseRadius = 50.0f;
float Enemy::baseSpeed = 250.0f;
std::vector<Enemy> Enemy::enemies;

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Vector2 centre{ screenWidth * 0.5f, screenHeight * 0.5f };
    Vector2 player = centre;
    Vector2 enemy = centre;
    Enemy::CreateEnemies();
    float playerSpeed = 500.f;
    float playerRadius = 50.0f;
    float enemySpeed = 300.0f;
    float enemyRadius = 75.0f;

    /*std::vector<Enemy> enemies;
    Enemy enemy1, enemy2, enemy3, enemy4;
    enemy1.position = Vector2{ screenWidth * 0.1f, screenHeight * 0.1f };
    enemy2.position = Vector2{ screenWidth * 0.9f, screenHeight * 0.1f };
    enemy3.position = Vector2{ screenWidth * 0.9f, screenHeight * 0.9f };
    enemy4.position = Vector2{ screenWidth * 0.1f, screenHeight * 0.9f };
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);*/

    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();
        float dt = GetFrameTime();
        float nsin = 1.0f - (sinf(tt) * 0.25f + 0.75f);
        unsigned char a = nsin * 255.0f;

        Vector2 direction{};

        if (IsKeyDown(KEY_W))
        {
            direction.y = -1.0f;
        }
        if (IsKeyDown(KEY_S))
        {
            direction.y = 1.0f;
        }
        if (IsKeyDown(KEY_A))
        {
            direction.x = -1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            direction.x = 1.0f;
        }
        player = player + direction * playerSpeed * dt;

        bool collision = CheckCollisionCircles(enemy, enemyRadius * 3.0f, player, playerRadius);
        Color playerColor = collision ? BURGUNDY : YELLOW;
        if (collision)
        {
            //AB = B - A
            Vector2 toPlayer = Normalize(player - enemy);
            enemy = enemy + toPlayer * enemySpeed * dt;
        }

        Enemy::Update(player, playerRadius, dt);

        BeginDrawing();
        ClearBackground(GRAY);

        Enemy::Render(a);

        DrawCircleV(enemy, enemyRadius, { 128, 0, 32, a });
        DrawCircleV(player, playerRadius, playerColor);
        /*Color enemy{ 255, 0, 0, a };
        Color enemy2{ 255, 0, 0, a };
        DrawCircleV({ screenWidth * 0.25f, screenHeight * 0.5f }, 125.0f, enemy);
        DrawCircleV({ screenWidth * 0.75f, screenHeight * 0.5f }, 125.0f, enemy2);*/
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

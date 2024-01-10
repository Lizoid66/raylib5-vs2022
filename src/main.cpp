#include "raylib.h"
#include "Math.h"

class Table
{
public:
    float x, y;
    float width, height;
    float weight;
    float legWidth, legHeight;
    int legs;
    Color legsColor, topColor;

    void Draw()
    {
        // Top of Table

        float spacing = width / (legs - 1);

        float legX = x;
        //DrawRectangle(legX, y, legWidth, legHeight, legsColor);
        for (int i = 0; i < legs; i++)
        {
            DrawRectangle(legX, y, legWidth, legHeight, legsColor);
            legX += spacing;
        }
        DrawRectangle(x, y, width, height, topColor);
    }
};


Vector2 Seek(Vector2 target, Vector2 position, Vector2 velocity, float speed)
{
    return Normalize(target - position) * speed - velocity;
}

int main()
{
    

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Table woodTable;

    woodTable.height = 60.0f;
    woodTable.width = 200.0f;
    woodTable.x = screenWidth * 0.5f - woodTable.width * 0.5f;
    woodTable.y = screenHeight * 0.75f - woodTable.height;
    woodTable.legsColor = BROWN;
    woodTable.topColor = GRAY;
    woodTable.legs = 4;
    woodTable.legWidth = 10.0f;
    woodTable.legHeight = woodTable.height * 3.0f;

    float radius = 25.0f;
    Vector2 position{ screenWidth * 0.5f, screenHeight * 0.5f };
    Vector2 velocity{ Random(-10.0f, 10.0f), Random(-10.0f, 10.0f) };

    const char* character = "fhwiuefhwuefhiuw";

    while (!WindowShouldClose())
    {
        /*float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        velocity = velocity + Seek(mouse, position, velocity, 1000.0f) * dt;
        position = position + velocity * dt;

        if (CheckCollisionPointCircle(mouse, position, radius))
            break;*/

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(character, 10, 10, 20, BURGUNDY);
        DrawCircleV(position, radius, CHARTREUSE);
        woodTable.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

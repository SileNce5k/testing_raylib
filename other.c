#include "include/raylib.h"
#include "common_functions.h"

Circle circle;
Vector2 window;

void DrawStar()
{
    DrawLine(window.x / 2, window.y / 2, (window.x / 2) + 10, (window.y / 2) + 10, RED);
}

int main(void)
{

    
    window.x = 800;
    window.y = 600;
    FontType font;
    font = FONT_DEFAULT;
    InitWindow(window.x, window.y, "other");
    SetTargetFPS(60);
    Vector2 center = {window.x / 2, window.y /2};

    while(!WindowShouldClose()){
        
        BeginDrawing();
            ClearBackground(BLACK);
            // DrawCircleLines(window.x / 2, window.y / 2, 12, RED); 
            // DrawStar();
            // DrawEllipse(window.x / 2, window.y / 2, 230.0f, 120.0f, WHITE);
            DrawPoly(center, 3, 30, 90.0f, YELLOW);
            DrawPoly(center, 3, 30, -90.0f, YELLOW);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}
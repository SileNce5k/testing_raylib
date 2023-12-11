#include "include/raylib.h"
#include "common_functions.h"

int main(void)
{

    Vector2 window;
    window.x = 800;
    window.y = 800;
    FontType font;
    font = FONT_DEFAULT;
    Sound sound;
    sound = LoadSound("mouse_click.mp3");
    PlaySound(sound);
    StopSound(sound);
    InitWindow(window.x, window.y, "other");
    SetTargetFPS(24);
    while(!WindowShouldClose()){
        Vector2 FirstLine;
        Vector2 SecondLine;
        SecondLine.x = GetRandomValue(0, window.x);
        SecondLine.y = GetRandomValue(0, window.y);
        FirstLine.x  = GetRandomValue(0, window.x);
        FirstLine.y  = GetRandomValue(0, window.y);
        
        
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleLines(window.x / 2, window.y / 2, 12, RED); 
            DrawLine(GetRandomValue(0, window.y), 0, window.x, window.y, RED);
            DrawLine(0, window.y, window.x, 0, RED);
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}
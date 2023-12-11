#include "include/raylib.h"
#include "common_functions.h"
Vector2 window_size = {800, 600};
char *title = "game_testing";
int main(void)
{
    InitWindow(window_size.x, window_size.y, title);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("text text text", window_size.x / 2, window_size.y / 2.5, 20, RED);
        EndDrawing();
    }
}
#include "include/raylib.h"
#include "limits.h"
#include "stdio.h"
#include <stdlib.h>
#include "common_functions.h"
#define FPS 60
#define REDTERM     "\033[31m"      /* Red */
#define RESETTERM   "\033[0m"
#define GREENTERM   "\033[32m"      /* Green */




typedef struct
{
    size_t amount;
    size_t capacity;
} Circles;


static const Color array_of_colors[] = {
    {130, 130, 130, 255},
    {80, 80, 80, 255},
    {253, 249, 0, 255},
    {255, 203, 0, 255},
    {255, 161, 0, 255},
    {255, 109, 194, 255},
    {230, 41, 55, 255},
    {190, 33, 55, 255},
    {0, 228, 48, 255},
    {0, 158, 47, 255},
    {0, 117, 44, 255},
    {102, 191, 255, 255},
    {0, 121, 241, 255},
    {0, 82, 172, 255},
    {200, 122, 255, 255},
    {135, 60, 190, 255},
    {112, 31, 126, 255},
    {211, 176, 131, 255},
    {127, 106, 79, 255},
    {76, 63, 47, 255},
    {255, 0, 255, 255}
};


int current_color = 7; // Initial Color = Red
void change_circle_color(Circle *circle)
{
    Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(200, 255)};
    circle->color = color;
}

Vector2 window_size;




#define MAX_BALLS 1048576 // 2^20

size_t amount_of_circles = 1;
Circle array_of_circles[MAX_BALLS];
bool have_warned = false;
void add_new_ball(void)
{
        int current_fps = GetFPS();
        if(amount_of_circles < MAX_BALLS && (current_fps > 30 || IsKeyDown(KEY_D))){
            array_of_circles[amount_of_circles] = initialize_ball(&window_size);
            amount_of_circles++;
            // printf("Amount of balls: %i\n", amount_of_circles);
        }else if(current_fps < 30 && !IsKeyDown(KEY_D)){
            amount_of_circles--;
        }
        else if(!have_warned){
            printf(REDTERM "too many balls!!\n" RESETTERM);
            have_warned = true;
        }
}



void draw_info(void)
{
    Color info_text_color = WHITE;
    DrawRectangle(0, 0, 200, 85, DARKGREEN);
    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 60, 20, info_text_color);
    DrawText(TextFormat("Frametime: %f", GetFrameTime()), 0, 40, 20, info_text_color);
    DrawText(TextFormat("Balls: %i", amount_of_circles), 0, 0, 20, info_text_color);
    DrawText(TextFormat("Max balls: %i", MAX_BALLS), 0, 20, 20, info_text_color);
}
Vector2 old_window = {800, 600};

int main(void)
{   

    window_size.x = 800;
    window_size.y = 600;
    char *window_title = "Ballz";

    SetTargetFPS(FPS);
    int flags = FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT;
    SetConfigFlags(flags);
    InitWindow(window_size.x, window_size.y, window_title);
    int current_monitor = GetCurrentMonitor();
    window_size.x = GetMonitorWidth(current_monitor);
    window_size.y = GetMonitorHeight(current_monitor);
    SetWindowSize(window_size.x, window_size.y);
    ToggleFullscreen();
    array_of_circles[0] = initialize_ball(&window_size);
    bool enable_info_overlay = true;
    
    
    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_SPACE)){
            if(amount_of_circles < MAX_BALLS){
                for(int i = 0;i <= 100 && amount_of_circles < MAX_BALLS; i++){
                    add_new_ball();
                    amount_of_circles++;
                }
                printf("Amount of balls: %i\n", amount_of_circles);
            }
        }
        if(IsKeyPressed(KEY_I)){
            enable_info_overlay = !enable_info_overlay;
        }
        if(IsKeyPressed(KEY_F)){
            if(!IsWindowFullscreen()){
                old_window.x = window_size.x;
                old_window.y = window_size.y;
                window_size.x = GetMonitorWidth(current_monitor);
                window_size.y = GetMonitorHeight(current_monitor);
                SetWindowSize(window_size.x, window_size.y);
                ToggleFullscreen();
            }else{
                ToggleFullscreen();
                SetWindowSize(old_window.x, old_window.y);
            }
        }
        window_size.x = GetScreenWidth();
        window_size.y = GetScreenHeight();
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = 0; i < amount_of_circles; i++){
                    DrawCircle(array_of_circles[i].x_pos, array_of_circles[i].y_pos ,array_of_circles[i].radius, array_of_circles[i].color); 
                    // DrawCircleLines(array_of_circles[i].x_pos, array_of_circles[i].y_pos ,array_of_circles[i].radius + 1, array_of_circles[i].color); 

            }
            
            if(enable_info_overlay){
                draw_info();
            }
        EndDrawing();
        for(int i = 0; i < amount_of_circles; i++)
            update_ball_position(&array_of_circles[i], &window_size);
    }
    CloseWindow();

    return 0;
}

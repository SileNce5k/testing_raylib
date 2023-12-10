#include "include/raylib.h"
#include "limits.h"
#include "stdio.h"
#include <stdlib.h>
#define FPS 60
#define REDTERM     "\033[31m"      /* Red */
#define RESETTERM   "\033[0m"
#define GREENTERM   "\033[32m"      /* Green */

typedef struct
{
    int x_pos;
    int y_pos;
    int radius;
    bool neg_width;
    bool neg_height;
    Color color;
    int speed;
} Circle;


typedef struct
{
    size_t amount;
    size_t capacity;
} Circles;


static const Color array_of_colors[] = {
    {200, 200, 200, 255},
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
    current_color = GetRandomValue(0, 21);
    circle->color = array_of_colors[current_color];
}



int main(void)
{   
    Vector2 window_size;
    window_size.x = 800;
    window_size.y = 600;


    char *window_title = "Rake";

    SetTargetFPS(FPS);
    int flags = FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT;
    SetConfigFlags(flags);
    InitWindow(window_size.x, window_size.y, window_title);
    Circle circle;
    
    circle.neg_height = false;
    circle.neg_width = false;
    circle.radius = 24;
    circle.x_pos = circle.radius;
    circle.y_pos = circle.radius;
    circle.speed = 7;
    circle.color = array_of_colors[0];
    
    while(!WindowShouldClose())
    {
        window_size.x = GetScreenWidth();
        window_size.y = GetScreenHeight();
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(circle.x_pos, circle.y_pos ,circle.radius, circle.color); 
        EndDrawing();
        if(circle.x_pos >= window_size.x - circle.radius){
            circle.neg_width = true;
            change_circle_color(&circle);
        }else if(circle.x_pos <= 0 + circle.radius){
            circle.neg_width = false;
            change_circle_color(&circle);
        }
        if(circle.neg_width){
            circle.x_pos -= circle.speed;
        }else {
            circle.x_pos += circle.speed;
        }


        if(circle.y_pos >= window_size.y - circle.radius){
            circle.neg_height = true;
            change_circle_color(&circle);
        }else if(circle.y_pos <= 0 + circle.radius){
            circle.neg_height = false;
            change_circle_color(&circle);
        }
        if(circle.neg_height){
            circle.y_pos -= circle.speed;
        }else{
            circle.y_pos += circle.speed;
        }
    }
    CloseWindow();

    return 0;
}

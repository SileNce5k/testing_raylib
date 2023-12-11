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
    Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255)};
    circle->color = color;
}

Vector2 window_size;


Circle initialize_ball(int radius, int speed)
{

    Circle circle;
    
    circle.neg_height = false;
    circle.neg_width = false;
    circle.radius = GetRandomValue(2, 24);
    circle.x_pos = GetRandomValue(1, window_size.x - circle.radius);
    circle.y_pos = GetRandomValue(1, window_size.y - circle.radius);
    if(circle.x_pos > window_size.x / 2){
        circle.neg_width = true;
    }
    if(circle.y_pos > window_size.y / 2){
        circle.neg_height = true;
    }
    circle.speed = GetRandomValue(3, 7);
    Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255)};
    circle.color = color;

    return circle;

}

#define MAX_BALLS 1234

size_t amount_of_circles = 1;
Circle array_of_circles[MAX_BALLS];
bool have_warned = false;
void add_new_ball(void)
{
    if(amount_of_circles < MAX_BALLS){
        array_of_circles[amount_of_circles] = initialize_ball(24,7);
        amount_of_circles++;
        printf("Amount of balls: %i\n", amount_of_circles);
    }else if(!have_warned){
        printf(REDTERM "too many balls!!\n" RESETTERM);
        have_warned = true;
    }
}

void update_ball_position(Circle *circle, Vector2 *window_size)
{
    if(circle->x_pos >= window_size->x - circle->radius){
            circle->neg_width = true;
            change_circle_color(circle);
            add_new_ball();
        }else if(circle->x_pos <= 0 + circle->radius){
            circle->neg_width = false;
            change_circle_color(circle);
            add_new_ball();
        }
        if(circle->neg_width){
            circle->x_pos -= circle->speed;
        }else {
            circle->x_pos += circle->speed;
        }


        if(circle->y_pos >= window_size->y - circle->radius){
            circle->neg_height = true;
            change_circle_color(circle);
            add_new_ball();
        }else if(circle->y_pos <= 0 + circle->radius){
            circle->neg_height = false;
            change_circle_color(circle);
            add_new_ball();
        }
        if(circle->neg_height){
            circle->y_pos -= circle->speed;
        }else{
            circle->y_pos += circle->speed;
        }
}


int main(void)
{   

    window_size.x = 800;
    window_size.y = 600;
    char *window_title = "Ballz";

    SetTargetFPS(FPS);
    int flags = FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MAXIMIZED;
    SetConfigFlags(flags);
    InitWindow(window_size.x, window_size.y, window_title);
    array_of_circles[0] = initialize_ball(24, 7);


    
    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_SPACE)){
            if(amount_of_circles <= MAX_BALLS){
                array_of_circles[amount_of_circles] = initialize_ball(24,7);
                amount_of_circles++;
                printf("Amount of balls: %i\n", amount_of_circles);
            }
        }
        window_size.x = GetScreenWidth();
        window_size.y = GetScreenHeight();
        
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = 0; i < amount_of_circles; i++)
                DrawCircle(array_of_circles[i].x_pos, array_of_circles[i].y_pos ,array_of_circles[i].radius, array_of_circles[i].color); 
        EndDrawing();
        for(int i = 0; i < amount_of_circles; i++)
            update_ball_position(&array_of_circles[i], &window_size);
    }
    CloseWindow();

    return 0;
}

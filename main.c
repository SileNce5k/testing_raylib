#include "include/raylib.h"
#include "limits.h"
#include "stdio.h"
#include <stdlib.h>
#include "common_functions.h"
#include "main.h"
#define FPS 60
#define REDTERM     "\033[31m"      /* Red */
#define RESETTERM   "\033[0m"
#define GREENTERM   "\033[32m"      /* Green */
void add_new_ball();


bool enable_ball_generator = true;
bool enable_ball_eraser = false;



int current_color = 7; // Initial Color = Red
void change_circle_color(Circle *circle)
{
    Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(200, 255)};
    circle->color = color;
}

typedef struct {
    size_t balls;
    size_t circles;
    size_t squares;
    size_t stars;
} Type_Amounts;

Type_Amounts types = {0, 0, 0, 0};


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


Vector2 window_size;




#define MAX_BALLS 1048576 // 2^20

size_t amount_of_circles = 1;
Circle array_of_circles[MAX_BALLS];
bool have_warned = false;
void add_new_ball()
{
        int current_fps = GetFPS();
        if(amount_of_circles < MAX_BALLS && enable_ball_generator){
            array_of_circles[amount_of_circles] = initialize_ball(&window_size);
            amount_of_circles++;
            // printf("Amount of balls: %i\n", amount_of_circles);
        }else if(enable_ball_eraser){
            amount_of_circles--;
        }
        else if(!have_warned && enable_ball_generator){
            printf(REDTERM "too many balls!!\n" RESETTERM);
            have_warned = true;
        }
}

void DrawStar(Circle *circle)
{
    Vector2 center = {circle->x_pos, circle->y_pos};
    DrawPoly(center, 3, circle->radius, 90.0f, circle->color);
    DrawPoly(center, 3, circle->radius, -90.0f, circle->color);
}




void draw_info(void)
{
    
    
    Color info_text_color = WHITE;
    DrawRectangle(0, 0, 235, 125, DARKGREEN);
    DrawText(TextFormat("FPS: %i", GetFPS()), 0, 60, 20, info_text_color);
    DrawText(TextFormat("Frametime: %f", GetFrameTime()), 0, 40, 20, info_text_color);
    DrawText(TextFormat("Balls: %i", amount_of_circles), 0, 0, 20, info_text_color);
    DrawText(TextFormat("Max balls: %i", MAX_BALLS), 0, 20, 20, info_text_color);
    DrawText(TextFormat("Generating: %s", enable_ball_generator? "true": "false"), 0, 80, 20, info_text_color);
    DrawText(TextFormat("Erasing: %s", enable_ball_eraser ? "true": "false"), 0, 100, 20, info_text_color);
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
        if(IsKeyPressed(KEY_C)){
            amount_of_circles -= 1000;
        }
        if(IsKeyPressed(KEY_E)){
            enable_ball_generator = !enable_ball_generator;
        }
        if(IsKeyPressed(KEY_R)){
            enable_ball_eraser = !enable_ball_eraser;
            enable_ball_generator = !enable_ball_generator;
        }
        if(IsKeyPressed(KEY_SPACE)){
            if(amount_of_circles < MAX_BALLS){
                for(int i = 0;i <= 100 && amount_of_circles < MAX_BALLS; i++){
                    add_new_ball();
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
                if(array_of_circles[i].type == BALL){
                    DrawCircle(array_of_circles[i].x_pos, array_of_circles[i].y_pos ,array_of_circles[i].radius, array_of_circles[i].color); 
                }else if(array_of_circles[i].type == CIRCLE){
                    DrawCircleLines(array_of_circles[i].x_pos, array_of_circles[i].y_pos ,array_of_circles[i].radius + 1, array_of_circles[i].color); 
                }else if(array_of_circles[i].type == RECTANGLE){
                    DrawRectangle(array_of_circles[i].x_pos, array_of_circles[i].y_pos, array_of_circles[i].radius * 2, array_of_circles[i].radius * 2, array_of_circles[i].color); 
                }else if(array_of_circles[i].type == STAR){
                    DrawStar(&array_of_circles[i]);
                }

            }
            
            if(enable_info_overlay){
                draw_info();
            }else{
                DrawFPS(0, 0);
            }
        EndDrawing();
        for(int i = 0; i < amount_of_circles; i++)
            update_ball_position(&array_of_circles[i], &window_size);
    }
    CloseWindow();

    return 0;
}

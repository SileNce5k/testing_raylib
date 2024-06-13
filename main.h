#pragma once
#include <stdlib.h>
#ifndef RAYLIB_H
#include "include/raylib.h"
#endif // RAYLIB_H
typedef enum  {
    BALL,
    CIRCLE,
    RECTANGLE,
    STAR,
} Type;
void draw_frame(void);
typedef struct
{
    int x_pos;
    int y_pos;
    int radius;
    bool neg_width;
    bool neg_height;
    Color color;
    int speed;
    Type type;
} Circle;

typedef struct 
{
    bool enable_info_overlay;
    bool enable_item_info;
    bool clear_background;
    bool enable_hotkeys_menu; 
    bool enable_ball_generator;
    bool enable_ball_eraser;
} Bools;




Circle initialize_ball(Vector2* window_size);

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
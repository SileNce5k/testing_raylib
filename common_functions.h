#pragma once
#ifndef RAYLIB_H
#include "include/raylib.h"
#endif // RAYLIB_H
typedef enum  {
    BALL,
    CIRCLE,
} Type;
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

Circle initialize_ball(Vector2* window_size);
void update_ball_position(Circle *circle, Vector2 *window_size);
void change_circle_color(Circle *circle);
void add_new_ball();
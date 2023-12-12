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
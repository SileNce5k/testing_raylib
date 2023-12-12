#ifndef COMMON_FUNC_H
#include "common_functions.h"
#endif // COMMON_FUNC_H
#define COMMON_FUNC_H
Circle initialize_ball(Vector2 *window_size, Type_Amounts types)
{

    Circle circle;
    
    circle.neg_height = false;
    circle.neg_width = false;
    circle.radius = GetRandomValue(5, 24);
    circle.x_pos = GetRandomValue(1, window_size->x - circle.radius);
    circle.y_pos = GetRandomValue(1, window_size->y - circle.radius);
    if(circle.x_pos > window_size->x / 2){
        circle.neg_width = true;
    }
    if(circle.y_pos > window_size->y / 2){
        circle.neg_height = true;
    }
    circle.speed = GetRandomValue(3, 7);
    Color color = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(200, 255)};
    circle.color = color;
    Type m_type;
    m_type = GetRandomValue(0, 3);
    circle.type = m_type;
    /*
        BALL,
        CIRCLE,
        RECTANGLE,
        STAR,
    */
    switch (circle.type)
    {
    case BALL:
        types.balls += 1;
        break;
    case CIRCLE:
        types.circles += 1;
        break;
    case RECTANGLE:
        types.squares += 1;
        break;
    case STAR:
        types.stars += 1; 
        break;
    default:
        break;
    }
    return circle;

}


#include "common_functions.h"
Circle initialize_ball(Vector2 *window_size)
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
    circle.type = GetRandomValue(0, 1);

    return circle;

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


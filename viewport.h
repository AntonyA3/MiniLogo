#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef RECT_H
#include "rect.h"
#define RECT_H
#endif

typedef struct 
{
    vec3 position;
    vec3 scale;
    float width;
    float height;
    float angle;
    Rect bounds;
}Viewport;


void init_viewport(Viewport* viewport, float width, float height);
void set_position_viewport(Viewport* viewport, vec3 position);
void move_position_viewport(Viewport* viewport, vec3 movement);
void set_angle_viewport(Viewport* viewport, float angle);
void rotate_viewport(Viewport* viewport, float angle);
void get_transform_viewport(Viewport* viewport, mat4x4 transform);
void move_y_viewport(Viewport* viewport, float y);
void move_x_viewport(Viewport* viewport, float x);
void clamp_viewport(Viewport* viewport, Rect rect);
void to_canvas_position_viewport(Viewport viewport, vec2 position);
void to_canvas_scale_viewport(Viewport viewport, vec2 position);
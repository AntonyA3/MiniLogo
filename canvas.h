
#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

typedef struct
{
    vec2 start;
    vec2 end;
    vec3 color;
}Canvas;

void init_canvas(Canvas* canvas, float width, float height, vec3 color);

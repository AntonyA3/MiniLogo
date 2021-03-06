#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

typedef struct 
{
    float x;
    float y;
    float sx;
    float sy;
}Rect;


int contains_point_rect(Rect rect, vec2 point);
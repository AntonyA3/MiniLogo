#include "canvas.h"

void init_canvas(Canvas* canvas, float width, float height, vec3 color){
    vec2 zero ={0.0f, 0.0f};
    vec2 end = {width, height};
    memcpy(canvas->start, zero, sizeof(vec2));
    memcpy(canvas->end,end, sizeof(vec2));
    memcpy(canvas->color, color, sizeof(vec3));
}

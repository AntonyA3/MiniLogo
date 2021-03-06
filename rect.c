#include "rect.h"


int contains_point_rect(Rect rect, vec2 point){
    return (point[0] >= rect.x)  && 
    (point[0] <= (rect.x + rect.sx)) &&
    (point[1] >= rect.y) &&
    (point[1] <= (rect.y + rect.sy));

}
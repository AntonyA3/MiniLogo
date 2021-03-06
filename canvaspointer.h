#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef MOUSESTATE_H
#include "mousestate.h"
#define MOUSESTATE_H
#endif

#ifndef VIEWPORT_H
#include "viewport.h"
#define VIEWPORT_H
#endif

typedef struct 
{
    vec2 lastPosition;
    vec2 currentPosition;
    vec2 deltaPosition;
}CanvasPointer;


void update_canvaspointer(CanvasPointer* canvasPointer, MouseState mousestate, Viewport viewport);

#ifndef STD_H
#include <stdio.h>
#include <stdlib.h>
#define STD_H
#endif

#ifndef DRAWRECT_H
#include "drawrect.h"
#define DRAWRECT_H
#endif


typedef struct 
{
    DrawRect* drawRects;
    unsigned int drawRectCount;
    unsigned int drawRectCapacity;
   
}CanvasObjects;


void init_canvas_objects(CanvasObjects* canvasObjects);
void add_drawrect_to_canvasobjects(CanvasObjects* canvasObjects, DrawRect rect);
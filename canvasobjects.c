#include "canvasobjects.h"

void init_canvas_objects(CanvasObjects* canvasObjects){
    canvasObjects->drawRectCount = 0;
    canvasObjects->drawRectCapacity= 0;
}

void add_drawrect_to_canvasobjects(CanvasObjects* canvasObjects, DrawRect rect){
    if(canvasObjects->drawRectCapacity == 0){
        canvasObjects->drawRectCapacity = 1;
        canvasObjects->drawRects = malloc(sizeof(DrawRect));
        memcpy(&canvasObjects->drawRects[canvasObjects->drawRectCount], &rect, sizeof(DrawRect));
        canvasObjects->drawRectCount += 1;
    }
    else if(canvasObjects->drawRectCount == canvasObjects->drawRectCapacity ){
        canvasObjects->drawRectCapacity *= 2;
        canvasObjects->drawRects = realloc(canvasObjects->drawRects, canvasObjects->drawRectCapacity * sizeof(DrawRect));
        memcpy(&canvasObjects->drawRects[canvasObjects->drawRectCount], &rect, sizeof(DrawRect));
        canvasObjects->drawRectCount += 1;   
    }else{
        memcpy(&canvasObjects->drawRects[canvasObjects->drawRectCount], &rect, sizeof(DrawRect));
        canvasObjects->drawRectCount += 1;      
    }
}
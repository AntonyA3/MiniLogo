#include "canvaspointer.h"


void update_canvaspointer(CanvasPointer* canvasPointer, MouseState mousestate, Viewport viewport){
    memcpy(canvasPointer->currentPosition, mousestate.currentPosition,sizeof(vec2));
    memcpy(canvasPointer->lastPosition, mousestate.lastPosition, sizeof(vec2));
    memcpy(canvasPointer->deltaPosition, mousestate.deltaPosition, sizeof(vec2));
    to_canvas_scale_viewport(viewport, canvasPointer->deltaPosition);
    to_canvas_position_viewport(viewport,  canvasPointer->currentPosition);
    to_canvas_position_viewport(viewport, canvasPointer->lastPosition);

}
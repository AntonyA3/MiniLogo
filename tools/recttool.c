#include "recttool.h"

void init_recttool(RectTool* rectTool){
    rectTool->state = RECT_TOOL_STATE_PICK_START;
}

void update_recttool(RectTool* rectTool, CanvasObjects* canvasObjects, CanvasPointer canvasPointer, MouseState mouseState, vec3 color){
    
    switch (rectTool->state)
    { 
    case  RECT_TOOL_STATE_PICK_START:
        if(mouseState.buttonState[0] == MOUSE_BUTTON_STATE_JUST_PRESSED){
            memcpy(rectTool->start, canvasPointer.currentPosition, sizeof(vec2));
            rectTool->state = RECT_TOOL_STATE_PICK_END;
        }
        break;
    case RECT_TOOL_STATE_PICK_END:
        
        memcpy(rectTool->end, canvasPointer.currentPosition, sizeof(vec2));


        vec2 halfExtents = {
                (rectTool->end[0] - rectTool->start[0]) * 0.5,
                (rectTool->end[1] - rectTool->start[1]) * 0.5,
            };
        vec3 position = {
            rectTool->start[0] + halfExtents[0] ,
            rectTool->start[1] + halfExtents[1],
            0.0f
        };
        memcpy(rectTool->rect.position, position, sizeof(vec3));
        memcpy(rectTool->rect.halfExtents, halfExtents, sizeof(vec2));
        memcpy(rectTool->rect.fillColor, color, sizeof(vec3));

        if(mouseState.buttonState[0] == MOUSE_BUTTON_STATE_JUST_RELEASED){
            rectTool->state = RECT_TOOL_STATE_CREATE_RECT;
        }
        break;
    case RECT_TOOL_STATE_CREATE_RECT:
        {
            vec2 halfExtents = {
                (rectTool->end[0] - rectTool->start[0]) * 0.5,
                (rectTool->end[1] - rectTool->start[1]) * 0.5,
            };
            vec3 position = {
                rectTool->start[0] + halfExtents[0] ,
                rectTool->start[1] + halfExtents[1],
                0.0f
            };
            memcpy(rectTool->rect.position, position, sizeof(vec3));
            memcpy(rectTool->rect.halfExtents, halfExtents, sizeof(vec2));
            memcpy(rectTool->rect.fillColor, color, sizeof(vec3));
            add_drawrect_to_canvasobjects(canvasObjects, rectTool->rect);
            rectTool->state = RECT_TOOL_STATE_PICK_START;
        }
        break;    
    default:
        break;
    }
}
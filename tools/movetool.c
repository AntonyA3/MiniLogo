#include "movetool.h"

void update_movetool(Viewport* viewport, CanvasPointer canvasPointer, int mouseState){
    if(mouseState == MOUSE_BUTTON_STATE_JUST_PRESSED || mouseState == MOUSE_BUTTON_STATE_PRESSED){
        move_x_viewport(viewport, canvasPointer.deltaPosition[0]);
        move_y_viewport(viewport, canvasPointer.deltaPosition[1]);
    }
   

}
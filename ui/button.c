#include "button.h"

void update_button(Button* button, MouseState mouse,  Button** lastSelected ){
    switch (button->state)
    {
    case BUTTON_STATE_SELECTED:
        if(button != *lastSelected){
            button->state = BUTTON_STATE_NOT_SELECTED;
        }
        break;
    case BUTTON_STATE_NOT_SELECTED:
        if(contains_point_rect(button->area, mouse.currentPosition)){
            button->state = BUTTON_STATE_HOVERING;
        }
        break;
    case BUTTON_STATE_HOVERING:
        if(!contains_point_rect(button->area, mouse.currentPosition)){
            button->state = BUTTON_STATE_NOT_SELECTED;
        }
        if(mouse.buttonState[0] == MOUSE_BUTTON_STATE_JUST_PRESSED){
            *lastSelected = button;
            button->state = BUTTON_STATE_SELECTED;
        }
        break;
    
    default:
        break;
    }

}
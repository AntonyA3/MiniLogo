
#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef RECT_H
#include "../rect.h"
#define RECT_H
#endif

#ifndef MOUSESTATE_H
#include "../mousestate.h"
#define MOUSESTATE_H
#endif

enum button_state{
    BUTTON_STATE_NOT_SELECTED,
    BUTTON_STATE_HOVERING,
    BUTTON_STATE_SELECTED
};

typedef struct {
    vec2 position;
    Rect area;
    unsigned int state;

    vec3 selectedColor;
    vec3 unselectedColor;
    vec3 hoveringColor;

}Button;

void update_button(Button* button, MouseState mouse, Button** lastSelected);
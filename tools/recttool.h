#ifndef CANVASPOINTER_H
#include "../canvaspointer.h"
#define CANVASPOINTER_H
#endif

#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef DRAWRECT_H
#include "../drawrect.h"
#define DRAWRECT_H
#endif

#ifndef MOUSESTATE_H
#include "../mousestate.h"
#define MOUSESTATE_H
#endif

#ifndef VIEWPORT_H
#include "../viewport.h"
#define VIEWPORT_H
#endif

#ifndef CANVASOBJECTS_H
#include "../canvasobjects.h"
#define CANVASOBJECTS_H
#endif
enum rect_tool_state{
    RECT_TOOL_STATE_PICK_START,
    RECT_TOOL_STATE_PICK_END,
    RECT_TOOL_STATE_CREATE_RECT
};

typedef struct 
{
    vec2 start;
    vec2 end;
    unsigned int state;
    DrawRect rect;
}RectTool;

void init_recttool(RectTool* rectTool);
void update_recttool(RectTool* rectTool, CanvasObjects* canvas, CanvasPointer canvasPointer, MouseState mouseState, vec3 color);

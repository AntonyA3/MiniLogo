#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef GLFW_H
#include <GLFW/glfw3.h>
#define GLFW_H
#endif

enum mouse_button_state {
    MOUSE_BUTTON_STATE_JUST_PRESSED,
    MOUSE_BUTTON_STATE_PRESSED,
    MOUSE_BUTTON_STATE_RELEASED,
    MOUSE_BUTTON_STATE_JUST_RELEASED
};


typedef struct{
    vec2 lastPosition;
    vec2 currentPosition;
    vec2 deltaPosition;
    unsigned int buttonState[3]; 
}MouseState;


void init_mousestate(MouseState* mouseState, vec2 startPosition);
void update_mousestate(MouseState* mouseState, GLFWwindow* window, vec2 newPosition);



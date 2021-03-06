#include "mousestate.h"
void init_mousestate(MouseState* mouseState, vec2 startPosition){
    mouseState->deltaPosition[0] = 0.0f;
    mouseState->deltaPosition[1] = 0.0f;
    mouseState->currentPosition[0] = startPosition[0];
    mouseState->currentPosition[1] =startPosition[1];
    mouseState->lastPosition[0] = startPosition[0];
    mouseState->lastPosition[1] -startPosition[1];

    for(int i = 0; i < 3; i++){
        mouseState->buttonState[i] = MOUSE_BUTTON_STATE_RELEASED;
    }
}

void update_mousestate(MouseState* mouseState, GLFWwindow* window ,vec2 newPosition){
    mouseState->lastPosition[0] = mouseState->currentPosition[0];
    mouseState->lastPosition[1] = mouseState->currentPosition[1];
    mouseState->currentPosition[0] = newPosition[0];
    mouseState->currentPosition[1] = newPosition[1];
    mouseState->deltaPosition[0] = newPosition[0] - mouseState->lastPosition[0];
    mouseState->deltaPosition[1] = newPosition[1] - mouseState->lastPosition[1];

    for(int i = 0; i < 3; i++){
        switch (mouseState->buttonState[i])
        {
            case MOUSE_BUTTON_STATE_RELEASED:
                if(glfwGetMouseButton(window, i) == GLFW_PRESS){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_JUST_PRESSED;
                }
                break;
            case MOUSE_BUTTON_STATE_JUST_PRESSED:
                if(glfwGetMouseButton(window, i) == GLFW_PRESS){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_PRESSED;
                }
                else if(glfwGetMouseButton(window, i) == GLFW_RELEASE){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_JUST_RELEASED;
                }
                break;
            case MOUSE_BUTTON_STATE_PRESSED:
                if(glfwGetMouseButton(window, i) == GLFW_RELEASE){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_JUST_RELEASED;
                }
                break;
            case MOUSE_BUTTON_STATE_JUST_RELEASED:
                if(glfwGetMouseButton(window, i) == GLFW_PRESS){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_JUST_PRESSED;
                }
                else if(glfwGetMouseButton(window, i) == GLFW_RELEASE){
                    mouseState->buttonState[i] = MOUSE_BUTTON_STATE_RELEASED;
                }
                break;
            default:
                break;
        }
    }


}



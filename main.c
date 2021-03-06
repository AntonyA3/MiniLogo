#include <GL/glew.h>
#define GLEW_H
#include <GLFW/glfw3.h>
#define GLFW_H
#include <stdio.h>
#include <stdlib.h>
#define STD_H
#include <linmath.h>
#define LINMATH_H
#include "mousestate.h"
#define MOUSESTATE_H
#include "canvas.h"
#define CANVAS_H
#include "drawrect.h"
#define DRAWRECT_H
#include "fillbatch.h"
#define FILLBATCH_H
#include "rect.h"
#define RECT_H
#include "viewport.h"
#define VIEWPORT_H
#include "canvaspointer.h"
#define CANVASPOINTER_H
#include "canvasobjects.h"
#define CANVASOBJECTS_H
#include "tools/recttool.h"
#define RECTTOOL_H
#include "ui/button.h"
#define BUTTON_H
#include "ui/buttonbatch.h"
#define BUTTONBATCH_H
#include "tools/movetool.h"
#define MOVETOOL_H

enum tool{
    TOOL_MOVE,
    TOOL_RECT_DRAW

};

static const char* window_title = "Mini Logo";
static int window_width = 400;
static int window_height = 400;
static float canvas_width= 300.0f;
static float canvas_height = 300.0f;
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void load_text_file(char** text,const char* filePath){

    FILE *fp;
    long length;
    fp = fopen(filePath, "rb");

    if (fp == NULL){
        printf("Could not open file %s",filePath);

    }else{
        fseek (fp, 0, SEEK_END);
        length = ftell (fp);
        fseek (fp, 0, SEEK_SET);
        *text = malloc(length);
        if (*text)
        {
            fread (*text, 1, length, fp);
        }
        fclose (fp);
    }
}

GLuint init_shader(const char* vertex_shader_text, const char* fragment_shader_text){
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertexShader);
    
    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(success){
        printf("vertex shader successful\n");
    }else{
        printf("vertex shader failed\n");
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragmentShader);

    success = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(success){
        printf("fragment shader successful\n");
    }else{
        printf("fragment shader failed\n");
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    success = 0;
    glGetProgramiv(program, GL_LINK_STATUS,&success);

    if(success){
        printf("program successful\n");
    }else{
        printf("program failed\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

GLuint init_shader_fron_file(char* vertShaderPath, char* fragShaderPath){
    char* vertexShaderSource;
    load_text_file(&vertexShaderSource, vertShaderPath);
    char* fragmentShaderSource;
    load_text_file(&fragmentShaderSource, fragShaderPath);
    GLuint shader =init_shader((const char*)vertexShaderSource, (const char*)fragmentShaderSource );
    free(vertexShaderSource);
    free(fragmentShaderSource);
    return shader;

}




void init_glfw_window(GLFWwindow** window,const char* title, int width, int height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if (*window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
    }
    glfwMakeContextCurrent(*window);

}

void init_glew(){
    GLenum glew_init = glewInit();
    if (GLEW_OK != glew_init){
        printf("Error with GLEW\n");
    }else{
        printf("GLEW has successfully been added\n");
    }
}



int main(void){
    GLFWwindow* window;
    GLuint fillShader, buttonShader;
    FillBatch fillBatch;
    ButtonBatch buttonBatch;
    Canvas canvas;
    Rect viewportBoundary;
    Viewport viewport;
    DrawRect sample_draw_rect;
    MouseState  mouseState;
    CanvasPointer canvasPointer;
    RectTool rectTool;
    CanvasObjects canvasObjects;
    Button buttons[2];
    Button* moveToolButton;
    Button* rectToolButton;
    Button* lastSelectedButton;
    int activeTool;

    
    init_glfw_window(&window, window_title, window_width, window_height);
    init_glew();
    fillShader = init_shader_fron_file("shaders/fill.vert", "shaders/fill.frag");
    buttonShader = init_shader_fron_file("shaders/button.vert", "shaders/button.frag");
    init_fillbatch(&fillBatch, 1000, 1000, fillShader);

    init_buttonbatch(&buttonBatch, 1000, 1000, buttonShader);

    {
        float width = canvas_width;
        float height = canvas_height;
        vec3 white = {1.0f, 1.0f, 1.0f};
        init_canvas(&canvas, canvas_width, canvas_height, white);
    }

    {
        vec3 mov = {-50.0f, -50.0f, 0.0f};
        init_viewport(&viewport, 400.0f, 400.0f);
        move_position_viewport(&viewport, mov );
    }

    {
        Rect r = {-200,-200, 600, 600};
        memcpy(&viewportBoundary, &r, sizeof(Rect));
    }

    {
        vec3 pos = {50.0f, 50.0f, 0.0f};
        vec2 ex = {10.0f, 10.0f};
        vec3 green = {0.0f, 1.0f, 0.0f};
        memcpy(sample_draw_rect.position, pos, sizeof(vec3));
        memcpy(sample_draw_rect.halfExtents, ex, sizeof(vec2));
        memcpy(sample_draw_rect.fillColor, green, sizeof(vec3));
    }
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        vec2 startpos = {(float)xPos, (float)yPos};
        init_mousestate(&mouseState, startpos);
    }
    {
        vec3 grey = {0.3f,0.3f,0.3f};
        vec3 lightgrey= {0.7f,0.7f,0.7f};
        vec3 blue = {0.1f,0.1f,1.0f};;
        moveToolButton = &buttons[0];
        moveToolButton->position[0] = 10.0f;
        moveToolButton->position[1] = 15.0f;
        moveToolButton->area.x = 10.0f;
        moveToolButton->area.y = 15.0f;
        moveToolButton->area.sx = 30.0f;
        moveToolButton->area.sy = 30.0f;
        moveToolButton->state  = BUTTON_STATE_SELECTED;
        memcpy(moveToolButton->unselectedColor, grey, sizeof(vec3));
        memcpy(moveToolButton->selectedColor, blue, sizeof(vec3));
        memcpy(moveToolButton->hoveringColor, lightgrey, sizeof(vec3));
        activeTool = 0;

        rectToolButton = &buttons[1];
        rectToolButton->position[0] = 10.0f;
        rectToolButton->position[1] = 30.0f +  20.0f;
        rectToolButton->area.x = 10.0f;
        rectToolButton->area.y = 30.0f + 20.0f;
        rectToolButton->area.sx = 30.0f;
        rectToolButton->area.sy = 30.0f;
        rectToolButton->state  = BUTTON_STATE_NOT_SELECTED;
        memcpy(rectToolButton->unselectedColor, grey, sizeof(vec3));
        memcpy(rectToolButton->selectedColor, blue, sizeof(vec3));
        memcpy(rectToolButton->hoveringColor, lightgrey, sizeof(vec3));

        lastSelectedButton = moveToolButton;
    }

    init_recttool(&rectTool);
    init_canvas_objects(&canvasObjects);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
       
        //update mouse state and canvas pointer
        {
            double xPos, yPos;
            vec2 newPos = {(float)xPos, (float)yPos};
            glfwGetCursorPos(window, &xPos, &yPos);
            update_mousestate(&mouseState,window ,newPos);
            update_canvaspointer(&canvasPointer, mouseState, viewport);
        }
       

        for(int i = 0; i < 2; i++){
            update_button(&buttons[i], mouseState, &lastSelectedButton);
            if(&buttons[i] == lastSelectedButton){
                activeTool = i;
            }
            add_button_buttonbatch(&buttonBatch, buttons[i]);
        }

        switch (activeTool)
        {
        case TOOL_MOVE:
            update_movetool( &viewport, canvasPointer, mouseState.buttonState[0]);
            clamp_viewport(&viewport, viewportBoundary);
            break;
        case TOOL_RECT_DRAW:
            {
                vec3 green = {0.0f, 1.0f, 0.0f};
                update_recttool(&rectTool, &canvasObjects, canvasPointer, mouseState, green);
                //update_recttool(&rectTool, ,canvasPointer,  mouseState, green);
            }
            break;
        default:
            break;
        }

        mat4x4 canvas_transform;
        get_transform_viewport(&viewport , canvas_transform);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        add_canvas_fillbatch(&fillBatch, canvas); 
        for(int i = 0; i < canvasObjects.drawRectCount; i++){
            add_drawrect_fillbatch(&fillBatch, canvasObjects.drawRects[i]);        
        }
        if(activeTool == TOOL_RECT_DRAW){
            add_drawrect_fillbatch(&fillBatch, rectTool.rect);
        }


        bind_fillbatch(&fillBatch);
        fillBatch.isChanged = 0;

        
        
        use_program_fillbatch(&fillBatch);
        draw_fillbatch(&fillBatch, canvas_transform);
        
        {
            mat4x4 transform, translation;
            mat4x4_ortho(transform, -200.0f, 200.0f, 200.0f, -200.0f, 0.0f, 1.0f);
            mat4x4_translate(translation, -200.0f, -200.0f, 0.0f);
            mat4x4_mul(transform, transform, translation);

            
            use_program_buttonbatch(&buttonBatch);
            bind_buttonbatch(&buttonBatch);
            draw_buttonbatch(&buttonBatch, transform);
        }

        glfwSwapBuffers(window);
        flush_fillbatch(&fillBatch);
        flush_buttonbatch(&buttonBatch);
        glfwPollEvents();    

   
    }

    glfwTerminate();
    
    return 0;
}
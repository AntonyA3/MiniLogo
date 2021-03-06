
#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef GLEW_H
#include <GL/glew.h>
#define GLEW_H
#endif

#ifndef BUTTON_H
#include "button.h"
#define BUTTON_H
#endif

#ifndef STD_H
#include <stdio.h>
#include <stdlib.h>
#define STD_H
#endif


typedef struct 
{
    vec2 position;
    vec3 color;
    vec2 iconCoord;

}ButtonVertex;


typedef struct
{
    ButtonVertex* verticies;
    unsigned int* indicies;
    unsigned int vertexCapacity;
    unsigned int indexCapacity;
    unsigned int vertexCount;
    unsigned int indexCount;
    unsigned int indexValue;
    GLuint vao;
    GLuint vbo;
    GLuint eab;
    GLuint shader;
}ButtonBatch;


void use_program_buttonbatch(ButtonBatch* batch);
void init_buttonbatch(ButtonBatch* batch, unsigned int vertexCapacity, unsigned int  indexCapacity, GLuint shader);

void add_vertex_buttonbatch(ButtonBatch* batch, ButtonVertex vertex);
void add_index_buttonbatch(ButtonBatch* batch, unsigned int index);
void add_button_buttonbatch(ButtonBatch* batch, Button button);
void bind_buttonbatch(ButtonBatch* batch);
void draw_buttonbatch(ButtonBatch* batch,  mat4x4 transform);
void flush_buttonbatch(ButtonBatch* batch);
void reset_buttonbatch(ButtonBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity);

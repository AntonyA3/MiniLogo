#ifndef LINMATH_H
#include <linmath.h>
#define LINMATH_H
#endif

#ifndef GLEW_H
#include <GL/glew.h>
#define GLEW_H
#endif

#ifndef STD_H
#include <stdio.h>
#include <stdlib.h>
#define STD_H
#endif

#ifndef CANVAS_H
#include "canvas.h"
#define CANVAS_H
#endif

#ifndef DRAWRECT_H
#include "drawrect.h"
#define DRAWRECT_H
#endif



typedef struct
{
    vec3 position;
    vec3 color;
}FillVertex;

typedef struct 
{
    FillVertex* verticies;
    unsigned int* indicies;
    unsigned int vertexCount;
    unsigned int indexCount;
    unsigned int vertexCapacity;
    unsigned int indexCapacity;
    unsigned int indexValue;
    unsigned int isChanged;
    GLuint vao;
    GLuint vbo;
    GLuint eab;
    GLuint shader;
}FillBatch;

void use_program_fillbatch(FillBatch* batch);
void init_fillbatch(FillBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity, GLuint shader);
void add_vertex_fillbatch(FillBatch* batch, FillVertex vertex);
void add_index_fillbatch(FillBatch* batch, unsigned int index);
void add_canvas_fillbatch(FillBatch* batch, Canvas canvas);
void add_drawrect_fillbatch(FillBatch* batch, DrawRect rect);
void bind_fillbatch(FillBatch* batch);
void draw_fillbatch(FillBatch* batch,  mat4x4 transform);
void flush_fillbatch(FillBatch* batch);
void reset_fillbatch(FillBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity);

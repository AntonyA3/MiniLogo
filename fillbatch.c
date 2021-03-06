#include "fillbatch.h"



void init_fillbatch(FillBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity, GLuint shader){
    batch->vertexCapacity = vertexCapacity;
    batch->indexCapacity = indexCapacity;
    batch->verticies = (FillVertex*) malloc(vertexCapacity * sizeof(FillVertex));
    batch->indicies =(unsigned int*) malloc(indexCapacity * sizeof(unsigned int));
    batch->shader = shader;
    batch->indexValue = 0;
    batch->vertexCount= 0;
    batch->indexCount = 0;
    batch->isChanged = 1;


    glGenVertexArrays(1, &batch->vao);
    glBindVertexArray(batch->vao);
    glGenBuffers(1, &batch->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glGenBuffers(1, &batch->eab);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->eab);
    glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(FillVertex), NULL);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, sizeof(FillVertex), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}


void add_vertex_fillbatch(FillBatch* batch, FillVertex vertex){
    if((batch->vertexCount + 1) >= batch->vertexCapacity){
       batch->verticies = (FillVertex*) realloc(batch->verticies, 2 * sizeof(FillVertex) * batch->vertexCapacity);
       batch->vertexCapacity = 2 * batch->vertexCapacity;
    }
    memcpy(&batch->verticies[batch->vertexCount], &vertex, sizeof(FillVertex));
    batch->vertexCount += 1;
    batch->isChanged = 1;


}
void add_index_fillbatch(FillBatch* batch, unsigned int index){
    if((batch->indexCount + 1) >= batch->indexCapacity){
        batch->indicies =(unsigned int*) realloc(batch->indicies, 2 * sizeof(unsigned int) * batch->indexCapacity);
        batch->indexCapacity = 2 * batch->indexCapacity;
    }
    batch->indicies[batch->indexCount] = index;
    batch->indexCount +=1;
    batch->isChanged = 1;

}

void add_canvas_fillbatch(FillBatch* batch, Canvas canvas){
    FillVertex verticies[4];

    verticies[0].position[0] = canvas.start[0];
    verticies[0].position[1] = canvas.start[1];
    verticies[0].position[2] = 0.0f;

    verticies[1].position[0] = canvas.end[0];
    verticies[1].position[1] = canvas.start[1];
    verticies[1].position[2] = 0.0f;

    verticies[2].position[0] = canvas.end[0];
    verticies[2].position[1] = canvas.end[1];
    verticies[2].position[2] = 0.0f;

    verticies[3].position[0] = canvas.start[0];
    verticies[3].position[1] = canvas.end[1];
    verticies[3].position[2] = 0.0f;
  
    
    for(int i = 0; i < 4; i++){
        memcpy(verticies[i].color, canvas.color, sizeof(vec3));
        add_vertex_fillbatch(batch, verticies[i]);
    }

    unsigned int indicies[6] = {
            0,1,2,
            0,2,3
    };

    for(int i = 0; i < 6; i++){
        indicies[i] += batch->indexValue;
    }
    batch->indexValue += 4;

    for(int i = 0; i < 6; i++){
        add_index_fillbatch(batch, indicies[i]);
    }
    batch->isChanged = 1;

}

void add_drawrect_fillbatch(FillBatch* batch, DrawRect rect){
    FillVertex verticies[4];

    verticies[0].position[0] = rect.position[0] - rect.halfExtents[0];
    verticies[0].position[1] = rect.position[1] - rect.halfExtents[1];
    verticies[0].position[2] = 0.0f;

    verticies[1].position[0] = rect.position[0] + rect.halfExtents[0];
    verticies[1].position[1] = rect.position[1] - rect.halfExtents[1];
    verticies[1].position[2] = 0.0f;

    verticies[2].position[0] = rect.position[0] + rect.halfExtents[0];
    verticies[2].position[1] = rect.position[1] + rect.halfExtents[1];
    verticies[2].position[2] = 0.0f;

    verticies[3].position[0] = rect.position[0] - rect.halfExtents[0];
    verticies[3].position[1] = rect.position[1] + rect.halfExtents[1];
    verticies[3].position[2] = 0.0f;
    
    
    for(int i = 0; i < 4; i++){
        memcpy(verticies[i].color, rect.fillColor, sizeof(vec3));
        add_vertex_fillbatch(batch, verticies[i]);
    }

    unsigned int indicies[6] = {
            0,1,2,
            0,2,3
    };

    for(int i = 0; i < 6; i++){
        indicies[i] += batch->indexValue;
    }
        batch->indexValue += 4;


    for(int i = 0; i < 6; i++){
        add_index_fillbatch(batch, indicies[i]);
    }   
    batch->isChanged = 1;
}

void bind_fillbatch(FillBatch* batch){
    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferData(GL_ARRAY_BUFFER, batch->vertexCount * sizeof(FillVertex), batch->verticies, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch->indexCount * sizeof(unsigned int), batch->indicies, GL_DYNAMIC_DRAW);
  
}

void use_program_fillbatch(FillBatch* batch){
    glUseProgram(batch->shader);
}

void draw_fillbatch(FillBatch* batch, mat4x4 transform){
    glUniformMatrix4fv(glGetUniformLocation(batch->shader, "transform"), 1, GL_FALSE, (GLfloat*)*transform);
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, batch->indexCount, GL_UNSIGNED_INT, 0);
}




void flush_fillbatch(FillBatch* batch){
    batch->vertexCount = 0;
    batch->indexCount = 0; 
    batch->indexValue = 0;
}

void reset_fillbatch(FillBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity){

    free(batch->verticies);
    free(batch->indicies);
    batch->verticies = malloc(vertexCapacity *sizeof(FillVertex));
    batch->indicies = malloc(indexCapacity * sizeof(unsigned int));
    batch->vertexCount = 0;
    batch->indexCount = 0;
    batch->indexValue = 0;
    batch->vertexCapacity = vertexCapacity;
    batch->indexCapacity = indexCapacity;
    

}
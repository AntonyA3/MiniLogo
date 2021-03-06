#include "buttonbatch.h"


void use_program_buttonbatch(ButtonBatch* batch){
    glUseProgram(batch->shader);
}
void init_buttonbatch(ButtonBatch* batch, unsigned int vertexCapacity, unsigned int  indexCapacity, GLuint shader){
    batch->verticies = (ButtonVertex*) malloc(vertexCapacity * sizeof(ButtonVertex));
    batch->indicies = (unsigned int*) malloc(indexCapacity * sizeof(unsigned int));
    batch->vertexCapacity = vertexCapacity;
    batch->indexCapacity = indexCapacity;
    batch->vertexCount = 0;
    batch->indexCount = 0;
    batch->indexValue = 0;
    batch->shader = shader;
    glGenVertexArrays(1, &batch->vao);
    glBindVertexArray(batch->vao);
    glGenBuffers(1, &batch->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glGenBuffers(1, &batch->eab);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->eab);
    glVertexAttribPointer(0, 2,GL_FLOAT, GL_FALSE, sizeof(ButtonVertex), NULL);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, sizeof(ButtonVertex), (void*)(2* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2,GL_FLOAT, GL_FALSE, sizeof(ButtonVertex), (void*)(5* sizeof(float)));
    glEnableVertexAttribArray(2);
}

void add_button_buttonbatch(ButtonBatch* batch, Button button){
    ButtonVertex verticies[4];

    verticies[0].position[0] = button.area.x;
    verticies[0].position[1] = button.area.y;

    verticies[1].position[0] = button.area.x + button.area.sx;
    verticies[1].position[1] = button.area.y;

    verticies[2].position[0] = button.area.x + button.area.sx;
    verticies[2].position[1] = button.area.y + button.area.sy;

    verticies[3].position[0] = button.area.x;
    verticies[3].position[1] = button.area.y + button.area.sy;
    
    switch (button.state)
    {
        case BUTTON_STATE_NOT_SELECTED:
            for(int i = 0; i <4; i++){
                memcpy(verticies[i].color, button.unselectedColor, sizeof(vec3));
            }
            break;
        case BUTTON_STATE_SELECTED:
            for(int i = 0; i <4; i++){
                memcpy(verticies[i].color, button.selectedColor, sizeof(vec3));
            }
            break;
        case BUTTON_STATE_HOVERING:
            for(int i = 0; i <4; i++){
                memcpy(verticies[i].color, button.hoveringColor, sizeof(vec3));
            }
            break;
        default:
            break;
    }
    unsigned int indicies[6] = {
        0,1,2,
        0,2,3
    };

    if((batch->vertexCount + 4) >= batch->vertexCapacity){
        batch->vertexCapacity = 2 * sizeof(batch->vertexCapacity) + 4;
        batch->verticies = realloc(batch->verticies, batch->vertexCapacity *sizeof(ButtonVertex));
    }
    memcpy(&batch->verticies[batch->vertexCount], verticies, 4 * sizeof(ButtonVertex));
    batch->vertexCount += 4;

    if((batch->indexCount + 6) >= batch->indexCount){
        batch->indexCapacity = 2 * sizeof(batch->indexCapacity) + 6;
        batch->indicies = realloc(batch->indicies, batch->indexCapacity * sizeof(unsigned int));
    }
    
    for(int i = 0; i < 6; i++){
        indicies[i] += batch->indexValue;
    }
    memcpy(&batch->indicies[batch->indexCount], indicies, 6 * sizeof(unsigned int));
    batch->indexCount += 6;
    batch->indexValue += 4;
}

void bind_buttonbatch(ButtonBatch* batch){
    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ButtonVertex) * batch->vertexCount, batch->verticies, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->eab);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch->indexCount * sizeof(unsigned int), batch->indicies, GL_DYNAMIC_DRAW);
}
void draw_buttonbatch(ButtonBatch* batch,  mat4x4 transform){
    glUniformMatrix4fv(glGetUniformLocation(batch->shader, "transform"), 1, GL_FALSE, (GLfloat*)*transform);
    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, batch->indexCount, GL_UNSIGNED_INT, 0);

}
void flush_buttonbatch(ButtonBatch* batch){
   batch->indexCount = 0;
   batch->vertexCount = 0;
   batch->indexValue = 0;
}
void reset_buttonbatch(ButtonBatch* batch, unsigned int vertexCapacity, unsigned int indexCapacity){
    free(batch->verticies);
    free(batch->indicies);
    batch->verticies = (ButtonVertex*) malloc(vertexCapacity * sizeof(ButtonVertex));
    batch->indicies = (unsigned int*) malloc(indexCapacity * sizeof(unsigned int));
    batch->vertexCapacity = vertexCapacity;
    batch->indexCapacity = indexCapacity;
    batch->vertexCount = 0;
    batch->indexCount = 0;
    batch->indexValue = 0;
}

#include "viewport.h"

void init_viewport(Viewport* viewport, float width, float height){
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    viewport->width = width;
    viewport->height = height;
    
    viewport->position[0] = halfWidth;
    viewport->position[1] = halfHeight;
    viewport->position[2] = 0.0f;

    viewport->scale[0] = 1.0f;
    viewport->scale[1] = 1.0f;
    viewport->scale[2] = 1.0f;

    viewport->bounds.x = viewport->position[0] - halfWidth;
    viewport->bounds.y = viewport->position[1] - halfHeight;
    viewport->bounds.sx = width;
    viewport->bounds.sy = height;
    viewport->angle = 0.0f;

   
}

void get_transform_viewport(Viewport* viewport, mat4x4 transform){
    mat4x4 projection,translation;
    float halfWidth = viewport->width * 0.5f;
    float halfHeight = viewport->height * 0.5f;
    mat4x4_identity(projection);
    mat4x4_ortho(projection, -halfWidth, halfWidth, halfHeight, -halfHeight, 0.0f, 1.0f);
    mat4x4_identity(translation);
    
    mat4x4_translate(translation, -viewport->position[0], -viewport->position[1], 0.0f);
    
    mat4x4_mul(transform, projection, translation);
}

void move_position_viewport(Viewport* viewport, vec3 movement){
    viewport->position[0] += movement[0];
    viewport->position[1] += movement[1];
    viewport->position[2] += movement[2];
    viewport->bounds.x += movement[0];
    viewport->bounds.y += movement[1];
}

void move_x_viewport(Viewport* viewport, float x){
    viewport->position[0] += x;
    viewport->bounds.x += x;
}

void move_y_viewport(Viewport* viewport, float y){
    viewport->position[1] += y;
    viewport->bounds.y += y;
}

void clamp_viewport(Viewport* viewport, Rect rect){
    float viewport_max;
    float rect_max;
    if(viewport->bounds.x < rect.x){
        move_x_viewport(viewport,  rect.x - viewport->bounds.x);
    }

    viewport_max = viewport->bounds.x + viewport->bounds.sx;
    rect_max = rect.x + rect.sx;

    if(viewport_max > rect_max){
        move_x_viewport(viewport, rect_max - viewport_max);
    }

    if(viewport->bounds.y < rect.y){
        move_y_viewport(viewport,  rect.y - viewport->bounds.y);
    }

    viewport_max = viewport->bounds.y + viewport->bounds.sy;
    rect_max = rect.y + rect.sy;

    if(viewport_max > rect_max){
        move_y_viewport(viewport, rect_max - viewport_max);
    }

}


void to_canvas_scale_viewport(Viewport viewport, vec2 position){
    position[0] = position[0] * viewport.scale[0];
    position[1] = position[1] * viewport.scale[1];

}
void to_canvas_position_viewport(Viewport viewport, vec2 position){
    position[0] += viewport.bounds.x;
    position[1] += viewport.bounds.y;

}

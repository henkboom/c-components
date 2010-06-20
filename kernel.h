#ifndef KERNEL_H
#define KERNEL_H

typedef struct {
    void (*update)(void *data);
    void (*draw)(void *data);
    void *data;
} kernel_scene_s;

int kernel_start(kernel_scene_s *scene);

#endif

#include "kernel.h"

#include <GL/glfw.h>
#include <stdio.h>

#define check(cond) do { if(!(cond)) { return 1; } } while(0)

static int running = 0;
static double next_update_time;
static double fps = 60;

static void sleep_until(double time)
{
    double current_time = glfwGetTime();
    if(current_time < time)
        glfwSleep(time - current_time);
}

static int on_close()
{
    running = 0;
    return GL_FALSE;
}

int kernel_start(kernel_scene_s *scene)
{
    check(glfwInit());
    glfwOpenWindow(640, 480, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
    glfwSetWindowCloseCallback(on_close);
    running = 1;

    glViewport(0, 0, 640, 480);
    next_update_time = glfwGetTime();

    while(running)
    {
        sleep_until(next_update_time);
        next_update_time = glfwGetTime() + 1/fps;

        scene->update(scene->data);
        scene->draw(scene->data);

        glfwSwapBuffers();
    }

    glfwTerminate();
    return 0;
}

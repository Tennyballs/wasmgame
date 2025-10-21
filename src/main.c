#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#define GLEW_STATIC
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GL/glfw.h>
#include <emscripten/html5.h>
#include "vector2.h"
#include <math.h>

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)
#define clamp(a, b, c) (min(max(a, c), b))

struct Main {
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
    EmscriptenWebGLContextAttributes attrs;
    Vector2i size;
} Main;

struct DeltaTime {
    long lastTime,
         currentTime;
    double delta;
} DeltaTime;


void gameLoop(){
    DeltaTime.currentTime = emscripten_get_now();
    DeltaTime.delta = (float) (DeltaTime.currentTime - DeltaTime.lastTime) / 1000.0;
    DeltaTime.lastTime = DeltaTime.currentTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor((float)(sin((double) DeltaTime.currentTime / 1000.0))*0.5f+0.5f, (float)(cos((double) DeltaTime.currentTime / 1000.0))*0.5f+0.5f, 1.0f, 1.0f);
}

EM_BOOL keyCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
    return false;
}

EM_BOOL mousemoved(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    printf("(%i, %i)\n", mouseEvent->screenX, mouseEvent->screenY);

    

    return false;
}

int main()
{
    if(!glfwInit())
    {
        printf("Unable to initialize GLFW!!\n");
        return 1;
    }
    printf("Initialized GLFW Successfully!\n");
    
    emscripten_set_window_title("Critter's Game");

    emscripten_webgl_init_context_attributes(&Main.attrs);

    Main.attrs.majorVersion = 2;
    Main.attrs.minorVersion = 0;
    Main.attrs.powerPreference = EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
    Main.attrs.antialias = EM_FALSE;

    Main.context = emscripten_webgl_create_context("#canvas", &Main.attrs);
    emscripten_webgl_make_context_current(Main.context);
    emscripten_set_canvas_element_size("#canvas", 640, 480);

    Main.size.x = 640;
    Main.size.y = 480;

    emscripten_set_keydown_callback("#canvas", NULL, true, keyCallback);
    emscripten_set_keyup_callback("#canvas", NULL, true, keyCallback);
    emscripten_set_mousemove_callback("#canvas", NULL, true, mousemoved);

    emscripten_set_main_loop(&gameLoop, -1, true);
}
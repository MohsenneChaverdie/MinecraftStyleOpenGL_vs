#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GLFW_APP_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GLFW_APP_H

#include <cstdlib>
#include <cstdio>
#include "glfw_window.h"

namespace Helper
{
    // a simpler header file that wraps some stuff about creating a window in OpenGL

    struct App
    {
        Window mWindow;

        Window &window()
        { return mWindow; }

        explicit App(int w = 1920, int h = 1080)
        {
            if (!glfwInit())
            {
                exit(EXIT_FAILURE);
            }

            printf("glfw initialized \n");

            mWindow.create(this, w, h);

            printf("glfw window created \n");

            glewExperimental = true;

            GLenum glewError = glewInit();

            if (glewError != GLEW_OK)
            {
                printf("glew init error\n%s\n", glewGetErrorString(glewError));
            }

            if (GLEW_APPLE_vertex_array_object)
            {
                printf("genVertexArrayAPPLE supported\n");
            }
            else if (GLEW_ARB_vertex_array_object)
            {
                printf("genVertexArrays supported\n");
            }

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glLineWidth(3);
        }

        void start()
        {
            printf("starting app\n");

            while (!mWindow.shouldClose())
            {
                mWindow.setViewport();

                glClearColor(.2, .2, .2, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                glClear(GL_DEPTH_BUFFER_BIT);

                // the method that we will override it in our main class
                onDraw();

                mWindow.swapBuffers();
                glfwPollEvents();
            }
        }

        ~App()
        {
            glfwTerminate();
        }

        // the method that we will override it in our main class
        virtual void onDraw()
        {}

        // to get mouse position in main class
        virtual void onMouseMove(int x, int y)
        {}
    };
}

#endif //PLAYINGWITHOPENGL_ESS_REVIEW_GLFW_APP_H

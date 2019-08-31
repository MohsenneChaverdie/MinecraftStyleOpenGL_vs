#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GLFW_WINDOW_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GLFW_WINDOW_H

#include "gl_lib.h"
#include <iostream>

namespace Helper
{
    struct TemplateWrapper
    {
        static void *app;

        // so we can register this method to glfwSetCursorPosCallback method
        // .. we need a template
        template<class t>
        static void OnMouseMove(GLFWwindow *window, double x, double y)
        {
            ((t *) (app))->onMouseMove(x, y);
        }
    };

    void *TemplateWrapper::app;

    // we will instantiate it in glfw_app.h header file
    struct Window
    {
        GLFWwindow *window{};

        TemplateWrapper templateWrapper;

        int mWidth{}, mHeight{};

        int width()
        {
            return mWidth;
        }

        int height()
        {
            return mHeight;
        }

        float ratio()
        {
            return (float) mWidth / (float) mHeight;
        }

        Window()
        = default;

        //Create a Window Context
        template<class t>
        void create(t *app, int w, int h, const char *name = "demo")
        {
            templateWrapper.app = app;

            mWidth = w;
            mHeight = h;

            window = glfwCreateWindow(w, h, name, NULL, NULL);

            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

            //register callbacks for keyboard and mouseStruct
            glfwSetCursorPosCallback(window, TemplateWrapper::OnMouseMove<t>);

            glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        //Get the Current framebuffer Size in pixels and Set the Viewport to it
        void setViewport()
        {
            glfwGetFramebufferSize(window, &mWidth, &mHeight);

            glViewport(0, 0, mWidth, mHeight);
        }

        //Check whether window should close
        bool shouldClose()
        {
            return glfwWindowShouldClose(window);
        }

        void shouldBeClosed(bool value) const
        {
            glfwSetWindowShouldClose(window, value);
        }

        //Swap front and back buffers
        void swapBuffers()
        {
            glfwSwapBuffers(window);
        }

        //Destroy the window
        void destroy()
        {
            glfwDestroyWindow(window);
        }

        ~Window()
        {
            destroy();
        }
    };
}

#endif

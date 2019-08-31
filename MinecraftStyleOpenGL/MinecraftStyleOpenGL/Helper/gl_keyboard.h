
#ifndef CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_KEYBOARD_H
#define CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_KEYBOARD_H

#include <iostream>
#include "gl_lib.h"

namespace Helper
{
    class Keyboard
    {
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        // initial position of the eye
        glm::vec3 cameraPos = glm::vec3(200.0f, 700.0f, 500.0f);

    public:

        [[nodiscard]] const glm::vec3 &getCameraPos() const
        {
            return cameraPos;
        }

    private:

        float run_speed;

    public:

        Keyboard()
        {
            run_speed = 1;
        }

        // it should be called in onDraw, every frame
        void ListenToKeys(glm::vec3 cameraFront, const Helper::Window &mWindow)
        {
            float cameraSpeed = 2.5f * run_speed;

            if (glfwGetKey(mWindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                mWindow.shouldBeClosed(true);
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                run_speed = 10;
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            {
                run_speed = 1;
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_W) == GLFW_PRESS)
            {
                cameraPos += cameraSpeed * cameraFront;
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_S) == GLFW_PRESS)
            {
                cameraPos -= cameraSpeed * cameraFront;
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_A) == GLFW_PRESS)
            {
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }

            if (glfwGetKey(mWindow.window, GLFW_KEY_D) == GLFW_PRESS)
            {
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
        };
    };
}

#endif //CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_KEYBOARD_H
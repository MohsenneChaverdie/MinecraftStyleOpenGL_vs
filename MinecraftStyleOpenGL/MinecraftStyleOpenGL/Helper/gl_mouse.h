
#ifndef CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_MOUSE_H
#define CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_MOUSE_H

#include <iostream>
#include "gl_lib.h"

namespace Helper
{
    // a simple wrapper for mouse camera eye rotation
    class Mouse
    {
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

        bool firstMouse = true;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float lastX;
        float lastY;
    public:

        [[nodiscard]] const glm::vec3 &getCameraFront() const
        {
            return cameraFront;
        }

    public:

        // to be called in registered mouseStruct class
        Mouse(float width, float height)
        {
            lastX = width / 2.0f;
            lastY = height / 2.0f;
        }

        // it will be called in mouse callback subscribed method
        void inMouseCallBack(int xPos, int yPos)
        {
            if (firstMouse)
            {
                lastX = (float) xPos;
                lastY = (float) yPos;
                firstMouse = false;
            }

            float xOffset = (float) xPos - lastX;
            float yOffset = lastY - (float) yPos;

            lastX = (float) xPos;
            lastY = (float) yPos;

            float sensitivity = 0.1f;
            xOffset *= sensitivity;
            yOffset *= sensitivity;

            yaw += xOffset;
            pitch += yOffset;

            if (pitch > 89.0f)
            {
                pitch = 89.0f;
            }

            if (pitch < -89.0f)
            {
                pitch = -89.0f;
            }

            glm::vec3 front;

            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(front);
        }
    };
}

#endif //CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_MOUSE_H
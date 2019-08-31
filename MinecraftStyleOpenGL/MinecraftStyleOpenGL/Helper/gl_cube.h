
#ifndef CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_CUBE_H
#define CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_CUBE_H

#include <iostream>
#include "gl_lib.h"
#include "gl_macros.h"
#include "glfw_app.h"
#include "gl_shader.h"
#include "gl_bitmap.h"
#include "gl_texture.h"
#include "gl_mouse.h"
#include "gl_keyboard.h"

namespace Helper
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color;
        glm::vec2 textureCoordinate;
    };

    Vertex cube[] = {
            {glm::vec3(-1, -1, 1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.33f)},
            {glm::vec3(1, -1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.33f)},
            {glm::vec3(1, 1, 1),    glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.66f)},
            {glm::vec3(-1, 1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.66f)},

            {glm::vec3(1, -1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.75f, 0.33f)},
            {glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(1.0f, 0.33f)},
            {glm::vec3(-1, 1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(1.0f, 0.66f)},
            {glm::vec3(1, 1, -1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.75f, 0.66f)},

            {glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.0f, 0.33f)},
            {glm::vec3(-1, -1, 1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.33f)},
            {glm::vec3(-1, 1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.66f)},
            {glm::vec3(-1, 1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.0f, 0.66f)},

            {glm::vec3(1, -1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.33f)},
            {glm::vec3(1, -1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.75f, 0.33f)},
            {glm::vec3(1, 1, -1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.75f, 0.66f)},
            {glm::vec3(1, 1, 1),    glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.66f)},

            {glm::vec3(-1, 1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.66f)},
            {glm::vec3(1, 1, 1),    glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.66f)},
            {glm::vec3(1, 1, -1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 1.0f)},
            {glm::vec3(-1, 1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 1.0f)},

            {glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.0f)},
            {glm::vec3(1, -1, -1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.0f)},
            {glm::vec3(1, -1, 1),   glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.5f, 0.33f)},
            {glm::vec3(-1, -1, 1),  glm::vec3(0, 0, 1), glm::vec4(.5, .5, .5, 1), glm::vec2(0.25f, 0.33f)},
    };

    GLubyte indices[24] = {
            0, 1, 2, 3, //front
            4, 5, 6, 7, //back
            8, 9, 10, 11, //left
            12, 13, 14, 15, //right
            16, 17, 18, 19, //top
            20, 21, 22, 23  //bottom
    };

    class Cube
    {
        // id of vertex Attribute
        GLuint positionID{}, normalID{}, colorID{}, textureCoordinateID{};

        // a buffer ID
        GLuint bufferID{}, elementID{};

        // an array ID
        GLuint arrayID{};

        Helper::Texture *texture{};

        GLuint modelID{}, normalMatrixID{};

    public:

        explicit Cube(GLuint shaderId, const char *FilePath)
        {
            // get attribute locations
            positionID = glGetAttribLocation(shaderId, "position");
            colorID = glGetAttribLocation(shaderId, "color");
            normalID = glGetAttribLocation(shaderId, "normal");
            textureCoordinateID = glGetAttribLocation(shaderId, "textureCoordinate");

            modelID = glGetUniformLocation(shaderId, "model");
            normalMatrixID = glGetUniformLocation(shaderId, "normalMatrix");

            // create the vertex array object
            GENVERTEXARRAYS(1, &arrayID);
            BINDVERTEXARRAY(arrayID);

            // create the vertex buffer object ..

            // generate one buffer
            glGenBuffers(1, &bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
            glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(Vertex), cube, GL_STATIC_DRAW);

            // create the element array buffer object
            glGenBuffers(1, &elementID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLubyte), indices, GL_STATIC_DRAW);

            // enable vertex attributes
            glEnableVertexAttribArray(positionID);
            glEnableVertexAttribArray(colorID);
            glEnableVertexAttribArray(normalID);
            glEnableVertexAttribArray(textureCoordinateID);

            // telling the OpenGL how to handle the buffer of data that is already on the GPU
            glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
            glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(glm::vec3) * 2));
            glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(glm::vec3));
            glVertexAttribPointer(textureCoordinateID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (void *) (sizeof(glm::vec3) * 2 + sizeof(glm::vec4)));

            // unbind everything
            BINDVERTEXARRAY(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            Helper::Bitmap img(FilePath);

            texture = new Helper::Texture(img.width, img.height, true, img.pixels.data());

            texture->update(img.pixels.data());
        }

        // this method should be called inside onDraw main loop
        void InsideLoop(glm::mat4 viewParam,
                        float scaleParam,
                        glm::vec3 translateParam,
                        float rotationAngle,
                        glm::vec3 rotationAxis)
        {
            texture->bind();
            BINDVERTEXARRAY(arrayID);

            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleParam));
            glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), rotationAngle * (PI / 180), rotationAxis);
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(translateParam));
            glm::mat4 model = translate * rotate * scale;

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewParam * model)));

            glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

            glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, (void *) nullptr);

            BINDVERTEXARRAY(0);
            texture->unbind();
        }
    };
}

#endif //CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_CUBE_H
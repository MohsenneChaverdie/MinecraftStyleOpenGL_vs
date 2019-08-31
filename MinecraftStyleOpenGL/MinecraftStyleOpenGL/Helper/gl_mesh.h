#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GL_MESH_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GL_MESH_H

#include <vector>

#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "gl_lib.h"
#include "gl_macros.h"

// a wrapper for cube mesh details, but I did not use it, since I decided to wrap the
// .. whole cube cal into one header file by itself

namespace Helper {
    struct Vertex {
        glm::vec3 position; // an xyz coordinate of the vertex
        glm::vec3 normal; // a normal at the vertex
        glm::vec4 color; // a color at the vertex
        glm::vec2 textureCoordinate; // a texture coordinate of the vertex

        // offset into memory for normal; it comes after position
        static size_t offsetNormal()
        {
            return sizeof(glm::vec3);
        }

        // offset into memory for color; it comes after position and normal
        static size_t offsetColor()
        {
            return sizeof(glm::vec3) * 2;
        }

        // offset into memory for texture UV; it comes after position, normal and color
        static size_t offsetTextureCoordinate()
        {
            return sizeof(glm::vec3) * 2 + sizeof(glm::vec4);
        }
    }; // end of vertex struct

    struct Mesh {
        // position in world space
        glm::vec3 mPos;

        // orientation in world space
        glm::quat mRot;

        // scale
        float mScale;

        std::vector<Vertex> vertices;

        std::vector<GLubyte> indices;

        // id of vertex attribute
        GLuint positionID{}, normalID{}, colorID{}, textureCoordinateID{};

        // a buffer ID and elementID
        GLuint bufferID{}, elementID{};

        // an array object ID
        GLuint arrayID{};

        Mesh() : mScale(1), mRot(1, 0, 0, 0), mPos(0, 0, 0) {}

        void getAttributes(GLuint shaderID)
        {
            // get attribute locations from Shader
            // (if these attributes do not exist in shader, ID = -1)
            positionID = glGetAttribLocation(shaderID, "position");
            colorID = glGetAttribLocation(shaderID, "color");
            normalID = glGetAttribLocation(shaderID, "normal");
            textureCoordinateID = glGetAttribLocation(shaderID, "textureCoordinate");
        }

        void buffer()
        {
            // create the vertex array object
            GENVERTEXARRAYS(1, &arrayID);
            BINDVERTEXARRAY(arrayID);

            // create the vertex buffer object
            // generate one buffer
            glGenBuffers(1, &bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
            // preparing for frequent updates
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

            // create the element array buffer object
            glGenBuffers(1, &elementID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
            // update frequently, if ever
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &(indices[0]), GL_STATIC_DRAW);

            // enable vertex attributes
            glEnableVertexAttribArray(positionID);
            glEnableVertexAttribArray(colorID);
            glEnableVertexAttribArray(normalID);
            glEnableVertexAttribArray(textureCoordinateID);

            // tell OpenGL how to handle the buffer of Data that is already on the GPU
            glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
            glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) Vertex::offsetColor());
            glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) Vertex::offsetNormal());
            glVertexAttribPointer(textureCoordinateID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (void *) Vertex::offsetTextureCoordinate());

            // unbind everything (note: unbind the vertex array object first)
            BINDVERTEXARRAY(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        } // end of buffer

        void subBuffer()
        {
            bind();
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            unbind();
        }

        void bind()
        {
            BINDVERTEXARRAY(arrayID);
        }

        void unbind()
        {
            BINDVERTEXARRAY(0);
        }

        glm::mat4 model()
        {
            glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(mScale));
            glm::mat4 rotate = glm::toMat4(mRot);
            glm::mat4 translate = glm::translate(glm::mat4(), mPos);

            return translate * rotate * scale;
        }

        void drawArrays(GLuint mode)
        {
            glDrawArrays(mode, 0, vertices.size());
        }

        void drawElements(GLuint mode)
        {
            glDrawElements(mode, indices.size(), GL_UNSIGNED_BYTE, (void *) nullptr);
        }
    }; // end of struct Mesh
} // end of namespace

#endif //PLAYINGWITHOPENGL_ESS_REVIEW_GL_MESH_H

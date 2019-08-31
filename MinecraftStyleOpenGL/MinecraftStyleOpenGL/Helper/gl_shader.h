#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GL_SHADER_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GL_SHADER_H

#include <iostream>
#include "gl_lib.h"

// it wraps all shader lines into one header file
// I use only one shader for all cubes.

namespace Helper
{
    const char *vert = GLSL(120,
                            attribute
                                    vec4 position;
                                    attribute
                                    vec3 normal;
                                    attribute
                                    vec4 color;
                                    attribute
                                    vec2 textureCoordinate;
                                    uniform
                                    mat4 projection;
                                    uniform
                                    mat4 view;
                                    uniform
                                    mat4 model;
                                    uniform
                                    mat3 normalMatrix;
                                    varying
                                    vec2 texCoord;
                                    varying float diffuse; // we use it to adjust texture color

                                    float doColor()
                                    {
                                        vec3 norm = normalize(normalMatrix * normalize(normal));
                                        vec3 light = normalize(vec3(1.0, 1.0, 1.0)); // light source
                                        diffuse = max(dot(norm, light), 1.0); // light value, 0 to 1.

                                        return diffuse;
                                    }

                                    void main(void)
                                    {
                                        diffuse = doColor();
                                        texCoord = textureCoordinate;
                                        gl_Position = projection * view * model * position;
                                    }
                       );

    const char *frag = GLSL(120,
                            uniform
                                    sampler2D sampler;
                                    varying
                                    vec2 texCoord;
                                    varying float diffuse;
                                    void main(void)
                                    {
                                        // alpha will be ignored from the bitmap
                                        gl_FragColor = vec4(texture2D(sampler, texCoord).rgb * diffuse, 1.0);
                                    }
                       );

    class Shader
    {
        GLuint sID;

        // function to check for shader compiler errors
        void compilerCheck(GLuint ID)
        {
            GLint comp;
            glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);

            if (comp == GL_FALSE)
            {
                std::cout << "Shader compilation Failed" << std::endl;
                GLchar messages[256];
                glGetShaderInfoLog(ID, sizeof(messages), nullptr, &messages[0]);
                std::cout << messages;
            }
        }

        // function to check for shader link errors
        void linkCheck(GLuint ID)
        {
            GLint linkStatus, validateStatus;
            glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);

            if (linkStatus == GL_FALSE)
            {
                std::cout << "Shader Linking Failed" << std::endl;
                GLchar messages[256];
                glGetProgramInfoLog(ID, sizeof(messages), nullptr, &messages[0]);
                std::cout << messages;
            }

            glValidateProgram(ID);
            glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

            std::cout << "Link: " << linkStatus << " Validate: " << validateStatus << std::endl;

            if (linkStatus == GL_FALSE)
            {
                std::cout << "Shader Validation Failed" << std::endl;
                GLchar messages[256];
                glGetProgramInfoLog(ID, sizeof(messages), nullptr, &messages[0]);
                std::cout << messages;
            }
        }

    public:

        // its results should not be discarded.
        [[nodiscard]] GLuint id() const
        { return sID; }

        Shader()
        {
            // create the shader

            // 1. create shader program
            sID = glCreateProgram();
            GLuint vID = glCreateShader(GL_VERTEX_SHADER);
            GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

            // 2. loader shader source code
            glShaderSource(vID, 1, &vert, nullptr);
            glShaderSource(fID, 1, &frag, nullptr);

            // 3. compile
            glCompileShader(vID);
            glCompileShader(fID);

            // 4. check for compile errors
            compilerCheck(vID);
            compilerCheck(fID);

            // 5. attach shaders to program
            glAttachShader(sID, vID);
            glAttachShader(sID, fID);

            // 6. link program
            glLinkProgram(sID);

            // 7. check for linking errors
            linkCheck(sID);

            // 8. Use Program
            glUseProgram(sID);
        }

        void bind()
        {
            glUseProgram(sID);
        }

        void unbind()
        {
            glUseProgram(0);
        }
    };
}

#endif //PLAYINGWITHOPENGL_ESS_REVIEW_GL_SHADER_H

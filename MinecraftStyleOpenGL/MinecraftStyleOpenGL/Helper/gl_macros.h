#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GL_MACROS_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GL_MACROS_H

#include <cmath>

namespace Helper {

#ifndef PI
#define PI (float)3.14159265359
#endif

#ifndef STRINGIFY
#define STRINGIFY(A) #A
#endif

    // it helps us to define shaders in one line
#ifndef GLSL
#define GLSL(version, shaderCode) "#version " #version "\n" #shaderCode
#endif

#ifndef RAND
#define RAND (1.0 * rand() / (RAND_MAX))
#endif

#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n, id) if (GLEW_ARB_vertex_array_object) glGenVertexArrays(n,id)
#endif

#ifndef BINDVERTEXARRAY
#define BINDVERTEXARRAY(id) if (GLEW_ARB_vertex_array_object) glBindVertexArray(id)
#endif
}

#endif //PLAYINGWITHOPENGL_ESS_REVIEW_GL_MACROS_H

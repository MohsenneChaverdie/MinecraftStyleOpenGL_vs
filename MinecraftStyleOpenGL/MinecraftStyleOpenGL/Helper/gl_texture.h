#ifndef PLAYINGWITHOPENGL_ESS_REVIEW_GL_TEXTURE_H
#define PLAYINGWITHOPENGL_ESS_REVIEW_GL_TEXTURE_H

#include "gl_lib.h"

namespace Helper {

    // all texture stuff in one header file

    struct Texture {

        GLuint tID{};

        int width, height;

        bool withLoadedImage;

        const void *pixels;

        [[nodiscard]] GLuint id() const
        {
            return tID;
        }

        Texture(int w, int h, bool withLoadedImage, const void *pixelData) : width(w),
                                                                             height(h),
                                                                             withLoadedImage(withLoadedImage),
                                                                             pixels(pixelData)
        {
            init();
        };

        void init()
        {
            // generate texture and bind it
            glGenTextures(1, &tID);

            glBindTexture(GL_TEXTURE_2D, tID);

            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         withLoadedImage ? GL_RGB : GL_RGBA,
                         width,
                         height,
                         0,
                         withLoadedImage ? GL_RGB : GL_RGBA,
                         withLoadedImage ? GL_UNSIGNED_BYTE : GL_FLOAT,
                         nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, withLoadedImage ? GL_LINEAR : GL_NEAREST);

            // unbind texture
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void bind()
        {
            glBindTexture(GL_TEXTURE_2D, tID);
        }

        void unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void update(void *data)
        {
            bind();

            // load data onto GPU
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                            width,
                            height,
                            withLoadedImage ? GL_BGR : GL_RGBA,
                            withLoadedImage ? GL_UNSIGNED_BYTE : GL_FLOAT, data);

            glGenerateMipmap(GL_TEXTURE_2D);
            unbind();
        }
    };
}

#endif //PLAYINGWITHOPENGL_ESS_REVIEW_GL_TEXTURE_H


#ifndef CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_RANDOM_H
#define CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_RANDOM_H

#include <random>

namespace Helper
{
    // to create proper random numbers in a range
    class Random
    {
        float generatedNumber;
    public:
        [[nodiscard]] float getGeneratedNumber() const
        {
            return generatedNumber;
        }

    public:
        Random(int min, int max)
        {
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_int_distribution<> distr(min, max);
            generatedNumber = distr(eng);
        }
    };
}

#endif //CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_RANDOM_H
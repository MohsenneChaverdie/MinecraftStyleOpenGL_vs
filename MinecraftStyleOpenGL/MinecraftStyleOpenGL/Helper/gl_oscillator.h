
#ifndef CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_OSCILLATOR_H
#define CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_OSCILLATOR_H

#include <iostream>

namespace Helper
{
    // it helps us to ping pong a value between two values
    class Oscillator
    {
        float min_;
        float max_;

        [[nodiscard]] float mod(float num, float div) const
        {
            const auto ratio = num / div;

            return div * (ratio - std::floor(ratio));
        }

        [[nodiscard]] float range() const
        {
            return max_ - min_;
        }

        [[nodiscard]] float cycle_length() const
        {
            return 2 * range();
        }

    public:
        Oscillator(float a, float b)
        {
            min_ = a < b ? a : b;
            max_ = a > b ? a : b;
        }

        [[nodiscard]] float normalize(float val) const
        {
            auto state = mod(val - min_, cycle_length());

            if (state > range())
            {
                state = cycle_length() - state;
            }

            return state + min_;
        }
    };
}

#endif //CMAKEPROJECT_OPENGL_MINECRAFTSTYLE_GL_OSCILLATOR_H
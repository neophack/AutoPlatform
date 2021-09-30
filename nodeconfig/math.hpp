#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <string>
namespace math {
    inline float Add(float a, float b) {
        return a + b;
    }
    inline void Sub(float a, float b, float & c) {
        c = a - b;
    }
    inline void Sub1(const float & a, const float & b, float & c) {
        c = a - b;
    }
    inline void Mul(float a, float b, float * c) {
        *c = a * b;
    }

    class Div {
    public:
        float operator()(float a, float b) {
            return a / b;
        }
    };
}
#endif //MATH_HPP

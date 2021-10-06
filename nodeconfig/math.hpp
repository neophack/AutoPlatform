#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <string>
namespace math {
    inline double Add(double inputVal1, double inputVal2) {
        return inputVal1 + inputVal2;
    }
    inline void Sub(double inputVal1, double inputVal2, double & result) {
        result = inputVal1 - inputVal2;
    }
    inline void Sub1(const double & inputVal1, const double & inputVal2, double & result) {
        result = inputVal1 - inputVal2;
    }
    inline void Mul(double inputVal1, double inputVal2, double * result) {
        *result = inputVal1 * inputVal2;
    }
    ///绝对值
    inline float Abs(double inputVal){
        return inputVal>=0?inputVal:-inputVal;
    }
    ///三角函数
    inline double Sin(double inputVal){
        return sin(inputVal);
    }
    inline double Cos(double inputVal){
        return cos(inputVal);
    }
    inline double Tan(double inputVal){
        return tan(inputVal);
    }
    ///反三角函数
    inline double Asin(double inputVal){
        return asin(inputVal);
    }
    inline double Acos(double inputVal){
        return acos(inputVal);
    }
    inline double Atan(double inputVal){
        return atan(inputVal);
    }
    ///取反
    inline double UnaryMinus(double inputVal){
        return -inputVal;
    }
    ///弧度转角度
    inline void Deg2Rad(double deg,double & rad){
        rad = deg*180/M_PI;
    }
    ///取符号位
    inline int Sign(double inputVal){
        if(inputVal>0) return 1;
        else if(inputVal==0) return 0;
        else return -1;
    }

    class Div {
    public:
        double operator()(double inputVal1, double inputVal2) {
            return inputVal1 / inputVal2;
        }
    };
}
#endif //MATH_HPP

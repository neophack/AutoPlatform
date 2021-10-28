#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <string>
#include <chrono>
#include "adas/node.hpp"

namespace math {
using namespace std::chrono_literals;
using namespace adas::node;

///加法运算
class add{
public:
    in<float> in1{0.0f,[this](){
            compute();
                   }};
    in<float> in2{0.0f,[this](){
            compute();
                   }};
    out<float> out1;
private:
    void compute(){
        out1(in1.get()+in2.get());
    }
};

///减法计算
class sub{
public:
    in<float> in1{0.0f,[this](){compute();}};
    in<float> in2{0.0f,[this](){compute();}};
    out<float> out1;
private:
    void compute(){
        out1(in1.get()-in2.get());
    }
};

///乘法计算
class mul{
public:
    in<float> in1{0.0f,[this](){compute();}};
    in<float> in2{0.0f,[this](){compute();}};
    out<float> out1;
private:
    void compute(){
        out1(in1.get()*in2.get());
    }
};

///除法计算
class div{
public:
    in<float> in1{0.0f,[this](){compute();}};
    in<float> in2{0.0f,[this](){compute();}};
    out<float> out1;
private:
    void compute(){
        out1(in1.get()/in2.get());
    }
};

///绝对值
class abs{
public:
    in<float> in1{0.0f,[this](){out1(in1.get()>=0?in1.get():-in1.get());}};
    out<float> out1;
};

///三角函数
class aicc_sin{
public:
    in<float> in1{
        0.0f,[this](){
            out1(sin(in1.get()));
        }
    };
    out<float> out1;
};

class aicc_cos{
public:
    in<float> in1{0.0f,[this](){out1(cos(in1.get()));}};
    out<float> out1;
};

class aicc_tan{
public:
    in<float> in1{0.0f,[this](){out1(tan(in1.get()));}};
    out<float> out1;
};

///反三角函数
class aicc_asin{
public:
    in<float> in1{0.0f,[this](){out1(asin(in1.get()));}};
    out<float> out1;
};

class aicc_acos{
public:
    in<float> in1{0.0f,[this](){out1(acos(in1.get()));}};
    out<float> out1;
};

class aicc_atan{
public:
    in<float> in1{0.0f,[this](){out1(atan(in1.get()));}};
    out<float> out1;
};

///取反
class unary_minus{
public:
    in<float> in1{0.0f,[this](){out1(-in1.get());}};
    out<float> out1;
};

///弧度转角度
class deg2rad{
public:
    in<float> in1{0.0f,[this](){out1(in1.get()*180/M_PI);}};
    out<float> out1;
};

///取符号位
class sign{
public:
    in<float> in1{0.0f,[this](){
            if(in1.get()>0) out1(1);
            else if(in1.get()==0) out1(0);
            else return out1(-1);
                  }};
    out<float> out1;
};

///乘方
class aicc_pow{
public:
    in<float> base_number{0.0f,[this](){
            compute();
                  }};
    in<int> exponent{1,[this](){
            compute();
                     }};
    out<float> out1;

private:
    void compute(){
        out1(pow(base_number.get(),exponent.get()));
    }
};

/// 开方
class rooting{
public:
    in<float> base_number{0.0f,[this](){
            compute();
                          }};
    in<int> exponent{1,[this](){
            compute();
                      }};
    out<float> out1;
private:
    void compute(){
        out1(pow(base_number.get(),-exponent.get()));
    }
};


//class test_node {
//public:
//    test_node() {
//        timer_.start();
//        timer2_.start();
//    }
//public:
//    out<double> out1;
//    out<double> out2;
//private:
//    timer timer_{timer::mode::cycle, 1s,[this](){timer_handler();}};
//    timer timer2_{timer::mode::single,500ms,[this](){timerout_handler();}};
//    int n_ = 0;
//    float m_ = 0.0f;

//    void timer_handler(){
//        sync_out so;
//        out1(n_++);
//        m_ += 0.1f;
//        out2(m_);
//    }

//    void timerout_handler() {
//        std::cout << "timeout" << std::endl;
//    }
//};

//class test2_node {
//private:
//    using count_type = std::chrono::steady_clock::duration::rep;
//    count_type prev_count = 0;
//    void in1_update(){
//        count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
//        std::cout << "test2_node::in1 " << in1.get() << ", " << in1.is_updated() << ", " << in2.is_updated() << std::endl;
//        prev_count = now;
//    }
//    void in2_update() {
//        count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
//        std::cout << "test2_node::in2 " << in2.get() << ", " << in1.is_updated() << ", " << in2.is_updated() << std::endl;
//        prev_count = now;
//    }
//public:
//    in<double> in1{0,[this](){in1_update();}};
//    in<double> in2{0.0f,[this](){in2_update();}};
//};
}
#endif //MATH_HPP

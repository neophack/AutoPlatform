#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <string>
#include <chrono>
#include <adas/node.hpp>

namespace math {
using namespace std::chrono_literals;
using namespace adas::node;

///加法运算
class add{
public:
    in<double> in1{0.0f,[this](){
            out1(in1.get() + in2.get());
                   }};
    in<double> in2{0.0f,[this](){
            out1(in1.get() + in2.get());
                   }};
    out<double> out1;

};

class test_node {
public:
    test_node() {
        timer_.start();
        timer2_.start();
    }
public:
    out<double> out1;
    out<double> out2;
private:
    timer timer_{timer::mode::cycle, 1s,[this](){timer_handler();}};
    timer timer2_{timer::mode::single,500ms,[this](){timerout_handler();}};
    int n_ = 0;
    float m_ = 0.0f;

    void timer_handler(){
        sync_out so;
        out1(n_++);
        m_ += 0.1f;
        out2(m_);
    }

    void timerout_handler() {
        std::cout << "timeout" << std::endl;
    }
};

class test2_node {
private:
    using count_type = std::chrono::steady_clock::duration::rep;
    count_type prev_count = 0;
    void in1_update(){
        count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
        std::cout << "test2_node::in1 " << in1.get() << ", " << in1.is_updated() << ", " << in2.is_updated() << std::endl;
        prev_count = now;
    }
    void in2_update() {
        count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
        std::cout << "test2_node::in2 " << in2.get() << ", " << in1.is_updated() << ", " << in2.is_updated() << std::endl;
        prev_count = now;
    }
public:
    in<double> in1{0,[this](){in1_update();}};
    in<double> in2{0.0f,[this](){in2_update();}};
};
}
#endif //MATH_HPP

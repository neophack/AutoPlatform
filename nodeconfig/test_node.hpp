#ifndef MATH_HPP
#define MATH_HPP

#include "adas/node.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "ehs3.hpp"
#include "eyeq4_object.hpp"

namespace test_package {
    using namespace std::chrono_literals;
    using namespace adas::node;

    class test_node {
    public:
        test_node() {
            timer_.start();
            timer2_.start();
        }

    public:
        out<int> out1;
        out<float> out2;

    private:
        timer timer_{timer::mode::cycle, 1s, [this]() { timer_handler(); }};
        timer timer2_{timer::mode::single, 500ms, [this]() { timeout_handler(); }};
        int n_ = 0;
        float m_ = 0.0f;

        void timer_handler() {
            sync_out so;
            out1(n_++);
            m_ += 0.1f;
            out2(m_);

        }

        void timeout_handler() {
            std::cout << "timeout" << std::endl;

        }

    };

    class test2_node {
    private:
        using count_type = std::chrono::steady_clock::duration::rep;
        count_type prev_count = 0;

        void in1_update() {
            count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
            std::cout << "test2_node::in1 " << in1.get() << ", " << in1.is_updated() << ", " << in2.is_updated()
                      << std::endl;
            prev_count = now;
        }

        void in2_update() {
            count_type now = std::chrono::steady_clock::now().time_since_epoch().count();
            std::cout << "test2_node::in2 " << in2.get() << ", " << in1.is_updated() << ", " << in2.is_updated()
                      << std::endl;
            prev_count = now;
        }

    public:
        in<int> in1{0, [this]() { in1_update(); }};
        in<float> in2{0.0f, [this]() { in2_update(); }};
    };

    class add {
    private:
        void a_update() {
            std::cout << "here a" << std::endl;
            y(a.get() + b.get());

        }

        void b_update() {
            std::cout << "here b" << std::endl;
            y(a.get() + b.get());
        }

    public:
        in<float> a{0.0f, [this]() { a_update(); }};
        in<float> b{0.0f, [this]() { b_update(); }};
        out<float> y;

    };


}
namespace can {
    using namespace std::chrono_literals;
    class input {
    private:
        adas::node::can_io &can_io_;
    public:

        explicit input(std::string channel) : can_io_(adas::node::can_io::get(channel)) {
            can_io_.receive_handler([this](const can_frame &msg) {
                can_msg(msg);
            });
        }

    public:
        adas::node::out<can_frame> can_msg;

    };

    class output {
    private:
        adas::node::can_io &can_io_;

        void can_msg_update() {
            can_io_.send(can_msg.get());
        }

    public:
        explicit output(std::string channel) : can_io_(adas::node::can_io::get(channel)) {}

        adas::node::in<can_frame> can_msg{{}, [this]() { can_msg_update(); }};
    };

}
namespace logging {
    class print_int {
    public:
        explicit print_int(std::string label) : label_(label) {}

        adas::node::in<int> number{{}, [this]() { number_update(); }};
    private:
        std::string label_;

        void number_update() {
            std::cout << label_ << ": " << number.get() << std::endl;

        }
    };

    class print_bool {
    public:
        adas::node::in<bool> b{{}, [this]() { b_update(); }};

        explicit print_bool(std::string label) : label_(label) {}

    private:
        std::string label_;

        void b_update() {
            std::cout << label_ << ": " << b.get() << std::endl;

        }
    };

    class print_void {
    public:
        adas::node::in<void> v{[this]() { v_update(); }};

        explicit print_void(std::string label) : label_(label) {}

    private:
        std::string label_;

        void v_update() {
            std::cout << label_ << ": <void>" << std::endl;

        }
    };

    class print_float {
    public:
        adas::node::in<float> number{{}, [this]() { number_update(); }};

        explicit print_float(std::string label) : label_(label) {}

    private:
        std::string label_;

        void number_update() {
            std::cout << label_ << ": " << number.get() << std::endl;

        }


    };
}
namespace constant {
    class int_value {
    private:
        int val_;
        adas::node::timer timer_{adas::node::timer::mode::single, std::chrono::seconds(0), [this]() {
            out(val_);
        }};
    public:
        adas::node::out<int> out;

        explicit int_value(int val) : val_(val) {
            timer_.start();
        }
    };

   class float_value {
    private:
        float val_;
        adas::node::timer timer_{adas::node::timer::mode::single, std::chrono::seconds(0), [this]() {
            out(val_);
        }};
    public:
        adas::node::out<float> out;

        explicit float_value(float val) : val_(val) {
            timer_.start();
        }
    };

    class float_seq {
    private:
        float val_;
        adas::node::timer timer_;
    public:
        adas::node::out<float> out;

        explicit float_seq(float val, int interval_ms) : val_(val), timer_{adas::node::timer::mode::cycle,
                                                                           std::chrono::milliseconds(interval_ms),
                                                                           [this]() {
                                                                               out(val_);
                                                                           }} {
            timer_.start();
        }
    };

    class bool_value {
    private:
        bool val_;
        adas::node::timer timer_{adas::node::timer::mode::single, std::chrono::seconds(0), [this]() {
            out(val_);
        }};
    public:
        adas::node::out<bool> out;

        explicit bool_value(bool val) : val_(val) {
            timer_.start();
        }
    };

    class void_value {
    private:
        adas::node::timer timer_{adas::node::timer::mode::single, std::chrono::seconds(0), [this]() {
            out();
        }};
    public:
        adas::node::out<void> out;

        explicit void_value() {
            timer_.start();
        }
    };

}
namespace convert {
    class int_to_bool {
    public:
        adas::node::out<bool> out;
        adas::node::in<int> in{0, [this]() {
            out(in.get() != 0);

        }};
    };

    class bool_to_int {
    public:
        adas::node::out<int> out;
        adas::node::in<bool> in{false, [this]() {
            out(in.get());

        }};
    };

    class int_to_float {
    public:
        adas::node::out<float> out;
        adas::node::in<int> in{0, [this]() {
            out(static_cast<float>(in.get()));

        }};
    };

    class float_to_int {
    public:
        adas::node::out<int> out;
        adas::node::in<float> in{0.0f, [this]() {
            out(static_cast<int>(std::round(in.get())));

        }};
    };

    class bool_to_void {
    public:
        adas::node::in<bool> in{false, [this]() {
            if (in.get())
                t();
            else
                f();
        }};
        adas::node::out<void> t;
        adas::node::out<void> f;


    };

    class void_to_bool {
    public:
        adas::node::in<void> t{[this]() {
            out(true);
        }}, f{[this]() {
            out(false);
        }};
        adas::node::out<bool> out;

    };

}
namespace op {
    //int
    class int_add {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(a.get() + b.get());
        }

    };

    class int_sub {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(a.get() - b.get());
        }

    };

    class int_mul {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(a.get() * b.get());
        }

    };

    class int_div {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(a.get() / b.get());
        }

    };

    class int_neg {
    public:
        adas::node::in<int> in{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(-in.get());
        }

    };

    class int_abs {
    public:
        adas::node::in<int> in{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(std::abs(in.get()));
        }

    };

    class int_sign {
    public:
        adas::node::in<int> in{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(in.get() >= 0 ? 1 : -1);
        }

    };

    class int_lt {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() < b.get());
        }

    };

    class int_le {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() <= b.get());
        }

    };

    class int_gt {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() > b.get());
        }
    };

    class int_ge {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() >= b.get());
        }
    };

    class int_eq {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() == b.get());
        }
    };

    class int_ne {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() != b.get());
        }
    };
    //float

    class float_add {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(a.get() + b.get());
        }

    };

    class float_sub {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(a.get() - b.get());
        }

    };

    class float_mul {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(a.get() * b.get());
        }

    };

    class float_div {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(a.get() / b.get());
        }

    };

    class float_neg {
    public:
        adas::node::in<float> in{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(-in.get());
        }

    };

    class float_abs {
    public:
        adas::node::in<float> in{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(std::abs(in.get()));
        }

    };

    class float_sign {
    public:
        adas::node::in<float> in{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(in.get() >= 0.0f ? 1.0f : -1.0f);
        }

    };

    class float_lt {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() < b.get());
        }

    };

    class float_le {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() <= b.get());
        }

    };

    class float_gt {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() > b.get());
        }
    };

    class float_ge {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() >= b.get());
        }
    };

    class float_eq {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() == b.get());
        }
    };

    class float_ne {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() != b.get());
        }
    };

    class bool_and {
    public:
        adas::node::in<bool> a{false, [this]() { update(); }}, b{false, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() && b.get());
        }
    };

    class bool_or {
    public:
        adas::node::in<bool> a{false, [this]() { update(); }}, b{false, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(a.get() || b.get());
        }
    };

    class bool_not {
    public:
        adas::node::in<bool> in{false, [this]() { update(); }};
        adas::node::out<bool> out;
    private:
        void update() {
            out(!in.get());
        }
    };
}
namespace condtion {
    class float_if {
    public:
        adas::node::in<bool> cond{false, []() {}};
        adas::node::in<float> t{0.0, [this]() {
            if (cond.get())
                out(t.get());
        }};
        adas::node::in<float> f{0.0, [this]() {
            if (!cond.get())
                out(f.get());
        }};
        adas::node::out<float> out;

    };

}
namespace alg {
    class int_min {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(std::min(a.get(), b.get()));
        }

    };

    class int_max {
    public:
        adas::node::in<int> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<int> out;
    private:
        void update() {
            out(std::min(a.get(), b.get()));
        }

    };

    class float_min {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(std::min(a.get(), b.get()));
        }

    };

    class float_max {
    public:
        adas::node::in<float> a{0, [this]() { update(); }}, b{0, [this]() { update(); }};
        adas::node::out<float> out;
    private:
        void update() {
            out(std::max(a.get(), b.get()));
        }

    };
}
namespace utility {
    class posedge {
    public:
        adas::node::in<bool> in{false, [this]() { update(); }};
        adas::node::out<void> out;
    private:
        bool first_update_{true};
        bool prev_in_;

        void update() {
            if (first_update_) {
                prev_in_ = in.get();
                first_update_ = false;
                return;
            }
            if (in.get() && !prev_in_)
                out();
            prev_in_ = in.get();
        }

    };

    class negedge {
    public:
        adas::node::in<bool> in{false, [this]() { update(); }};
        adas::node::out<void> out;
    private:
        bool first_update_{true};
        bool prev_in_;

        void update() {
            if (first_update_) {
                prev_in_ = in.get();
                first_update_ = false;
                return;
            }
            if (!in.get() && prev_in_)
                out();
            prev_in_ = in.get();
        }

    };

    class float_clamp {
    public:
        adas::node::in<float> in{0.0f, [this]() {
            out(std::clamp(in.get(), low.get(), high.get()));
        }};
        adas::node::in<float> low{0.0f, []() {}};
        adas::node::in<float> high{0.0f, []() {}};
        adas::node::out<float> out;
    };

    class int_counter {
    private:
        int n_, lo_, hi_, step_;
    public:
        int_counter(int low, int high, int step) : lo_(low), hi_(high), n_(low), step_(step) {}

        adas::node::in<void> inc{[this]() {
            n_ += step_;
            if (n_ > hi_)
                n_ = hi_;
            out(n_);

        }};
        adas::node::in<void> dec{[this]() {
            n_ -= step_;
            if (n_ < lo_)
                n_ = lo_;
            out(n_);

        }};
        adas::node::out<int> out;

    };

    class int_cycle_counter {
    private:
        int n_, lo_, hi_, init_value_;
    public:
        int_cycle_counter(int low, int high, int init_value) : lo_(low), hi_(high), n_(init_value),
                                                               init_value_(init_value) {}

        adas::node::in<void> inc{[this]() {
            n_++;
            if (n_ > hi_)
                n_ = lo_;
            out(n_);

        }};
        adas::node::in<void> dec{[this]() {
            n_--;
            if (n_ < lo_)
                n_ = hi_;
            out(n_);

        }};
        adas::node::in<void> reset{[this]() {
            n_ = init_value_;
            out(n_);
        }};
        adas::node::out<int> out;

    };

    class bool_merge {
    public:
        adas::node::in<bool> in1{false, [this]() {
            out(in1.get());
        }};
        adas::node::in<bool> in2{false, [this]() {
            out(in1.get());
        }};
        adas::node::in<bool> in3{false, [this]() {
            out(in1.get());
        }};
        adas::node::in<bool> in4{false, [this]() {
            out(in1.get());
        }};
        adas::node::in<bool> in5{false, [this]() {
            out(in1.get());
        }};
        adas::node::out<bool> out;
    private:
    };

    class void_merge {
    public:
        adas::node::in<void> in1{[this]() {
            out();
        }};
        adas::node::in<void> in2{[this]() {
            out();
        }};
        adas::node::in<void> in3{[this]() {
            out();
        }};
        adas::node::in<void> in4{[this]() {
            out();
        }};
        adas::node::in<void> in5{[this]() {
            out();
        }};
        adas::node::out<void> out;
    private:
    };

}
namespace adas::ehs3::utility {
    class acc_state {
    public:
        adas::node::in<bool> main_switch{false, [this]() { update(); }};
        adas::node::in<bool> auto_control_enabled{false, [this]() { update(); }};
        adas::node::out<int> state;
    private:
        void update() {
            if (main_switch.get() && auto_control_enabled.get())
                state(1);
            else if (main_switch.get() && !auto_control_enabled.get())
                state(2);
            else
                state(0);


        }
    };

    class curvature_to_steering_angle {
    private:
        float _wheel_base;
        float _steering_ratio;
    public:
        adas::node::in<float> curvature{0.0f, [this]() {
            float c = curvature.get();
            float r = 1.0f / std::abs(c);
            float a = std::atan2(_wheel_base, r) * _steering_ratio;
            angle(std::copysign(a * 57.2957f, c));

        }};
        adas::node::out<float> angle;

        curvature_to_steering_angle(float wheel_base, float steering_radio) : _wheel_base(wheel_base),
                                                                              _steering_ratio(steering_radio) {

        }

    };

    class cipv {
    public:
        adas::node::in<can_frame> can_msg{{}, [this]() { can_msg_update(); }};
        adas::node::out<bool> is_valid;
        adas::node::out<int> object_id;
        adas::node::out<float> long_distance;
        adas::node::out<float> long_velocity;
        adas::node::out<float> long_acceleration;

    private:
        int cipv_id_{0};
        int current_id_{0};
        float long_distance_;
        float long_velocity_;
        float long_acceleration_;

        void process_header() {
            eyeq4::object::Objects_Header header(const_cast<unsigned char *>(can_msg.get().data));
            cipv_id_ = header.OBJ_VD_CIPV_ID();
        }

        void process_objects() {
            if (0 == cipv_id_)
                return;
            int index = (can_msg.get().can_id - 0x111) % 4;
            if (0 == index) {
                eyeq4::object::ObjectDate0_A obj_a(const_cast<unsigned char *>(can_msg.get().data));
                current_id_ = obj_a.OBJ_ID();

            } else if (1 == index && current_id_ == cipv_id_) {
                eyeq4::object::ObjectDate0_B obj_b(const_cast<unsigned char *>(can_msg.get().data));
                long_velocity_ = obj_b.OBJ_Abs_Long_Velocity();

            } else if (2 == index && current_id_ == cipv_id_) {
                eyeq4::object::ObjectDate0_C obj_c(const_cast<unsigned char *>(can_msg.get().data));
                long_distance_ = obj_c.OBJ_Long_Distance();
                long_acceleration_ = obj_c.OBJ_Abs_Long_Acc();

            } else if (3 == index && current_id_ == cipv_id_) {
                eyeq4::object::ObjectDate0_D obj_d(const_cast<unsigned char *>(can_msg.get().data));

            }

        }

        void done() {
            adas::node::sync_out so;
            if (cipv_id_ != 0) {
                is_valid(true);
                object_id(cipv_id_);
                long_distance(long_distance_);
                long_velocity(long_velocity_);
                long_acceleration(long_acceleration_);

            } else {
                is_valid(false);
                object_id(0);
                long_distance(0);
                long_velocity(0);
                long_acceleration(0);

            }

        }

        void can_msg_update() {
            auto id = can_msg.get().can_id;
            if (0x110 == id)
                process_header();
            else if (id >= 0x111 && id <= 0x138)
                process_objects();
            if (0x138 == id)
                done();
        }
//    private:
//        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(30), [this]() {
//            is_valid(true);
//            object_id(10);
//            long_distance(49);
//            long_velocity(0.0 * 0.277778f);
//            long_acceleration(0);
//        }};
//    public:
//        cipv() {
//            timer_.start();
//        }
    };

}

#endif //MATH_HPP

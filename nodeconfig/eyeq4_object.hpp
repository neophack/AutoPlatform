#pragma once
#include <adas/can.h>
#include <adas/node.hpp>
#include <chrono>
#include <algorithm>
namespace eyeq4::object {
    /* None */
    /* id: 0x110 */
    class Objects_Header : public adas::can::CanData {
    public:
        Objects_Header() : adas::can::CanData(8) {}
        explicit Objects_Header(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* The Current In Path Vehicle object ID */
        uint8_t OBJ_VD_CIPV_ID() const {
            return get<uint8_t>(32, 8, LITTLE_ENDIAN);
        }
        void OBJ_VD_CIPV_ID(uint8_t value) {
            set<uint8_t>(32, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class Objects_Header {
    private:
        void can_msg_update() {
            if(0x110 != can_msg.get().can_id)
                return;
            eyeq4::object::Objects_Header can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_VD_CIPV_ID(static_cast<int>(can_data.OBJ_VD_CIPV_ID()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_VD_CIPV_ID;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Objects_Header {
    public:
        Objects_Header() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_VD_CIPV_ID{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::Objects_Header data;
            data.OBJ_VD_CIPV_ID(OBJ_VD_CIPV_ID.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x110};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x111 */
    class ObjectDate0_A : public adas::can::CanData {
    public:
        ObjectDate0_A() : adas::can::CanData(8) {}
        explicit ObjectDate0_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate0_A {
    private:
        void can_msg_update() {
            if(0x111 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate0_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate0_A {
    public:
        ObjectDate0_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate0_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate0_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate0_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate0_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate0_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate0_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate0_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x111};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x112 */
    class ObjectDate0_B : public adas::can::CanData {
    public:
        ObjectDate0_B() : adas::can::CanData(8) {}
        explicit ObjectDate0_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate0_B {
    private:
        void can_msg_update() {
            if(0x112 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate0_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate0_B {
    public:
        ObjectDate0_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate0_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate0_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x112};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x113 */
    class ObjectDate0_C : public adas::can::CanData {
    public:
        ObjectDate0_C() : adas::can::CanData(8) {}
        explicit ObjectDate0_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate0_C {
    private:
        void can_msg_update() {
            if(0x113 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate0_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate0_C {
    public:
        ObjectDate0_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate0_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x113};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x114 */
    class ObjectDate0_D : public adas::can::CanData {
    public:
        ObjectDate0_D() : adas::can::CanData(8) {}
        explicit ObjectDate0_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate0_D {
    private:
        void can_msg_update() {
            if(0x114 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate0_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate0_D {
    public:
        ObjectDate0_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate0_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x114};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x115 */
    class ObjectDate1_A : public adas::can::CanData {
    public:
        ObjectDate1_A() : adas::can::CanData(8) {}
        explicit ObjectDate1_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate1_A {
    private:
        void can_msg_update() {
            if(0x115 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate1_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate1_A {
    public:
        ObjectDate1_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate1_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate1_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate1_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate1_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate1_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate1_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate1_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x115};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x116 */
    class ObjectDate1_B : public adas::can::CanData {
    public:
        ObjectDate1_B() : adas::can::CanData(8) {}
        explicit ObjectDate1_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate1_B {
    private:
        void can_msg_update() {
            if(0x116 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate1_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate1_B {
    public:
        ObjectDate1_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate1_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate1_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x116};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x117 */
    class ObjectDate1_C : public adas::can::CanData {
    public:
        ObjectDate1_C() : adas::can::CanData(8) {}
        explicit ObjectDate1_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate1_C {
    private:
        void can_msg_update() {
            if(0x117 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate1_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate1_C {
    public:
        ObjectDate1_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate1_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x117};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x118 */
    class ObjectDate1_D : public adas::can::CanData {
    public:
        ObjectDate1_D() : adas::can::CanData(8) {}
        explicit ObjectDate1_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate1_D {
    private:
        void can_msg_update() {
            if(0x118 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate1_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate1_D {
    public:
        ObjectDate1_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate1_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x118};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x119 */
    class ObjectDate2_A : public adas::can::CanData {
    public:
        ObjectDate2_A() : adas::can::CanData(8) {}
        explicit ObjectDate2_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate2_A {
    private:
        void can_msg_update() {
            if(0x119 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate2_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate2_A {
    public:
        ObjectDate2_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate2_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate2_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate2_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate2_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate2_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate2_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate2_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x119};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11a */
    class ObjectDate2_B : public adas::can::CanData {
    public:
        ObjectDate2_B() : adas::can::CanData(8) {}
        explicit ObjectDate2_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate2_B {
    private:
        void can_msg_update() {
            if(0x11a != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate2_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate2_B {
    public:
        ObjectDate2_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate2_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate2_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11a};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11b */
    class ObjectDate2_C : public adas::can::CanData {
    public:
        ObjectDate2_C() : adas::can::CanData(8) {}
        explicit ObjectDate2_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate2_C {
    private:
        void can_msg_update() {
            if(0x11b != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate2_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate2_C {
    public:
        ObjectDate2_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate2_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11b};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11c */
    class ObjectDate2_D : public adas::can::CanData {
    public:
        ObjectDate2_D() : adas::can::CanData(8) {}
        explicit ObjectDate2_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate2_D {
    private:
        void can_msg_update() {
            if(0x11c != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate2_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate2_D {
    public:
        ObjectDate2_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate2_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11c};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11d */
    class ObjectDate3_A : public adas::can::CanData {
    public:
        ObjectDate3_A() : adas::can::CanData(8) {}
        explicit ObjectDate3_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate3_A {
    private:
        void can_msg_update() {
            if(0x11d != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate3_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate3_A {
    public:
        ObjectDate3_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate3_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate3_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate3_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate3_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate3_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate3_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate3_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11d};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11e */
    class ObjectDate3_B : public adas::can::CanData {
    public:
        ObjectDate3_B() : adas::can::CanData(8) {}
        explicit ObjectDate3_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate3_B {
    private:
        void can_msg_update() {
            if(0x11e != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate3_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate3_B {
    public:
        ObjectDate3_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate3_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate3_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11e};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x11f */
    class ObjectDate3_C : public adas::can::CanData {
    public:
        ObjectDate3_C() : adas::can::CanData(8) {}
        explicit ObjectDate3_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate3_C {
    private:
        void can_msg_update() {
            if(0x11f != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate3_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate3_C {
    public:
        ObjectDate3_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate3_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x11f};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x120 */
    class ObjectDate3_D : public adas::can::CanData {
    public:
        ObjectDate3_D() : adas::can::CanData(8) {}
        explicit ObjectDate3_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate3_D {
    private:
        void can_msg_update() {
            if(0x120 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate3_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate3_D {
    public:
        ObjectDate3_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate3_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x120};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x121 */
    class ObjectDate4_A : public adas::can::CanData {
    public:
        ObjectDate4_A() : adas::can::CanData(8) {}
        explicit ObjectDate4_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate4_A {
    private:
        void can_msg_update() {
            if(0x121 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate4_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate4_A {
    public:
        ObjectDate4_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate4_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate4_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate4_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate4_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate4_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate4_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate4_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x121};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x122 */
    class ObjectDate4_B : public adas::can::CanData {
    public:
        ObjectDate4_B() : adas::can::CanData(8) {}
        explicit ObjectDate4_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate4_B {
    private:
        void can_msg_update() {
            if(0x122 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate4_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate4_B {
    public:
        ObjectDate4_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate4_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate4_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x122};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x123 */
    class ObjectDate4_C : public adas::can::CanData {
    public:
        ObjectDate4_C() : adas::can::CanData(8) {}
        explicit ObjectDate4_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate4_C {
    private:
        void can_msg_update() {
            if(0x123 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate4_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate4_C {
    public:
        ObjectDate4_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate4_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x123};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x124 */
    class ObjectDate4_D : public adas::can::CanData {
    public:
        ObjectDate4_D() : adas::can::CanData(8) {}
        explicit ObjectDate4_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate4_D {
    private:
        void can_msg_update() {
            if(0x124 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate4_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate4_D {
    public:
        ObjectDate4_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate4_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x124};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x125 */
    class ObjectDate5_A : public adas::can::CanData {
    public:
        ObjectDate5_A() : adas::can::CanData(8) {}
        explicit ObjectDate5_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate5_A {
    private:
        void can_msg_update() {
            if(0x125 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate5_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate5_A {
    public:
        ObjectDate5_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate5_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate5_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate5_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate5_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate5_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate5_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate5_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x125};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x126 */
    class ObjectDate5_B : public adas::can::CanData {
    public:
        ObjectDate5_B() : adas::can::CanData(8) {}
        explicit ObjectDate5_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate5_B {
    private:
        void can_msg_update() {
            if(0x126 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate5_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate5_B {
    public:
        ObjectDate5_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate5_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate5_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x126};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x127 */
    class ObjectDate5_C : public adas::can::CanData {
    public:
        ObjectDate5_C() : adas::can::CanData(8) {}
        explicit ObjectDate5_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate5_C {
    private:
        void can_msg_update() {
            if(0x127 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate5_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate5_C {
    public:
        ObjectDate5_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate5_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x127};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x128 */
    class ObjectDate5_D : public adas::can::CanData {
    public:
        ObjectDate5_D() : adas::can::CanData(8) {}
        explicit ObjectDate5_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate5_D {
    private:
        void can_msg_update() {
            if(0x128 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate5_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate5_D {
    public:
        ObjectDate5_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate5_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x128};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x129 */
    class ObjectDate6_A : public adas::can::CanData {
    public:
        ObjectDate6_A() : adas::can::CanData(8) {}
        explicit ObjectDate6_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate6_A {
    private:
        void can_msg_update() {
            if(0x129 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate6_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate6_A {
    public:
        ObjectDate6_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate6_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate6_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate6_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate6_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate6_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate6_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate6_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x129};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12a */
    class ObjectDate6_B : public adas::can::CanData {
    public:
        ObjectDate6_B() : adas::can::CanData(8) {}
        explicit ObjectDate6_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate6_B {
    private:
        void can_msg_update() {
            if(0x12a != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate6_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate6_B {
    public:
        ObjectDate6_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate6_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate6_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12a};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12b */
    class ObjectDate6_C : public adas::can::CanData {
    public:
        ObjectDate6_C() : adas::can::CanData(8) {}
        explicit ObjectDate6_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate6_C {
    private:
        void can_msg_update() {
            if(0x12b != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate6_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate6_C {
    public:
        ObjectDate6_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate6_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12b};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12c */
    class ObjectDate6_D : public adas::can::CanData {
    public:
        ObjectDate6_D() : adas::can::CanData(8) {}
        explicit ObjectDate6_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate6_D {
    private:
        void can_msg_update() {
            if(0x12c != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate6_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate6_D {
    public:
        ObjectDate6_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate6_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12c};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12d */
    class ObjectDate7_A : public adas::can::CanData {
    public:
        ObjectDate7_A() : adas::can::CanData(8) {}
        explicit ObjectDate7_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate7_A {
    private:
        void can_msg_update() {
            if(0x12d != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate7_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate7_A {
    public:
        ObjectDate7_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate7_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate7_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate7_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate7_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate7_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate7_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate7_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12d};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12e */
    class ObjectDate7_B : public adas::can::CanData {
    public:
        ObjectDate7_B() : adas::can::CanData(8) {}
        explicit ObjectDate7_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate7_B {
    private:
        void can_msg_update() {
            if(0x12e != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate7_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate7_B {
    public:
        ObjectDate7_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate7_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate7_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12e};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x12f */
    class ObjectDate7_C : public adas::can::CanData {
    public:
        ObjectDate7_C() : adas::can::CanData(8) {}
        explicit ObjectDate7_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate7_C {
    private:
        void can_msg_update() {
            if(0x12f != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate7_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate7_C {
    public:
        ObjectDate7_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate7_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x12f};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x130 */
    class ObjectDate7_D : public adas::can::CanData {
    public:
        ObjectDate7_D() : adas::can::CanData(8) {}
        explicit ObjectDate7_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate7_D {
    private:
        void can_msg_update() {
            if(0x130 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate7_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate7_D {
    public:
        ObjectDate7_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate7_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x130};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x131 */
    class ObjectDate8_A : public adas::can::CanData {
    public:
        ObjectDate8_A() : adas::can::CanData(8) {}
        explicit ObjectDate8_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate8_A {
    private:
        void can_msg_update() {
            if(0x131 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate8_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate8_A {
    public:
        ObjectDate8_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate8_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate8_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate8_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate8_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate8_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate8_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate8_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x131};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x132 */
    class ObjectDate8_B : public adas::can::CanData {
    public:
        ObjectDate8_B() : adas::can::CanData(8) {}
        explicit ObjectDate8_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate8_B {
    private:
        void can_msg_update() {
            if(0x132 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate8_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate8_B {
    public:
        ObjectDate8_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate8_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate8_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x132};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x133 */
    class ObjectDate8_C : public adas::can::CanData {
    public:
        ObjectDate8_C() : adas::can::CanData(8) {}
        explicit ObjectDate8_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate8_C {
    private:
        void can_msg_update() {
            if(0x133 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate8_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate8_C {
    public:
        ObjectDate8_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate8_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x133};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x134 */
    class ObjectDate8_D : public adas::can::CanData {
    public:
        ObjectDate8_D() : adas::can::CanData(8) {}
        explicit ObjectDate8_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate8_D {
    private:
        void can_msg_update() {
            if(0x134 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate8_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate8_D {
    public:
        ObjectDate8_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate8_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x134};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x135 */
    class ObjectDate9_A : public adas::can::CanData {
    public:
        ObjectDate9_A() : adas::can::CanData(8) {}
        explicit ObjectDate9_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Motion_Category_Choices {
            ONCOMING = 13,
            PRECEEDING = 12,
            MOVING = 11,
            RTAP = 10,
            LTAP = 9,
            CROSSING = 8,
            MOVING_OUT = 7,
            MOVING_IN = 6,
            CLOSE_CUT_IN = 5,
            PASSING_OUT = 4,
            PASSING_IN = 3,
            PASSING = 2,
            UNDEFINED = 1,
            INVALID = 0,
        };

        enum class OBJ_Object_Class_Choices {
            UNCERTAIN_VCL = 8,
            ANIMAL = 7,
            GENERAL_OBJECT = 6,
            PEDESTRIAN = 5,
            BICYCLE = 4,
            BIKE = 3,
            TRUCK = 2,
            CAR = 1,
            INVALID = 0,
        };

        enum class OBJ_Motion_Status_Choices {
            MOVINGSLOWLY = 5,
            STOPPED = 4,
            STATIONARY = 3,
            MOVING = 2,
            UNKNOWN = 1,
            INVALID = 0,
        };

        enum class OBJ_Brake_Light_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Right_Choices {
            True = 1,
            False = 0,
        };

        enum class OBJ_Turn_Indicator_Left_Choices {
            True = 1,
            False = 0,
        };

        /* The detected OBJ ID  */
        uint8_t OBJ_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void OBJ_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* Existence probability of vehicle */
        float OBJ_Existence_Probability() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Existence_Probability(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The general scene identification (is the target cutting us, moving in or out of lane etc.) */
        OBJ_Motion_Category_Choices OBJ_Motion_Category() const {
            return static_cast<OBJ_Motion_Category_Choices>(get<uint8_t>(17, 4, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Category(OBJ_Motion_Category_Choices value) {
            set<uint8_t>(17, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Frame age of obstacle */
        uint16_t OBJ_Object_Age() const {
            return get<uint16_t>(21, 11, LITTLE_ENDIAN);
        }
        void OBJ_Object_Age(uint16_t value) {
            set<uint16_t>(21, 11, LITTLE_ENDIAN, value);
        }

        /* Were measurements predicted, old, or not valid */
        uint8_t OBJ_Measuring_Status() const {
            return get<uint8_t>(32, 3, LITTLE_ENDIAN);
        }
        void OBJ_Measuring_Status(uint8_t value) {
            set<uint8_t>(32, 3, LITTLE_ENDIAN, value);
        }

        /* Kind of object. */
        OBJ_Object_Class_Choices OBJ_Object_Class() const {
            return static_cast<OBJ_Object_Class_Choices>(get<uint8_t>(35, 4, LITTLE_ENDIAN));
        }
        void OBJ_Object_Class(OBJ_Object_Class_Choices value) {
            set<uint8_t>(35, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The target is moving or stopped */
        OBJ_Motion_Status_Choices OBJ_Motion_Status() const {
            return static_cast<OBJ_Motion_Status_Choices>(get<uint8_t>(39, 3, LITTLE_ENDIAN));
        }
        void OBJ_Motion_Status(OBJ_Motion_Status_Choices value) {
            set<uint8_t>(39, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* if bit is on the brake light is on */
        OBJ_Brake_Light_Choices OBJ_Brake_Light() const {
            return static_cast<OBJ_Brake_Light_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void OBJ_Brake_Light(OBJ_Brake_Light_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the right bliking light is on */
        OBJ_Turn_Indicator_Right_Choices OBJ_Turn_Indicator_Right() const {
            return static_cast<OBJ_Turn_Indicator_Right_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Right(OBJ_Turn_Indicator_Right_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* if bit is on the left blinking light is on */
        OBJ_Turn_Indicator_Left_Choices OBJ_Turn_Indicator_Left() const {
            return static_cast<OBJ_Turn_Indicator_Left_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void OBJ_Turn_Indicator_Left(OBJ_Turn_Indicator_Left_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate9_A {
    private:
        void can_msg_update() {
            if(0x135 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate9_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_ID(static_cast<int>(can_data.OBJ_ID()));
            OBJ_Existence_Probability(can_data.OBJ_Existence_Probability());
            OBJ_Motion_Category(static_cast<int>(can_data.OBJ_Motion_Category()));
            OBJ_Object_Age(static_cast<int>(can_data.OBJ_Object_Age()));
            OBJ_Measuring_Status(static_cast<int>(can_data.OBJ_Measuring_Status()));
            OBJ_Object_Class(static_cast<int>(can_data.OBJ_Object_Class()));
            OBJ_Motion_Status(static_cast<int>(can_data.OBJ_Motion_Status()));
            OBJ_Brake_Light(static_cast<int>(can_data.OBJ_Brake_Light()));
            OBJ_Turn_Indicator_Right(static_cast<int>(can_data.OBJ_Turn_Indicator_Right()));
            OBJ_Turn_Indicator_Left(static_cast<int>(can_data.OBJ_Turn_Indicator_Left()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_ID;
        adas::node::out<float> OBJ_Existence_Probability;
        adas::node::out<int> OBJ_Motion_Category;
        adas::node::out<int> OBJ_Object_Age;
        adas::node::out<int> OBJ_Measuring_Status;
        adas::node::out<int> OBJ_Object_Class;
        adas::node::out<int> OBJ_Motion_Status;
        adas::node::out<int> OBJ_Brake_Light;
        adas::node::out<int> OBJ_Turn_Indicator_Right;
        adas::node::out<int> OBJ_Turn_Indicator_Left;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate9_A {
    public:
        ObjectDate9_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_ID{0, [](){}};
        adas::node::in<float> OBJ_Existence_Probability{0, [](){}};
        adas::node::in<int> OBJ_Motion_Category{0, [](){}};
        adas::node::in<int> OBJ_Object_Age{0, [](){}};
        adas::node::in<int> OBJ_Measuring_Status{0, [](){}};
        adas::node::in<int> OBJ_Object_Class{0, [](){}};
        adas::node::in<int> OBJ_Motion_Status{0, [](){}};
        adas::node::in<int> OBJ_Brake_Light{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Right{0, [](){}};
        adas::node::in<int> OBJ_Turn_Indicator_Left{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate9_A data;
            data.OBJ_ID(OBJ_ID.get());
            data.OBJ_Existence_Probability(OBJ_Existence_Probability.get());
            data.OBJ_Motion_Category(eyeq4::object::ObjectDate9_A::OBJ_Motion_Category_Choices{OBJ_Motion_Category.get()});
            data.OBJ_Object_Age(OBJ_Object_Age.get());
            data.OBJ_Measuring_Status(OBJ_Measuring_Status.get());
            data.OBJ_Object_Class(eyeq4::object::ObjectDate9_A::OBJ_Object_Class_Choices{OBJ_Object_Class.get()});
            data.OBJ_Motion_Status(eyeq4::object::ObjectDate9_A::OBJ_Motion_Status_Choices{OBJ_Motion_Status.get()});
            data.OBJ_Brake_Light(eyeq4::object::ObjectDate9_A::OBJ_Brake_Light_Choices{OBJ_Brake_Light.get()});
            data.OBJ_Turn_Indicator_Right(eyeq4::object::ObjectDate9_A::OBJ_Turn_Indicator_Right_Choices{OBJ_Turn_Indicator_Right.get()});
            data.OBJ_Turn_Indicator_Left(eyeq4::object::ObjectDate9_A::OBJ_Turn_Indicator_Left_Choices{OBJ_Turn_Indicator_Left.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x135};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x136 */
    class ObjectDate9_B : public adas::can::CanData {
    public:
        ObjectDate9_B() : adas::can::CanData(8) {}
        explicit ObjectDate9_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class OBJ_Lane_Assignment_Choices {
            RIGHT_RIGHT = 5,
            RIGHT = 4,
            HOST = 3,
            LEFT = 2,
            LEFT_LEFT = 1,
            UNKNOWN = 0,
        };

        /* the lane on which the object is measured */
        OBJ_Lane_Assignment_Choices OBJ_Lane_Assignment() const {
            return static_cast<OBJ_Lane_Assignment_Choices>(get<uint8_t>(0, 3, LITTLE_ENDIAN));
        }
        void OBJ_Lane_Assignment(OBJ_Lane_Assignment_Choices value) {
            set<uint8_t>(0, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* The actual width of the target vehicle in the world (not to be mistaken with the width of the visible part of the vehicle) */
        float OBJ_Width() const {
            return get<uint16_t>(3, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void OBJ_Width(float value) {
            set<uint16_t>(3, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* The length in the world.  */
        float OBJ_Length() const {
            return get<uint16_t>(20, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(0);
        }
        void OBJ_Length(float value) {
            set<uint16_t>(20, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.05)));
        }

        /* the longtitudinal ground speed */
        float OBJ_Abs_Long_Velocity() const {
            return get<uint16_t>(37, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-65);
        }
        void OBJ_Abs_Long_Velocity(float value) {
            set<uint16_t>(37, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-65))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate9_B {
    private:
        void can_msg_update() {
            if(0x136 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate9_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lane_Assignment(static_cast<int>(can_data.OBJ_Lane_Assignment()));
            OBJ_Width(can_data.OBJ_Width());
            OBJ_Length(can_data.OBJ_Length());
            OBJ_Abs_Long_Velocity(can_data.OBJ_Abs_Long_Velocity());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> OBJ_Lane_Assignment;
        adas::node::out<float> OBJ_Width;
        adas::node::out<float> OBJ_Length;
        adas::node::out<float> OBJ_Abs_Long_Velocity;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate9_B {
    public:
        ObjectDate9_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> OBJ_Lane_Assignment{0, [](){}};
        adas::node::in<float> OBJ_Width{0, [](){}};
        adas::node::in<float> OBJ_Length{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Velocity{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate9_B data;
            data.OBJ_Lane_Assignment(eyeq4::object::ObjectDate9_B::OBJ_Lane_Assignment_Choices{OBJ_Lane_Assignment.get()});
            data.OBJ_Width(OBJ_Width.get());
            data.OBJ_Length(OBJ_Length.get());
            data.OBJ_Abs_Long_Velocity(OBJ_Abs_Long_Velocity.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x136};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x137 */
    class ObjectDate9_C : public adas::can::CanData {
    public:
        ObjectDate9_C() : adas::can::CanData(8) {}
        explicit ObjectDate9_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* the lateral ground speed锛孭ositive on left turn */
        float OBJ_Abs_Lat_Velocity() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-50);
        }
        void OBJ_Abs_Lat_Velocity(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-50))/static_cast<float>(0.05)));
        }

        /* the lateral ground acceleration */
        float OBJ_Abs_Long_Acc() const {
            return get<uint16_t>(21, 9, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-10.3);
        }
        void OBJ_Abs_Long_Acc(float value) {
            set<uint16_t>(21, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10.3))/static_cast<float>(0.05)));
        }

        /* longtitudinal distance to the middle of the RL and RR corners.   */
        float OBJ_Long_Distance() const {
            return get<uint16_t>(38, 14, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-200);
        }
        void OBJ_Long_Distance(float value) {
            set<uint16_t>(38, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-200))/static_cast<float>(0.05)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate9_C {
    private:
        void can_msg_update() {
            if(0x137 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate9_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Abs_Lat_Velocity(can_data.OBJ_Abs_Lat_Velocity());
            OBJ_Abs_Long_Acc(can_data.OBJ_Abs_Long_Acc());
            OBJ_Long_Distance(can_data.OBJ_Long_Distance());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Abs_Lat_Velocity;
        adas::node::out<float> OBJ_Abs_Long_Acc;
        adas::node::out<float> OBJ_Long_Distance;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate9_C {
    public:
        ObjectDate9_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Abs_Lat_Velocity{0, [](){}};
        adas::node::in<float> OBJ_Abs_Long_Acc{0, [](){}};
        adas::node::in<float> OBJ_Long_Distance{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate9_C data;
            data.OBJ_Abs_Lat_Velocity(OBJ_Abs_Lat_Velocity.get());
            data.OBJ_Abs_Long_Acc(OBJ_Abs_Long_Acc.get());
            data.OBJ_Long_Distance(OBJ_Long_Distance.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x137};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x138 */
    class ObjectDate9_D : public adas::can::CanData {
    public:
        ObjectDate9_D() : adas::can::CanData(8) {}
        explicit ObjectDate9_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* lateral distance to the middle of the RL and RR corners锛孭ositive on left turn.   */
        float OBJ_Lat_Distance() const {
            return get<uint16_t>(13, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void OBJ_Lat_Distance(float value) {
            set<uint16_t>(13, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* The momentary angular speed锛孭ositive on left turn  */
        float OBJ_Angle_Rate() const {
            return get<uint16_t>(46, 12, LITTLE_ENDIAN) * static_cast<float>(0.002) + static_cast<float>(-2.234);
        }
        void OBJ_Angle_Rate(float value) {
            set<uint16_t>(46, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-2.234))/static_cast<float>(0.002)));
        }

        /* None */
        uint8_t Rolling_Counter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void Rolling_Counter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ObjectDate9_D {
    private:
        void can_msg_update() {
            if(0x138 != can_msg.get().can_id)
                return;
            eyeq4::object::ObjectDate9_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            OBJ_Lat_Distance(can_data.OBJ_Lat_Distance());
            OBJ_Angle_Rate(can_data.OBJ_Angle_Rate());
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> OBJ_Lat_Distance;
        adas::node::out<float> OBJ_Angle_Rate;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class ObjectDate9_D {
    public:
        ObjectDate9_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> OBJ_Lat_Distance{0, [](){}};
        adas::node::in<float> OBJ_Angle_Rate{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::object::ObjectDate9_D data;
            data.OBJ_Lat_Distance(OBJ_Lat_Distance.get());
            data.OBJ_Angle_Rate(OBJ_Angle_Rate.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x138};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

}

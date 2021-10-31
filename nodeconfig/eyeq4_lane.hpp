#pragma once
#include <adas/can.h>
#include <adas/node.hpp>
#include <chrono>
#include <algorithm>
namespace eyeq4::lane {
    /* None */
    /* id: 0x140 */
    class Lanes_Support_Header : public adas::can::CanData {
    public:
        Lanes_Support_Header() : adas::can::CanData(8) {}
        explicit Lanes_Support_Header(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class is_Construction_Area_Choices {
            TRUE = 1,
            FALSE = 0,
        };

        /* Multi-frame estimation of host lane width to be used for prediction or another driving cue/ scene cue */
        float Host_Estimated_Width() const {
            return get<uint16_t>(0, 9, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Host_Estimated_Width(float value) {
            set<uint16_t>(0, 9, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* True if this is a construction area scene.  */
        is_Construction_Area_Choices is_Construction_Area() const {
            return static_cast<is_Construction_Area_Choices>(get<bool>(9, 1, LITTLE_ENDIAN));
        }
        void is_Construction_Area(is_Construction_Area_Choices value) {
            set<bool>(9, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* None */
        uint8_t Reserved_0() const {
            return get<uint8_t>(10, 6, LITTLE_ENDIAN);
        }
        void Reserved_0(uint8_t value) {
            set<uint8_t>(10, 6, LITTLE_ENDIAN, value);
        }

        /* None */
        uint64_t Reserved_1() const {
            return get<uint64_t>(16, 40, LITTLE_ENDIAN);
        }
        void Reserved_1(uint64_t value) {
            set<uint64_t>(16, 40, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Lanes_Support_Header {
    private:
        void can_msg_update() {
            if(0x140 != can_msg.get().can_id)
                return;
            eyeq4::lane::Lanes_Support_Header can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Host_Estimated_Width(can_data.Host_Estimated_Width());
            is_Construction_Area(static_cast<int>(can_data.is_Construction_Area()));
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Host_Estimated_Width;
        adas::node::out<int> is_Construction_Area;
        adas::node::out<int> Reserved_0;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Lanes_Support_Header {
    public:
        Lanes_Support_Header() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Host_Estimated_Width{0, [](){}};
        adas::node::in<int> is_Construction_Area{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Lanes_Support_Header data;
            data.Host_Estimated_Width(Host_Estimated_Width.get());
            data.is_Construction_Area(eyeq4::lane::Lanes_Support_Header::is_Construction_Area_Choices{is_Construction_Area.get()});
            data.Reserved_0(Reserved_0.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x140};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x141 */
    class Left_Lane_A : public adas::can::CanData {
    public:
        Left_Lane_A() : adas::can::CanData(8) {}
        explicit Left_Lane_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class is_Lane_Valid_Choices {
            TRUE = 1,
            FALSE = 0,
        };

        enum class Lane_Crossing_Choices {
            TRUE = 1,
            FALSE = 0,
        };

        enum class Lane_DECEL_Type_Choices {
            DASHED = 2,
            SOLID = 1,
            NO_DECEL = 0,
        };

        enum class Lane_Type_Class_Choices {
            HOV_LANE = 11,
            DECELERATION = 10,
            BOTTS = 5,
            DLM = 4,
            ROAD_EDGE = 3,
            DASHED = 2,
            SOLID = 1,
            UNDECIDED = 0,
        };

        enum class Lane_Color_Choices {
            BLUE_GREEN = 3,
            YELLOW_ORANGE_RED = 2,
            WHITE = 1,
            UNDECIDED = 0,
        };

        enum class Lane_DLM_Type_Choices {
            UNDECIDED = 5,
            DASHED_DASHED = 4,
            SOLID_SOLID = 3,
            DASHED_SOLID = 2,
            SOLID_DASHED = 1,
            NOT_DLM = 0,
        };

        /* ID to be used for comparing frames */
        uint8_t Lane_Track_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void Lane_Track_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* True if L host polynom is found */
        is_Lane_Valid_Choices is_Lane_Valid() const {
            return static_cast<is_Lane_Valid_Choices>(get<bool>(8, 1, LITTLE_ENDIAN));
        }
        void is_Lane_Valid(is_Lane_Valid_Choices value) {
            set<bool>(8, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* Existence probability of lane mark */
        float Lane_Exist_Probability() const {
            return get<uint8_t>(9, 7, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_Exist_Probability(float value) {
            set<uint8_t>(9, 7, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Is left lane mark crossed (Lane change) */
        Lane_Crossing_Choices Lane_Crossing() const {
            return static_cast<Lane_Crossing_Choices>(get<bool>(16, 1, LITTLE_ENDIAN));
        }
        void Lane_Crossing(Lane_Crossing_Choices value) {
            set<bool>(16, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* For deceleration, what is inner line type (ENUM) */
        Lane_DECEL_Type_Choices Lane_DECEL_Type() const {
            return static_cast<Lane_DECEL_Type_Choices>(get<uint8_t>(17, 3, LITTLE_ENDIAN));
        }
        void Lane_DECEL_Type(Lane_DECEL_Type_Choices value) {
            set<uint8_t>(17, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* ENUM of Lane Mark Type Classification */
        Lane_Type_Class_Choices Lane_Type_Class() const {
            return static_cast<Lane_Type_Class_Choices>(get<uint8_t>(20, 4, LITTLE_ENDIAN));
        }
        void Lane_Type_Class(Lane_Type_Class_Choices value) {
            set<uint8_t>(20, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Start of longitudinal view range of lane mark */
        float Lane_View_Range_Start() const {
            return get<uint16_t>(24, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_Start(float value) {
            set<uint16_t>(24, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        bool Reserved_0() const {
            return get<bool>(39, 1, LITTLE_ENDIAN);
        }
        void Reserved_0(bool value) {
            set<bool>(39, 1, LITTLE_ENDIAN, value);
        }

        /* End of longitudinal view range of lane mark */
        float Lane_View_Range_End() const {
            return get<uint16_t>(40, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_End(float value) {
            set<uint16_t>(40, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* ENUM lane mark color */
        Lane_Color_Choices Lane_Color() const {
            return static_cast<Lane_Color_Choices>(get<uint8_t>(55, 2, LITTLE_ENDIAN));
        }
        void Lane_Color(Lane_Color_Choices value) {
            set<uint8_t>(55, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* For double lane mark, what type of DLM (ENUM) */
        Lane_DLM_Type_Choices Lane_DLM_Type() const {
            return static_cast<Lane_DLM_Type_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Lane_DLM_Type(Lane_DLM_Type_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Left_Lane_A {
    private:
        void can_msg_update() {
            if(0x141 != can_msg.get().can_id)
                return;
            eyeq4::lane::Left_Lane_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_Track_ID(static_cast<int>(can_data.Lane_Track_ID()));
            is_Lane_Valid(static_cast<int>(can_data.is_Lane_Valid()));
            Lane_Exist_Probability(can_data.Lane_Exist_Probability());
            Lane_Crossing(static_cast<int>(can_data.Lane_Crossing()));
            Lane_DECEL_Type(static_cast<int>(can_data.Lane_DECEL_Type()));
            Lane_Type_Class(static_cast<int>(can_data.Lane_Type_Class()));
            Lane_View_Range_Start(can_data.Lane_View_Range_Start());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_View_Range_End(can_data.Lane_View_Range_End());
            Lane_Color(static_cast<int>(can_data.Lane_Color()));
            Lane_DLM_Type(static_cast<int>(can_data.Lane_DLM_Type()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> Lane_Track_ID;
        adas::node::out<int> is_Lane_Valid;
        adas::node::out<float> Lane_Exist_Probability;
        adas::node::out<int> Lane_Crossing;
        adas::node::out<int> Lane_DECEL_Type;
        adas::node::out<int> Lane_Type_Class;
        adas::node::out<float> Lane_View_Range_Start;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_View_Range_End;
        adas::node::out<int> Lane_Color;
        adas::node::out<int> Lane_DLM_Type;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Left_Lane_A {
    public:
        Left_Lane_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> Lane_Track_ID{0, [](){}};
        adas::node::in<int> is_Lane_Valid{0, [](){}};
        adas::node::in<float> Lane_Exist_Probability{0, [](){}};
        adas::node::in<int> Lane_Crossing{0, [](){}};
        adas::node::in<int> Lane_DECEL_Type{0, [](){}};
        adas::node::in<int> Lane_Type_Class{0, [](){}};
        adas::node::in<float> Lane_View_Range_Start{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_View_Range_End{0, [](){}};
        adas::node::in<int> Lane_Color{0, [](){}};
        adas::node::in<int> Lane_DLM_Type{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Left_Lane_A data;
            data.Lane_Track_ID(Lane_Track_ID.get());
            data.is_Lane_Valid(eyeq4::lane::Left_Lane_A::is_Lane_Valid_Choices{is_Lane_Valid.get()});
            data.Lane_Exist_Probability(Lane_Exist_Probability.get());
            data.Lane_Crossing(eyeq4::lane::Left_Lane_A::Lane_Crossing_Choices{Lane_Crossing.get()});
            data.Lane_DECEL_Type(eyeq4::lane::Left_Lane_A::Lane_DECEL_Type_Choices{Lane_DECEL_Type.get()});
            data.Lane_Type_Class(eyeq4::lane::Left_Lane_A::Lane_Type_Class_Choices{Lane_Type_Class.get()});
            data.Lane_View_Range_Start(Lane_View_Range_Start.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_View_Range_End(Lane_View_Range_End.get());
            data.Lane_Color(eyeq4::lane::Left_Lane_A::Lane_Color_Choices{Lane_Color.get()});
            data.Lane_DLM_Type(eyeq4::lane::Left_Lane_A::Lane_DLM_Type_Choices{Lane_DLM_Type.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x141};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x142 */
    class Left_Lane_B : public adas::can::CanData {
    public:
        Left_Lane_B() : adas::can::CanData(8) {}
        explicit Left_Lane_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class Prediction_Source_Choices {
            MERGE = 6,
            GR_SHADOW = 5,
            DIVERGING = 4,
            OCCLUDED = 3,
            HEADWAY = 2,
            LOSS = 1,
            NONE = 0,
        };

        /* Width of lane mark in M */
        float Line_Marker_Width() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Line_Marker_Width(float value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_0() const {
            return get<uint8_t>(8, 7, LITTLE_ENDIAN);
        }
        void Reserved_0(uint8_t value) {
            set<uint8_t>(8, 7, LITTLE_ENDIAN, value);
        }

        /* Average length of each section of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Average_Length() const {
            return get<uint16_t>(15, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Average_Length(float value) {
            set<uint16_t>(15, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Average gap between of sections of dashed line when lane mark is dashed in CM.  This is a multi-frame signal. */
        float Dash_Average_Gap() const {
            return get<uint16_t>(28, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Average_Gap(float value) {
            set<uint16_t>(28, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(41, 16, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(41, 16, LITTLE_ENDIAN, value);
        }

        /* Prediction source if Lane mark is predicted  Prediction source if Lane mark is predicted   */
        Prediction_Source_Choices Prediction_Source() const {
            return static_cast<Prediction_Source_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Prediction_Source(Prediction_Source_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Left_Lane_B {
    private:
        void can_msg_update() {
            if(0x142 != can_msg.get().can_id)
                return;
            eyeq4::lane::Left_Lane_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Line_Marker_Width(can_data.Line_Marker_Width());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Dash_Average_Length(can_data.Dash_Average_Length());
            Dash_Average_Gap(can_data.Dash_Average_Gap());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Prediction_Source(static_cast<int>(can_data.Prediction_Source()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Line_Marker_Width;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Dash_Average_Length;
        adas::node::out<float> Dash_Average_Gap;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Prediction_Source;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Left_Lane_B {
    public:
        Left_Lane_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Line_Marker_Width{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Dash_Average_Length{0, [](){}};
        adas::node::in<float> Dash_Average_Gap{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Prediction_Source{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Left_Lane_B data;
            data.Line_Marker_Width(Line_Marker_Width.get());
            data.Reserved_0(Reserved_0.get());
            data.Dash_Average_Length(Dash_Average_Length.get());
            data.Dash_Average_Gap(Dash_Average_Gap.get());
            data.Reserved_1(Reserved_1.get());
            data.Prediction_Source(eyeq4::lane::Left_Lane_B::Prediction_Source_Choices{Prediction_Source.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x142};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x143 */
    class Left_Lane_C : public adas::can::CanData {
    public:
        Left_Lane_C() : adas::can::CanData(8) {}
        explicit Left_Lane_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C0() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void Lane_C0(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(11, 14, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(11, 14, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C1() const {
            return get<uint16_t>(25, 10, LITTLE_ENDIAN) * static_cast<float>(0.000977) + static_cast<float>(-0.357);
        }
        void Lane_C1(float value) {
            set<uint16_t>(25, 10, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.357))/static_cast<float>(0.000977)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(35, 12, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(35, 12, LITTLE_ENDIAN, value);
        }

        /* None */
        bool Reserved_2() const {
            return get<bool>(47, 1, LITTLE_ENDIAN);
        }
        void Reserved_2(bool value) {
            set<bool>(47, 1, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_3() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_3(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_4() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_4(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Left_Lane_C {
    private:
        void can_msg_update() {
            if(0x143 != can_msg.get().can_id)
                return;
            eyeq4::lane::Left_Lane_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C0(can_data.Lane_C0());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C1(can_data.Lane_C1());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Reserved_3(static_cast<int>(can_data.Reserved_3()));
            Reserved_4(static_cast<int>(can_data.Reserved_4()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C0;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C1;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Reserved_3;
        adas::node::out<int> Reserved_4;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Left_Lane_C {
    public:
        Left_Lane_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C0{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C1{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Reserved_3{0, [](){}};
        adas::node::in<int> Reserved_4{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Left_Lane_C data;
            data.Lane_C0(Lane_C0.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C1(Lane_C1.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Reserved_3(Reserved_3.get());
            data.Reserved_4(Reserved_4.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x143};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x144 */
    class Left_Lane_D : public adas::can::CanData {
    public:
        Left_Lane_D() : adas::can::CanData(8) {}
        explicit Left_Lane_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C2() const {
            return get<uint16_t>(0, 16, LITTLE_ENDIAN) * static_cast<float>(9.77e-07) + static_cast<float>(-0.032);
        }
        void Lane_C2(float value) {
            set<uint16_t>(0, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.032))/static_cast<float>(9.77e-07)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(16, 16, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(16, 16, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C3() const {
            return get<uint16_t>(32, 16, LITTLE_ENDIAN) * static_cast<float>(3.73e-09) + static_cast<float>(-0.000122);
        }
        void Lane_C3(float value) {
            set<uint16_t>(32, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.000122))/static_cast<float>(3.73e-09)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Left_Lane_D {
    private:
        void can_msg_update() {
            if(0x144 != can_msg.get().can_id)
                return;
            eyeq4::lane::Left_Lane_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C2(can_data.Lane_C2());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C3(can_data.Lane_C3());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C2;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C3;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Left_Lane_D {
    public:
        Left_Lane_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C2{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C3{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Left_Lane_D data;
            data.Lane_C2(Lane_C2.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C3(Lane_C3.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x144};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x145 */
    class Right_Lane_A : public adas::can::CanData {
    public:
        Right_Lane_A() : adas::can::CanData(8) {}
        explicit Right_Lane_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class is_Lane_Valid_Choices {
            TRUE = 1,
            FALSE = 0,
        };

        enum class Lane_Crossing_Choices {
            TRUE = 1,
            FALSE = 0,
        };

        enum class Lane_DECEL_Type_Choices {
            DASHED = 2,
            SOLID = 1,
            NO_DECEL = 0,
        };

        enum class Lane_Type_Class_Choices {
            HOV_LANE = 11,
            DECELERATION = 10,
            BOTTS = 5,
            DLM = 4,
            ROAD_EDGE = 3,
            DASHED = 2,
            SOLID = 1,
            UNDECIDED = 0,
        };

        enum class Lane_Color_Choices {
            BLUE_GREEN = 3,
            YELLOW_ORANGE_RED = 2,
            WHITE = 1,
            UNDECIDED = 0,
        };

        enum class Lane_DLM_Type_Choices {
            UNDECIDED = 5,
            DASHED_DASHED = 4,
            SOLID_SOLID = 3,
            DASHED_SOLID = 2,
            SOLID_DASHED = 1,
            NOT_DLM = 0,
        };

        /* ID to be used for comparing frames */
        uint8_t Lane_Track_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void Lane_Track_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* True if L host polynom is found */
        is_Lane_Valid_Choices is_Lane_Valid() const {
            return static_cast<is_Lane_Valid_Choices>(get<bool>(8, 1, LITTLE_ENDIAN));
        }
        void is_Lane_Valid(is_Lane_Valid_Choices value) {
            set<bool>(8, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* Existence probability of lane mark */
        float Lane_Exist_Probability() const {
            return get<uint8_t>(9, 7, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_Exist_Probability(float value) {
            set<uint8_t>(9, 7, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Is left lane mark crossed (Lane change) */
        Lane_Crossing_Choices Lane_Crossing() const {
            return static_cast<Lane_Crossing_Choices>(get<bool>(16, 1, LITTLE_ENDIAN));
        }
        void Lane_Crossing(Lane_Crossing_Choices value) {
            set<bool>(16, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* For deceleration, what is inner line type (ENUM) */
        Lane_DECEL_Type_Choices Lane_DECEL_Type() const {
            return static_cast<Lane_DECEL_Type_Choices>(get<uint8_t>(17, 3, LITTLE_ENDIAN));
        }
        void Lane_DECEL_Type(Lane_DECEL_Type_Choices value) {
            set<uint8_t>(17, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* ENUM of Lane Mark Type Classification */
        Lane_Type_Class_Choices Lane_Type_Class() const {
            return static_cast<Lane_Type_Class_Choices>(get<uint8_t>(20, 4, LITTLE_ENDIAN));
        }
        void Lane_Type_Class(Lane_Type_Class_Choices value) {
            set<uint8_t>(20, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Start of longitudinal view range of lane mark */
        float Lane_View_Range_Start() const {
            return get<uint16_t>(24, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_Start(float value) {
            set<uint16_t>(24, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        bool Reserved_0() const {
            return get<bool>(39, 1, LITTLE_ENDIAN);
        }
        void Reserved_0(bool value) {
            set<bool>(39, 1, LITTLE_ENDIAN, value);
        }

        /* End of longitudinal view range of lane mark */
        float Lane_View_Range_End() const {
            return get<uint16_t>(40, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_End(float value) {
            set<uint16_t>(40, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* ENUM lane mark color */
        Lane_Color_Choices Lane_Color() const {
            return static_cast<Lane_Color_Choices>(get<uint8_t>(55, 2, LITTLE_ENDIAN));
        }
        void Lane_Color(Lane_Color_Choices value) {
            set<uint8_t>(55, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* For double lane mark, what type of DLM (ENUM) */
        Lane_DLM_Type_Choices Lane_DLM_Type() const {
            return static_cast<Lane_DLM_Type_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Lane_DLM_Type(Lane_DLM_Type_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Right_Lane_A {
    private:
        void can_msg_update() {
            if(0x145 != can_msg.get().can_id)
                return;
            eyeq4::lane::Right_Lane_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_Track_ID(static_cast<int>(can_data.Lane_Track_ID()));
            is_Lane_Valid(static_cast<int>(can_data.is_Lane_Valid()));
            Lane_Exist_Probability(can_data.Lane_Exist_Probability());
            Lane_Crossing(static_cast<int>(can_data.Lane_Crossing()));
            Lane_DECEL_Type(static_cast<int>(can_data.Lane_DECEL_Type()));
            Lane_Type_Class(static_cast<int>(can_data.Lane_Type_Class()));
            Lane_View_Range_Start(can_data.Lane_View_Range_Start());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_View_Range_End(can_data.Lane_View_Range_End());
            Lane_Color(static_cast<int>(can_data.Lane_Color()));
            Lane_DLM_Type(static_cast<int>(can_data.Lane_DLM_Type()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> Lane_Track_ID;
        adas::node::out<int> is_Lane_Valid;
        adas::node::out<float> Lane_Exist_Probability;
        adas::node::out<int> Lane_Crossing;
        adas::node::out<int> Lane_DECEL_Type;
        adas::node::out<int> Lane_Type_Class;
        adas::node::out<float> Lane_View_Range_Start;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_View_Range_End;
        adas::node::out<int> Lane_Color;
        adas::node::out<int> Lane_DLM_Type;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Right_Lane_A {
    public:
        Right_Lane_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> Lane_Track_ID{0, [](){}};
        adas::node::in<int> is_Lane_Valid{0, [](){}};
        adas::node::in<float> Lane_Exist_Probability{0, [](){}};
        adas::node::in<int> Lane_Crossing{0, [](){}};
        adas::node::in<int> Lane_DECEL_Type{0, [](){}};
        adas::node::in<int> Lane_Type_Class{0, [](){}};
        adas::node::in<float> Lane_View_Range_Start{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_View_Range_End{0, [](){}};
        adas::node::in<int> Lane_Color{0, [](){}};
        adas::node::in<int> Lane_DLM_Type{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Right_Lane_A data;
            data.Lane_Track_ID(Lane_Track_ID.get());
            data.is_Lane_Valid(eyeq4::lane::Right_Lane_A::is_Lane_Valid_Choices{is_Lane_Valid.get()});
            data.Lane_Exist_Probability(Lane_Exist_Probability.get());
            data.Lane_Crossing(eyeq4::lane::Right_Lane_A::Lane_Crossing_Choices{Lane_Crossing.get()});
            data.Lane_DECEL_Type(eyeq4::lane::Right_Lane_A::Lane_DECEL_Type_Choices{Lane_DECEL_Type.get()});
            data.Lane_Type_Class(eyeq4::lane::Right_Lane_A::Lane_Type_Class_Choices{Lane_Type_Class.get()});
            data.Lane_View_Range_Start(Lane_View_Range_Start.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_View_Range_End(Lane_View_Range_End.get());
            data.Lane_Color(eyeq4::lane::Right_Lane_A::Lane_Color_Choices{Lane_Color.get()});
            data.Lane_DLM_Type(eyeq4::lane::Right_Lane_A::Lane_DLM_Type_Choices{Lane_DLM_Type.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x145};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x146 */
    class Right_Lane_B : public adas::can::CanData {
    public:
        Right_Lane_B() : adas::can::CanData(8) {}
        explicit Right_Lane_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class Prediction_Source_Choices {
            MERGE = 6,
            GR_SHADOW = 5,
            DIVERGING = 4,
            OCCLUDED = 3,
            HEADWAY = 2,
            LOSS = 1,
            NONE = 0,
        };

        /* Width of lane mark in M */
        float Line_Marker_Width() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Line_Marker_Width(float value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_0() const {
            return get<uint8_t>(8, 7, LITTLE_ENDIAN);
        }
        void Reserved_0(uint8_t value) {
            set<uint8_t>(8, 7, LITTLE_ENDIAN, value);
        }

        /* Average length of each section of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Average_Length() const {
            return get<uint16_t>(15, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Average_Length(float value) {
            set<uint16_t>(15, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Average gap between of sections of dashed line when lane mark is dashed in CM.  This is a multi-frame signal. */
        float Dash_Average_Gap() const {
            return get<uint16_t>(28, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Average_Gap(float value) {
            set<uint16_t>(28, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(41, 16, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(41, 16, LITTLE_ENDIAN, value);
        }

        /* None */
        Prediction_Source_Choices Prediction_Source() const {
            return static_cast<Prediction_Source_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Prediction_Source(Prediction_Source_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Right_Lane_B {
    private:
        void can_msg_update() {
            if(0x146 != can_msg.get().can_id)
                return;
            eyeq4::lane::Right_Lane_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Line_Marker_Width(can_data.Line_Marker_Width());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Dash_Average_Length(can_data.Dash_Average_Length());
            Dash_Average_Gap(can_data.Dash_Average_Gap());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Prediction_Source(static_cast<int>(can_data.Prediction_Source()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Line_Marker_Width;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Dash_Average_Length;
        adas::node::out<float> Dash_Average_Gap;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Prediction_Source;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Right_Lane_B {
    public:
        Right_Lane_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Line_Marker_Width{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Dash_Average_Length{0, [](){}};
        adas::node::in<float> Dash_Average_Gap{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Prediction_Source{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Right_Lane_B data;
            data.Line_Marker_Width(Line_Marker_Width.get());
            data.Reserved_0(Reserved_0.get());
            data.Dash_Average_Length(Dash_Average_Length.get());
            data.Dash_Average_Gap(Dash_Average_Gap.get());
            data.Reserved_1(Reserved_1.get());
            data.Prediction_Source(eyeq4::lane::Right_Lane_B::Prediction_Source_Choices{Prediction_Source.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x146};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x147 */
    class Right_Lane_C : public adas::can::CanData {
    public:
        Right_Lane_C() : adas::can::CanData(8) {}
        explicit Right_Lane_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C0() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void Lane_C0(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(11, 14, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(11, 14, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C1() const {
            return get<uint16_t>(25, 10, LITTLE_ENDIAN) * static_cast<float>(0.000977) + static_cast<float>(-0.357);
        }
        void Lane_C1(float value) {
            set<uint16_t>(25, 10, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.357))/static_cast<float>(0.000977)));
        }

        /* None */
        float Reserved_1() const {
            return get<uint16_t>(35, 12, LITTLE_ENDIAN) * static_cast<float>(0.0001) + static_cast<float>(0);
        }
        void Reserved_1(float value) {
            set<uint16_t>(35, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.0001)));
        }

        /* None */
        bool Reserved_2() const {
            return get<bool>(47, 1, LITTLE_ENDIAN);
        }
        void Reserved_2(bool value) {
            set<bool>(47, 1, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_3() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_3(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_4() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_4(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Right_Lane_C {
    private:
        void can_msg_update() {
            if(0x147 != can_msg.get().can_id)
                return;
            eyeq4::lane::Right_Lane_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C0(can_data.Lane_C0());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C1(can_data.Lane_C1());
            Reserved_1(can_data.Reserved_1());
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Reserved_3(static_cast<int>(can_data.Reserved_3()));
            Reserved_4(static_cast<int>(can_data.Reserved_4()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C0;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C1;
        adas::node::out<float> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Reserved_3;
        adas::node::out<int> Reserved_4;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Right_Lane_C {
    public:
        Right_Lane_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C0{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C1{0, [](){}};
        adas::node::in<float> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Reserved_3{0, [](){}};
        adas::node::in<int> Reserved_4{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Right_Lane_C data;
            data.Lane_C0(Lane_C0.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C1(Lane_C1.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Reserved_3(Reserved_3.get());
            data.Reserved_4(Reserved_4.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x147};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x148 */
    class Right_Lane_D : public adas::can::CanData {
    public:
        Right_Lane_D() : adas::can::CanData(8) {}
        explicit Right_Lane_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C2() const {
            return get<uint16_t>(0, 16, LITTLE_ENDIAN) * static_cast<float>(9.77e-07) + static_cast<float>(-0.032);
        }
        void Lane_C2(float value) {
            set<uint16_t>(0, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.032))/static_cast<float>(9.77e-07)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(16, 16, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(16, 16, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C3() const {
            return get<uint16_t>(32, 16, LITTLE_ENDIAN) * static_cast<float>(3.73e-09) + static_cast<float>(-0.000122);
        }
        void Lane_C3(float value) {
            set<uint16_t>(32, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.000122))/static_cast<float>(3.73e-09)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Right_Lane_D {
    private:
        void can_msg_update() {
            if(0x148 != can_msg.get().can_id)
                return;
            eyeq4::lane::Right_Lane_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C2(can_data.Lane_C2());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C3(can_data.Lane_C3());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C2;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C3;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Right_Lane_D {
    public:
        Right_Lane_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C2{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C3{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Right_Lane_D data;
            data.Lane_C2(Lane_C2.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C3(Lane_C3.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x148};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x149 */
    class Next_Right_Lane_A : public adas::can::CanData {
    public:
        Next_Right_Lane_A() : adas::can::CanData(8) {}
        explicit Next_Right_Lane_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class Lane_Type_Class_Choices {
            HOV_LANE = 11,
            DECELERATION = 10,
            BOTTS = 5,
            DLM = 4,
            ROAD_EDGE = 3,
            DASHED = 2,
            SOLID = 1,
            UNDECIDED = 0,
        };

        enum class Lane_Color_Choices {
            BLUE_GREEN = 3,
            YELLOW_ORANGE_RED = 2,
            WHITE = 1,
            UNDECIDED = 0,
        };

        enum class Lane_DLM_Type_Choices {
            UNDECIDED = 5,
            DASHED_DASHED = 4,
            SOLID_SOLID = 3,
            DASHED_SOLID = 2,
            SOLID_DASHED = 1,
            NOT_DLM = 0,
        };

        /* ID to be used for comparing frames */
        uint8_t Lane_Track_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void Lane_Track_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        bool Reserved_0() const {
            return get<bool>(8, 1, LITTLE_ENDIAN);
        }
        void Reserved_0(bool value) {
            set<bool>(8, 1, LITTLE_ENDIAN, value);
        }

        /* Existence probability of lane mark */
        float Lane_Exist_Probability() const {
            return get<uint8_t>(9, 7, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_Exist_Probability(float value) {
            set<uint8_t>(9, 7, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(16, 4, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(16, 4, LITTLE_ENDIAN, value);
        }

        /* ENUM of Lane Mark Type Classification */
        Lane_Type_Class_Choices Lane_Type_Class() const {
            return static_cast<Lane_Type_Class_Choices>(get<uint8_t>(20, 4, LITTLE_ENDIAN));
        }
        void Lane_Type_Class(Lane_Type_Class_Choices value) {
            set<uint8_t>(20, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Start of longitudinal view range of lane mark */
        float Lane_View_Range_Start() const {
            return get<uint16_t>(24, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_Start(float value) {
            set<uint16_t>(24, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        bool Reserved_2() const {
            return get<bool>(39, 1, LITTLE_ENDIAN);
        }
        void Reserved_2(bool value) {
            set<bool>(39, 1, LITTLE_ENDIAN, value);
        }

        /* End of longitudinal view range of lane mark */
        float Lane_View_Range_End() const {
            return get<uint16_t>(40, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_End(float value) {
            set<uint16_t>(40, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* ENUM lane mark color */
        Lane_Color_Choices Lane_Color() const {
            return static_cast<Lane_Color_Choices>(get<uint8_t>(55, 2, LITTLE_ENDIAN));
        }
        void Lane_Color(Lane_Color_Choices value) {
            set<uint8_t>(55, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* For double lane mark, what type of DLM (ENUM) */
        Lane_DLM_Type_Choices Lane_DLM_Type() const {
            return static_cast<Lane_DLM_Type_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Lane_DLM_Type(Lane_DLM_Type_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Next_Right_Lane_A {
    private:
        void can_msg_update() {
            if(0x149 != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Right_Lane_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_Track_ID(static_cast<int>(can_data.Lane_Track_ID()));
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_Exist_Probability(can_data.Lane_Exist_Probability());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Lane_Type_Class(static_cast<int>(can_data.Lane_Type_Class()));
            Lane_View_Range_Start(can_data.Lane_View_Range_Start());
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Lane_View_Range_End(can_data.Lane_View_Range_End());
            Lane_Color(static_cast<int>(can_data.Lane_Color()));
            Lane_DLM_Type(static_cast<int>(can_data.Lane_DLM_Type()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> Lane_Track_ID;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_Exist_Probability;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Lane_Type_Class;
        adas::node::out<float> Lane_View_Range_Start;
        adas::node::out<int> Reserved_2;
        adas::node::out<float> Lane_View_Range_End;
        adas::node::out<int> Lane_Color;
        adas::node::out<int> Lane_DLM_Type;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Right_Lane_A {
    public:
        Next_Right_Lane_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> Lane_Track_ID{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_Exist_Probability{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Lane_Type_Class{0, [](){}};
        adas::node::in<float> Lane_View_Range_Start{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<float> Lane_View_Range_End{0, [](){}};
        adas::node::in<int> Lane_Color{0, [](){}};
        adas::node::in<int> Lane_DLM_Type{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Right_Lane_A data;
            data.Lane_Track_ID(Lane_Track_ID.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_Exist_Probability(Lane_Exist_Probability.get());
            data.Reserved_1(Reserved_1.get());
            data.Lane_Type_Class(eyeq4::lane::Next_Right_Lane_A::Lane_Type_Class_Choices{Lane_Type_Class.get()});
            data.Lane_View_Range_Start(Lane_View_Range_Start.get());
            data.Reserved_2(Reserved_2.get());
            data.Lane_View_Range_End(Lane_View_Range_End.get());
            data.Lane_Color(eyeq4::lane::Next_Right_Lane_A::Lane_Color_Choices{Lane_Color.get()});
            data.Lane_DLM_Type(eyeq4::lane::Next_Right_Lane_A::Lane_DLM_Type_Choices{Lane_DLM_Type.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x149};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14a */
    class Next_Right_Lane_B : public adas::can::CanData {
    public:
        Next_Right_Lane_B() : adas::can::CanData(8) {}
        explicit Next_Right_Lane_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Width of lane mark in M */
        float Line_Marker_Width() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Line_Marker_Width(float value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_0() const {
            return get<uint8_t>(8, 7, LITTLE_ENDIAN);
        }
        void Reserved_0(uint8_t value) {
            set<uint8_t>(8, 7, LITTLE_ENDIAN, value);
        }

        /* Average length of each section of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Avg_Length() const {
            return get<uint16_t>(15, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Avg_Length(float value) {
            set<uint16_t>(15, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Average gap between of sections of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Avg_Gap() const {
            return get<uint16_t>(28, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Avg_Gap(float value) {
            set<uint16_t>(28, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(41, 16, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(41, 16, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(57, 3, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, value);
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
    class Next_Right_Lane_B {
    private:
        void can_msg_update() {
            if(0x14a != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Right_Lane_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Line_Marker_Width(can_data.Line_Marker_Width());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Dash_Avg_Length(can_data.Dash_Avg_Length());
            Dash_Avg_Gap(can_data.Dash_Avg_Gap());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Line_Marker_Width;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Dash_Avg_Length;
        adas::node::out<float> Dash_Avg_Gap;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Right_Lane_B {
    public:
        Next_Right_Lane_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Line_Marker_Width{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Dash_Avg_Length{0, [](){}};
        adas::node::in<float> Dash_Avg_Gap{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Right_Lane_B data;
            data.Line_Marker_Width(Line_Marker_Width.get());
            data.Reserved_0(Reserved_0.get());
            data.Dash_Avg_Length(Dash_Avg_Length.get());
            data.Dash_Avg_Gap(Dash_Avg_Gap.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14a};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14b */
    class Next_Right_Lane_C : public adas::can::CanData {
    public:
        Next_Right_Lane_C() : adas::can::CanData(8) {}
        explicit Next_Right_Lane_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C0() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void Lane_C0(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(11, 14, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(11, 14, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C1() const {
            return get<uint16_t>(25, 10, LITTLE_ENDIAN) * static_cast<float>(0.000977) + static_cast<float>(-0.357);
        }
        void Lane_C1(float value) {
            set<uint16_t>(25, 10, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.357))/static_cast<float>(0.000977)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(35, 12, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(35, 12, LITTLE_ENDIAN, value);
        }

        /* None */
        bool Reserved_2() const {
            return get<bool>(47, 1, LITTLE_ENDIAN);
        }
        void Reserved_2(bool value) {
            set<bool>(47, 1, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_3() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_3(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_4() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_4(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Next_Right_Lane_C {
    private:
        void can_msg_update() {
            if(0x14b != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Right_Lane_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C0(can_data.Lane_C0());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C1(can_data.Lane_C1());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Reserved_3(static_cast<int>(can_data.Reserved_3()));
            Reserved_4(static_cast<int>(can_data.Reserved_4()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C0;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C1;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Reserved_3;
        adas::node::out<int> Reserved_4;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Right_Lane_C {
    public:
        Next_Right_Lane_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C0{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C1{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Reserved_3{0, [](){}};
        adas::node::in<int> Reserved_4{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Right_Lane_C data;
            data.Lane_C0(Lane_C0.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C1(Lane_C1.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Reserved_3(Reserved_3.get());
            data.Reserved_4(Reserved_4.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14b};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14c */
    class Next_Right_Lane_D : public adas::can::CanData {
    public:
        Next_Right_Lane_D() : adas::can::CanData(8) {}
        explicit Next_Right_Lane_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C2() const {
            return get<uint16_t>(0, 16, LITTLE_ENDIAN) * static_cast<float>(9.77e-07) + static_cast<float>(-0.032);
        }
        void Lane_C2(float value) {
            set<uint16_t>(0, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.032))/static_cast<float>(9.77e-07)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(16, 16, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(16, 16, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C3() const {
            return get<uint16_t>(32, 16, LITTLE_ENDIAN) * static_cast<float>(3.73e-09) + static_cast<float>(-0.000122);
        }
        void Lane_C3(float value) {
            set<uint16_t>(32, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.000122))/static_cast<float>(3.73e-09)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Next_Right_Lane_D {
    private:
        void can_msg_update() {
            if(0x14c != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Right_Lane_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C2(can_data.Lane_C2());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C3(can_data.Lane_C3());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C2;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C3;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Right_Lane_D {
    public:
        Next_Right_Lane_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C2{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C3{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Right_Lane_D data;
            data.Lane_C2(Lane_C2.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C3(Lane_C3.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14c};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14d */
    class Next_Left_Lane_A : public adas::can::CanData {
    public:
        Next_Left_Lane_A() : adas::can::CanData(8) {}
        explicit Next_Left_Lane_A(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class Lane_Type_Class_Choices {
            HOV_LANE = 11,
            DECELERATION = 10,
            BOTTS = 5,
            DLM = 4,
            ROAD_EDGE = 3,
            DASHED = 2,
            SOLID = 1,
            UNDECIDED = 0,
        };

        enum class Lane_Color_Choices {
            BLUE_GREEN = 3,
            YELLOW_ORANGE_RED = 2,
            WHITE = 1,
            UNDECIDED = 0,
        };

        enum class Lane_DLM_Type_Choices {
            UNDECIDED = 5,
            DASHED_DASHED = 4,
            SOLID_SOLID = 3,
            DASHED_SOLID = 2,
            SOLID_DASHED = 1,
            NOT_DLM = 0,
        };

        /* ID to be used for comparing frames */
        uint8_t Lane_Track_ID() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void Lane_Track_ID(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        bool Reserved_0() const {
            return get<bool>(8, 1, LITTLE_ENDIAN);
        }
        void Reserved_0(bool value) {
            set<bool>(8, 1, LITTLE_ENDIAN, value);
        }

        /* Existence probability of lane mark */
        float Lane_Exist_Probability() const {
            return get<uint8_t>(9, 7, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_Exist_Probability(float value) {
            set<uint8_t>(9, 7, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(16, 4, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(16, 4, LITTLE_ENDIAN, value);
        }

        /* ENUM of Lane Mark Type Classification */
        Lane_Type_Class_Choices Lane_Type_Class() const {
            return static_cast<Lane_Type_Class_Choices>(get<uint8_t>(20, 4, LITTLE_ENDIAN));
        }
        void Lane_Type_Class(Lane_Type_Class_Choices value) {
            set<uint8_t>(20, 4, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Start of longitudinal view range of lane mark */
        float Lane_View_Range_Start() const {
            return get<uint16_t>(24, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_Start(float value) {
            set<uint16_t>(24, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        bool Reserved_2() const {
            return get<bool>(39, 1, LITTLE_ENDIAN);
        }
        void Reserved_2(bool value) {
            set<bool>(39, 1, LITTLE_ENDIAN, value);
        }

        /* End of longitudinal view range of lane mark */
        float Lane_View_Range_End() const {
            return get<uint16_t>(40, 15, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Lane_View_Range_End(float value) {
            set<uint16_t>(40, 15, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* ENUM lane mark color */
        Lane_Color_Choices Lane_Color() const {
            return static_cast<Lane_Color_Choices>(get<uint8_t>(55, 2, LITTLE_ENDIAN));
        }
        void Lane_Color(Lane_Color_Choices value) {
            set<uint8_t>(55, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* For double lane mark, what type of DLM (ENUM) */
        Lane_DLM_Type_Choices Lane_DLM_Type() const {
            return static_cast<Lane_DLM_Type_Choices>(get<uint8_t>(57, 3, LITTLE_ENDIAN));
        }
        void Lane_DLM_Type(Lane_DLM_Type_Choices value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
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
    class Next_Left_Lane_A {
    private:
        void can_msg_update() {
            if(0x14d != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Left_Lane_A can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_Track_ID(static_cast<int>(can_data.Lane_Track_ID()));
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_Exist_Probability(can_data.Lane_Exist_Probability());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Lane_Type_Class(static_cast<int>(can_data.Lane_Type_Class()));
            Lane_View_Range_Start(can_data.Lane_View_Range_Start());
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Lane_View_Range_End(can_data.Lane_View_Range_End());
            Lane_Color(static_cast<int>(can_data.Lane_Color()));
            Lane_DLM_Type(static_cast<int>(can_data.Lane_DLM_Type()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> Lane_Track_ID;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_Exist_Probability;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Lane_Type_Class;
        adas::node::out<float> Lane_View_Range_Start;
        adas::node::out<int> Reserved_2;
        adas::node::out<float> Lane_View_Range_End;
        adas::node::out<int> Lane_Color;
        adas::node::out<int> Lane_DLM_Type;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Left_Lane_A {
    public:
        Next_Left_Lane_A() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> Lane_Track_ID{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_Exist_Probability{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Lane_Type_Class{0, [](){}};
        adas::node::in<float> Lane_View_Range_Start{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<float> Lane_View_Range_End{0, [](){}};
        adas::node::in<int> Lane_Color{0, [](){}};
        adas::node::in<int> Lane_DLM_Type{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Left_Lane_A data;
            data.Lane_Track_ID(Lane_Track_ID.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_Exist_Probability(Lane_Exist_Probability.get());
            data.Reserved_1(Reserved_1.get());
            data.Lane_Type_Class(eyeq4::lane::Next_Left_Lane_A::Lane_Type_Class_Choices{Lane_Type_Class.get()});
            data.Lane_View_Range_Start(Lane_View_Range_Start.get());
            data.Reserved_2(Reserved_2.get());
            data.Lane_View_Range_End(Lane_View_Range_End.get());
            data.Lane_Color(eyeq4::lane::Next_Left_Lane_A::Lane_Color_Choices{Lane_Color.get()});
            data.Lane_DLM_Type(eyeq4::lane::Next_Left_Lane_A::Lane_DLM_Type_Choices{Lane_DLM_Type.get()});
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14d};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14e */
    class Next_Left_Lane_B : public adas::can::CanData {
    public:
        Next_Left_Lane_B() : adas::can::CanData(8) {}
        explicit Next_Left_Lane_B(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Width of lane mark in M */
        float Line_Marker_Width() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Line_Marker_Width(float value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint8_t Reserved_0() const {
            return get<uint8_t>(8, 7, LITTLE_ENDIAN);
        }
        void Reserved_0(uint8_t value) {
            set<uint8_t>(8, 7, LITTLE_ENDIAN, value);
        }

        /* Average length of each section of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Avg_Length() const {
            return get<uint16_t>(15, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Avg_Length(float value) {
            set<uint16_t>(15, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* Average gap between of sections of dashed line when lane mark is dashed in CM. This is a multi-frame signal. */
        float Dash_Avg_Gap() const {
            return get<uint16_t>(28, 13, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void Dash_Avg_Gap(float value) {
            set<uint16_t>(28, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(41, 16, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(41, 16, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(57, 3, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(57, 3, LITTLE_ENDIAN, value);
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
    class Next_Left_Lane_B {
    private:
        void can_msg_update() {
            if(0x14e != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Left_Lane_B can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Line_Marker_Width(can_data.Line_Marker_Width());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Dash_Avg_Length(can_data.Dash_Avg_Length());
            Dash_Avg_Gap(can_data.Dash_Avg_Gap());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Line_Marker_Width;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Dash_Avg_Length;
        adas::node::out<float> Dash_Avg_Gap;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Left_Lane_B {
    public:
        Next_Left_Lane_B() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Line_Marker_Width{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Dash_Avg_Length{0, [](){}};
        adas::node::in<float> Dash_Avg_Gap{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Left_Lane_B data;
            data.Line_Marker_Width(Line_Marker_Width.get());
            data.Reserved_0(Reserved_0.get());
            data.Dash_Avg_Length(Dash_Avg_Length.get());
            data.Dash_Avg_Gap(Dash_Avg_Gap.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14e};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x14f */
    class Next_Left_Lane_C : public adas::can::CanData {
    public:
        Next_Left_Lane_C() : adas::can::CanData(8) {}
        explicit Next_Left_Lane_C(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C0() const {
            return get<uint16_t>(0, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void Lane_C0(float value) {
            set<uint16_t>(0, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* None */
        uint16_t Reserved_2() const {
            return get<uint16_t>(11, 14, LITTLE_ENDIAN);
        }
        void Reserved_2(uint16_t value) {
            set<uint16_t>(11, 14, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C1() const {
            return get<uint16_t>(25, 10, LITTLE_ENDIAN) * static_cast<float>(0.000977) + static_cast<float>(-0.357);
        }
        void Lane_C1(float value) {
            set<uint16_t>(25, 10, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.357))/static_cast<float>(0.000977)));
        }

        /* None */
        uint16_t Reserved_1() const {
            return get<uint16_t>(35, 12, LITTLE_ENDIAN);
        }
        void Reserved_1(uint16_t value) {
            set<uint16_t>(35, 12, LITTLE_ENDIAN, value);
        }

        /* None */
        bool Reserved_5() const {
            return get<bool>(47, 1, LITTLE_ENDIAN);
        }
        void Reserved_5(bool value) {
            set<bool>(47, 1, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_3() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_3(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_4() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_4(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Next_Left_Lane_C {
    private:
        void can_msg_update() {
            if(0x14f != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Left_Lane_C can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C0(can_data.Lane_C0());
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Lane_C1(can_data.Lane_C1());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_5(static_cast<int>(can_data.Reserved_5()));
            Reserved_3(static_cast<int>(can_data.Reserved_3()));
            Reserved_4(static_cast<int>(can_data.Reserved_4()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C0;
        adas::node::out<int> Reserved_2;
        adas::node::out<float> Lane_C1;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_5;
        adas::node::out<int> Reserved_3;
        adas::node::out<int> Reserved_4;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Left_Lane_C {
    public:
        Next_Left_Lane_C() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C0{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<float> Lane_C1{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_5{0, [](){}};
        adas::node::in<int> Reserved_3{0, [](){}};
        adas::node::in<int> Reserved_4{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Left_Lane_C data;
            data.Lane_C0(Lane_C0.get());
            data.Reserved_2(Reserved_2.get());
            data.Lane_C1(Lane_C1.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_5(Reserved_5.get());
            data.Reserved_3(Reserved_3.get());
            data.Reserved_4(Reserved_4.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x14f};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x150 */
    class Next_Left_Lane_D : public adas::can::CanData {
    public:
        Next_Left_Lane_D() : adas::can::CanData(8) {}
        explicit Next_Left_Lane_D(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C2() const {
            return get<uint16_t>(0, 16, LITTLE_ENDIAN) * static_cast<float>(9.77e-07) + static_cast<float>(-0.032);
        }
        void Lane_C2(float value) {
            set<uint16_t>(0, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.032))/static_cast<float>(9.77e-07)));
        }

        /* None */
        uint16_t Reserved_0() const {
            return get<uint16_t>(16, 16, LITTLE_ENDIAN);
        }
        void Reserved_0(uint16_t value) {
            set<uint16_t>(16, 16, LITTLE_ENDIAN, value);
        }

        /* Ci is coefficient corresponding to variable with power of 'i'锛孭ositive on left turn */
        float Lane_C3() const {
            return get<uint16_t>(32, 16, LITTLE_ENDIAN) * static_cast<float>(3.73e-09) + static_cast<float>(-0.000122);
        }
        void Lane_C3(float value) {
            set<uint16_t>(32, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-0.000122))/static_cast<float>(3.73e-09)));
        }

        /* None */
        uint8_t Reserved_1() const {
            return get<uint8_t>(48, 8, LITTLE_ENDIAN);
        }
        void Reserved_1(uint8_t value) {
            set<uint8_t>(48, 8, LITTLE_ENDIAN, value);
        }

        /* None */
        uint8_t Reserved_2() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void Reserved_2(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
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
    class Next_Left_Lane_D {
    private:
        void can_msg_update() {
            if(0x150 != can_msg.get().can_id)
                return;
            eyeq4::lane::Next_Left_Lane_D can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            Lane_C2(can_data.Lane_C2());
            Reserved_0(static_cast<int>(can_data.Reserved_0()));
            Lane_C3(can_data.Lane_C3());
            Reserved_1(static_cast<int>(can_data.Reserved_1()));
            Reserved_2(static_cast<int>(can_data.Reserved_2()));
            Rolling_Counter(static_cast<int>(can_data.Rolling_Counter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> Lane_C2;
        adas::node::out<int> Reserved_0;
        adas::node::out<float> Lane_C3;
        adas::node::out<int> Reserved_1;
        adas::node::out<int> Reserved_2;
        adas::node::out<int> Rolling_Counter;
    };
    }

    namespace pack {
    class Next_Left_Lane_D {
    public:
        Next_Left_Lane_D() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> Lane_C2{0, [](){}};
        adas::node::in<int> Reserved_0{0, [](){}};
        adas::node::in<float> Lane_C3{0, [](){}};
        adas::node::in<int> Reserved_1{0, [](){}};
        adas::node::in<int> Reserved_2{0, [](){}};
        adas::node::in<int> Rolling_Counter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            eyeq4::lane::Next_Left_Lane_D data;
            data.Lane_C2(Lane_C2.get());
            data.Reserved_0(Reserved_0.get());
            data.Lane_C3(Lane_C3.get());
            data.Reserved_1(Reserved_1.get());
            data.Reserved_2(Reserved_2.get());
            data.Rolling_Counter(Rolling_Counter.get());
            can_frame frame{.can_id=0x150};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

}

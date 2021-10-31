#pragma once
#include <adas/can.h>
#include <adas/node.hpp>
#include <chrono>
#include <algorithm>
namespace adas::ehs3 {
    /* None */
    /* id: 0x5c8 */
    class DCU1 : public adas::can::CanData {
    public:
        DCU1() : adas::can::CanData(8) {}
        explicit DCU1(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class DCU1_TargetDistanceStage_Choices {
            DistanceStage4 = 4,
            DistanceStage3 = 3,
            DistanceStage2 = 2,
            DistanceStage1 = 1,
            NoGap = 0,
        };

        enum class DCU1_ObjectCaptured_Choices {
            Captured = 1,
            NoCaptured = 0,
        };

        enum class DCU1_FCWWarning_Choices {
            CautionaryAlert = 2,
            ImminentAlert = 1,
            NoAlert = 0,
        };

        enum class DCU1_PleaseTakeOver_Choices {
            Intervention = 1,
            NoIntervention = 0,
        };

        enum class DCU1_AEBIntervention_Choices {
            Intervention = 1,
            NoIntervention = 0,
        };

        enum class DCU1_LanesDisplay_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class DCU1_LeftLaneCaptured_Choices {
            Captured = 1,
            NoCaptured = 0,
        };

        enum class DCU1_RightLaneCaptured_Choices {
            Captured = 1,
            NoCaptured = 0,
        };

        enum class DCU1_ACC_Active_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class DCU1_LKS_Active_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class DCU1_DSMWarning_Choices {
            Warning2 = 2,
            Warning1 = 1,
            Inactive = 0,
        };

        enum class DCU1_LDWWarning_Choices {
            RightWarning = 2,
            LeftWarning = 1,
            Inactive = 0,
        };

        enum class DCU1_TSRWarning_Choices {
            Warning2 = 2,
            Warning1 = 1,
            Inactive = 0,
        };

        enum class DCU1_AEB_Active_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class DCU1_ACT_Active_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class DCU1_APA_Active_Choices {
            Active = 1,
            Inactive = 0,
        };

        /* 校验和 */
        uint8_t DCU1_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void DCU1_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 设定巡航速度 */
        uint8_t DCU1_TargetSpeed() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN);
        }
        void DCU1_TargetSpeed(uint8_t value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, value);
        }

        /* 设定跟车距离 */
        DCU1_TargetDistanceStage_Choices DCU1_TargetDistanceStage() const {
            return static_cast<DCU1_TargetDistanceStage_Choices>(get<uint8_t>(16, 3, LITTLE_ENDIAN));
        }
        void DCU1_TargetDistanceStage(DCU1_TargetDistanceStage_Choices value) {
            set<uint8_t>(16, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 捕获车辆 */
        DCU1_ObjectCaptured_Choices DCU1_ObjectCaptured() const {
            return static_cast<DCU1_ObjectCaptured_Choices>(get<bool>(19, 1, LITTLE_ENDIAN));
        }
        void DCU1_ObjectCaptured(DCU1_ObjectCaptured_Choices value) {
            set<bool>(19, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 前车碰撞报警 */
        DCU1_FCWWarning_Choices DCU1_FCWWarning() const {
            return static_cast<DCU1_FCWWarning_Choices>(get<uint8_t>(20, 2, LITTLE_ENDIAN));
        }
        void DCU1_FCWWarning(DCU1_FCWWarning_Choices value) {
            set<uint8_t>(20, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 提示请求接管 */
        DCU1_PleaseTakeOver_Choices DCU1_PleaseTakeOver() const {
            return static_cast<DCU1_PleaseTakeOver_Choices>(get<bool>(22, 1, LITTLE_ENDIAN));
        }
        void DCU1_PleaseTakeOver(DCU1_PleaseTakeOver_Choices value) {
            set<bool>(22, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* AEB制动警示 */
        DCU1_AEBIntervention_Choices DCU1_AEBIntervention() const {
            return static_cast<DCU1_AEBIntervention_Choices>(get<bool>(23, 1, LITTLE_ENDIAN));
        }
        void DCU1_AEBIntervention(DCU1_AEBIntervention_Choices value) {
            set<bool>(23, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 激活车道线显示，注意会覆盖ACC显示 */
        DCU1_LanesDisplay_Choices DCU1_LanesDisplay() const {
            return static_cast<DCU1_LanesDisplay_Choices>(get<bool>(24, 1, LITTLE_ENDIAN));
        }
        void DCU1_LanesDisplay(DCU1_LanesDisplay_Choices value) {
            set<bool>(24, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 捕获左车道线 */
        DCU1_LeftLaneCaptured_Choices DCU1_LeftLaneCaptured() const {
            return static_cast<DCU1_LeftLaneCaptured_Choices>(get<bool>(25, 1, LITTLE_ENDIAN));
        }
        void DCU1_LeftLaneCaptured(DCU1_LeftLaneCaptured_Choices value) {
            set<bool>(25, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 捕获右车道线 */
        DCU1_RightLaneCaptured_Choices DCU1_RightLaneCaptured() const {
            return static_cast<DCU1_RightLaneCaptured_Choices>(get<bool>(26, 1, LITTLE_ENDIAN));
        }
        void DCU1_RightLaneCaptured(DCU1_RightLaneCaptured_Choices value) {
            set<bool>(26, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 自动适应巡航 */
        DCU1_ACC_Active_Choices DCU1_ACC_Active() const {
            return static_cast<DCU1_ACC_Active_Choices>(get<uint8_t>(28, 2, LITTLE_ENDIAN));
        }
        void DCU1_ACC_Active(DCU1_ACC_Active_Choices value) {
            set<uint8_t>(28, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 自动车道保持 */
        DCU1_LKS_Active_Choices DCU1_LKS_Active() const {
            return static_cast<DCU1_LKS_Active_Choices>(get<uint8_t>(30, 2, LITTLE_ENDIAN));
        }
        void DCU1_LKS_Active(DCU1_LKS_Active_Choices value) {
            set<uint8_t>(30, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 疲劳驾驶告警 */
        DCU1_DSMWarning_Choices DCU1_DSMWarning() const {
            return static_cast<DCU1_DSMWarning_Choices>(get<uint8_t>(32, 2, LITTLE_ENDIAN));
        }
        void DCU1_DSMWarning(DCU1_DSMWarning_Choices value) {
            set<uint8_t>(32, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 车道线偏离告警 */
        DCU1_LDWWarning_Choices DCU1_LDWWarning() const {
            return static_cast<DCU1_LDWWarning_Choices>(get<uint8_t>(34, 2, LITTLE_ENDIAN));
        }
        void DCU1_LDWWarning(DCU1_LDWWarning_Choices value) {
            set<uint8_t>(34, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 超速告警 */
        DCU1_TSRWarning_Choices DCU1_TSRWarning() const {
            return static_cast<DCU1_TSRWarning_Choices>(get<uint8_t>(36, 2, LITTLE_ENDIAN));
        }
        void DCU1_TSRWarning(DCU1_TSRWarning_Choices value) {
            set<uint8_t>(36, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* TSR限定车速 */
        uint8_t DCU1_TSRLimitSpeed() const {
            return get<uint8_t>(40, 8, LITTLE_ENDIAN);
        }
        void DCU1_TSRLimitSpeed(uint8_t value) {
            set<uint8_t>(40, 8, LITTLE_ENDIAN, value);
        }

        /* 自动紧急制动 */
        DCU1_AEB_Active_Choices DCU1_AEB_Active() const {
            return static_cast<DCU1_AEB_Active_Choices>(get<uint8_t>(48, 2, LITTLE_ENDIAN));
        }
        void DCU1_AEB_Active(DCU1_AEB_Active_Choices value) {
            set<uint8_t>(48, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 自动换道 */
        DCU1_ACT_Active_Choices DCU1_ACT_Active() const {
            return static_cast<DCU1_ACT_Active_Choices>(get<uint8_t>(50, 2, LITTLE_ENDIAN));
        }
        void DCU1_ACT_Active(DCU1_ACT_Active_Choices value) {
            set<uint8_t>(50, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 自动泊车 */
        DCU1_APA_Active_Choices DCU1_APA_Active() const {
            return static_cast<DCU1_APA_Active_Choices>(get<uint8_t>(52, 2, LITTLE_ENDIAN));
        }
        void DCU1_APA_Active(DCU1_APA_Active_Choices value) {
            set<uint8_t>(52, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 生命信号 */
        uint8_t DCU1_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void DCU1_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class DCU1 {
    private:
        void can_msg_update() {
            if(0x5c8 != can_msg.get().can_id)
                return;
            adas::ehs3::DCU1 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            DCU1_Checksum(static_cast<int>(can_data.DCU1_Checksum()));
            DCU1_TargetSpeed(static_cast<int>(can_data.DCU1_TargetSpeed()));
            DCU1_TargetDistanceStage(static_cast<int>(can_data.DCU1_TargetDistanceStage()));
            DCU1_ObjectCaptured(static_cast<int>(can_data.DCU1_ObjectCaptured()));
            DCU1_FCWWarning(static_cast<int>(can_data.DCU1_FCWWarning()));
            DCU1_PleaseTakeOver(static_cast<int>(can_data.DCU1_PleaseTakeOver()));
            DCU1_AEBIntervention(static_cast<int>(can_data.DCU1_AEBIntervention()));
            DCU1_LanesDisplay(static_cast<int>(can_data.DCU1_LanesDisplay()));
            DCU1_LeftLaneCaptured(static_cast<int>(can_data.DCU1_LeftLaneCaptured()));
            DCU1_RightLaneCaptured(static_cast<int>(can_data.DCU1_RightLaneCaptured()));
            DCU1_ACC_Active(static_cast<int>(can_data.DCU1_ACC_Active()));
            DCU1_LKS_Active(static_cast<int>(can_data.DCU1_LKS_Active()));
            DCU1_DSMWarning(static_cast<int>(can_data.DCU1_DSMWarning()));
            DCU1_LDWWarning(static_cast<int>(can_data.DCU1_LDWWarning()));
            DCU1_TSRWarning(static_cast<int>(can_data.DCU1_TSRWarning()));
            DCU1_TSRLimitSpeed(static_cast<int>(can_data.DCU1_TSRLimitSpeed()));
            DCU1_AEB_Active(static_cast<int>(can_data.DCU1_AEB_Active()));
            DCU1_ACT_Active(static_cast<int>(can_data.DCU1_ACT_Active()));
            DCU1_APA_Active(static_cast<int>(can_data.DCU1_APA_Active()));
            DCU1_LiveCounter(static_cast<int>(can_data.DCU1_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> DCU1_Checksum;
        adas::node::out<int> DCU1_TargetSpeed;
        adas::node::out<int> DCU1_TargetDistanceStage;
        adas::node::out<int> DCU1_ObjectCaptured;
        adas::node::out<int> DCU1_FCWWarning;
        adas::node::out<int> DCU1_PleaseTakeOver;
        adas::node::out<int> DCU1_AEBIntervention;
        adas::node::out<int> DCU1_LanesDisplay;
        adas::node::out<int> DCU1_LeftLaneCaptured;
        adas::node::out<int> DCU1_RightLaneCaptured;
        adas::node::out<int> DCU1_ACC_Active;
        adas::node::out<int> DCU1_LKS_Active;
        adas::node::out<int> DCU1_DSMWarning;
        adas::node::out<int> DCU1_LDWWarning;
        adas::node::out<int> DCU1_TSRWarning;
        adas::node::out<int> DCU1_TSRLimitSpeed;
        adas::node::out<int> DCU1_AEB_Active;
        adas::node::out<int> DCU1_ACT_Active;
        adas::node::out<int> DCU1_APA_Active;
        adas::node::out<int> DCU1_LiveCounter;
    };
    }

    namespace pack {
    class DCU1 {
    public:
        DCU1() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> DCU1_Checksum{0, [](){}};
        adas::node::in<int> DCU1_TargetSpeed{0, [](){}};
        adas::node::in<int> DCU1_TargetDistanceStage{0, [](){}};
        adas::node::in<int> DCU1_ObjectCaptured{0, [](){}};
        adas::node::in<int> DCU1_FCWWarning{0, [](){}};
        adas::node::in<int> DCU1_PleaseTakeOver{0, [](){}};
        adas::node::in<int> DCU1_AEBIntervention{0, [](){}};
        adas::node::in<int> DCU1_LanesDisplay{0, [](){}};
        adas::node::in<int> DCU1_LeftLaneCaptured{0, [](){}};
        adas::node::in<int> DCU1_RightLaneCaptured{0, [](){}};
        adas::node::in<int> DCU1_ACC_Active{0, [](){}};
        adas::node::in<int> DCU1_LKS_Active{0, [](){}};
        adas::node::in<int> DCU1_DSMWarning{0, [](){}};
        adas::node::in<int> DCU1_LDWWarning{0, [](){}};
        adas::node::in<int> DCU1_TSRWarning{0, [](){}};
        adas::node::in<int> DCU1_TSRLimitSpeed{0, [](){}};
        adas::node::in<int> DCU1_AEB_Active{0, [](){}};
        adas::node::in<int> DCU1_ACT_Active{0, [](){}};
        adas::node::in<int> DCU1_APA_Active{0, [](){}};
        adas::node::in<int> DCU1_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::DCU1 data;
            data.DCU1_Checksum(DCU1_Checksum.get());
            data.DCU1_TargetSpeed(DCU1_TargetSpeed.get());
            data.DCU1_TargetDistanceStage(adas::ehs3::DCU1::DCU1_TargetDistanceStage_Choices{DCU1_TargetDistanceStage.get()});
            data.DCU1_ObjectCaptured(adas::ehs3::DCU1::DCU1_ObjectCaptured_Choices{DCU1_ObjectCaptured.get()});
            data.DCU1_FCWWarning(adas::ehs3::DCU1::DCU1_FCWWarning_Choices{DCU1_FCWWarning.get()});
            data.DCU1_PleaseTakeOver(adas::ehs3::DCU1::DCU1_PleaseTakeOver_Choices{DCU1_PleaseTakeOver.get()});
            data.DCU1_AEBIntervention(adas::ehs3::DCU1::DCU1_AEBIntervention_Choices{DCU1_AEBIntervention.get()});
            data.DCU1_LanesDisplay(adas::ehs3::DCU1::DCU1_LanesDisplay_Choices{DCU1_LanesDisplay.get()});
            data.DCU1_LeftLaneCaptured(adas::ehs3::DCU1::DCU1_LeftLaneCaptured_Choices{DCU1_LeftLaneCaptured.get()});
            data.DCU1_RightLaneCaptured(adas::ehs3::DCU1::DCU1_RightLaneCaptured_Choices{DCU1_RightLaneCaptured.get()});
            data.DCU1_ACC_Active(adas::ehs3::DCU1::DCU1_ACC_Active_Choices{DCU1_ACC_Active.get()});
            data.DCU1_LKS_Active(adas::ehs3::DCU1::DCU1_LKS_Active_Choices{DCU1_LKS_Active.get()});
            data.DCU1_DSMWarning(adas::ehs3::DCU1::DCU1_DSMWarning_Choices{DCU1_DSMWarning.get()});
            data.DCU1_LDWWarning(adas::ehs3::DCU1::DCU1_LDWWarning_Choices{DCU1_LDWWarning.get()});
            data.DCU1_TSRWarning(adas::ehs3::DCU1::DCU1_TSRWarning_Choices{DCU1_TSRWarning.get()});
            data.DCU1_TSRLimitSpeed(DCU1_TSRLimitSpeed.get());
            data.DCU1_AEB_Active(adas::ehs3::DCU1::DCU1_AEB_Active_Choices{DCU1_AEB_Active.get()});
            data.DCU1_ACT_Active(adas::ehs3::DCU1::DCU1_ACT_Active_Choices{DCU1_ACT_Active.get()});
            data.DCU1_APA_Active(adas::ehs3::DCU1::DCU1_APA_Active_Choices{DCU1_APA_Active.get()});
            data.DCU1_LiveCounter(DCU1_LiveCounter.get());
            can_frame frame{.can_id=0x5c8};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x68d */
    class VCU4 : public adas::can::CanData {
    public:
        VCU4() : adas::can::CanData(8) {}
        explicit VCU4(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* 校验和 */
        uint8_t VCU4_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU4_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 方向盘转矩 */
        float VCU4_HandSteeringTorque() const {
            return get<uint16_t>(8, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void VCU4_HandSteeringTorque(float value) {
            set<uint16_t>(8, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* EPS驱动转矩 */
        float VCU4_SteeringInputTorque() const {
            return get<uint16_t>(19, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void VCU4_SteeringInputTorque(float value) {
            set<uint16_t>(19, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* 驱动电机最大可用扭矩 */
        float VCU4_MAMTorque() const {
            return get<uint16_t>(30, 13, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(0);
        }
        void VCU4_MAMTorque(float value) {
            set<uint16_t>(30, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.1)));
        }

        /* ACC请求扭矩 */
        float VCU4_RequestTorque() const {
            return get<uint16_t>(43, 13, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(0);
        }
        void VCU4_RequestTorque(float value) {
            set<uint16_t>(43, 13, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.1)));
        }

        /* 转向状态机 */
        uint8_t VCU4_SteeringStateMachine() const {
            return get<uint8_t>(56, 4, LITTLE_ENDIAN);
        }
        void VCU4_SteeringStateMachine(uint8_t value) {
            set<uint8_t>(56, 4, LITTLE_ENDIAN, value);
        }

        /* 生命信号 */
        uint8_t VCU4_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU4_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU4 {
    private:
        void can_msg_update() {
            if(0x68d != can_msg.get().can_id)
                return;
            adas::ehs3::VCU4 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU4_Checksum(static_cast<int>(can_data.VCU4_Checksum()));
            VCU4_HandSteeringTorque(can_data.VCU4_HandSteeringTorque());
            VCU4_SteeringInputTorque(can_data.VCU4_SteeringInputTorque());
            VCU4_MAMTorque(can_data.VCU4_MAMTorque());
            VCU4_RequestTorque(can_data.VCU4_RequestTorque());
            VCU4_SteeringStateMachine(static_cast<int>(can_data.VCU4_SteeringStateMachine()));
            VCU4_LiveCounter(static_cast<int>(can_data.VCU4_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU4_Checksum;
        adas::node::out<float> VCU4_HandSteeringTorque;
        adas::node::out<float> VCU4_SteeringInputTorque;
        adas::node::out<float> VCU4_MAMTorque;
        adas::node::out<float> VCU4_RequestTorque;
        adas::node::out<int> VCU4_SteeringStateMachine;
        adas::node::out<int> VCU4_LiveCounter;
    };
    }

    namespace pack {
    class VCU4 {
    public:
        VCU4() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU4_Checksum{0, [](){}};
        adas::node::in<float> VCU4_HandSteeringTorque{0, [](){}};
        adas::node::in<float> VCU4_SteeringInputTorque{0, [](){}};
        adas::node::in<float> VCU4_MAMTorque{0, [](){}};
        adas::node::in<float> VCU4_RequestTorque{0, [](){}};
        adas::node::in<int> VCU4_SteeringStateMachine{0, [](){}};
        adas::node::in<int> VCU4_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU4 data;
            data.VCU4_Checksum(VCU4_Checksum.get());
            data.VCU4_HandSteeringTorque(VCU4_HandSteeringTorque.get());
            data.VCU4_SteeringInputTorque(VCU4_SteeringInputTorque.get());
            data.VCU4_MAMTorque(VCU4_MAMTorque.get());
            data.VCU4_RequestTorque(VCU4_RequestTorque.get());
            data.VCU4_SteeringStateMachine(VCU4_SteeringStateMachine.get());
            data.VCU4_LiveCounter(VCU4_LiveCounter.get());
            can_frame frame{.can_id=0x68d};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x68e */
    class VCU5 : public adas::can::CanData {
    public:
        VCU5() : adas::can::CanData(8) {}
        explicit VCU5(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* 校验和 */
        uint8_t VCU5_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU5_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 油门开度 */
        float VCU5_AccelPedalPosition() const {
            return get<uint8_t>(8, 8, LITTLE_ENDIAN) * static_cast<float>(0.4) + static_cast<float>(0);
        }
        void VCU5_AccelPedalPosition(float value) {
            set<uint8_t>(8, 8, LITTLE_ENDIAN, static_cast<uint8_t>((value-(0))/static_cast<float>(0.4)));
        }

        /* 制动主缸压力 */
        float VCU5_MasterCylinderPressure() const {
            return get<uint16_t>(16, 10, LITTLE_ENDIAN) * static_cast<float>(0.2) + static_cast<float>(0);
        }
        void VCU5_MasterCylinderPressure(float value) {
            set<uint16_t>(16, 10, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.2)));
        }

        /* 驱动纵向实时扭矩 */
        float VCU5_ActuateTorque() const {
            return get<uint16_t>(26, 14, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(-800);
        }
        void VCU5_ActuateTorque(float value) {
            set<uint16_t>(26, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-800))/static_cast<float>(0.1)));
        }

        /* 软件版本号 */
        uint8_t VCU5_Version() const {
            return get<uint8_t>(40, 8, LITTLE_ENDIAN);
        }
        void VCU5_Version(uint8_t value) {
            set<uint8_t>(40, 8, LITTLE_ENDIAN, value);
        }

        /* 剩余开机次数(4095=永久) */
        uint16_t VCU5_RemainingTimes() const {
            return get<uint16_t>(48, 12, LITTLE_ENDIAN);
        }
        void VCU5_RemainingTimes(uint16_t value) {
            set<uint16_t>(48, 12, LITTLE_ENDIAN, value);
        }

        /* 生命信号 */
        uint8_t VCU5_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU5_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU5 {
    private:
        void can_msg_update() {
            if(0x68e != can_msg.get().can_id)
                return;
            adas::ehs3::VCU5 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU5_Checksum(static_cast<int>(can_data.VCU5_Checksum()));
            VCU5_AccelPedalPosition(can_data.VCU5_AccelPedalPosition());
            VCU5_MasterCylinderPressure(can_data.VCU5_MasterCylinderPressure());
            VCU5_ActuateTorque(can_data.VCU5_ActuateTorque());
            VCU5_Version(static_cast<int>(can_data.VCU5_Version()));
            VCU5_RemainingTimes(static_cast<int>(can_data.VCU5_RemainingTimes()));
            VCU5_LiveCounter(static_cast<int>(can_data.VCU5_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU5_Checksum;
        adas::node::out<float> VCU5_AccelPedalPosition;
        adas::node::out<float> VCU5_MasterCylinderPressure;
        adas::node::out<float> VCU5_ActuateTorque;
        adas::node::out<int> VCU5_Version;
        adas::node::out<int> VCU5_RemainingTimes;
        adas::node::out<int> VCU5_LiveCounter;
    };
    }

    namespace pack {
    class VCU5 {
    public:
        VCU5() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU5_Checksum{0, [](){}};
        adas::node::in<float> VCU5_AccelPedalPosition{0, [](){}};
        adas::node::in<float> VCU5_MasterCylinderPressure{0, [](){}};
        adas::node::in<float> VCU5_ActuateTorque{0, [](){}};
        adas::node::in<int> VCU5_Version{0, [](){}};
        adas::node::in<int> VCU5_RemainingTimes{0, [](){}};
        adas::node::in<int> VCU5_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU5 data;
            data.VCU5_Checksum(VCU5_Checksum.get());
            data.VCU5_AccelPedalPosition(VCU5_AccelPedalPosition.get());
            data.VCU5_MasterCylinderPressure(VCU5_MasterCylinderPressure.get());
            data.VCU5_ActuateTorque(VCU5_ActuateTorque.get());
            data.VCU5_Version(VCU5_Version.get());
            data.VCU5_RemainingTimes(VCU5_RemainingTimes.get());
            data.VCU5_LiveCounter(VCU5_LiveCounter.get());
            can_frame frame{.can_id=0x68e};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* None */
    /* id: 0x5c1 */
    class ACU2 : public adas::can::CanData {
    public:
        ACU2() : adas::can::CanData(8) {}
        explicit ACU2(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class ACU2_SteeringRequestSt_Choices {
            TorqueRequest = 2,
            AngleRequest = 1,
            NoRequest = 0,
        };

        /* 校验和 */
        uint8_t ACU2_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void ACU2_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 横向请求 */
        ACU2_SteeringRequestSt_Choices ACU2_SteeringRequestSt() const {
            return static_cast<ACU2_SteeringRequestSt_Choices>(get<uint8_t>(8, 2, LITTLE_ENDIAN));
        }
        void ACU2_SteeringRequestSt(ACU2_SteeringRequestSt_Choices value) {
            set<uint8_t>(8, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 屏蔽车速，角度控制需设置 */
        bool ACU2_MaskVehicleSpeed() const {
            return get<bool>(10, 1, LITTLE_ENDIAN);
        }
        void ACU2_MaskVehicleSpeed(bool value) {
            set<bool>(10, 1, LITTLE_ENDIAN, value);
        }

        /* 请求的方向盘转角 */
        int ACU2_SteeringAngleRequest() const {
            return get<uint16_t>(12, 11, LITTLE_ENDIAN) + static_cast<int>(-600);
        }
        void ACU2_SteeringAngleRequest(int value) {
            set<uint16_t>(12, 11, LITTLE_ENDIAN, static_cast<uint16_t>(value-(-600)));
        }

        /* 请求的方向盘转速 */
        uint16_t ACU2_SteeringSpeedRequest() const {
            return get<uint16_t>(23, 9, LITTLE_ENDIAN);
        }
        void ACU2_SteeringSpeedRequest(uint16_t value) {
            set<uint16_t>(23, 9, LITTLE_ENDIAN, value);
        }

        /* 请求的EPS转矩 */
        float ACU2_SteeringTorqueRequest() const {
            return get<uint16_t>(32, 11, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-10);
        }
        void ACU2_SteeringTorqueRequest(float value) {
            set<uint16_t>(32, 11, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-10))/static_cast<float>(0.01)));
        }

        /* 生命信号 */
        uint8_t ACU2_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void ACU2_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ACU2 {
    private:
        void can_msg_update() {
            if(0x5c1 != can_msg.get().can_id)
                return;
            adas::ehs3::ACU2 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            ACU2_Checksum(static_cast<int>(can_data.ACU2_Checksum()));
            ACU2_SteeringRequestSt(static_cast<int>(can_data.ACU2_SteeringRequestSt()));
            ACU2_MaskVehicleSpeed(static_cast<int>(can_data.ACU2_MaskVehicleSpeed()));
            ACU2_SteeringAngleRequest(static_cast<int>(can_data.ACU2_SteeringAngleRequest()));
            ACU2_SteeringSpeedRequest(static_cast<int>(can_data.ACU2_SteeringSpeedRequest()));
            ACU2_SteeringTorqueRequest(can_data.ACU2_SteeringTorqueRequest());
            ACU2_LiveCounter(static_cast<int>(can_data.ACU2_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> ACU2_Checksum;
        adas::node::out<int> ACU2_SteeringRequestSt;
        adas::node::out<int> ACU2_MaskVehicleSpeed;
        adas::node::out<int> ACU2_SteeringAngleRequest;
        adas::node::out<int> ACU2_SteeringSpeedRequest;
        adas::node::out<float> ACU2_SteeringTorqueRequest;
        adas::node::out<int> ACU2_LiveCounter;
    };
    }

    namespace pack {
    class ACU2 {
    public:
        ACU2() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> ACU2_Checksum{0, [](){}};
        adas::node::in<int> ACU2_SteeringRequestSt{0, [](){}};
        adas::node::in<int> ACU2_MaskVehicleSpeed{0, [](){}};
        adas::node::in<int> ACU2_SteeringAngleRequest{0, [](){}};
        adas::node::in<int> ACU2_SteeringSpeedRequest{0, [](){}};
        adas::node::in<float> ACU2_SteeringTorqueRequest{0, [](){}};
        adas::node::in<int> ACU2_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::ACU2 data;
            data.ACU2_Checksum(ACU2_Checksum.get());
            data.ACU2_SteeringRequestSt(adas::ehs3::ACU2::ACU2_SteeringRequestSt_Choices{ACU2_SteeringRequestSt.get()});
            data.ACU2_MaskVehicleSpeed(ACU2_MaskVehicleSpeed.get());
            data.ACU2_SteeringAngleRequest(ACU2_SteeringAngleRequest.get());
            data.ACU2_SteeringSpeedRequest(ACU2_SteeringSpeedRequest.get());
            data.ACU2_SteeringTorqueRequest(ACU2_SteeringTorqueRequest.get());
            data.ACU2_LiveCounter(ACU2_LiveCounter.get());
            can_frame frame{.can_id=0x5c1};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Control Report */
    /* id: 0x68c */
    class VCU3 : public adas::can::CanData {
    public:
        VCU3() : adas::can::CanData(8) {}
        explicit VCU3(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class VCU3_BrakingAutoControlSt_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU3_BrakingFailureSt_Choices {
            ESPandHCUFail = 4,
            YRSFail = 3,
            SpeedSensorFail = 2,
            ESPFail = 1,
            NoFail = 0,
        };

        enum class VCU3_BrakingTakeOverSt_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU3_ValidityCO_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_ValidityCCO_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_DrivingAutoControlSt_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU3_DrivingFailureSt_Choices {
            YRSFail = 3,
            SpeedSensorFail = 2,
            HCUFail = 1,
            NoFail = 0,
        };

        enum class VCU3_DrivingTakeOverSt_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU3_ValidityEXT_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_ValidityCEXT_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_SteeringAutoControlSt_Choices {
            TorqueActive = 2,
            AngleActive = 1,
            Inactive = 0,
        };

        enum class VCU3_SteeringFailureSt_Choices {
            LKSFail = 4,
            APAFail = 3,
            SASFail = 2,
            EPSFail = 1,
            NoFail = 0,
        };

        enum class VCU3_SteeringTakeOverSt_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU3_ValidityEPS_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_ValidityCEPS_Choices {
            Deactive = 1,
            Active = 0,
        };

        enum class VCU3_SystemControlSt_Choices {
            BothActive = 3,
            AccelActive = 2,
            SteerActive = 1,
            Inactive = 0,
        };

        /* 校验和 */
        uint8_t VCU3_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU3_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 制动线控状态 */
        VCU3_BrakingAutoControlSt_Choices VCU3_BrakingAutoControlSt() const {
            return static_cast<VCU3_BrakingAutoControlSt_Choices>(get<uint8_t>(8, 2, LITTLE_ENDIAN));
        }
        void VCU3_BrakingAutoControlSt(VCU3_BrakingAutoControlSt_Choices value) {
            set<uint8_t>(8, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 制动错误状态 */
        VCU3_BrakingFailureSt_Choices VCU3_BrakingFailureSt() const {
            return static_cast<VCU3_BrakingFailureSt_Choices>(get<uint8_t>(10, 3, LITTLE_ENDIAN));
        }
        void VCU3_BrakingFailureSt(VCU3_BrakingFailureSt_Choices value) {
            set<uint8_t>(10, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 制动接管状态 */
        VCU3_BrakingTakeOverSt_Choices VCU3_BrakingTakeOverSt() const {
            return static_cast<VCU3_BrakingTakeOverSt_Choices>(get<bool>(13, 1, LITTLE_ENDIAN));
        }
        void VCU3_BrakingTakeOverSt(VCU3_BrakingTakeOverSt_Choices value) {
            set<bool>(13, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* CO总线有效性 */
        VCU3_ValidityCO_Choices VCU3_ValidityCO() const {
            return static_cast<VCU3_ValidityCO_Choices>(get<bool>(14, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityCO(VCU3_ValidityCO_Choices value) {
            set<bool>(14, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* CCO总线有效性 */
        VCU3_ValidityCCO_Choices VCU3_ValidityCCO() const {
            return static_cast<VCU3_ValidityCCO_Choices>(get<bool>(15, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityCCO(VCU3_ValidityCCO_Choices value) {
            set<bool>(15, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 驱动线控状态 */
        VCU3_DrivingAutoControlSt_Choices VCU3_DrivingAutoControlSt() const {
            return static_cast<VCU3_DrivingAutoControlSt_Choices>(get<uint8_t>(16, 2, LITTLE_ENDIAN));
        }
        void VCU3_DrivingAutoControlSt(VCU3_DrivingAutoControlSt_Choices value) {
            set<uint8_t>(16, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 驱动错误状态 */
        VCU3_DrivingFailureSt_Choices VCU3_DrivingFailureSt() const {
            return static_cast<VCU3_DrivingFailureSt_Choices>(get<uint8_t>(18, 3, LITTLE_ENDIAN));
        }
        void VCU3_DrivingFailureSt(VCU3_DrivingFailureSt_Choices value) {
            set<uint8_t>(18, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 驱动接管状态 */
        VCU3_DrivingTakeOverSt_Choices VCU3_DrivingTakeOverSt() const {
            return static_cast<VCU3_DrivingTakeOverSt_Choices>(get<bool>(21, 1, LITTLE_ENDIAN));
        }
        void VCU3_DrivingTakeOverSt(VCU3_DrivingTakeOverSt_Choices value) {
            set<bool>(21, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* EXT总线有效性 */
        VCU3_ValidityEXT_Choices VCU3_ValidityEXT() const {
            return static_cast<VCU3_ValidityEXT_Choices>(get<bool>(22, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityEXT(VCU3_ValidityEXT_Choices value) {
            set<bool>(22, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* CEXT总线有效性 */
        VCU3_ValidityCEXT_Choices VCU3_ValidityCEXT() const {
            return static_cast<VCU3_ValidityCEXT_Choices>(get<bool>(23, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityCEXT(VCU3_ValidityCEXT_Choices value) {
            set<bool>(23, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 转向线控状态 */
        VCU3_SteeringAutoControlSt_Choices VCU3_SteeringAutoControlSt() const {
            return static_cast<VCU3_SteeringAutoControlSt_Choices>(get<uint8_t>(24, 2, LITTLE_ENDIAN));
        }
        void VCU3_SteeringAutoControlSt(VCU3_SteeringAutoControlSt_Choices value) {
            set<uint8_t>(24, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 转向错误状态 */
        VCU3_SteeringFailureSt_Choices VCU3_SteeringFailureSt() const {
            return static_cast<VCU3_SteeringFailureSt_Choices>(get<uint8_t>(26, 3, LITTLE_ENDIAN));
        }
        void VCU3_SteeringFailureSt(VCU3_SteeringFailureSt_Choices value) {
            set<uint8_t>(26, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 转向接管状态 */
        VCU3_SteeringTakeOverSt_Choices VCU3_SteeringTakeOverSt() const {
            return static_cast<VCU3_SteeringTakeOverSt_Choices>(get<bool>(29, 1, LITTLE_ENDIAN));
        }
        void VCU3_SteeringTakeOverSt(VCU3_SteeringTakeOverSt_Choices value) {
            set<bool>(29, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* EPS总线有效性 */
        VCU3_ValidityEPS_Choices VCU3_ValidityEPS() const {
            return static_cast<VCU3_ValidityEPS_Choices>(get<bool>(30, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityEPS(VCU3_ValidityEPS_Choices value) {
            set<bool>(30, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* CEPS总线有效性 */
        VCU3_ValidityCEPS_Choices VCU3_ValidityCEPS() const {
            return static_cast<VCU3_ValidityCEPS_Choices>(get<bool>(31, 1, LITTLE_ENDIAN));
        }
        void VCU3_ValidityCEPS(VCU3_ValidityCEPS_Choices value) {
            set<bool>(31, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 行驶里程(Drive distance since prime start) */
        float VCU3_DDSPS() const {
            return get<uint32_t>(32, 25, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(0);
        }
        void VCU3_DDSPS(float value) {
            set<uint32_t>(32, 25, LITTLE_ENDIAN, static_cast<uint32_t>((value-(0))/static_cast<float>(0.1)));
        }

        /* 线控状态 */
        VCU3_SystemControlSt_Choices VCU3_SystemControlSt() const {
            return static_cast<VCU3_SystemControlSt_Choices>(get<uint8_t>(58, 2, LITTLE_ENDIAN));
        }
        void VCU3_SystemControlSt(VCU3_SystemControlSt_Choices value) {
            set<uint8_t>(58, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 生命信号 */
        uint8_t VCU3_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU3_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU3 {
    private:
        void can_msg_update() {
            if(0x68c != can_msg.get().can_id)
                return;
            adas::ehs3::VCU3 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU3_Checksum(static_cast<int>(can_data.VCU3_Checksum()));
            VCU3_BrakingAutoControlSt(static_cast<int>(can_data.VCU3_BrakingAutoControlSt()));
            VCU3_BrakingFailureSt(static_cast<int>(can_data.VCU3_BrakingFailureSt()));
            VCU3_BrakingTakeOverSt(static_cast<int>(can_data.VCU3_BrakingTakeOverSt()));
            VCU3_ValidityCO(static_cast<int>(can_data.VCU3_ValidityCO()));
            VCU3_ValidityCCO(static_cast<int>(can_data.VCU3_ValidityCCO()));
            VCU3_DrivingAutoControlSt(static_cast<int>(can_data.VCU3_DrivingAutoControlSt()));
            VCU3_DrivingFailureSt(static_cast<int>(can_data.VCU3_DrivingFailureSt()));
            VCU3_DrivingTakeOverSt(static_cast<int>(can_data.VCU3_DrivingTakeOverSt()));
            VCU3_ValidityEXT(static_cast<int>(can_data.VCU3_ValidityEXT()));
            VCU3_ValidityCEXT(static_cast<int>(can_data.VCU3_ValidityCEXT()));
            VCU3_SteeringAutoControlSt(static_cast<int>(can_data.VCU3_SteeringAutoControlSt()));
            VCU3_SteeringFailureSt(static_cast<int>(can_data.VCU3_SteeringFailureSt()));
            VCU3_SteeringTakeOverSt(static_cast<int>(can_data.VCU3_SteeringTakeOverSt()));
            VCU3_ValidityEPS(static_cast<int>(can_data.VCU3_ValidityEPS()));
            VCU3_ValidityCEPS(static_cast<int>(can_data.VCU3_ValidityCEPS()));
            VCU3_DDSPS(can_data.VCU3_DDSPS());
            VCU3_SystemControlSt(static_cast<int>(can_data.VCU3_SystemControlSt()));
            VCU3_LiveCounter(static_cast<int>(can_data.VCU3_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU3_Checksum;
        adas::node::out<int> VCU3_BrakingAutoControlSt;
        adas::node::out<int> VCU3_BrakingFailureSt;
        adas::node::out<int> VCU3_BrakingTakeOverSt;
        adas::node::out<int> VCU3_ValidityCO;
        adas::node::out<int> VCU3_ValidityCCO;
        adas::node::out<int> VCU3_DrivingAutoControlSt;
        adas::node::out<int> VCU3_DrivingFailureSt;
        adas::node::out<int> VCU3_DrivingTakeOverSt;
        adas::node::out<int> VCU3_ValidityEXT;
        adas::node::out<int> VCU3_ValidityCEXT;
        adas::node::out<int> VCU3_SteeringAutoControlSt;
        adas::node::out<int> VCU3_SteeringFailureSt;
        adas::node::out<int> VCU3_SteeringTakeOverSt;
        adas::node::out<int> VCU3_ValidityEPS;
        adas::node::out<int> VCU3_ValidityCEPS;
        adas::node::out<float> VCU3_DDSPS;
        adas::node::out<int> VCU3_SystemControlSt;
        adas::node::out<int> VCU3_LiveCounter;
    };
    }

    namespace pack {
    class VCU3 {
    public:
        VCU3() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU3_Checksum{0, [](){}};
        adas::node::in<int> VCU3_BrakingAutoControlSt{0, [](){}};
        adas::node::in<int> VCU3_BrakingFailureSt{0, [](){}};
        adas::node::in<int> VCU3_BrakingTakeOverSt{0, [](){}};
        adas::node::in<int> VCU3_ValidityCO{0, [](){}};
        adas::node::in<int> VCU3_ValidityCCO{0, [](){}};
        adas::node::in<int> VCU3_DrivingAutoControlSt{0, [](){}};
        adas::node::in<int> VCU3_DrivingFailureSt{0, [](){}};
        adas::node::in<int> VCU3_DrivingTakeOverSt{0, [](){}};
        adas::node::in<int> VCU3_ValidityEXT{0, [](){}};
        adas::node::in<int> VCU3_ValidityCEXT{0, [](){}};
        adas::node::in<int> VCU3_SteeringAutoControlSt{0, [](){}};
        adas::node::in<int> VCU3_SteeringFailureSt{0, [](){}};
        adas::node::in<int> VCU3_SteeringTakeOverSt{0, [](){}};
        adas::node::in<int> VCU3_ValidityEPS{0, [](){}};
        adas::node::in<int> VCU3_ValidityCEPS{0, [](){}};
        adas::node::in<float> VCU3_DDSPS{0, [](){}};
        adas::node::in<int> VCU3_SystemControlSt{0, [](){}};
        adas::node::in<int> VCU3_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU3 data;
            data.VCU3_Checksum(VCU3_Checksum.get());
            data.VCU3_BrakingAutoControlSt(adas::ehs3::VCU3::VCU3_BrakingAutoControlSt_Choices{VCU3_BrakingAutoControlSt.get()});
            data.VCU3_BrakingFailureSt(adas::ehs3::VCU3::VCU3_BrakingFailureSt_Choices{VCU3_BrakingFailureSt.get()});
            data.VCU3_BrakingTakeOverSt(adas::ehs3::VCU3::VCU3_BrakingTakeOverSt_Choices{VCU3_BrakingTakeOverSt.get()});
            data.VCU3_ValidityCO(adas::ehs3::VCU3::VCU3_ValidityCO_Choices{VCU3_ValidityCO.get()});
            data.VCU3_ValidityCCO(adas::ehs3::VCU3::VCU3_ValidityCCO_Choices{VCU3_ValidityCCO.get()});
            data.VCU3_DrivingAutoControlSt(adas::ehs3::VCU3::VCU3_DrivingAutoControlSt_Choices{VCU3_DrivingAutoControlSt.get()});
            data.VCU3_DrivingFailureSt(adas::ehs3::VCU3::VCU3_DrivingFailureSt_Choices{VCU3_DrivingFailureSt.get()});
            data.VCU3_DrivingTakeOverSt(adas::ehs3::VCU3::VCU3_DrivingTakeOverSt_Choices{VCU3_DrivingTakeOverSt.get()});
            data.VCU3_ValidityEXT(adas::ehs3::VCU3::VCU3_ValidityEXT_Choices{VCU3_ValidityEXT.get()});
            data.VCU3_ValidityCEXT(adas::ehs3::VCU3::VCU3_ValidityCEXT_Choices{VCU3_ValidityCEXT.get()});
            data.VCU3_SteeringAutoControlSt(adas::ehs3::VCU3::VCU3_SteeringAutoControlSt_Choices{VCU3_SteeringAutoControlSt.get()});
            data.VCU3_SteeringFailureSt(adas::ehs3::VCU3::VCU3_SteeringFailureSt_Choices{VCU3_SteeringFailureSt.get()});
            data.VCU3_SteeringTakeOverSt(adas::ehs3::VCU3::VCU3_SteeringTakeOverSt_Choices{VCU3_SteeringTakeOverSt.get()});
            data.VCU3_ValidityEPS(adas::ehs3::VCU3::VCU3_ValidityEPS_Choices{VCU3_ValidityEPS.get()});
            data.VCU3_ValidityCEPS(adas::ehs3::VCU3::VCU3_ValidityCEPS_Choices{VCU3_ValidityCEPS.get()});
            data.VCU3_DDSPS(VCU3_DDSPS.get());
            data.VCU3_SystemControlSt(adas::ehs3::VCU3::VCU3_SystemControlSt_Choices{VCU3_SystemControlSt.get()});
            data.VCU3_LiveCounter(VCU3_LiveCounter.get());
            can_frame frame{.can_id=0x68c};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Control By Wire */
    /* id: 0x5c0 */
    class ACU1 : public adas::can::CanData {
    public:
        ACU1() : adas::can::CanData(8) {}
        explicit ACU1(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class ACU1_AccelerationRequestSt_Choices {
            Request = 1,
            NoRequest = 0,
        };

        enum class ACU1_EPBRequest_Choices {
            Locking = 2,
            Releasing = 1,
            NoRequest = 0,
        };

        enum class ACU1_GearRequest_Choices {
            D = 4,
            N = 3,
            R = 2,
            P = 1,
            NoRequest = 0,
        };

        enum class ACU1_StandStillRequest_Choices {
            Request = 1,
            NoRequest = 0,
        };

        enum class ACU1_SteeringLightRequest_Choices {
            RightOn = 2,
            LeftOn = 1,
            Off = 0,
        };

        enum class ACU1_HazardLightRequest_Choices {
            On = 1,
            Off = 0,
        };

        /* 校验和 */
        uint8_t ACU1_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void ACU1_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 纵向请求 */
        ACU1_AccelerationRequestSt_Choices ACU1_AccelerationRequestSt() const {
            return static_cast<ACU1_AccelerationRequestSt_Choices>(get<uint8_t>(8, 2, LITTLE_ENDIAN));
        }
        void ACU1_AccelerationRequestSt(ACU1_AccelerationRequestSt_Choices value) {
            set<uint8_t>(8, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 手刹请求 */
        ACU1_EPBRequest_Choices ACU1_EPBRequest() const {
            return static_cast<ACU1_EPBRequest_Choices>(get<uint8_t>(10, 2, LITTLE_ENDIAN));
        }
        void ACU1_EPBRequest(ACU1_EPBRequest_Choices value) {
            set<uint8_t>(10, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 档位请求 */
        ACU1_GearRequest_Choices ACU1_GearRequest() const {
            return static_cast<ACU1_GearRequest_Choices>(get<uint8_t>(12, 3, LITTLE_ENDIAN));
        }
        void ACU1_GearRequest(ACU1_GearRequest_Choices value) {
            set<uint8_t>(12, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 驻车请求 */
        ACU1_StandStillRequest_Choices ACU1_StandStillRequest() const {
            return static_cast<ACU1_StandStillRequest_Choices>(get<bool>(15, 1, LITTLE_ENDIAN));
        }
        void ACU1_StandStillRequest(ACU1_StandStillRequest_Choices value) {
            set<bool>(15, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 请求的纵向加减速度 */
        float ACU1_AX_Request() const {
            return get<uint16_t>(16, 12, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-20);
        }
        void ACU1_AX_Request(float value) {
            set<uint16_t>(16, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-20))/static_cast<float>(0.01)));
        }

        /* 左转灯请求 */
        ACU1_SteeringLightRequest_Choices ACU1_SteeringLightRequest() const {
            return static_cast<ACU1_SteeringLightRequest_Choices>(get<uint8_t>(32, 2, LITTLE_ENDIAN));
        }
        void ACU1_SteeringLightRequest(ACU1_SteeringLightRequest_Choices value) {
            set<uint8_t>(32, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 双闪灯请求 */
        ACU1_HazardLightRequest_Choices ACU1_HazardLightRequest() const {
            return static_cast<ACU1_HazardLightRequest_Choices>(get<uint8_t>(34, 2, LITTLE_ENDIAN));
        }
        void ACU1_HazardLightRequest(ACU1_HazardLightRequest_Choices value) {
            set<uint8_t>(34, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 生命信号 */
        uint8_t ACU1_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void ACU1_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class ACU1 {
    private:
        void can_msg_update() {
            if(0x5c0 != can_msg.get().can_id)
                return;
            adas::ehs3::ACU1 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            ACU1_Checksum(static_cast<int>(can_data.ACU1_Checksum()));
            ACU1_AccelerationRequestSt(static_cast<int>(can_data.ACU1_AccelerationRequestSt()));
            ACU1_EPBRequest(static_cast<int>(can_data.ACU1_EPBRequest()));
            ACU1_GearRequest(static_cast<int>(can_data.ACU1_GearRequest()));
            ACU1_StandStillRequest(static_cast<int>(can_data.ACU1_StandStillRequest()));
            ACU1_AX_Request(can_data.ACU1_AX_Request());
            ACU1_SteeringLightRequest(static_cast<int>(can_data.ACU1_SteeringLightRequest()));
            ACU1_HazardLightRequest(static_cast<int>(can_data.ACU1_HazardLightRequest()));
            ACU1_LiveCounter(static_cast<int>(can_data.ACU1_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> ACU1_Checksum;
        adas::node::out<int> ACU1_AccelerationRequestSt;
        adas::node::out<int> ACU1_EPBRequest;
        adas::node::out<int> ACU1_GearRequest;
        adas::node::out<int> ACU1_StandStillRequest;
        adas::node::out<float> ACU1_AX_Request;
        adas::node::out<int> ACU1_SteeringLightRequest;
        adas::node::out<int> ACU1_HazardLightRequest;
        adas::node::out<int> ACU1_LiveCounter;
    };
    }

    namespace pack {
    class ACU1 {
    public:
        ACU1() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> ACU1_Checksum{0, [](){}};
        adas::node::in<int> ACU1_AccelerationRequestSt{0, [](){}};
        adas::node::in<int> ACU1_EPBRequest{0, [](){}};
        adas::node::in<int> ACU1_GearRequest{0, [](){}};
        adas::node::in<int> ACU1_StandStillRequest{0, [](){}};
        adas::node::in<float> ACU1_AX_Request{0, [](){}};
        adas::node::in<int> ACU1_SteeringLightRequest{0, [](){}};
        adas::node::in<int> ACU1_HazardLightRequest{0, [](){}};
        adas::node::in<int> ACU1_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::ACU1 data;
            data.ACU1_Checksum(ACU1_Checksum.get());
            data.ACU1_AccelerationRequestSt(adas::ehs3::ACU1::ACU1_AccelerationRequestSt_Choices{ACU1_AccelerationRequestSt.get()});
            data.ACU1_EPBRequest(adas::ehs3::ACU1::ACU1_EPBRequest_Choices{ACU1_EPBRequest.get()});
            data.ACU1_GearRequest(adas::ehs3::ACU1::ACU1_GearRequest_Choices{ACU1_GearRequest.get()});
            data.ACU1_StandStillRequest(adas::ehs3::ACU1::ACU1_StandStillRequest_Choices{ACU1_StandStillRequest.get()});
            data.ACU1_AX_Request(ACU1_AX_Request.get());
            data.ACU1_SteeringLightRequest(adas::ehs3::ACU1::ACU1_SteeringLightRequest_Choices{ACU1_SteeringLightRequest.get()});
            data.ACU1_HazardLightRequest(adas::ehs3::ACU1::ACU1_HazardLightRequest_Choices{ACU1_HazardLightRequest.get()});
            data.ACU1_LiveCounter(ACU1_LiveCounter.get());
            can_frame frame{.can_id=0x5c0};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Special Info */
    /* id: 0x68a */
    class VCU1 : public adas::can::CanData {
    public:
        VCU1() : adas::can::CanData(8) {}
        explicit VCU1(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* 校验和 */
        uint8_t VCU1_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU1_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 纵向加速度(传感器)前正后负 */
        float VCU1_LongitudinalAccel() const {
            return get<uint16_t>(8, 12, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-20);
        }
        void VCU1_LongitudinalAccel(float value) {
            set<uint16_t>(8, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-20))/static_cast<float>(0.01)));
        }

        /* 横向加速度(传感器)左负右正 */
        float VCU1_LateraAccel() const {
            return get<uint16_t>(20, 12, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(-20);
        }
        void VCU1_LateraAccel(float value) {
            set<uint16_t>(20, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-20))/static_cast<float>(0.01)));
        }

        /* 航偏角速率(传感器)左负右正 */
        float VCU1_YawRate() const {
            return get<uint16_t>(32, 12, LITTLE_ENDIAN) * static_cast<float>(0.05) + static_cast<float>(-100);
        }
        void VCU1_YawRate(float value) {
            set<uint16_t>(32, 12, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-100))/static_cast<float>(0.05)));
        }

        /* 熄火时间 */
        uint16_t VCU1_IgnitionOffTime() const {
            return get<uint16_t>(44, 12, LITTLE_ENDIAN);
        }
        void VCU1_IgnitionOffTime(uint16_t value) {
            set<uint16_t>(44, 12, LITTLE_ENDIAN, value);
        }

        /* 生命信号 */
        uint8_t VCU1_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU1_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU1 {
    private:
        void can_msg_update() {
            if(0x68a != can_msg.get().can_id)
                return;
            adas::ehs3::VCU1 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU1_Checksum(static_cast<int>(can_data.VCU1_Checksum()));
            VCU1_LongitudinalAccel(can_data.VCU1_LongitudinalAccel());
            VCU1_LateraAccel(can_data.VCU1_LateraAccel());
            VCU1_YawRate(can_data.VCU1_YawRate());
            VCU1_IgnitionOffTime(static_cast<int>(can_data.VCU1_IgnitionOffTime()));
            VCU1_LiveCounter(static_cast<int>(can_data.VCU1_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU1_Checksum;
        adas::node::out<float> VCU1_LongitudinalAccel;
        adas::node::out<float> VCU1_LateraAccel;
        adas::node::out<float> VCU1_YawRate;
        adas::node::out<int> VCU1_IgnitionOffTime;
        adas::node::out<int> VCU1_LiveCounter;
    };
    }

    namespace pack {
    class VCU1 {
    public:
        VCU1() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU1_Checksum{0, [](){}};
        adas::node::in<float> VCU1_LongitudinalAccel{0, [](){}};
        adas::node::in<float> VCU1_LateraAccel{0, [](){}};
        adas::node::in<float> VCU1_YawRate{0, [](){}};
        adas::node::in<int> VCU1_IgnitionOffTime{0, [](){}};
        adas::node::in<int> VCU1_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU1 data;
            data.VCU1_Checksum(VCU1_Checksum.get());
            data.VCU1_LongitudinalAccel(VCU1_LongitudinalAccel.get());
            data.VCU1_LateraAccel(VCU1_LateraAccel.get());
            data.VCU1_YawRate(VCU1_YawRate.get());
            data.VCU1_IgnitionOffTime(VCU1_IgnitionOffTime.get());
            data.VCU1_LiveCounter(VCU1_LiveCounter.get());
            can_frame frame{.can_id=0x68a};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Special Info */
    /* id: 0x68b */
    class VCU2 : public adas::can::CanData {
    public:
        VCU2() : adas::can::CanData(8) {}
        explicit VCU2(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class VCU2_DriverSideBuckle_Choices {
            Unbuckled = 1,
            Buckled = 0,
        };

        enum class VCU2_WiperStatus_Choices {
            HighSpeed = 3,
            LowSpeed = 2,
            Interval = 1,
            Off = 0,
        };

        enum class VCU2_JerkSt_Choices {
            Press = 1,
            NoPress = 0,
        };

        enum class VCU2_Button1_Choices {
            Press = 1,
            NoPress = 0,
        };

        enum class VCU2_Button2_Choices {
            Press = 1,
            NoPress = 0,
        };

        enum class VCU2_DriverDoorStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_PassengerDoorStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_RLDoorStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_RRDoorStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_DriverLockStatus_Choices {
            Unlock = 1,
            Lock = 0,
        };

        enum class VCU2_PassengerLockStatus_Choices {
            Unlock = 1,
            Lock = 0,
        };

        enum class VCU2_RLLockStatus_Choices {
            Unlock = 1,
            Lock = 0,
        };

        enum class VCU2_RRLockStatus_Choices {
            Unlock = 1,
            Lock = 0,
        };

        enum class VCU2_EngHoodStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_LuggageDoorStatus_Choices {
            Open = 1,
            Close = 0,
        };

        enum class VCU2_EVReady_Choices {
            On = 2,
            Preparing = 1,
            Off = 0,
        };

        enum class VCU2_IgnitionKey_Choices {
            Start = 3,
            On = 2,
            Accessory = 1,
            Lock = 0,
        };

        enum class VCU2_SteeringLight_Choices {
            RightOn = 2,
            LeftOn = 1,
            Off = 0,
        };

        enum class VCU2_HazardLight_Choices {
            On = 1,
            Off = 0,
        };

        enum class VCU2_LowBeamStatus_Choices {
            On = 1,
            Off = 0,
        };

        enum class VCU2_HighBeamStatus_Choices {
            On = 1,
            Off = 0,
        };

        enum class VCU2_MainSwitch_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU2_ResumeSwitch_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU2_CancelSwitch_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU2_UpSwitch_Choices {
            Active = 1,
            Inactive = 0,
        };

        enum class VCU2_DownSwitch_Choices {
            Active = 1,
            Inactive = 0,
        };

        /* 校验和 */
        uint8_t VCU2_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU2_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 主驾安全带状态 */
        VCU2_DriverSideBuckle_Choices VCU2_DriverSideBuckle() const {
            return static_cast<VCU2_DriverSideBuckle_Choices>(get<uint8_t>(8, 2, LITTLE_ENDIAN));
        }
        void VCU2_DriverSideBuckle(VCU2_DriverSideBuckle_Choices value) {
            set<uint8_t>(8, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 雨刷器状态 */
        VCU2_WiperStatus_Choices VCU2_WiperStatus() const {
            return static_cast<VCU2_WiperStatus_Choices>(get<uint8_t>(10, 3, LITTLE_ENDIAN));
        }
        void VCU2_WiperStatus(VCU2_WiperStatus_Choices value) {
            set<uint8_t>(10, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 中控急停按钮状态(选装) */
        VCU2_JerkSt_Choices VCU2_JerkSt() const {
            return static_cast<VCU2_JerkSt_Choices>(get<bool>(13, 1, LITTLE_ENDIAN));
        }
        void VCU2_JerkSt(VCU2_JerkSt_Choices value) {
            set<bool>(13, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 中控按钮1状态(选装) */
        VCU2_Button1_Choices VCU2_Button1() const {
            return static_cast<VCU2_Button1_Choices>(get<bool>(14, 1, LITTLE_ENDIAN));
        }
        void VCU2_Button1(VCU2_Button1_Choices value) {
            set<bool>(14, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 中控按钮2状态(选装) */
        VCU2_Button2_Choices VCU2_Button2() const {
            return static_cast<VCU2_Button2_Choices>(get<bool>(15, 1, LITTLE_ENDIAN));
        }
        void VCU2_Button2(VCU2_Button2_Choices value) {
            set<bool>(15, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 主驾驶门开关状态 */
        VCU2_DriverDoorStatus_Choices VCU2_DriverDoorStatus() const {
            return static_cast<VCU2_DriverDoorStatus_Choices>(get<uint8_t>(16, 2, LITTLE_ENDIAN));
        }
        void VCU2_DriverDoorStatus(VCU2_DriverDoorStatus_Choices value) {
            set<uint8_t>(16, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 副驾驶门开关状态 */
        VCU2_PassengerDoorStatus_Choices VCU2_PassengerDoorStatus() const {
            return static_cast<VCU2_PassengerDoorStatus_Choices>(get<uint8_t>(18, 2, LITTLE_ENDIAN));
        }
        void VCU2_PassengerDoorStatus(VCU2_PassengerDoorStatus_Choices value) {
            set<uint8_t>(18, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 左后门开关状态 */
        VCU2_RLDoorStatus_Choices VCU2_RLDoorStatus() const {
            return static_cast<VCU2_RLDoorStatus_Choices>(get<uint8_t>(20, 2, LITTLE_ENDIAN));
        }
        void VCU2_RLDoorStatus(VCU2_RLDoorStatus_Choices value) {
            set<uint8_t>(20, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 右后门开关状态 */
        VCU2_RRDoorStatus_Choices VCU2_RRDoorStatus() const {
            return static_cast<VCU2_RRDoorStatus_Choices>(get<uint8_t>(22, 2, LITTLE_ENDIAN));
        }
        void VCU2_RRDoorStatus(VCU2_RRDoorStatus_Choices value) {
            set<uint8_t>(22, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 主驾驶门锁状态 */
        VCU2_DriverLockStatus_Choices VCU2_DriverLockStatus() const {
            return static_cast<VCU2_DriverLockStatus_Choices>(get<uint8_t>(24, 2, LITTLE_ENDIAN));
        }
        void VCU2_DriverLockStatus(VCU2_DriverLockStatus_Choices value) {
            set<uint8_t>(24, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 副驾驶门锁状态 */
        VCU2_PassengerLockStatus_Choices VCU2_PassengerLockStatus() const {
            return static_cast<VCU2_PassengerLockStatus_Choices>(get<uint8_t>(26, 2, LITTLE_ENDIAN));
        }
        void VCU2_PassengerLockStatus(VCU2_PassengerLockStatus_Choices value) {
            set<uint8_t>(26, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 左后门锁状态 */
        VCU2_RLLockStatus_Choices VCU2_RLLockStatus() const {
            return static_cast<VCU2_RLLockStatus_Choices>(get<uint8_t>(28, 2, LITTLE_ENDIAN));
        }
        void VCU2_RLLockStatus(VCU2_RLLockStatus_Choices value) {
            set<uint8_t>(28, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 右后门锁状态 */
        VCU2_RRLockStatus_Choices VCU2_RRLockStatus() const {
            return static_cast<VCU2_RRLockStatus_Choices>(get<uint8_t>(30, 2, LITTLE_ENDIAN));
        }
        void VCU2_RRLockStatus(VCU2_RRLockStatus_Choices value) {
            set<uint8_t>(30, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 引擎盖开关状态 */
        VCU2_EngHoodStatus_Choices VCU2_EngHoodStatus() const {
            return static_cast<VCU2_EngHoodStatus_Choices>(get<uint8_t>(32, 2, LITTLE_ENDIAN));
        }
        void VCU2_EngHoodStatus(VCU2_EngHoodStatus_Choices value) {
            set<uint8_t>(32, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 后备箱开关状态 */
        VCU2_LuggageDoorStatus_Choices VCU2_LuggageDoorStatus() const {
            return static_cast<VCU2_LuggageDoorStatus_Choices>(get<uint8_t>(34, 2, LITTLE_ENDIAN));
        }
        void VCU2_LuggageDoorStatus(VCU2_LuggageDoorStatus_Choices value) {
            set<uint8_t>(34, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* Ready信号 */
        VCU2_EVReady_Choices VCU2_EVReady() const {
            return static_cast<VCU2_EVReady_Choices>(get<uint8_t>(36, 2, LITTLE_ENDIAN));
        }
        void VCU2_EVReady(VCU2_EVReady_Choices value) {
            set<uint8_t>(36, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 点火钥匙状态 */
        VCU2_IgnitionKey_Choices VCU2_IgnitionKey() const {
            return static_cast<VCU2_IgnitionKey_Choices>(get<uint8_t>(38, 2, LITTLE_ENDIAN));
        }
        void VCU2_IgnitionKey(VCU2_IgnitionKey_Choices value) {
            set<uint8_t>(38, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 转向灯信号 */
        VCU2_SteeringLight_Choices VCU2_SteeringLight() const {
            return static_cast<VCU2_SteeringLight_Choices>(get<uint8_t>(40, 2, LITTLE_ENDIAN));
        }
        void VCU2_SteeringLight(VCU2_SteeringLight_Choices value) {
            set<uint8_t>(40, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 双闪灯信号 */
        VCU2_HazardLight_Choices VCU2_HazardLight() const {
            return static_cast<VCU2_HazardLight_Choices>(get<uint8_t>(42, 2, LITTLE_ENDIAN));
        }
        void VCU2_HazardLight(VCU2_HazardLight_Choices value) {
            set<uint8_t>(42, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 近光灯状态 */
        VCU2_LowBeamStatus_Choices VCU2_LowBeamStatus() const {
            return static_cast<VCU2_LowBeamStatus_Choices>(get<uint8_t>(44, 2, LITTLE_ENDIAN));
        }
        void VCU2_LowBeamStatus(VCU2_LowBeamStatus_Choices value) {
            set<uint8_t>(44, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 远光灯状态 */
        VCU2_HighBeamStatus_Choices VCU2_HighBeamStatus() const {
            return static_cast<VCU2_HighBeamStatus_Choices>(get<uint8_t>(46, 2, LITTLE_ENDIAN));
        }
        void VCU2_HighBeamStatus(VCU2_HighBeamStatus_Choices value) {
            set<uint8_t>(46, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* ACC主开关 */
        VCU2_MainSwitch_Choices VCU2_MainSwitch() const {
            return static_cast<VCU2_MainSwitch_Choices>(get<bool>(48, 1, LITTLE_ENDIAN));
        }
        void VCU2_MainSwitch(VCU2_MainSwitch_Choices value) {
            set<bool>(48, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* ACC继续开关 */
        VCU2_ResumeSwitch_Choices VCU2_ResumeSwitch() const {
            return static_cast<VCU2_ResumeSwitch_Choices>(get<bool>(49, 1, LITTLE_ENDIAN));
        }
        void VCU2_ResumeSwitch(VCU2_ResumeSwitch_Choices value) {
            set<bool>(49, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* ACC暂停开关 */
        VCU2_CancelSwitch_Choices VCU2_CancelSwitch() const {
            return static_cast<VCU2_CancelSwitch_Choices>(get<bool>(50, 1, LITTLE_ENDIAN));
        }
        void VCU2_CancelSwitch(VCU2_CancelSwitch_Choices value) {
            set<bool>(50, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* ACC加速开关 */
        VCU2_UpSwitch_Choices VCU2_UpSwitch() const {
            return static_cast<VCU2_UpSwitch_Choices>(get<bool>(51, 1, LITTLE_ENDIAN));
        }
        void VCU2_UpSwitch(VCU2_UpSwitch_Choices value) {
            set<bool>(51, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* ACC减速开关 */
        VCU2_DownSwitch_Choices VCU2_DownSwitch() const {
            return static_cast<VCU2_DownSwitch_Choices>(get<bool>(52, 1, LITTLE_ENDIAN));
        }
        void VCU2_DownSwitch(VCU2_DownSwitch_Choices value) {
            set<bool>(52, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 生命信号 */
        uint8_t VCU2_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU2_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU2 {
    private:
        void can_msg_update() {
            if(0x68b != can_msg.get().can_id)
                return;
            adas::ehs3::VCU2 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU2_Checksum(static_cast<int>(can_data.VCU2_Checksum()));
            VCU2_DriverSideBuckle(static_cast<int>(can_data.VCU2_DriverSideBuckle()));
            VCU2_WiperStatus(static_cast<int>(can_data.VCU2_WiperStatus()));
            VCU2_JerkSt(static_cast<int>(can_data.VCU2_JerkSt()));
            VCU2_Button1(static_cast<int>(can_data.VCU2_Button1()));
            VCU2_Button2(static_cast<int>(can_data.VCU2_Button2()));
            VCU2_DriverDoorStatus(static_cast<int>(can_data.VCU2_DriverDoorStatus()));
            VCU2_PassengerDoorStatus(static_cast<int>(can_data.VCU2_PassengerDoorStatus()));
            VCU2_RLDoorStatus(static_cast<int>(can_data.VCU2_RLDoorStatus()));
            VCU2_RRDoorStatus(static_cast<int>(can_data.VCU2_RRDoorStatus()));
            VCU2_DriverLockStatus(static_cast<int>(can_data.VCU2_DriverLockStatus()));
            VCU2_PassengerLockStatus(static_cast<int>(can_data.VCU2_PassengerLockStatus()));
            VCU2_RLLockStatus(static_cast<int>(can_data.VCU2_RLLockStatus()));
            VCU2_RRLockStatus(static_cast<int>(can_data.VCU2_RRLockStatus()));
            VCU2_EngHoodStatus(static_cast<int>(can_data.VCU2_EngHoodStatus()));
            VCU2_LuggageDoorStatus(static_cast<int>(can_data.VCU2_LuggageDoorStatus()));
            VCU2_EVReady(static_cast<int>(can_data.VCU2_EVReady()));
            VCU2_IgnitionKey(static_cast<int>(can_data.VCU2_IgnitionKey()));
            VCU2_SteeringLight(static_cast<int>(can_data.VCU2_SteeringLight()));
            VCU2_HazardLight(static_cast<int>(can_data.VCU2_HazardLight()));
            VCU2_LowBeamStatus(static_cast<int>(can_data.VCU2_LowBeamStatus()));
            VCU2_HighBeamStatus(static_cast<int>(can_data.VCU2_HighBeamStatus()));
            VCU2_MainSwitch(static_cast<int>(can_data.VCU2_MainSwitch()));
            VCU2_ResumeSwitch(static_cast<int>(can_data.VCU2_ResumeSwitch()));
            VCU2_CancelSwitch(static_cast<int>(can_data.VCU2_CancelSwitch()));
            VCU2_UpSwitch(static_cast<int>(can_data.VCU2_UpSwitch()));
            VCU2_DownSwitch(static_cast<int>(can_data.VCU2_DownSwitch()));
            VCU2_LiveCounter(static_cast<int>(can_data.VCU2_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU2_Checksum;
        adas::node::out<int> VCU2_DriverSideBuckle;
        adas::node::out<int> VCU2_WiperStatus;
        adas::node::out<int> VCU2_JerkSt;
        adas::node::out<int> VCU2_Button1;
        adas::node::out<int> VCU2_Button2;
        adas::node::out<int> VCU2_DriverDoorStatus;
        adas::node::out<int> VCU2_PassengerDoorStatus;
        adas::node::out<int> VCU2_RLDoorStatus;
        adas::node::out<int> VCU2_RRDoorStatus;
        adas::node::out<int> VCU2_DriverLockStatus;
        adas::node::out<int> VCU2_PassengerLockStatus;
        adas::node::out<int> VCU2_RLLockStatus;
        adas::node::out<int> VCU2_RRLockStatus;
        adas::node::out<int> VCU2_EngHoodStatus;
        adas::node::out<int> VCU2_LuggageDoorStatus;
        adas::node::out<int> VCU2_EVReady;
        adas::node::out<int> VCU2_IgnitionKey;
        adas::node::out<int> VCU2_SteeringLight;
        adas::node::out<int> VCU2_HazardLight;
        adas::node::out<int> VCU2_LowBeamStatus;
        adas::node::out<int> VCU2_HighBeamStatus;
        adas::node::out<int> VCU2_MainSwitch;
        adas::node::out<int> VCU2_ResumeSwitch;
        adas::node::out<int> VCU2_CancelSwitch;
        adas::node::out<int> VCU2_UpSwitch;
        adas::node::out<int> VCU2_DownSwitch;
        adas::node::out<int> VCU2_LiveCounter;
    };
    }

    namespace pack {
    class VCU2 {
    public:
        VCU2() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU2_Checksum{0, [](){}};
        adas::node::in<int> VCU2_DriverSideBuckle{0, [](){}};
        adas::node::in<int> VCU2_WiperStatus{0, [](){}};
        adas::node::in<int> VCU2_JerkSt{0, [](){}};
        adas::node::in<int> VCU2_Button1{0, [](){}};
        adas::node::in<int> VCU2_Button2{0, [](){}};
        adas::node::in<int> VCU2_DriverDoorStatus{0, [](){}};
        adas::node::in<int> VCU2_PassengerDoorStatus{0, [](){}};
        adas::node::in<int> VCU2_RLDoorStatus{0, [](){}};
        adas::node::in<int> VCU2_RRDoorStatus{0, [](){}};
        adas::node::in<int> VCU2_DriverLockStatus{0, [](){}};
        adas::node::in<int> VCU2_PassengerLockStatus{0, [](){}};
        adas::node::in<int> VCU2_RLLockStatus{0, [](){}};
        adas::node::in<int> VCU2_RRLockStatus{0, [](){}};
        adas::node::in<int> VCU2_EngHoodStatus{0, [](){}};
        adas::node::in<int> VCU2_LuggageDoorStatus{0, [](){}};
        adas::node::in<int> VCU2_EVReady{0, [](){}};
        adas::node::in<int> VCU2_IgnitionKey{0, [](){}};
        adas::node::in<int> VCU2_SteeringLight{0, [](){}};
        adas::node::in<int> VCU2_HazardLight{0, [](){}};
        adas::node::in<int> VCU2_LowBeamStatus{0, [](){}};
        adas::node::in<int> VCU2_HighBeamStatus{0, [](){}};
        adas::node::in<int> VCU2_MainSwitch{0, [](){}};
        adas::node::in<int> VCU2_ResumeSwitch{0, [](){}};
        adas::node::in<int> VCU2_CancelSwitch{0, [](){}};
        adas::node::in<int> VCU2_UpSwitch{0, [](){}};
        adas::node::in<int> VCU2_DownSwitch{0, [](){}};
        adas::node::in<int> VCU2_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU2 data;
            data.VCU2_Checksum(VCU2_Checksum.get());
            data.VCU2_DriverSideBuckle(adas::ehs3::VCU2::VCU2_DriverSideBuckle_Choices{VCU2_DriverSideBuckle.get()});
            data.VCU2_WiperStatus(adas::ehs3::VCU2::VCU2_WiperStatus_Choices{VCU2_WiperStatus.get()});
            data.VCU2_JerkSt(adas::ehs3::VCU2::VCU2_JerkSt_Choices{VCU2_JerkSt.get()});
            data.VCU2_Button1(adas::ehs3::VCU2::VCU2_Button1_Choices{VCU2_Button1.get()});
            data.VCU2_Button2(adas::ehs3::VCU2::VCU2_Button2_Choices{VCU2_Button2.get()});
            data.VCU2_DriverDoorStatus(adas::ehs3::VCU2::VCU2_DriverDoorStatus_Choices{VCU2_DriverDoorStatus.get()});
            data.VCU2_PassengerDoorStatus(adas::ehs3::VCU2::VCU2_PassengerDoorStatus_Choices{VCU2_PassengerDoorStatus.get()});
            data.VCU2_RLDoorStatus(adas::ehs3::VCU2::VCU2_RLDoorStatus_Choices{VCU2_RLDoorStatus.get()});
            data.VCU2_RRDoorStatus(adas::ehs3::VCU2::VCU2_RRDoorStatus_Choices{VCU2_RRDoorStatus.get()});
            data.VCU2_DriverLockStatus(adas::ehs3::VCU2::VCU2_DriverLockStatus_Choices{VCU2_DriverLockStatus.get()});
            data.VCU2_PassengerLockStatus(adas::ehs3::VCU2::VCU2_PassengerLockStatus_Choices{VCU2_PassengerLockStatus.get()});
            data.VCU2_RLLockStatus(adas::ehs3::VCU2::VCU2_RLLockStatus_Choices{VCU2_RLLockStatus.get()});
            data.VCU2_RRLockStatus(adas::ehs3::VCU2::VCU2_RRLockStatus_Choices{VCU2_RRLockStatus.get()});
            data.VCU2_EngHoodStatus(adas::ehs3::VCU2::VCU2_EngHoodStatus_Choices{VCU2_EngHoodStatus.get()});
            data.VCU2_LuggageDoorStatus(adas::ehs3::VCU2::VCU2_LuggageDoorStatus_Choices{VCU2_LuggageDoorStatus.get()});
            data.VCU2_EVReady(adas::ehs3::VCU2::VCU2_EVReady_Choices{VCU2_EVReady.get()});
            data.VCU2_IgnitionKey(adas::ehs3::VCU2::VCU2_IgnitionKey_Choices{VCU2_IgnitionKey.get()});
            data.VCU2_SteeringLight(adas::ehs3::VCU2::VCU2_SteeringLight_Choices{VCU2_SteeringLight.get()});
            data.VCU2_HazardLight(adas::ehs3::VCU2::VCU2_HazardLight_Choices{VCU2_HazardLight.get()});
            data.VCU2_LowBeamStatus(adas::ehs3::VCU2::VCU2_LowBeamStatus_Choices{VCU2_LowBeamStatus.get()});
            data.VCU2_HighBeamStatus(adas::ehs3::VCU2::VCU2_HighBeamStatus_Choices{VCU2_HighBeamStatus.get()});
            data.VCU2_MainSwitch(adas::ehs3::VCU2::VCU2_MainSwitch_Choices{VCU2_MainSwitch.get()});
            data.VCU2_ResumeSwitch(adas::ehs3::VCU2::VCU2_ResumeSwitch_Choices{VCU2_ResumeSwitch.get()});
            data.VCU2_CancelSwitch(adas::ehs3::VCU2::VCU2_CancelSwitch_Choices{VCU2_CancelSwitch.get()});
            data.VCU2_UpSwitch(adas::ehs3::VCU2::VCU2_UpSwitch_Choices{VCU2_UpSwitch.get()});
            data.VCU2_DownSwitch(adas::ehs3::VCU2::VCU2_DownSwitch_Choices{VCU2_DownSwitch.get()});
            data.VCU2_LiveCounter(VCU2_LiveCounter.get());
            can_frame frame{.can_id=0x68b};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Vehicle Info */
    /* id: 0x68f */
    class VCU6 : public adas::can::CanData {
    public:
        VCU6() : adas::can::CanData(8) {}
        explicit VCU6(unsigned char *data) : adas::can::CanData(data, 8) {}

        enum class VCU6_GearInfo_Choices {
            NoConnect = 7,
            D = 3,
            N = 2,
            R = 1,
            P = 0,
        };

        enum class VCU6_BrakeInfo_Choices {
            Brake = 1,
            NoBrake = 0,
        };

        enum class VCU6_EPBSwitch_Choices {
            Release = 2,
            Lock = 1,
            NoRequest = 0,
        };

        enum class VCU6_EPBStatus_Choices {
            Locking = 3,
            Releasing = 2,
            Locked = 1,
            Released = 0,
        };

        enum class VCU6_DrivingDirection_Choices {
            Stop = 2,
            Backward = 1,
            Forward = 0,
        };

        /* 校验和 */
        uint8_t VCU6_Checksum() const {
            return get<uint8_t>(0, 8, LITTLE_ENDIAN);
        }
        void VCU6_Checksum(uint8_t value) {
            set<uint8_t>(0, 8, LITTLE_ENDIAN, value);
        }

        /* 档位信息 */
        VCU6_GearInfo_Choices VCU6_GearInfo() const {
            return static_cast<VCU6_GearInfo_Choices>(get<uint8_t>(8, 3, LITTLE_ENDIAN));
        }
        void VCU6_GearInfo(VCU6_GearInfo_Choices value) {
            set<uint8_t>(8, 3, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 制动信号 */
        VCU6_BrakeInfo_Choices VCU6_BrakeInfo() const {
            return static_cast<VCU6_BrakeInfo_Choices>(get<bool>(11, 1, LITTLE_ENDIAN));
        }
        void VCU6_BrakeInfo(VCU6_BrakeInfo_Choices value) {
            set<bool>(11, 1, LITTLE_ENDIAN, static_cast<bool>(value));
        }

        /* 电子手刹开关 */
        VCU6_EPBSwitch_Choices VCU6_EPBSwitch() const {
            return static_cast<VCU6_EPBSwitch_Choices>(get<uint8_t>(12, 2, LITTLE_ENDIAN));
        }
        void VCU6_EPBSwitch(VCU6_EPBSwitch_Choices value) {
            set<uint8_t>(12, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 电子手刹状态信号 */
        VCU6_EPBStatus_Choices VCU6_EPBStatus() const {
            return static_cast<VCU6_EPBStatus_Choices>(get<uint8_t>(14, 2, LITTLE_ENDIAN));
        }
        void VCU6_EPBStatus(VCU6_EPBStatus_Choices value) {
            set<uint8_t>(14, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 车速 */
        float VCU6_VehicleSpeed() const {
            return get<uint16_t>(16, 14, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void VCU6_VehicleSpeed(float value) {
            set<uint16_t>(16, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* 行驶方向 */
        VCU6_DrivingDirection_Choices VCU6_DrivingDirection() const {
            return static_cast<VCU6_DrivingDirection_Choices>(get<uint8_t>(30, 2, LITTLE_ENDIAN));
        }
        void VCU6_DrivingDirection(VCU6_DrivingDirection_Choices value) {
            set<uint8_t>(30, 2, LITTLE_ENDIAN, static_cast<uint8_t>(value));
        }

        /* 方向盘角度 */
        float VCU6_SteeringAngle() const {
            return get<uint16_t>(32, 14, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(-600);
        }
        void VCU6_SteeringAngle(float value) {
            set<uint16_t>(32, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-600))/static_cast<float>(0.1)));
        }

        /* 反向盘角速度 */
        float VCU6_SteeringSpeed() const {
            return get<uint16_t>(46, 14, LITTLE_ENDIAN) * static_cast<float>(0.1) + static_cast<float>(-600);
        }
        void VCU6_SteeringSpeed(float value) {
            set<uint16_t>(46, 14, LITTLE_ENDIAN, static_cast<uint16_t>((value-(-600))/static_cast<float>(0.1)));
        }

        /* 生命信号 */
        uint8_t VCU6_LiveCounter() const {
            return get<uint8_t>(60, 4, LITTLE_ENDIAN);
        }
        void VCU6_LiveCounter(uint8_t value) {
            set<uint8_t>(60, 4, LITTLE_ENDIAN, value);
        }

    };

    namespace unpack {
    class VCU6 {
    private:
        void can_msg_update() {
            if(0x68f != can_msg.get().can_id)
                return;
            adas::ehs3::VCU6 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU6_Checksum(static_cast<int>(can_data.VCU6_Checksum()));
            VCU6_GearInfo(static_cast<int>(can_data.VCU6_GearInfo()));
            VCU6_BrakeInfo(static_cast<int>(can_data.VCU6_BrakeInfo()));
            VCU6_EPBSwitch(static_cast<int>(can_data.VCU6_EPBSwitch()));
            VCU6_EPBStatus(static_cast<int>(can_data.VCU6_EPBStatus()));
            VCU6_VehicleSpeed(can_data.VCU6_VehicleSpeed());
            VCU6_DrivingDirection(static_cast<int>(can_data.VCU6_DrivingDirection()));
            VCU6_SteeringAngle(can_data.VCU6_SteeringAngle());
            VCU6_SteeringSpeed(can_data.VCU6_SteeringSpeed());
            VCU6_LiveCounter(static_cast<int>(can_data.VCU6_LiveCounter()));
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<int> VCU6_Checksum;
        adas::node::out<int> VCU6_GearInfo;
        adas::node::out<int> VCU6_BrakeInfo;
        adas::node::out<int> VCU6_EPBSwitch;
        adas::node::out<int> VCU6_EPBStatus;
        adas::node::out<float> VCU6_VehicleSpeed;
        adas::node::out<int> VCU6_DrivingDirection;
        adas::node::out<float> VCU6_SteeringAngle;
        adas::node::out<float> VCU6_SteeringSpeed;
        adas::node::out<int> VCU6_LiveCounter;
    };
    }

    namespace pack {
    class VCU6 {
    public:
        VCU6() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<int> VCU6_Checksum{0, [](){}};
        adas::node::in<int> VCU6_GearInfo{0, [](){}};
        adas::node::in<int> VCU6_BrakeInfo{0, [](){}};
        adas::node::in<int> VCU6_EPBSwitch{0, [](){}};
        adas::node::in<int> VCU6_EPBStatus{0, [](){}};
        adas::node::in<float> VCU6_VehicleSpeed{0, [](){}};
        adas::node::in<int> VCU6_DrivingDirection{0, [](){}};
        adas::node::in<float> VCU6_SteeringAngle{0, [](){}};
        adas::node::in<float> VCU6_SteeringSpeed{0, [](){}};
        adas::node::in<int> VCU6_LiveCounter{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU6 data;
            data.VCU6_Checksum(VCU6_Checksum.get());
            data.VCU6_GearInfo(adas::ehs3::VCU6::VCU6_GearInfo_Choices{VCU6_GearInfo.get()});
            data.VCU6_BrakeInfo(adas::ehs3::VCU6::VCU6_BrakeInfo_Choices{VCU6_BrakeInfo.get()});
            data.VCU6_EPBSwitch(adas::ehs3::VCU6::VCU6_EPBSwitch_Choices{VCU6_EPBSwitch.get()});
            data.VCU6_EPBStatus(adas::ehs3::VCU6::VCU6_EPBStatus_Choices{VCU6_EPBStatus.get()});
            data.VCU6_VehicleSpeed(VCU6_VehicleSpeed.get());
            data.VCU6_DrivingDirection(adas::ehs3::VCU6::VCU6_DrivingDirection_Choices{VCU6_DrivingDirection.get()});
            data.VCU6_SteeringAngle(VCU6_SteeringAngle.get());
            data.VCU6_SteeringSpeed(VCU6_SteeringSpeed.get());
            data.VCU6_LiveCounter(VCU6_LiveCounter.get());
            can_frame frame{.can_id=0x68f};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

    /* Wheel Speed Info */
    /* id: 0x690 */
    class VCU7 : public adas::can::CanData {
    public:
        VCU7() : adas::can::CanData(8) {}
        explicit VCU7(unsigned char *data) : adas::can::CanData(data, 8) {}

        /* 左前轮速 */
        float VCU7_WheelSpeed_FL() const {
            return get<uint16_t>(0, 16, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void VCU7_WheelSpeed_FL(float value) {
            set<uint16_t>(0, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* 右前轮速 */
        float VCU7_WheelSpeed_FR() const {
            return get<uint16_t>(16, 16, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void VCU7_WheelSpeed_FR(float value) {
            set<uint16_t>(16, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* 左后轮速 */
        float VCU7_WheelSpeed_RL() const {
            return get<uint16_t>(32, 16, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void VCU7_WheelSpeed_RL(float value) {
            set<uint16_t>(32, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

        /* 右后轮速 */
        float VCU7_WheelSpeed_RR() const {
            return get<uint16_t>(48, 16, LITTLE_ENDIAN) * static_cast<float>(0.01) + static_cast<float>(0);
        }
        void VCU7_WheelSpeed_RR(float value) {
            set<uint16_t>(48, 16, LITTLE_ENDIAN, static_cast<uint16_t>((value-(0))/static_cast<float>(0.01)));
        }

    };

    namespace unpack {
    class VCU7 {
    private:
        void can_msg_update() {
            if(0x690 != can_msg.get().can_id)
                return;
            adas::ehs3::VCU7 can_data(const_cast<unsigned char*>(can_msg.get().data));
            adas::node::sync_out so;
            VCU7_WheelSpeed_FL(can_data.VCU7_WheelSpeed_FL());
            VCU7_WheelSpeed_FR(can_data.VCU7_WheelSpeed_FR());
            VCU7_WheelSpeed_RL(can_data.VCU7_WheelSpeed_RL());
            VCU7_WheelSpeed_RR(can_data.VCU7_WheelSpeed_RR());
        }
    public:
        adas::node::in<can_frame> can_msg{{}, [this](){can_msg_update();}};
        adas::node::out<float> VCU7_WheelSpeed_FL;
        adas::node::out<float> VCU7_WheelSpeed_FR;
        adas::node::out<float> VCU7_WheelSpeed_RL;
        adas::node::out<float> VCU7_WheelSpeed_RR;
    };
    }

    namespace pack {
    class VCU7 {
    public:
        VCU7() {
            timer_.start();
        }
    public:
        adas::node::out<can_frame> can_msg;
        adas::node::in<float> VCU7_WheelSpeed_FL{0, [](){}};
        adas::node::in<float> VCU7_WheelSpeed_FR{0, [](){}};
        adas::node::in<float> VCU7_WheelSpeed_RL{0, [](){}};
        adas::node::in<float> VCU7_WheelSpeed_RR{0, [](){}};
    private:
        adas::node::timer timer_{adas::node::timer::mode::cycle, std::chrono::milliseconds(20) , [this]() { timer_handler(); }};
        void timer_handler() {
            adas::ehs3::VCU7 data;
            data.VCU7_WheelSpeed_FL(VCU7_WheelSpeed_FL.get());
            data.VCU7_WheelSpeed_FR(VCU7_WheelSpeed_FR.get());
            data.VCU7_WheelSpeed_RL(VCU7_WheelSpeed_RL.get());
            data.VCU7_WheelSpeed_RR(VCU7_WheelSpeed_RR.get());
            can_frame frame{.can_id=0x690};
            frame.can_dlc = data.data().size();
            std::copy(data.data().begin(), data.data().end(), frame.data);
            can_msg(frame);
        }
    };
    }

}

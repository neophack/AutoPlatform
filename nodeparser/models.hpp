#pragma once

#include <QtCore/QObject>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include "invocable.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MyNodeData : public NodeData {
private:
    QString _name;
public:
    explicit MyNodeData(QString name) : _name(std::move(name)) {}

    NodeDataType
    type() const override { return NodeDataType{"MyNodeData", _name}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.

class MyDataModel : public NodeDataModel {
    Q_OBJECT
private:
    QString _name, _caption;
    std::vector<QString> _in, _out;

public:
    MyDataModel(QString name, QString caption, std::vector<QString> in, std::vector<QString> out) :
        _name(std::move(name)), _caption(std::move(caption)), _in(std::move(in)), _out(std::move(out)) {}

    virtual
    ~MyDataModel() {}

public:

    QString
    caption() const override {
        return _caption;
    }

    QString
    name() const override {
        return _name;
    }

public:

    QJsonObject
    save() const override {
        QJsonObject modelJson;

        modelJson["name"] = name();

        return modelJson;
    }

public:

    unsigned int
    nPorts(PortType type) const override {
        switch (type) {

        case PortType::None:
            return 0;
        case PortType::In:
            return _in.size();
        case PortType::Out:
            return _out.size();
        default:
            return 0;
        }
    }

    NodeDataType
    dataType(PortType type, PortIndex index) const override {
        QString port_name;
        switch (type) {

        case PortType::None:
            port_name = "<none>";
            break;
        case PortType::In:
            port_name = _in[index];
            break;
        case PortType::Out:
            port_name = _out[index];
            break;
        }
        //return MyNodeData(port_name).type();
        return NodeDataType{"my_type", _name};
    }

    std::shared_ptr<NodeData>
    outData(PortIndex) override {
        return nullptr;
    }

    void
    setInData(std::shared_ptr<NodeData>, int) override {
        //
    }

    QWidget *
    embeddedWidget() override { return nullptr; }
};

class CANInputModel : public MyDataModel {
public:
    CANInputModel() : MyDataModel("CANInput", "CAN Input", {}, {"message"}) {}
};

class CANOutputModel : public MyDataModel {
public:
    CANOutputModel() : MyDataModel("CANOutput", "CAN Output", {"message"}, {}) {}
};

class CameraModel : public MyDataModel {
public:
    CameraModel() : MyDataModel("GeneralCam", "General Cam", {}, {"image"}) {}
};

class LidarModel : public MyDataModel {
public:
    LidarModel() : MyDataModel("Lidar", "Lidar", {}, {"point_cloud"}) {}
};

class GPSModel : public MyDataModel {
public:
    GPSModel() : MyDataModel("GPS", "GPS", {}, {"nav_status"}) {}
};

class MobileyeEyeQModel : public MyDataModel {
public:
    MobileyeEyeQModel() : MyDataModel("SmartCam", "Smart Cam", {}, {"objects", "lanes", "CIPV", "TSR"}) {}
};

class PathTrackingModel : public MyDataModel {
public:
    PathTrackingModel() : MyDataModel("PathTracking", "Path Tracking", {"curve"}, {"steering_angle"}) {}
};

class VelocityControlModel : public MyDataModel {
public:
    VelocityControlModel() : MyDataModel("VelocityControl", "Velocity Control",
    {"CIPV", "target_velocity", "target_distance"}, {"acceleration"}) {}
};

class EHS3ControlModel : public MyDataModel {
public:
    EHS3ControlModel() : MyDataModel("VehicleEHS3Control", "红旗 EHS3 底盘控制",
    {"steer_ctrl_req", "steering_angle", "accel_ctrl_req", "acceleration", "gear_req",
                                     "parking_brake_req"}, {"can_msg"}) {}
};

class EHS3FeedbackModel : public MyDataModel {
public:
    EHS3FeedbackModel() : MyDataModel("VehicleEHS3Feedback", "红旗 EHS3 底盘反馈", {"can_msg"},
    {"steer_ctrl_enabled", "steer_takeover", "accel_ctrl_enabled", "accel_takeover",
                                      "gear", "parking_brake",
                                      "button_LKS", "button_HWA", "button_ACC_main", "button_ACC_resume",
                                      "button_ACC_cancel", "button_ACC_up", "button_ACC_down"}) {}
};

class Radar : public MyDataModel {
public:
    Radar() : MyDataModel("Radar", "Radar", {"can_msg"}, {"objects"}) {}
};

class IMU : public MyDataModel {
public:
    IMU() : MyDataModel("IMU", "IMU", {}, {"acceleration", "angular_velocity"}) {}
};

class ACCState : public MyDataModel {
public:
    ACCState() : MyDataModel("ACCApp", "ACC 应用",
    {"button_main", "button_resume", "button_cancel", "button_up", "button_down",
                             "accel_ctrl_enabled", "accel_takeover", "gear", "parking_brake"},
    {"accel_ctrl_req", "target_distance", "target_velocity", "gear_req",
                             "parking_brake_req"}) {}
};

class LKSState : public MyDataModel {
public:
    LKSState() : MyDataModel("LKSApp", "LKS 应用", {"button_main", "steer_ctrl_enabled", "steer_takeover"},
    {"steer_ctrl_req"}) {}
};

class LaneCenter : public MyDataModel {
public:
    LaneCenter() : MyDataModel("LaneCenter", "Lane Center", {"lanes"}, {"curve"}) {}
};

class Func : public MyDataModel {
public:
    Func() : MyDataModel("Add", "Add", {"a", "b"}, {"out"}) {}
};
class InvocableDataModel : public NodeDataModel {
    Q_OBJECT
private:
    Invocable _invocable;

public:
    InvocableDataModel (Invocable  invocable): _invocable(std::move(invocable)) {}


public:

    QString
    caption() const override {
        return QString::fromStdString(_invocable.getName());
    }

    QString
    name() const override {
        return QString::fromStdString(_invocable.getName());
    }

public:

    QJsonObject
    save() const override {
        QJsonObject modelJson;

        modelJson["name"] = name();

        return modelJson;
    }

public:

    unsigned int
    nPorts(PortType type) const override {
        switch (type) {
        case PortType::None:
            return 0;
        case PortType::In:
            return _invocable.getNumInput();
        case PortType::Out:
            return _invocable.getNumOutput() + (_invocable.getReturning().isVoid()? 0 : 1);
        default:
            return 0;
        }
    }

    NodeDataType
    dataType(PortType type, PortIndex index) const override {
        QString port_name;
        QString type_name;
        switch (type) {

        case PortType::None:
            port_name = "<none>";
            break;
        case PortType::In:
            port_name = QString::fromStdString(_invocable.getInputParam(index).getName());
            type_name = QString::fromStdString(_invocable.getInputParam(index).getType());
            break;
        case PortType::Out:
            if(!_invocable.getReturning().isVoid()) {
                if(0 == index)
                    return NodeDataType{QString::fromStdString(_invocable.getReturning().getType()), "out"};
                else
                    index--;
            }
            port_name = QString::fromStdString(_invocable.getOutputParam(index).getName());
            type_name = QString::fromStdString(_invocable.getOutputParam(index).getType());
            break;
        }
        return NodeDataType{type_name, port_name};
    }

    std::shared_ptr<NodeData>
    outData(PortIndex) override {
        return nullptr;
    }

    void
    setInData(std::shared_ptr<NodeData>, int) override {
        //
    }

    QWidget *
    embeddedWidget() override { return nullptr; }
};

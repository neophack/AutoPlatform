#ifndef NODESOURCEDATAMODEL_H
#define NODESOURCEDATAMODEL_H

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include "TextData.hpp"
#include <nodes/NodeDataModel>
#include <iostream>


using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::NodeData;

class AICCSourceDataModel : public NodeDataModel
{
    Q_OBJECT
public:
    AICCSourceDataModel();
    virtual
    ~AICCSourceDataModel(){}

public:
    QString caption() const override{return QStringLiteral("数据源");}
    bool captionVisible() const override {return false;}
    QString name() const override {return QString("数据源节点");}


public:
    unsigned int nPorts(PortType portType) const override;
    NodeDataType dataType(PortType portType,PortIndex portIndex) const override;
    std::shared_ptr<NodeData> outData(PortIndex port) override;
    void setInData(std::shared_ptr<NodeData>,int) override{};
    QWidget *embeddedWidget() override{return _lineEdit;}

private:
    QLineEdit *_lineEdit;

};

#endif // NODESOURCEDATAMODEL_H

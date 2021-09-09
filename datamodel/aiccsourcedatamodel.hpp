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
    AICCSourceDataModel():_lineEdit(new QLineEdit("Default Text"))
    {
        connect(_lineEdit,&QLineEdit::textChanged,this,[=](QString const &string)
        {
            Q_UNUSED(string);
            Q_EMIT dataUpdated(0);
        });
    }
    virtual
    ~AICCSourceDataModel(){}

public:
    QString caption() const override{return QStringLiteral("数据源");}
    bool captionVisible() const override {return false;}
    QString name() const override {return QString("数据源节点");}


public:
    unsigned int nPorts(PortType portType) const override
    {
        unsigned int result = 1;
        switch(portType)
        {
        case PortType::In:
            result = 0;
            break;
        case PortType::Out:
            result = 1;
        default:
            break;
        }
        return result;
    }
    NodeDataType dataType(PortType portType,PortIndex portIndex) const override{return TextData().type();}
    std::shared_ptr<NodeData> outData(PortIndex port) override{return std::make_shared<TextData>(_lineEdit->text());}
    void setInData(std::shared_ptr<NodeData>,int) override{};
    QWidget *embeddedWidget() override{return _lineEdit;}

private:
    QLineEdit *_lineEdit;

};

#endif // NODESOURCEDATAMODEL_H

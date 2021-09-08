#ifndef AICCDISPLAYDATAMODEL_H
#define AICCDISPLAYDATAMODEL_H

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <nodes/NodeDataModel>
#include "TextData.hpp"
#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

class AICCDisplayDataModel : public NodeDataModel
{
    Q_OBJECT

    Q_PROPERTY(QString caption READ caption )
    Q_PROPERTY(QString captionVisible READ captionVisible )

public:
    AICCDisplayDataModel();
    virtual ~AICCDisplayDataModel(){}
public:
    QString caption() const override{return QString("数据结果");}
    bool captionVisible() const override {return false;}
    QString name() const override { return QString("数据结果节点");}
public:
    unsigned int nPorts(PortType portType) const override;
    NodeDataType dataType(PortType portType,PortIndex portIndex) const override;
    std::shared_ptr<NodeData> outData(PortIndex port) override;
    void setInData(std::shared_ptr<NodeData> data,int) override
    {
        auto textData = std::dynamic_pointer_cast<TextData>(data);
        if(textData)
        {
            _label->setText(textData->text());
        }
        else
        {
            _label->clear();
        }
        _label->adjustSize();
    }

    QWidget * embeddedWidget() override{return _label;}

private:
    QLabel *_label;
};

#endif // AICCDISPLAYDATAMODEL_H

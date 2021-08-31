#ifndef AICCCALCULATOR_H
#define AICCCALCULATOR_H

#include <nodes/NodeDataModel>
#include <QLineEdit>
#include <QLabel>
#include <QtGui/QDoubleValidator>

#include <QtCore/QObject>
#include <iostream>

using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::NodeData;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeValidationState;

///
class DecimalData:public NodeData
{
public:
    DecimalData():_number(0.0){}
    DecimalData(double const number):_number(number){}
    NodeDataType type() const override {return NodeDataType{"decimal","Decimal"};}
    double number() const{return _number;}
    QString numberAsText()const{return QString::number(_number,'f');}
private:
    double _number;
};

class AICCNumberSourceDataModel:public NodeDataModel
{
    Q_OBJECT
public:
    AICCNumberSourceDataModel():_lineEdit(new QLineEdit())
    {
        _lineEdit->setValidator(new QDoubleValidator());
        _lineEdit->setMaximumSize(_lineEdit->sizeHint());
        connect(_lineEdit,&QLineEdit::textChanged,this,[&](QString const &string)
        {
            Q_UNUSED(string);
            bool ok = false;
            double number = _lineEdit->text().toDouble(&ok);
            if(ok)
            {
                _number = std::make_shared<DecimalData>(number);
                Q_EMIT dataUpdated(0);
            } else Q_EMIT dataInvalidated(0);
        });
        _lineEdit->setText("0.0");
    }

    ~AICCNumberSourceDataModel(){}
public:
    QString caption() const override{return QStringLiteral("四则运算源数据");}
    bool captionVisible() const override{return false;}
    QString name() const override {return QStringLiteral("AICCNumberSource");}

    //public:
    QJsonObject save() const override
    {
        QJsonObject modelJson = NodeDataModel::save();
        if(_number)
            modelJson["number"]=QString::number(_number->number());
        return modelJson;
    }

    void restore(QJsonObject const &p) override
    {
        QJsonValue v=p["number"];
        if(!v.isUndefined())
        {
            QString strNum = v.toString();
            bool ok;
            double d = strNum.toDouble(&ok);
            if(ok)
            {
                _number = std::make_shared<DecimalData>(d);
                _lineEdit->setText(strNum);
            }
        }
    };

public:
    unsigned int nPorts(PortType portType) const override
    {
        unsigned int result = 1;
        switch(portType){
        case PortType::In:
            result = 0;
            break;
        case PortType::Out:
            result = 1;
            break;
        default:
            break;
        }
        return result;
    };

    NodeDataType dataType(PortType portType,PortIndex portIndex) const override{return DecimalData().type();};
    std::shared_ptr<NodeData> outData(PortIndex port) override{return _number;};
    void setInData(std::shared_ptr<NodeData> data,int) override{}
    QWidget *embeddedWidget() override {return _lineEdit;}
private:
    std::shared_ptr<DecimalData> _number;
    QLineEdit *_lineEdit;

};


class AICCNumberResultDataModel:public NodeDataModel
{
    Q_OBJECT
public:
    AICCNumberResultDataModel():_label(new QLabel())
    {
        _label->setMargin(3);
    }
    ~AICCNumberResultDataModel(){}
public:
    QString caption() const override {return QStringLiteral("Number Result");}
    bool captionVisible() const override {return false;}
    QString name() const override {return QStringLiteral("AICCNumberResult");}
public:
    unsigned int nPorts(PortType portType) const override
    {
        unsigned int result = 1;
        switch(portType)
        {
        case PortType::In:
            result = 1;
            break;
        case PortType::Out:
            result = 0;
            break;
        default:
            break;
        }
        return result;
    };

    NodeDataType dataType(PortType portType,PortIndex portIndex) const override{return DecimalData().type();};
    std::shared_ptr<NodeData> outData(PortIndex port) override{std::shared_ptr<NodeData> ptr;return ptr;}
    void setInData(std::shared_ptr<NodeData> data,int) override
    {
        auto numberData = std::dynamic_pointer_cast<DecimalData>(data);
        if(numberData)
        {
            modelValidationState = NodeValidationState::Valid;
            modelValidationError = QString();
            _label->setText(numberData->numberAsText());
        }
        else
        {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _label->clear();
        }
        _label->adjustSize();
    };

    QWidget *embeddedWidget() override {return _label;}
    NodeValidationState validationState() const override{return modelValidationState;};
    QString validationMessage() const override{return modelValidationError;};
private:
    NodeValidationState modelValidationState = NodeValidationState::Warning;
    QString modelValidationError = QStringLiteral("Missing or incorrect inputs");

    QLabel *_label;
};



#endif // AICCCALCULATOR_H

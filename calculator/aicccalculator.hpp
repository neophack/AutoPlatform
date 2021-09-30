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

///节点数据类
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

///源数据节点
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
public:
    virtual bool portCaptionVisible(PortType portType,PortIndex portIndex) const override{Q_UNUSED(portType);Q_UNUSED(portIndex);return true;}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::Out:
            return QStringLiteral("输入数据");
        default:
            break;
        }
        return QString();
    }

public:
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

///结果数据节点
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
    virtual bool portCaptionVisible(PortType portType,PortIndex portIndex) const override{Q_UNUSED(portType);Q_UNUSED(portIndex);return true;}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::In:
            return QStringLiteral("结果");
        default:
            break;
        }
        return QString();
    }
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
//        auto numberData = std::dynamic_pointer_cast<DecimalData>(data);
        auto numberData = std::static_pointer_cast<DecimalData>(data);
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

//--------------------------------计算部分----------------------
///计算操作数据模型基类
class MathOperationDataModel:public NodeDataModel
{
    Q_OBJECT
public:
    virtual ~MathOperationDataModel(){}
public:
    virtual bool portCaptionVisible(PortType portType,PortIndex portIndex) const override{Q_UNUSED(portType);Q_UNUSED(portIndex);return true;}
    unsigned int nPorts(PortType portType) const override
    {
        unsigned int result;
        if(portType == PortType::In)
            result = 2;
        else
            result = 1;
        return result;
    }
    NodeDataType dataType(PortType portType,PortIndex portIndex) const override{return DecimalData().type();}
    std::shared_ptr<NodeData> outData(PortIndex port) override{return std::static_pointer_cast<NodeData>(_result);}
    void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override
    {
//        auto numberData = std::dynamic_pointer_cast<DecimalData>(data);
        auto numberData = std::static_pointer_cast<DecimalData>(data);
        if(portIndex==0)
            _number1 = numberData;
        else
            _number2 = numberData;
        compute();
    }
    QWidget *embeddedWidget() override{return nullptr;}
    NodeValidationState validationState() const override{return modelValidationState;}
    QString validationMessage() const override {return modelValidationError;}
protected:
    virtual void compute() = 0;

protected:
    std::weak_ptr<DecimalData> _number1;
    std::weak_ptr<DecimalData> _number2;
    std::shared_ptr<DecimalData> _result;
    NodeValidationState modelValidationState = NodeValidationState::Warning;
    QString modelValidationError = QString("Missing or incorrect inputs");
};

///加法计算
class AICCAdditionModel:public MathOperationDataModel
{
public:
    virtual ~AICCAdditionModel(){}
public:
    QString caption() const override{return QStringLiteral("加法");}
    QString name()const override{return QStringLiteral("AICCAdditionOperation");}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::In:
            if(portIndex==0)
                return QStringLiteral("被加数");
            else if(portIndex==1)
                return QStringLiteral("加数");
        case PortType::Out:
            return QStringLiteral("结果");
        default:
            break;
        }
        return QString();
    }
private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;
        auto n1 = _number1.lock();
        auto n2 = _number2.lock();
        if(n1 && n2)
        {
            modelValidationState = NodeValidationState::Valid;
            modelValidationError = QString();
            _result = std::make_shared<DecimalData>(n1->number()+n2->number());
        }
        else
        {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }
        Q_EMIT dataUpdated(outPortIndex);
    }
};

///减法计算
class AICCSubtractionModel:public MathOperationDataModel
{
public:
    virtual ~AICCSubtractionModel(){}
public:
    QString caption() const override {return QStringLiteral("减法");}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::In:
            if(portIndex == 0)
                return QStringLiteral("被减数");
            else if(portIndex == 1)
                return QStringLiteral("减数");
        case PortType::Out:
            return QStringLiteral("结果");
        default:
            break;
        }
        return QString();
    }
    QString name() const override {return QStringLiteral("AICCSubtractionOperation");}
private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;
        auto n1 = _number1.lock();
        auto n2 = _number2.lock();
        if(n1 && n2)
        {
            modelValidationState = NodeValidationState::Valid;
            modelValidationError = QString();
            _result = std::make_shared<DecimalData>(n1->number()-n2->number());
        }
        else
        {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }
        Q_EMIT dataUpdated(outPortIndex);
    }
};

///乘法计算
class AICCMultiplicationModel:public MathOperationDataModel
{
public:virtual ~AICCMultiplicationModel(){}
public:
    QString caption() const override {return QStringLiteral("乘法");}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::In:
            if(portIndex==0)
                return QStringLiteral("被乘数");
            else if(portIndex==1)
                return QStringLiteral("乘数");
        case PortType::Out:
            return QStringLiteral("结果");
        default:
            break;
        }
        return QString();
    }
    QString name() const override{return QStringLiteral("AICCMultiplicationOperation");}
private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;
        auto n1 = _number1.lock();
        auto n2 = _number2.lock();
        if(n1 && n2)
        {
            modelValidationState = NodeValidationState::Valid;
            modelValidationError = QString();
            _result = std::make_shared<DecimalData>(n1->number()*n2->number());
        }
        else
        {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }
        Q_EMIT dataUpdated(outPortIndex);
    }

};

///除法计算
class AICCDivisionModel:public MathOperationDataModel
{
public:virtual ~AICCDivisionModel(){}
public:
    QString caption() const override {return QStringLiteral("除法");}
    virtual QString portCaption(PortType portType,PortIndex portIndex) const override
    {
        switch(portType)
        {
        case PortType::In:
            if(portIndex==0)
                return QStringLiteral("被除数");
            else if(portIndex==1)
                return QStringLiteral("除数");
        case PortType::Out:
            return QStringLiteral("结果");
        default:
            break;
        }
        return QString();
    }
    QString name() const override{return QStringLiteral("AICCDivisionOperation");}
private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;
        auto n1 = _number1.lock();
        auto n2 = _number2.lock();
        if(n1 && n2)
        {
            modelValidationState = NodeValidationState::Valid;
            modelValidationError = QString();
            _result = std::make_shared<DecimalData>(n1->number()/n2->number());
        }
        else
        {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }
        Q_EMIT dataUpdated(outPortIndex);
    }
};

///求余计算


#endif // AICCCALCULATOR_H


#include "datamodel/aiccsourcedatamodel.hpp"


AICCSourceDataModel::AICCSourceDataModel():_lineEdit(new QLineEdit("Default Text"))
{
    //    _lineEdit->setValidator(new QDoubleValidator());
    //    _lineEdit->setMaximumSize(_lineEdit->sizeHint());
    connect(_lineEdit,&QLineEdit::textChanged,this,[=](QString const &string){
        Q_UNUSED(string);
        Q_EMIT dataUpdated(0);
    });
}

unsigned int AICCSourceDataModel::nPorts(PortType portType) const
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

NodeDataType AICCSourceDataModel::dataType(PortType,PortIndex) const
{
    return TextData().type();
}

std::shared_ptr<NodeData> AICCSourceDataModel::outData(PortIndex)
{
    return std::make_shared<TextData>(_lineEdit->text());
}

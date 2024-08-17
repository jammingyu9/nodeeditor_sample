#include "ProgramDataModel.hpp"
#include "ProgramData.hpp"
#include "RoutineData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QIntValidator>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

ProgramDataModel::ProgramDataModel()
    : _program(std::make_shared<ProgramData>(QString("")))
    , _params{nullptr}
{}

QJsonObject ProgramDataModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["name"] = _program->name();
    return modelJson;
}

void ProgramDataModel::load(QJsonObject const &p)
{
    QJsonValue v = p["name"];

    if (!v.isUndefined()) {
        QString name = v.toString();

        _program = std::make_shared<ProgramData>(name);
        if (_params) {
            _params->setParamName(name);
        }
    }
}

unsigned int ProgramDataModel::nPorts(PortType portType) const
{
    unsigned int result;

    if (portType == PortType::In)
        result = 3;
    else
        result = 0;

    return result;
}

void ProgramDataModel::onNameTextEdited(QString const &str)
{

    _program = std::make_shared<ProgramData>(str);

    Q_EMIT dataUpdated(0);
}

NodeDataType ProgramDataModel::dataType(PortType portType, PortIndex portIndex) const
{
    if (portType == PortType::In) {
        return RoutineData().type();
    }
    return ProgramData().type();
}

std::shared_ptr<NodeData> ProgramDataModel::outData(PortIndex)
{
    return _program; // inherits NodeData
}

QWidget *ProgramDataModel::embeddedWidget()
{
    if (!_params) {
        _params = new ProgramParamWidget();

        connect(_params->nameParamEdit(), &QLineEdit::textChanged, this, &ProgramDataModel::onNameTextEdited);

        _params->setParamName(_program->name());
    }

    return _params;
}

void ProgramDataModel::setName(QString name)
{
    _program = std::make_shared<ProgramData>(name);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamName(name);
}

QString ProgramDataModel::programName() const
{
    if (_program)
        return _program->name();
    else
        return QString("N/A");
}

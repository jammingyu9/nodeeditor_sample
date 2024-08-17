#include "RoutineDataModel.hpp"
#include "RoutineData.hpp"
#include "TrainSetData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QIntValidator>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

RoutineDataModel::RoutineDataModel()
    : _routine(std::make_shared<RoutineData>(QString(""), 1, 15))
    , _params{nullptr}
{}

QJsonObject RoutineDataModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["name"] = _routine->name();
    modelJson["repetition"] = QString::number(_routine->repetition());
    modelJson["resttime"] = QString::number(_routine->restTime());

    return modelJson;
}

void RoutineDataModel::load(QJsonObject const &p)
{
    QJsonValue v1 = p["name"];
    QJsonValue v2 = p["repetition"];
    QJsonValue v3 = p["resttime"];

    if (!v1.isUndefined() && !v2.isUndefined() && !v3.isUndefined()) {
        QString name = v1.toString();
        QString strRepetition = v2.toString();
        QString strRestTime = v3.toString();

        bool ok1, ok2;
        unsigned int repetition = strRepetition.toUInt(&ok1);
        unsigned int restTime = strRestTime.toUInt(&ok2);

        if (ok1 && ok2) {
            _routine = std::make_shared<RoutineData>(name, repetition, restTime);
            if (_params) {
                _params->setParamName(name);
                _params->setParamRepetition(repetition);
                _params->setParamRestTime(restTime);
            }
        }
    }
}

unsigned int RoutineDataModel::nPorts(PortType portType) const
{
    unsigned int result;

    if (portType == PortType::In)
        result = 5;
    else
        result = 1;

    return result;
}

void RoutineDataModel::onNameTextEdited(QString const &str)
{
    unsigned int repetition = _routine->repetition();
    unsigned int restTime = _routine->restTime();

    _routine = std::make_shared<RoutineData>(str, repetition, restTime);

    Q_EMIT dataUpdated(0);
}

void RoutineDataModel::onRepetitionTextEdited(QString const &str)
{
    bool ok = false;
    unsigned int repetition = str.toUInt(&ok);

    if (ok) {
        QString name = _routine->name();
        unsigned int restTime = _routine->restTime();
        _routine = std::make_shared<RoutineData>(name, repetition, restTime);

        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

void RoutineDataModel::onRestTimeTextEdited(QString const &str)
{
    bool ok = false;
    unsigned int restTime = str.toUInt(&ok);

    if (ok) {
        QString name = _routine->name();
        unsigned int repetition = _routine->repetition();
        _routine = std::make_shared<RoutineData>(name, repetition, restTime);

        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType RoutineDataModel::dataType(PortType portType, PortIndex portIndex) const
{
    if (portType == PortType::In) {
        return TrainSetData().type();
    }
    return RoutineData().type();
}

std::shared_ptr<NodeData> RoutineDataModel::outData(PortIndex)
{
    return _routine; // inherits NodeData
}

QWidget *RoutineDataModel::embeddedWidget()
{
    if (!_params) {
        _params = new RoutineParamWidget();

        connect(_params->nameParamEdit(), &QLineEdit::textChanged, this, &RoutineDataModel::onNameTextEdited);
        connect(_params->repetitionParamEdit(), &QLineEdit::textChanged, this, &RoutineDataModel::onRepetitionTextEdited);
        connect(_params->restTimeParamEdit(), &QLineEdit::textChanged, this, &RoutineDataModel::onRestTimeTextEdited);

        _params->setParamName(_routine->name());
        _params->setParamRepetition(_routine->repetition());
        _params->setParamRestTime(_routine->restTime());
    }

    return _params;
}

void RoutineDataModel::setName(QString name)
{
    unsigned int repetition = 0;
    unsigned int restTime = 3;
    if (_routine) {
        repetition = _routine->repetition();
        restTime = _routine->restTime();
    }

    _routine = std::make_shared<RoutineData>(name, repetition, restTime);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamName(name);
}

void RoutineDataModel::setRepetition(unsigned int repetition)
{
    QString name("");
    unsigned int restTime = 3;
    if (_routine) {
        name = _routine->name();
        restTime = _routine->restTime();
    }

    _routine = std::make_shared<RoutineData>(name, repetition, restTime);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamRepetition(repetition);
}

void RoutineDataModel::setRestTime(unsigned int restTime)
{
    QString name("");
    unsigned int repetition = 0;
    if (_routine) {
        name = _routine->name();
        repetition = _routine->repetition();
    }

    _routine = std::make_shared<RoutineData>(name, repetition, restTime);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamRestTime(restTime);
}

QString RoutineDataModel::routineName() const
{
    if (_routine)
        return _routine->name();
    else
        return QString("");
}

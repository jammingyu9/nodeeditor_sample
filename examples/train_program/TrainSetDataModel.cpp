#include "TrainSetDataModel.hpp"
#include "TrainSetData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QIntValidator>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

TrainSetDataModel::TrainSetDataModel()
    : _trainset(std::make_shared<TrainSetData>(QString(""), 0, 3))
    , _params{nullptr}
{}

QJsonObject TrainSetDataModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["name"] = _trainset->name();
    modelJson["count"] = QString::number(_trainset->count());
    modelJson["interval"] = QString::number(_trainset->interval());

    return modelJson;
}

void TrainSetDataModel::load(QJsonObject const &p)
{
    QJsonValue v1 = p["name"];
    QJsonValue v2 = p["count"];
    QJsonValue v3 = p["interval"];

    if (!v1.isUndefined() && !v2.isUndefined() && !v3.isUndefined()) {
        QString name = v1.toString();
        QString strCount = v2.toString();
        QString strInterval = v3.toString();

        bool ok1, ok2;
        unsigned int count = strCount.toUInt(&ok1);
        unsigned int interval = strInterval.toUInt(&ok2);

        if (ok1 && ok2) {
            _trainset = std::make_shared<TrainSetData>(name, count, interval);
            if (_params) {
                _params->setParamName(name);
                _params->setParamCount(count);
                _params->setParamInterval(interval);
            }
        }
    }
}

unsigned int TrainSetDataModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
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
}

void TrainSetDataModel::onNameTextEdited(QString const &str)
{
    QString name = str;

    unsigned int count = _trainset->count();
    unsigned int interval = _trainset->interval();

    _trainset = std::make_shared<TrainSetData>(name, count, interval);

    Q_EMIT dataUpdated(0);
}

void TrainSetDataModel::onCountTextEdited(QString const &str)
{
    bool ok = false;
    unsigned int count = str.toUInt(&ok);

    if (ok) {
        QString name = _trainset->name();
        unsigned int interval = _trainset->interval();
        _trainset = std::make_shared<TrainSetData>(name, count, interval);

        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

void TrainSetDataModel::onIntervalTextEdited(QString const &str)
{
    bool ok = false;
    unsigned int interval = str.toUInt(&ok);

    if (ok) {
        QString name = _trainset->name();
        unsigned int count = _trainset->count();
        _trainset = std::make_shared<TrainSetData>(name, count, interval);

        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType TrainSetDataModel::dataType(PortType portType, PortIndex portIndex) const
{
    return TrainSetData().type();
}

std::shared_ptr<NodeData> TrainSetDataModel::outData(PortIndex)
{
    return _trainset; // inherits NodeData
}

QWidget *TrainSetDataModel::embeddedWidget()
{
    if (!_params) {
        _params = new TrainSetParamWidget();

        connect(_params->nameParamEdit(), &QLineEdit::textChanged, this, &TrainSetDataModel::onNameTextEdited);
        connect(_params->countParamEdit(), &QLineEdit::textChanged, this, &TrainSetDataModel::onCountTextEdited);
        connect(_params->intervalParamEdit(), &QLineEdit::textChanged, this, &TrainSetDataModel::onIntervalTextEdited);

        _params->setParamName(_trainset->name());
        _params->setParamCount(_trainset->count());
        _params->setParamInterval(_trainset->interval());
    }

    return _params;
}

void TrainSetDataModel::setName(QString name)
{
    unsigned int count = 0;
    unsigned int interval = 3;
    if (_trainset) {
        count = _trainset->count();
        interval = _trainset->interval();
    }

    _trainset = std::make_shared<TrainSetData>(name, count, interval);
}

void TrainSetDataModel::setCount(unsigned int count)
{
    QString name("");
    unsigned int interval = 3;
    if (_trainset) {
        name = _trainset->name();
        interval = _trainset->interval();
    }

    _trainset = std::make_shared<TrainSetData>(name, count, interval);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamCount(count);
}

void TrainSetDataModel::setInterval(unsigned int interval)
{
    unsigned int count = 0;
    QString name("");
    if (_trainset) {
        name = _trainset->name();
        count = _trainset->count();
    }

    _trainset = std::make_shared<TrainSetData>(name, count, interval);

    Q_EMIT dataUpdated(0);

    if (_params)
        _params->setParamInterval(interval);
}

QString TrainSetDataModel::trainSetName() const
{
    if (_trainset)
        return _trainset->name();
    else
        return QString("");
}

#pragma once

#include <QtNodes/NodeDelegateModel>
#include <QtCore/QObject>

#include "TrainSetData.hpp"
#include "TrainSetParamWidget.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class TrainSetDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    TrainSetDataModel();

    virtual ~TrainSetDataModel() {}

public:
    QString caption() const override { return QStringLiteral("Train Set"); }
    bool captionVisible() const override { return false; }
    QString name() const override { return QStringLiteral("TrainSet"); }

public:
    QJsonObject save() const override;
    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(PortType portType) const override;
    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
    std::shared_ptr<NodeData> outData(PortIndex port) override;
    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}
    QWidget *embeddedWidget() override;

public:
    QString trainSetName() const;

public:
    void setName(QString name);
    void setCount(unsigned int count);
    void setInterval(unsigned int interval);

private Q_SLOTS:
    void onNameTextEdited(QString const &str);
    void onCountTextEdited(QString const &str);
    void onIntervalTextEdited(QString const &str);

private:
    std::shared_ptr<TrainSetData> _trainset;
    TrainSetParamWidget *_params;
};

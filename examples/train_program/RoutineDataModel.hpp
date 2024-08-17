#pragma once

#include <QtNodes/NodeDelegateModel>
#include <QtCore/QObject>

#include "RoutineData.hpp"
#include "RoutineParamWidget.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class RoutineDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    RoutineDataModel();

    virtual ~RoutineDataModel() {}

public:
    QString caption() const override { return QStringLiteral("Routine"); }
    bool captionVisible() const override { return false; }
    QString name() const override { return QStringLiteral("Routine"); }

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
    QString routineName() const;

public:
    void setName(QString name);
    void setRepetition(unsigned int count);
    void setRestTime(unsigned int interval);

private Q_SLOTS:
    void onNameTextEdited(QString const &str);
    void onRepetitionTextEdited(QString const &str);
    void onRestTimeTextEdited(QString const &str);

private:
    std::shared_ptr<RoutineData> _routine;
    RoutineParamWidget *_params;
};

#pragma once

#include <QtNodes/NodeDelegateModel>
#include <QtCore/QObject>

#include "ProgramData.hpp"
#include "ProgramParamWidget.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class ProgramDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    ProgramDataModel();

    virtual ~ProgramDataModel() {}

public:
    QString caption() const override { return QStringLiteral("Program"); }
    bool captionVisible() const override { return false; }
    QString name() const override { return QStringLiteral("Program"); }

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
    QString programName() const;

public:
    void setName(QString name);

private Q_SLOTS:
    void onNameTextEdited(QString const &string);

private:
    std::shared_ptr<ProgramData> _program;
    ProgramParamWidget *_params;
};

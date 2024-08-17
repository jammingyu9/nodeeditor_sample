#pragma once

#include <QtCore/QObject>
#include <QtNodes/NodeData>
#include <QVBoxLayout>
#include <QScrollArea>

using QtNodes::NodeData;

class BaseParamWidget : public QScrollArea
{
    Q_OBJECT

public:
    BaseParamWidget();
    virtual ~BaseParamWidget() {}

public:
    void setLayout(QVBoxLayout* layout) { _layout = layout; }
    QVBoxLayout *layout() { return _layout; }

    void addWidget(QWidget* widget) { _layout->addWidget(widget); }

private:
    QVBoxLayout *_layout = nullptr;
};

#pragma once

#include <QVBoxLayout>
#include <QJsonObject>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtNodes/NodeDelegateModel>

#include "BaseParamWidget.hpp"

class ProgramParamWidget : public BaseParamWidget
{
    Q_OBJECT

public:
    ProgramParamWidget();

public:
    void setParamName(QString name);

    QLineEdit *nameParamEdit();

private:
    QLabel *_nameLabel;
    QLineEdit *_nameParamEdit;
};

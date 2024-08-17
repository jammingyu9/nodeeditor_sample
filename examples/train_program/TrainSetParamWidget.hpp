#pragma once

#include <QtWidgets/QScrollArea>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtNodes/NodeDelegateModel>

#include "BaseParamWidget.hpp"

class TrainSetParamWidget : public BaseParamWidget
{
    Q_OBJECT

public:
    TrainSetParamWidget();

public:
    void setParamName(QString name);
    void setParamCount(unsigned int count);
    void setParamInterval(unsigned int interval);

    QLineEdit *nameParamEdit();
    QLineEdit *countParamEdit();
    QLineEdit *intervalParamEdit();

private:
    QLabel *_nameLabel;
    QLabel *_countLabel;
    QLabel *_intervalLabel;
    QLineEdit *_nameParamEdit;
    QLineEdit *_countParamEdit;
    QLineEdit *_intervalParamEdit;

};

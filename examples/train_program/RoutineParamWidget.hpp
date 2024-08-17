#pragma once

#include <QVBoxLayout>
#include <QJsonObject>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtNodes/NodeDelegateModel>

#include "BaseParamWidget.hpp"

class RoutineParamWidget : public BaseParamWidget
{
    Q_OBJECT

public:
    RoutineParamWidget();

public:
    void setParamName(QString name);
    void setParamRepetition(unsigned int repetition);
    void setParamRestTime(unsigned int restTime);

    QLineEdit *nameParamEdit();
    QLineEdit *repetitionParamEdit();
    QLineEdit *restTimeParamEdit();

private:
    QLabel *_nameLabel;
    QLabel *_repetitionLabel;
    QLabel *_restTimeLabel;
    QLineEdit *_nameParamEdit;
    QLineEdit *_repetitionParamEdit;
    QLineEdit *_restTimeParamEdit;

};

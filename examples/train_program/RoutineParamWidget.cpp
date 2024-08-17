#include "RoutineParamWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <Qtgui/QIntValidator>

RoutineParamWidget::RoutineParamWidget()
{
    _nameParamEdit = new QLineEdit();

    _repetitionParamEdit = new QLineEdit();
    _repetitionParamEdit->setValidator(new QIntValidator());
    _repetitionParamEdit->setMaximumSize(_repetitionParamEdit->sizeHint());

    _restTimeParamEdit = new QLineEdit();
    _restTimeParamEdit->setValidator(new QIntValidator());
    _restTimeParamEdit->setMaximumSize(_restTimeParamEdit->sizeHint());

    setLayout(new QVBoxLayout(this));

    _nameLabel = new QLabel("Routine Name");
    _repetitionLabel = new QLabel("Repetition");
    _restTimeLabel = new QLabel("Rest Time");

    addWidget(_nameLabel);
    addWidget(_nameParamEdit);
    addWidget(_repetitionLabel);
    addWidget(_repetitionParamEdit);
    addWidget(_restTimeLabel);
    addWidget(_restTimeParamEdit);
}

void RoutineParamWidget::setParamName(QString name)
{
    _nameParamEdit->setText(name);
}

void RoutineParamWidget::setParamRepetition(unsigned int repetition)
{
    _repetitionParamEdit->setText(QString::number(repetition));
}

void RoutineParamWidget::setParamRestTime(unsigned int restTime)
{
    _restTimeParamEdit->setText(QString::number(restTime));
}

QLineEdit *RoutineParamWidget::nameParamEdit()
{
    return _nameParamEdit;
}

QLineEdit *RoutineParamWidget::repetitionParamEdit()
{
    return _repetitionParamEdit;
}

QLineEdit *RoutineParamWidget::restTimeParamEdit()
{
    return _restTimeParamEdit;
}

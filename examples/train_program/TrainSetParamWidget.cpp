#include "TrainSetParamWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <Qtgui/QIntValidator>

TrainSetParamWidget::TrainSetParamWidget()
    : BaseParamWidget()
{
    _nameParamEdit = new QLineEdit();

    _countParamEdit = new QLineEdit();
    _countParamEdit->setValidator(new QIntValidator());
    _countParamEdit->setMaximumSize(_countParamEdit->sizeHint());

    _intervalParamEdit = new QLineEdit();
    _intervalParamEdit->setValidator(new QIntValidator());
    _intervalParamEdit->setMaximumSize(_intervalParamEdit->sizeHint());

    setLayout(new QVBoxLayout(this));

    _nameLabel = new QLabel("TrainSet Name");
    _countLabel = new QLabel("Count");
    _intervalLabel = new QLabel("Interval");

    addWidget(_nameLabel);
    addWidget(_nameParamEdit);
    addWidget(_countLabel);
    addWidget(_countParamEdit);
    addWidget(_intervalLabel);
    addWidget(_intervalParamEdit);
}

void TrainSetParamWidget::setParamName(QString name)
{
    _nameParamEdit->setText(name);
}

void TrainSetParamWidget::setParamCount(unsigned int count)
{
    _countParamEdit->setText(QString::number(count));
}

void TrainSetParamWidget::setParamInterval(unsigned int interval)
{
    _intervalParamEdit->setText(QString::number(interval));
}

QLineEdit *TrainSetParamWidget::nameParamEdit()
{
    return _nameParamEdit;
}

QLineEdit *TrainSetParamWidget::countParamEdit()
{
    return _countParamEdit;
}

QLineEdit *TrainSetParamWidget::intervalParamEdit()
{
    return _intervalParamEdit;
}

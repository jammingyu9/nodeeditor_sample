#include "ProgramParamWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>

ProgramParamWidget::ProgramParamWidget()
{
    _nameParamEdit = new QLineEdit();

    setLayout(new QVBoxLayout(this));

    _nameLabel = new QLabel("Program Name");

    addWidget(_nameLabel);
    addWidget(_nameParamEdit);
}

void ProgramParamWidget::setParamName(QString name)
{
    _nameParamEdit->setText(name);
}

QLineEdit *ProgramParamWidget::nameParamEdit()
{
    return _nameParamEdit;
}

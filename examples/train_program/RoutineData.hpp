#pragma once

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class RoutineData : public NodeData
{
public:
    RoutineData()
        : _name(""), _repetition(0), _restTime(15)
    {}

    RoutineData(QString const name, unsigned int const repetition, unsigned int const restTime)
        : _name(name), _repetition(repetition), _restTime(restTime)
    {}

public:
    NodeDataType type() const override { return NodeDataType{"Routine", "routine"}; }

    QString name() const { return _name; }

    unsigned int repetition() { return _repetition; }
    QString repetitionAsText() const { return QString::number(_repetition); }

    unsigned int restTime() { return _restTime; }
    QString restTimeAsText() const { return QString::number(_restTime); }

private:
    QString _name;
    unsigned int _repetition;
    unsigned int _restTime;
};

#pragma once

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class TrainSetData : public NodeData
{
public:
    TrainSetData()
        : _name(""), _count(0), _interval(5)
    {}

    TrainSetData(QString const name, unsigned int const count, unsigned int const interval)
        : _name(name), _count(count), _interval(interval)
    {}

    QString name() const { return _name; }
    NodeDataType type() const override { return NodeDataType{"Trainset", "trainset"}; }
    unsigned int count() const { return _count; }
    QString countAsText() const { return QString::number(_count); }
    unsigned int interval() const { return _interval; }
    QString intervalAsText() const { return QString::number(_interval); }

private:
    QString _name;
    unsigned int _count;
    unsigned int _interval;
};

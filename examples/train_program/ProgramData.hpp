#pragma once

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class ProgramData : public NodeData
{
public:
    ProgramData()
        : _name("")
    {}

    ProgramData(QString const name)
        : _name(name)
    {}

public:
    NodeDataType type() const override { return NodeDataType{"Program", "program"}; }

    QString name() const { return _name; }

private:
    QString _name;
};


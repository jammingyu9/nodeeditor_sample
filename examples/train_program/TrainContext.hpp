#pragma once

#include <QString>

#include <QtNodes/DataFlowGraphModel>

#include "TrainSetData.hpp"
#include "RoutineData.hpp"
#include "ProgramData.hpp"

using QtNodes::DataFlowGraphModel;
using QtNodes::NodeId;

class TrainContext
{
public:
    TrainContext(DataFlowGraphModel *graph);
    virtual ~TrainContext() {}

public:
    void clear();
    void load();

    std::vector<RoutineData> routines() const;
    std::vector<TrainSetData> trainSets(int idx) const;

private:
    std::vector<TrainSetData> _trainSets;
    std::vector<RoutineData> _routines;
    std::vector<int> _routineSetCount;
    std::shared_ptr<ProgramData> _programData;
    std::shared_ptr<DataFlowGraphModel> _graph;
};

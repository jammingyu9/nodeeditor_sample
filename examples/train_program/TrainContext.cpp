#include "TrainContext.hpp"

TrainContext::TrainContext(DataFlowGraphModel *graph)
    : _programData(nullptr)
{
    if (graph)
        _graph.reset(graph);
}

std::vector<RoutineData> TrainContext::routines() const
{
    return _routines;
}

std::vector<TrainSetData> TrainContext::trainSets(int idx) const
{
    int setIdx = 0;
    int count = _routineSetCount[idx];

    std::vector<TrainSetData> sets;

    for (int i = 0; i < idx; i++)
        setIdx += _routineSetCount[i];

    for (int i = 0; i < count; i++)
        sets.push_back(_trainSets[setIdx + i]);

    return sets;
}

void TrainContext::clear()
{
    // clean up current context
    _trainSets.clear();
    _routines.clear();
    _routineSetCount.clear();
    _programData.reset();
}

void TrainContext::load()
{
    std::vector<NodeId> ids(_graph->allNodeIds().begin(), _graph->allNodeIds().end());
    auto it = ids.begin();

    for (; it != ids.end(); it++) {

        QVariant type = _graph->nodeData(*it, QtNodes::NodeRole::Type);
        QString typeStr = type.toString();

        QVariant data = _graph->nodeData(*it, QtNodes::NodeRole::InternalData);
        QJsonObject obj = data.toJsonObject()["internal-data"].toObject();

        if (typeStr == "Program") {

            _programData = std::make_shared<ProgramData>(obj["name"].toString());

        } else if (typeStr == "Routine") {

            int repetition = obj["repetition"].toString().toInt();
            int restTime = obj["resttime"].toString().toInt();
            _routines.push_back(RoutineData(obj["name"].toString(), repetition, restTime));
            _routineSetCount.push_back(_graph->allConnectionIds(*it).size() - 1);

        } else if (typeStr == "TrainSet") {

            int count = obj["count"].toString().toInt();
            int interval = obj["interval"].toString().toInt();
            _trainSets.push_back(TrainSetData(obj["name"].toString(), count, interval));

        }
    }
}

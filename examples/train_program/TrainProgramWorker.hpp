#pragma once

#include <QThread>

#include "TrainContext.hpp"

class TrainProgramWorker : public QThread
{
    Q_OBJECT

public:
    TrainProgramWorker(TrainContext *context);
    ~TrainProgramWorker();

    void startProgram();

    void run() override;

signals:
    void countDownChanged(unsigned int count);
    void routineChanged(QString routineName);
    void trainSetChanged(QString trainSetName);
    void programFinished();

public Q_SLOTS:
    void onPause();
    void onResume();

private:
    std::shared_ptr<TrainContext> _context;
    bool _runFlag = true;
    bool _startFlag = false;
};

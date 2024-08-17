#include "TrainProgramWorker.hpp"

#include <QTimer>

TrainProgramWorker::TrainProgramWorker(TrainContext *context)
    : _context(context)
{
}

TrainProgramWorker::~TrainProgramWorker()
{
    _context.reset();
}


void TrainProgramWorker::startProgram()
{
    if (!_startFlag) {
        _startFlag = true;
    }
}

void TrainProgramWorker::run()
{
    while (true) {
        if (_startFlag) {
            if (_context.get() == nullptr) {
                return;
            }

            _context->clear();
            _context->load();

            std::vector<RoutineData> routines = _context->routines();
            auto it = routines.begin();

            for (; it != routines.end(); it++)
            {
                QString routineName(it->name());
                Q_EMIT routineChanged(routineName);
                QThread::msleep(3000);

                std::vector<TrainSetData> trainSets = _context->trainSets(it - routines.begin());

                int repetition = it->repetition();
                int restTime = it->restTime();

                for (int i = 0; i < repetition; i++) {

                    auto itSet = trainSets.begin();

                    for (; itSet != trainSets.end(); itSet++) {

                        QString trainSetName(itSet->name());

                        Q_EMIT trainSetChanged(trainSetName);
                        QThread::msleep(3000);

                        // start set counting
                        unsigned int interval = itSet->interval();

                        Q_EMIT countDownChanged(0);
                        QThread::msleep(3000);

                        int count = itSet->count();

                        for (int i = 1; i <= count; i++) {
                            while (!_runFlag) { QThread::msleep(100); }
                            Q_EMIT countDownChanged(i);
                            QThread::msleep(interval * 200);
                        }
                    }

                    QString trainSetRestName("휴식 시간");
                    Q_EMIT trainSetChanged(trainSetRestName);
                    QThread::msleep(restTime * 1000);
                }
            }

            Q_EMIT programFinished();

            _startFlag = false;
        }

        // wait until start flag is set
        QThread::msleep(100);
    }
}


void TrainProgramWorker::onPause()
{
    _runFlag = false;
}

void TrainProgramWorker::onResume()
{
    _runFlag = true;
}

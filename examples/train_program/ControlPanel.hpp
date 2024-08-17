#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>

#include <QTextToSpeech>

#include <QtNodes/DataFlowGraphModel>

#include "TrainContext.hpp"
#include "TrainProgramWorker.hpp"

using QtNodes::NodeId;
using QtNodes::DataFlowGraphModel;

class ControlPanel : public QGroupBox
{
    Q_OBJECT
public:
    ControlPanel(TrainContext *context);

    virtual ~ControlPanel() {}

public:
    void startTrainProgramWorker();

    void processProgram();
    void pauseProgram();
    void resumeProgram();

signals:
    void pause();
    void resume();

private Q_SLOTS:
    void onStartButtonPressed();
    void onPauseButtonPressed();
    void onResumeButtonPressed();

    void onCountDownChanged(unsigned int count);
    void onRoutineChanged(QString routineName);
    void onTrainSetChanged(QString trainSetName);
    void onFinished();

private:
    QPushButton *_startButton;
    QPushButton *_pauseButton;
    QPushButton *_resumeButton;
    QLabel *_routineLabel;
    QLabel *_trainSetLabel;
    QLabel *_countDownLabel;
    QStatusBar *_statusBar;
    QTimer *_timer;
    QTextToSpeech *_speech;

    TrainProgramWorker *_worker;
    std::shared_ptr<TrainContext> _context;
};

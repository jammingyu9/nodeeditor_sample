#include "ControlPanel.hpp"
#include "ProgramDataModel.hpp"
#include "RoutineDataModel.hpp"
#include "TrainSetDataModel.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

ControlPanel::ControlPanel(TrainContext *context)
    : QGroupBox("User Control Panel"), _context()
{
    if (context)
        _context.reset(context);

    _statusBar = new QStatusBar();
    _statusBar->showMessage(QString("Press start when ready."));

    _routineLabel = new QLabel("Routine Name: -");
    _routineLabel->setFixedSize(250, 60);
    _routineLabel->setAlignment(Qt::AlignCenter);
    _routineLabel->setStyleSheet("font-weight: bold; color: white; font-size: 20px");

    _trainSetLabel = new QLabel("Set Name: -");
    _trainSetLabel->setFixedSize(250, 60);
    _trainSetLabel->setAlignment(Qt::AlignCenter);
    _trainSetLabel->setStyleSheet("font-weight: bold; color: green; font-size: 20px");

    _countDownLabel = new QLabel("Set Count: 준비");
    _countDownLabel->setFixedSize(250, 60);
    _countDownLabel->setAlignment(Qt::AlignCenter);
    _countDownLabel->setStyleSheet("font-weight: bold; color: red; font-size: 20px");

    _startButton = new QPushButton("Start");
    _pauseButton = new QPushButton("Pause");
    _pauseButton->setEnabled(false);
    _resumeButton = new QPushButton("Resume");
    _resumeButton->setEnabled(false);

    connect(_startButton, &QPushButton::pressed, this, &ControlPanel::onStartButtonPressed);
    connect(_pauseButton, &QPushButton::pressed, this, &ControlPanel::onPauseButtonPressed);
    connect(_resumeButton, &QPushButton::pressed, this, &ControlPanel::onResumeButtonPressed);

    setAlignment(Qt::AlignHCenter);

    QVBoxLayout *vbl = new QVBoxLayout;
    QHBoxLayout *hbl = new QHBoxLayout;

    hbl->addWidget(_startButton);
    hbl->addWidget(_pauseButton);
    hbl->addWidget(_resumeButton);

    vbl->setAlignment(Qt::AlignCenter);
    vbl->addLayout(hbl);
    vbl->addWidget(_routineLabel);
    vbl->addWidget(_trainSetLabel);
    vbl->addWidget(_countDownLabel);
    vbl->addWidget(_statusBar);

    setLayout(vbl);

    _speech = new QTextToSpeech();

    _worker = new TrainProgramWorker(_context.get());

    connect(_worker, &TrainProgramWorker::countDownChanged, this, &ControlPanel::onCountDownChanged);
    connect(_worker, &TrainProgramWorker::routineChanged, this, &ControlPanel::onRoutineChanged);
    connect(_worker, &TrainProgramWorker::trainSetChanged, this, &ControlPanel::onTrainSetChanged);
    connect(_worker, &TrainProgramWorker::programFinished, this, &ControlPanel::onFinished);

    connect(this, &ControlPanel::pause, _worker, &TrainProgramWorker::onPause);
    connect(this, &ControlPanel::resume, _worker, &TrainProgramWorker::onResume);

    _worker->start();
}

void ControlPanel::startTrainProgramWorker()
{
    _statusBar->showMessage(QString("Start training program.."));

    _worker->startProgram();
}


void ControlPanel::onStartButtonPressed()
{
    _startButton->setText(QString("Start"));
    _startButton->setEnabled(false);
    _pauseButton->setEnabled(true);
    _resumeButton->setEnabled(false);

    if (_context.get()) {
        startTrainProgramWorker();
    } else {
        _statusBar->showMessage("Context is not set.");
    }
}

void ControlPanel::onPauseButtonPressed()
{
    _startButton->setText(QString("Restart"));
    _startButton->setEnabled(true);
    _pauseButton->setEnabled(false);
    _resumeButton->setEnabled(true);

    Q_EMIT pause();
    _statusBar->showMessage(QString("Program paused."));

}

void ControlPanel::onResumeButtonPressed()
{
    _startButton->setText(QString("Start"));
    _startButton->setEnabled(false);
    _pauseButton->setEnabled(true);
    _resumeButton->setEnabled(false);

    Q_EMIT resume();
    _statusBar->showMessage(QString("Program resumed."));

}

void ControlPanel::onCountDownChanged(unsigned int count)
{
    QString countStr("준비");

    if (count > 0)
        countStr = QString::number(count);

    _countDownLabel->setText(QString("Set Count: ") + countStr);

    _speech->say(countStr);
}

void ControlPanel::onRoutineChanged(QString routineName)
{
    QString nodeDisplayText("Routine: " + routineName);

    _routineLabel->setText(nodeDisplayText);
    _speech->say(routineName);
}

void ControlPanel::onTrainSetChanged(QString trainSetName)
{
    QString nodeDisplayText("TrainSet: " + trainSetName);

    _trainSetLabel->setText(nodeDisplayText);
    _speech->say(trainSetName);
}

void ControlPanel::onFinished()
{
    _startButton->setEnabled(true);
    _pauseButton->setEnabled(false);
    _resumeButton->setEnabled(false);

    _statusBar->showMessage("Processing complete.");

    _speech->say("수고하셨습니다.");
}

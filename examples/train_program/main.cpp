#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

#include "TrainSetDataModel.hpp"
#include "RoutineDataModel.hpp"
#include "ProgramDataModel.hpp"
#include "TrainContext.hpp"

#include "ControlPanel.hpp"

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;

static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

    ret->registerModel<TrainSetDataModel>("TrainSets");
    ret->registerModel<RoutineDataModel>("Routines");
    ret->registerModel<ProgramDataModel>("Programs");

    return ret;
}

static void setStyle()
{
    ConnectionStyle::setConnectionStyle(
        R"(
        {
            "ConnectionStyle": {
                "ConstructionColor": "gray",
                "NormalColor": "black",
                "SelectedColor": "gray",
                "SelectedHaloColor": "deepskyblue",
                "HoveredColor": "deepskyblue",

                "LineWidth": 3.0,
                "ConstructionLineWidth": 2.0,
                "PointDiameter": 10.0,

                "UseDataDefinedColors": true
            }
        }
    )");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setStyle();

    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();

    QWidget mainWidget;

    auto menuBar = new QMenuBar();

    QMenu *menu = menuBar->addMenu("File");

    auto saveAction = menu->addAction("Save");
    saveAction->setShortcut(QKeySequence::Save);

    auto loadAction = menu->addAction("Load");
    loadAction->setShortcut(QKeySequence::Open);

    QHBoxLayout *layout = new QHBoxLayout(&mainWidget);

    DataFlowGraphModel dataFlowGraphModel(registry);

    layout->addWidget(menuBar);
    auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, &mainWidget);

    auto view = new GraphicsView(scene);
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QObject::connect(saveAction, &QAction::triggered, scene, [scene, &mainWidget]() {
        if (scene->save())
            mainWidget.setWindowModified(false);
    });

    QObject::connect(loadAction, &QAction::triggered, scene, &DataFlowGraphicsScene::load);
    QObject::connect(scene, &DataFlowGraphicsScene::sceneLoaded, view, &GraphicsView::centerScene);
    QObject::connect(scene, &DataFlowGraphicsScene::modified, &mainWidget, [&mainWidget]() {
        mainWidget.setWindowModified(true);
    });

    TrainContext *context = new TrainContext(&dataFlowGraphModel);
    ControlPanel *controlPanel = new ControlPanel(context);

    layout->addWidget(controlPanel);

    mainWidget.setWindowTitle("[*] Muscle Train Program Planner");
    mainWidget.resize(800, 700);

    mainWidget.move(QApplication::primaryScreen()->availableGeometry().center() - mainWidget.rect().center());
    mainWidget.showNormal();

    return app.exec();
}

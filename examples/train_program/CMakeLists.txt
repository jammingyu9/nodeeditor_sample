set(CALC_SOURCE_FILES
  main.cpp
  BaseParamWidget.cpp
  TrainSetDataModel.cpp
  TrainSetParamWidget.cpp
  RoutineDataModel.cpp
  RoutineParamWidget.cpp
  ProgramDataModel.cpp
  ProgramParamWidget.cpp
)

set(CALC_HEADER_FILES
  BaseParamWidget.hpp
  TrainSetData.hpp
  TrainSetDataModel.hpp
  TrainSetParamWidget.hpp
  RoutineData.hpp
  RoutineDataModel.hpp
  RoutineParamWidget.hpp
  ProgramData.hpp
  ProgramDataModel.hpp
  ProgramParamWidget.hpp
)

add_executable(train_program
  ${CALC_SOURCE_FILES}
  ${CALC_HEAEDR_FILES}
  ControlPanel.hpp
  ControlPanel.cpp
  TrainContext.hpp
  TrainContext.cpp
  TrainProgramWorker.hpp
  TrainProgramWorker.cpp
)

target_link_libraries(train_program QtNodes)

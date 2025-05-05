### Qt图形界面程序架构

### 1.  基本架构

- #### 名称

  **三层架构**：UI - 业务-数据访问

- #### 思想

  根据依赖倒置原则。UI层依赖业务层的接口；业务层依赖数据访问层的接口。

  使用**构造函数注入**来实现依赖倒置。

  如果接口有多个实现，可以使用工厂模式，通过读取配置文件或其他方式来决定接口对应的是哪个实现。

  即使接口只有一个实现，也应该创建接口。

- #### 举例

  ```c++
  int main(int argc, char *argv[]) {
      QApplication app(argc, argv);
      
      // 1. 构造数据访问层
      ConfigReader config("config.ini");
      CameraIOBase* camera = CameraFactory::createCamera(config);//工厂模式实现
      RobotIOBase* robot = RobotFactory::createRobot(config);
      DatabaseAccess* database = new DatabaseAccess(config.getString("db_connection"));
      
      // 2. 构造业务层（注入数据访问层对象）
      ICameraService* cameraService = new CameraService(camera);//构造函数注入
      IRobotService* robotService = new RobotService(robot);
      IProjectService* projectService = new ProjectService(database);
      
      // 3. 构造UI层（注入业务层对象）
      MainWindow* mainWindow = new MainWindow(cameraService, robotService, projectService);//构造函数注入
      mainWindow->show();
      
      int result = app.exec();
      
      // 资源清理（按照创建顺序的逆序）
      delete mainWindow;
      delete projectService;
      delete robotService;
      delete cameraService;
      delete database;
      delete robot;
      delete camera;
      
      return result;
  }
  ```

  

### 2. 常用架构

#### 2.1 状态机架构

- 思想

  使用qt的QStateMachine来完成状态机的管理（创建、转换、事件（信号）、行为（槽））

  根据单一职责原则。若是状态需要保存在数据库中，需要在数据访问层增加一个数据库访问的组件。然后这个状态机组件、数据库访问组件都由一个业务（服务）来调用

- 举例

  .h

  ```c++
  #ifndef TIREPRODUCTIONSTATEMACHIINE_H
  #define TIREPRODUCTIONSTATEMACHIINE_H
  
  #include <QStateMachine>
  #include <QState>
  #include <QFinalState>
  #include <QObject>
  #include <QString>
  
  class TireProductionStateMachine : public QObject
  {
      Q_OBJECT
  
  public:
      explicit TireProductionStateMachine(QObject *parent = nullptr);
      ~TireProductionStateMachine();
  
      // 启动状态机
      void start();
      // 获取当前状态
      QString getCurrentState() const;
  
  public slots:
      // 触发状态转换的槽函数
      void startLaserCleaning();
      void laserCleaningCompleted();
      void startAdhesiveApplication();
      void adhesiveApplicationCompleted();
      void start3DInspection();
      void inspectionPassed();
      void inspectionFailed();
      void resetMachine();
  
  signals:
      // 状态变化信号
      void stateChanged(const QString &stateName);
      // 生产完成信号
      void productionCompleted();
      // 生产失败信号
      void productionFailed(const QString &reason);
  
  private:
      QStateMachine *m_stateMachine;
      QState *m_initialState;
      QState *m_laserCleaningState;
      QState *m_adhesiveApplicationState;
      QState *m_inspectionState;
      QFinalState *m_completedState;
      QFinalState *m_failedState;
      
      QString m_currentState;
  };
  
  #endif // TIREPRODUCTIONSTATEMACHIINE_H
  ```

  

  .cpp

  ```c++
  # cpp
  #include "TireProductionStateMachine.h"
  #include <QDebug>
  
  TireProductionStateMachine::TireProductionStateMachine(QObject *parent)
      : QObject(parent), m_currentState("Initial")
  {
      // 创建状态机
      m_stateMachine = new QStateMachine(this);
      
      // 创建各个状态
      m_initialState = new QState();
      m_laserCleaningState = new QState();
      m_adhesiveApplicationState = new QState();
      m_inspectionState = new QState();
      m_completedState = new QFinalState();
      m_failedState = new QFinalState();
      
      // 将状态添加到状态机
      m_stateMachine->addState(m_initialState);
      m_stateMachine->addState(m_laserCleaningState);
      m_stateMachine->addState(m_adhesiveApplicationState);
      m_stateMachine->addState(m_inspectionState);
      m_stateMachine->addState(m_completedState);
      m_stateMachine->addState(m_failedState);
      
      // 设置初始状态
      m_stateMachine->setInitialState(m_initialState);
      
      // 设置状态转换
      m_initialState->addTransition(this, SIGNAL(startLaserCleaning()), m_laserCleaningState);
      m_laserCleaningState->addTransition(this, SIGNAL(laserCleaningCompleted()), m_adhesiveApplicationState);
      m_adhesiveApplicationState->addTransition(this, SIGNAL(adhesiveApplicationCompleted()), m_inspectionState);
      m_inspectionState->addTransition(this, SIGNAL(inspectionPassed()), m_completedState);
      m_inspectionState->addTransition(this, SIGNAL(inspectionFailed()), m_failedState);
      
      // 状态进入和退出的处理
      connect(m_initialState, &QState::entered, [this]() {
          m_currentState = "Initial";
          emit stateChanged(m_currentState);
          qDebug() << "Entered Initial state";
      });
      
      connect(m_laserCleaningState, &QState::entered, [this]() {
          m_currentState = "LaserCleaning";
          emit stateChanged(m_currentState);
          qDebug() << "Entered Laser Cleaning state";
      });
      
      connect(m_adhesiveApplicationState, &QState::entered, [this]() {
          m_currentState = "AdhesiveApplication";
          emit stateChanged(m_currentState);
          qDebug() << "Entered Adhesive Application state";
      });
      
      connect(m_inspectionState, &QState::entered, [this]() {
          m_currentState = "3DInspection";
          emit stateChanged(m_currentState);
          qDebug() << "Entered 3D Inspection state";
      });
      
      connect(m_completedState, &QState::entered, [this]() {
          m_currentState = "Completed";
          emit stateChanged(m_currentState);
          emit productionCompleted();
          qDebug() << "Tire production completed successfully";
      });
      
      connect(m_failedState, &QState::entered, [this]() {
          m_currentState = "Failed";
          emit stateChanged(m_currentState);
          emit productionFailed("3D Inspection failed");
          qDebug() << "Tire production failed at 3D Inspection";
      });
  }
  
      m_stateMachine->start();
  }
  ```

  

  main

  ```c++
  #include <QCoreApplication>
  #include "TireProductionStateMachine.h"
  
  int main(int argc, char *argv[])
  {
      QCoreApplication a(argc, argv);
      
      TireProductionStateMachine tireMachine;
      
      // 连接状态变化信号
      QObject::connect(&tireMachine, &TireProductionStateMachine::stateChanged, 
          [](const QString &state) {
              qDebug() << "Tire state changed to:" << state;
          });
      
      QObject::connect(&tireMachine, &TireProductionStateMachine::productionCompleted, 
          []() {
              qDebug() << "Production cycle completed successfully";
          });
      
      QObject::connect(&tireMachine, &TireProductionStateMachine::productionFailed, 
          [](const QString &reason) {
              qDebug() << "Production failed:" << reason;
          });
      
      // 启动状态机
      tireMachine.start();
      
      // 模拟生产过程
      QTimer::singleShot(1000, &tireMachine, &TireProductionStateMachine::startLaserCleaning);
      QTimer::singleShot(3000, &tireMachine, &TireProductionStateMachine::laserCleaningCompleted);
      QTimer::singleShot(4000, &tireMachine, &TireProductionStateMachine::adhesiveApplicationCompleted);
      QTimer::singleShot(6000, &tireMachine, &TireProductionStateMachine::inspectionPassed);
      // 或者失败: QTimer::singleShot(6000, &tireMachine, &TireProductionStateMachine::inspectionFailed);
      
      return a.exec();
  }
  ```

  


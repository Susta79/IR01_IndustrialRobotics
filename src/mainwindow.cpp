#include "mainwindow.h"
#include "kinematic.h"

#include <QMainWindow>
#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QTimer>

#define VERSION "1.1.0"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
   this->pTrajectory = new Trajectory();
   this->pKinematic = new Kinematic(this);
   this->pRobot = new Robot("Robot1");
   this->pTcpClient = new TcpClient();
   this->pbKinematic = new QPushButton("Kinematic");
   // QTimer tmr
   tmrMain = new QTimer(this);
   connect(tmrMain, &QTimer::timeout, this, &MainWindow::tmrMain_timeout);

   QVBoxLayout *vBoxLayout = new QVBoxLayout();
   vBoxLayout->addWidget(this->pRobot->gbGroup);
   vBoxLayout->addWidget(this->pbKinematic);
   vBoxLayout->addWidget(this->pTcpClient->gbGroup);
   vBoxLayout->addWidget(this->pTrajectory->gbPTP);

   QWidget *windowMS = new QWidget();
   windowMS->setLayout(vBoxLayout);

   QHBoxLayout *hBoxLayout = new QHBoxLayout();
   hBoxLayout->addWidget(windowMS);

   QWidget *windowGen = new QWidget();
   windowGen->setLayout(hBoxLayout);

   setCentralWidget(windowGen);

   this->setWindowTitle(tr("IR01_IndustrialRobotics"));
   this->move(10, 10);

   connect(pbKinematic, &QPushButton::clicked, this, &MainWindow::pbKinematic_clicked);

   this->tmrMain->start(100);
}

MainWindow::~MainWindow()
{
   if (pRobot) {
      delete pRobot;
      pRobot = nullptr;
   }
   if (pKinematic) {
      delete pKinematic;
      pKinematic = nullptr;
   }
}

void MainWindow::pbKinematic_clicked()
{
   pKinematic->exec();
}

void MainWindow::tmrMain_timeout() {
   this->pTcpClient->pCmdJoint->set_joint1_deg(this->pRobot->pJoint->get_joint1_deg());
   this->pTcpClient->pCmdJoint->set_joint2_deg(this->pRobot->pJoint->get_joint2_deg());
   this->pTcpClient->pCmdJoint->set_joint3_deg(this->pRobot->pJoint->get_joint3_deg());
   this->pTcpClient->pCmdJoint->set_joint4_deg(this->pRobot->pJoint->get_joint4_deg());
   this->pTcpClient->pCmdJoint->set_joint5_deg(this->pRobot->pJoint->get_joint5_deg());
   this->pTcpClient->pCmdJoint->set_joint6_deg(this->pRobot->pJoint->get_joint6_deg());

   return;
}
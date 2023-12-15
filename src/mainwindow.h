#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "robot.h"
#include "tcpclient.h"
#include "kinematic.h"

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QGroupBox>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void pbKinematic_clicked();
    void tmrMain_timeout();

private:
    Kinematic* pKinematic;
    Robot* pRobot;
    TcpClient* pTcpClient;
    QPushButton *pbKinematic;
    QTimer* tmrMain;
};

#endif // MAINWINDOW_H

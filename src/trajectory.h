#ifndef TRAJECTORY_H
#define TRAJECTORY_H

//#define _USE_MATH_DEFINES
//#include <math.h>

//#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QPushButton>

#include <Eigen\Geometry>

#include "pose.h"

//using namespace Eigen;

class Trajectory : public QObject
{
private:
    Q_OBJECT
    
    QPushButton *pbLinear;
    QPushButton *pbJoint;
    
    Pose* pFromPose;
    Pose* pToPose;
    
    QDoubleSpinBox *dsbMaxSpeed;
    QDoubleSpinBox *dsbMaxAccDec;
    QDoubleSpinBox *dsbMaxJerk;

private slots:
    void pbLinear_released();
    void pbJoint_released();

private:

    void Linear();
    void Joint();

public:
    QGroupBox *gbPTP;

    Trajectory();
    ~Trajectory();
};

#endif // TRAJECTORY_H
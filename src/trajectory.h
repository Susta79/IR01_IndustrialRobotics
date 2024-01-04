#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "pose.h"

class Trajectory : public QObject
{
private:
    Q_OBJECT
    
    Pose* pFromPose;
    Pose* pToPose;
    
    QDoubleSpinBox *dsbMaxSpeed;
    QDoubleSpinBox *dsbMaxAccDec;
    QDoubleSpinBox *dsbMaxJerk;

    QPushButton *pbLinear;
    QPushButton *pbJoint;
    
private slots:
    void pbLinear_released();
    void pbJoint_released();

private:

    void Linear(Pose*, Pose*);
    void Joint();

public:
    QGroupBox *gbGroup;

    Trajectory();
    ~Trajectory();
};

#endif // TRAJECTORY_H
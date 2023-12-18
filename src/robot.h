#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>

#include <Eigen/Dense>

#include "joint.h"
#include "link.h"
#include "pose.h"
#include <IR01/error_def.h>

using namespace Eigen;

class Robot : public QObject
{
private:
    Q_OBJECT
    
    QString name;
    QPushButton *pbFK;
    QPushButton *pbIK;
    QGroupBox *gbFrontBack;
    QRadioButton *cbFront;
    QRadioButton *cbBack;
    QGroupBox *gbUpDown;
    QRadioButton *cbUp;
    QRadioButton *cbDown;
    QGroupBox *gbPosNeg;
    QRadioButton *cbPositive;
    QRadioButton *cbNegative;

    Link* pLink;
    Pose* pPose;

private slots:
    void pbFK_released();
    void pbIK_released();

public:
    enum FrontBack { Front, Back };
    Q_ENUM(FrontBack)

    enum UpDown { Up, Down };
    Q_ENUM(UpDown)

    enum PosNeg { Positive, Negative };
    Q_ENUM(PosNeg)

    Joint* pJoint;
    Joint* pRealJoint;
    QGroupBox *gbGroup;

    Robot(QString name);
    ~Robot();
    Affine3d FK(Array<double, 6, 1>);
    // IK: return the joint value 
    // Inverse kinematics IK: from pose to joint values.
    // paramenters:
    //      pose: desired robot pose
    //      joint: set the actual joint values and get the new values as output
    // 
    ARCCode_t IK(Affine3d p, Robot::FrontBack fb, Robot::UpDown ud, Robot::PosNeg pn, Array<double, 6, 1>& joint);
    ARCCode_t IK_2(Affine3d p, Array<double, 6, 1>& joint);
    ARCCode_t IK_3(Affine3d p, Robot::FrontBack fb, Robot::UpDown ud, Robot::PosNeg pn, Array<double, 6, 1>& joint);
};

#endif // ROBOT_H
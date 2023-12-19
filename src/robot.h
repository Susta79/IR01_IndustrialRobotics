#ifndef ROBOT_H
#define ROBOT_H

#include <QString>
#include <QGroupBox>
#include <QPushButton>
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

    Link* pLink;
    Pose* pPose;

private slots:
    void pbFK_released();
    void pbIK_released();

public:
    Joint* pJoint;
    QGroupBox *gbGroup;

    Robot(QString name);
    ~Robot();
    Affine3d FK(Array<double, 6, 1>);
    ARCCode_t IK(Pose* p, Array<double, 6, 1>& joint);
};

#endif // ROBOT_H
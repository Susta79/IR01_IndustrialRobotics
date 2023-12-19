#ifndef POSE_H
#define POSE_H

#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QRadioButton>

#include <Eigen\Geometry>

#include "pose_conf.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Eigen;

class Pose
{
private:
    QString name;
    QDoubleSpinBox *dsbX;
    QDoubleSpinBox *dsbY;
    QDoubleSpinBox *dsbZ;
    QDoubleSpinBox *dsbA;
    QDoubleSpinBox *dsbB;
    QDoubleSpinBox *dsbC;
    PoseConf* poseConf;

public:
    QGroupBox *gbGroup;

    Pose() { new (this) Pose("", Affine3d::Identity()); }
    Pose(QString n) { new (this) Pose(n, Affine3d::Identity()); }
    Pose(Affine3d m) { new (this) Pose("", m); }
    Pose(QString name, Affine3d m);
    ~Pose();

    // pose
    Affine3d get_pose();
    void set_pose(Affine3d);

    // x
    double get_x() { return this->dsbX->value(); }
    void set_x(double val) { this->dsbX->setValue(val); }

    // y
    double get_y() { return this->dsbY->value(); }
    void set_y(double val) { this->dsbY->setValue(val); }

    // z
    double get_z() { return this->dsbZ->value(); }
    void set_z(double val) { this->dsbZ->setValue(val); }

    // a
    double get_a() { return this->dsbA->value(); }
    void set_a(double val) { this->dsbA->setValue(val); }

    // b
    double get_b() { return this->dsbB->value(); }
    void set_b(double val) { this->dsbB->setValue(val); }

    // c
    double get_c() { return this->dsbC->value(); }
    void set_c(double val) { this->dsbC->setValue(val); }

    // PoseConf
    PoseConf* get_conf() { return this->poseConf;}
};

#endif // POSE_H
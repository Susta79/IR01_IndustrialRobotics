#ifndef JOINT_H
#define JOINT_H

#define _USE_MATH_DEFINES
#include <math.h>

#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <Eigen/Dense>

using namespace Eigen;

class Joint
{
private:
    QString name;
    QDoubleSpinBox *dsbJoint1;
    QDoubleSpinBox *dsbJoint2;
    QDoubleSpinBox *dsbJoint3;
    QDoubleSpinBox *dsbJoint4;
    QDoubleSpinBox *dsbJoint5;
    QDoubleSpinBox *dsbJoint6;

public:
    QGroupBox *gbJoints;

    Joint(QString n);
    ~Joint();

    Array<double, 6, 1> get_joints_rad();
    void set_joints_rad(Array<double, 6, 1>);
    Array<double, 6, 1> get_joints_deg();
    void set_joints_deg(Array<double, 6, 1>);

    // Joint1
    double Joint::get_joint1_rad() { return this->dsbJoint1->value() * M_PI / 180.0; }
    double Joint::get_joint1_deg() { return this->dsbJoint1->value(); }
    void Joint::set_joint1_rad(double val) { this->dsbJoint1->setValue(val); }
    void Joint::set_joint1_deg(double val) { this->dsbJoint1->setValue(val); }

    // Joint2
    double Joint::get_joint2_rad() { return this->dsbJoint2->value() * M_PI / 180.0; }
    double Joint::get_joint2_deg() { return this->dsbJoint2->value(); }
    void Joint::set_joint2_rad(double val) { this->dsbJoint2->setValue(val); }
    void Joint::set_joint2_deg(double val) { this->dsbJoint2->setValue(val); }

    // Joint3
    double Joint::get_joint3_rad() { return this->dsbJoint3->value() * M_PI / 180.0; }
    double Joint::get_joint3_deg() { return this->dsbJoint3->value(); }
    void Joint::set_joint3_rad(double val) { this->dsbJoint3->setValue(val); }
    void Joint::set_joint3_deg(double val) { this->dsbJoint3->setValue(val); }

    // Joint4
    double Joint::get_joint4_rad() { return this->dsbJoint4->value() * M_PI / 180.0; }
    double Joint::get_joint4_deg() { return this->dsbJoint4->value(); }
    void Joint::set_joint4_rad(double val) { this->dsbJoint4->setValue(val); }
    void Joint::set_joint4_deg(double val) { this->dsbJoint4->setValue(val); }

    // Joint5
    double Joint::get_joint5_rad() { return this->dsbJoint5->value() * M_PI / 180.0; }
    double Joint::get_joint5_deg() { return this->dsbJoint5->value(); }
    void Joint::set_joint5_rad(double val) { this->dsbJoint5->setValue(val); }
    void Joint::set_joint5_deg(double val) { this->dsbJoint5->setValue(val); }

    // Joint6
    double Joint::get_joint6_rad() { return this->dsbJoint6->value() * M_PI / 180.0; }
    double Joint::get_joint6_deg() { return this->dsbJoint6->value(); }
    void Joint::set_joint6_rad(double val) { this->dsbJoint6->setValue(val); }
    void Joint::set_joint6_deg(double val) { this->dsbJoint6->setValue(val); }

};

#endif // JOINT_H
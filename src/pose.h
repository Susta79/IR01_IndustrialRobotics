#ifndef POSE_H
#define POSE_H

#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>
//#include <QCheckBox>
#include <QComboBox>

#include <Eigen\Geometry>

//#include "pose_conf.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Eigen;
using namespace std;

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
    QComboBox* cbPoseConf;

public:
    QGroupBox *gbGroup;

    Pose() { new (this) Pose("", Affine3d::Identity(), "FUP"); }
    Pose(QString name) { new (this) Pose(name, Affine3d::Identity(), "FUP"); }
    Pose(Affine3d m) { new (this) Pose("", m, "FUP"); }
    Pose(Affine3d m, string cfg) { new (this) Pose("", m, cfg); }
    Pose(QString name, Affine3d m, string cfg);
    ~Pose();

    // pose
    Affine3d get_pose();
    void set_pose(Affine3d m) { set_pose(m, "FUP"); };
    void set_pose(Affine3d m, string cfg);

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
    //PoseConf* get_pose_conf() { return this->poseConf; }
    //void set_pose_conf(PoseConf* cfg) { if (poseConf) { delete poseConf; } this->poseConf=cfg; }
//
    //// Conf
    //string get_conf() { return this->poseConf->get_conf(); }
    //void set_conf(string cfg) { this->poseConf->set_conf(cfg); }
//
    //bool is_conf_Front() { return this->poseConf->is_conf_Front(); }
    //bool is_conf_Back()  { return this->poseConf->is_conf_Back(); }
    //bool is_conf_Up()    { return this->poseConf->is_conf_Up(); }
    //bool is_conf_Down()  { return this->poseConf->is_conf_Down(); }
    //bool is_conf_Positive()   { return this->poseConf->is_conf_Positive(); }
    //bool is_conf_Negative()   { return this->poseConf->is_conf_Negative(); }

    // Conf
    string get_conf() { return this->cbPoseConf->currentText().toStdString(); }
    void set_conf(string cfg);

    bool is_conf_Front()    { return (this->get_conf().find("F")!=string::npos); }
    bool is_conf_Back()     { return (this->get_conf().find("B")!=string::npos); }
    bool is_conf_Up()       { return (this->get_conf().find("U")!=string::npos); }
    bool is_conf_Down()     { return (this->get_conf().find("D")!=string::npos); }
    bool is_conf_Positive() { return (this->get_conf().find("P")!=string::npos); }
    bool is_conf_Negative() { return (this->get_conf().find("N")!=string::npos); }
};

#endif // POSE_H
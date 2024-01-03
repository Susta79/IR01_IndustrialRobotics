#include "pose.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <Eigen/Dense>

Pose::Pose(QString n, Affine3d m, string cfg){
    this->name = n;

    this->dsbX = new QDoubleSpinBox;
    this->dsbX->setRange(-9999.0, 9999.0);
    this->dsbX->setSingleStep(1.0);
    this->dsbX->setSuffix("mm");
    this->dsbX->setValue(0.0);
    this->dsbX->setDecimals(2);

    this->dsbY = new QDoubleSpinBox;
    this->dsbY->setRange(-9999.0, 9999.0);
    this->dsbY->setSingleStep(1.0);
    this->dsbY->setSuffix("mm");
    this->dsbY->setValue(0.0);
    this->dsbY->setDecimals(2);

    this->dsbZ = new QDoubleSpinBox;
    this->dsbZ->setRange(-9999.0, 9999.0);
    this->dsbZ->setSingleStep(1.0);
    this->dsbZ->setSuffix("mm");
    this->dsbZ->setValue(0.0);
    this->dsbZ->setDecimals(2);

    this->dsbA = new QDoubleSpinBox;
    this->dsbA->setRange(-360.0, 360.0);
    this->dsbA->setSingleStep(1.0);
    this->dsbA->setSuffix("°");
    this->dsbA->setValue(0.0);
    this->dsbA->setDecimals(3);

    this->dsbB = new QDoubleSpinBox;
    this->dsbB->setRange(-360.0, 360.0);
    this->dsbB->setSingleStep(1.0);
    this->dsbB->setSuffix("°");
    this->dsbB->setValue(0.0);
    this->dsbB->setDecimals(3);

    this->dsbC = new QDoubleSpinBox;
    this->dsbC->setRange(-360.0, 360.0);
    this->dsbC->setSingleStep(1.0);
    this->dsbC->setSuffix("°");
    this->dsbC->setValue(0.0);
    this->dsbC->setDecimals(3);

    this->cbPoseConf = new QComboBox();
    this->cbPoseConf->addItem("FUP",QChar('FUP'));
    this->cbPoseConf->addItem("FUN",QChar('FUN'));
    this->cbPoseConf->addItem("FDP",QChar('FDP'));
    this->cbPoseConf->addItem("FDN",QChar('FDN'));
    this->cbPoseConf->addItem("BUP",QChar('BUP'));
    this->cbPoseConf->addItem("BUN",QChar('BUN'));
    this->cbPoseConf->addItem("BDP",QChar('BDP'));
    this->cbPoseConf->addItem("BDN",QChar('BDN'));
    this->cbPoseConf->addItem("###",QChar('###'));
    this->cbPoseConf->setCurrentIndex(0);

    this->gbGroup = new QGroupBox("Pose");
    QFormLayout *layoutJoints = new QFormLayout;
    layoutJoints->addRow(new QLabel("X:"), dsbX);
    layoutJoints->addRow(new QLabel("Y:"), dsbY);
    layoutJoints->addRow(new QLabel("Z:"), dsbZ);
    layoutJoints->addRow(new QLabel("A:"), dsbA);
    layoutJoints->addRow(new QLabel("B:"), dsbB);
    layoutJoints->addRow(new QLabel("C:"), dsbC);
    layoutJoints->addRow(new QLabel("Cfg:"), cbPoseConf);
    this->gbGroup->setLayout(layoutJoints);

    this->set_pose(m);
    this->set_conf(cfg);
}

Pose::~Pose(){
    if (dsbX) {
        delete dsbX;
        dsbX = nullptr;
    }
    if (dsbY) {
        delete dsbY;
        dsbY = nullptr;
    }
    if (dsbZ) {
        delete dsbZ;
        dsbZ = nullptr;
    }
    if (dsbA) {
        delete dsbA;
        dsbA = nullptr;
    }
    if (dsbB) {
        delete dsbB;
        dsbB = nullptr;
    }
    if (dsbC) {
        delete dsbC;
        dsbC = nullptr;
    }
    if (cbPoseConf) {
        delete cbPoseConf;
        cbPoseConf = nullptr;
    }
    if (gbGroup) {
        delete gbGroup;
        gbGroup = nullptr;
    }
}

// pose
Affine3d Pose::get_pose(){
    Matrix3d rot;
    Affine3d p = Affine3d::Identity();
    p.translation() = Vector3d(this->dsbX->value(), this->dsbY->value(), this->dsbZ->value());
    rot = AngleAxisd(this->dsbC->value() * M_PI / 180.0, Vector3d::UnitZ()) *
        AngleAxisd(this->dsbB->value() * M_PI / 180.0, Vector3d::UnitY()) *
        AngleAxisd(this->dsbA->value() * M_PI / 180.0, Vector3d::UnitX());
    p.linear() = rot;
    return p;
}

void Pose::set_pose(Affine3d m, string cfg){
    Vector3d t = m.translation();
    this->dsbX->setValue(t.x());
    this->dsbY->setValue(t.y());
    this->dsbZ->setValue(t.z());
    Vector3d ea = m.rotation().eulerAngles(2, 1, 0) * 180.0 / M_PI;
    this->dsbA->setValue(ea.z());
    this->dsbB->setValue(ea.y());
    this->dsbC->setValue(ea.x());

    this->set_conf(cfg);
}

void Pose::set_conf(string cfg) {
    int found = cbPoseConf->findText(QString::fromStdString(cfg));
    if ( found>=0 ) cbPoseConf->setCurrentIndex( found );
    // return;
    //if (cfg=="FUP")
    //    cbPoseConf->setCurrentText(QString::fromStdString("FUP"));
    //else if (cfg=="FUN")
    //    cbPoseConf->setCurrentText(QString::fromStdString("FUN"));
    //else if (cfg=="FDP")
    //    cbPoseConf->setCurrentText(QString::fromStdString("FDP"));
    //else if (cfg=="FDN")
    //    cbPoseConf->setCurrentText(QString::fromStdString("FDN"));
    //else if (cfg=="BUP")
    //    cbPoseConf->setCurrentText(QString::fromStdString("BUP"));
    //else if (cfg=="BUN")
    //    cbPoseConf->setCurrentText(QString::fromStdString("BUN"));
    //else if (cfg=="BDP")
    //    cbPoseConf->setCurrentText(QString::fromStdString("BDP"));
    //else if (cfg=="BDN")
    //    cbPoseConf->setCurrentText(QString::fromStdString("BDN"));
}

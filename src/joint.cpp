#include "joint.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>

Joint::Joint(QString n){
    this->name = n;

    // Group Joints
    this->dsbJoint1 = new QDoubleSpinBox;
    this->dsbJoint1->setRange(-360.0, 360.0);
    this->dsbJoint1->setSingleStep(1.0);
    this->dsbJoint1->setSuffix("°");
    this->dsbJoint1->setValue(0.0);
    this->dsbJoint1->setDecimals(3);

    this->dsbJoint2 = new QDoubleSpinBox;
    this->dsbJoint2->setRange(-360.0, 360.0);
    this->dsbJoint2->setSingleStep(1.0);
    this->dsbJoint2->setSuffix("°");
    this->dsbJoint2->setValue(0.0);
    this->dsbJoint2->setDecimals(3);

    this->dsbJoint3 = new QDoubleSpinBox;
    this->dsbJoint3->setRange(-360.0, 360.0);
    this->dsbJoint3->setSingleStep(1.0);
    this->dsbJoint3->setSuffix("°");
    this->dsbJoint3->setValue(0.0);
    this->dsbJoint3->setDecimals(3);

    this->dsbJoint4 = new QDoubleSpinBox;
    this->dsbJoint4->setRange(-360.0, 360.0);
    this->dsbJoint4->setSingleStep(1.0);
    this->dsbJoint4->setSuffix("°");
    this->dsbJoint4->setValue(0.0);
    this->dsbJoint4->setDecimals(3);

    this->dsbJoint5 = new QDoubleSpinBox;
    this->dsbJoint5->setRange(-360.0, 360.0);
    this->dsbJoint5->setSingleStep(1.0);
    this->dsbJoint5->setSuffix("°");
    this->dsbJoint5->setValue(0.0);
    this->dsbJoint5->setDecimals(3);

    this->dsbJoint6 = new QDoubleSpinBox;
    this->dsbJoint6->setRange(-360.0, 360.0);
    this->dsbJoint6->setSingleStep(1.0);
    this->dsbJoint6->setSuffix("°");
    this->dsbJoint6->setValue(0.0);
    this->dsbJoint6->setDecimals(3);

    this->gbJoints = new QGroupBox(this->name);
    QFormLayout *layoutJoints = new QFormLayout;
    layoutJoints->addRow(new QLabel("Joint 1:"), dsbJoint1);
    layoutJoints->addRow(new QLabel("Joint 2:"), dsbJoint2);
    layoutJoints->addRow(new QLabel("Joint 3:"), dsbJoint3);
    layoutJoints->addRow(new QLabel("Joint 4:"), dsbJoint4);
    layoutJoints->addRow(new QLabel("Joint 5:"), dsbJoint5);
    layoutJoints->addRow(new QLabel("Joint 6:"), dsbJoint6);
    this->gbJoints->setLayout(layoutJoints);
}

Joint::~Joint(){
    // Group Joints
    if (dsbJoint1) {
        delete dsbJoint1;
        dsbJoint1 = nullptr;
    }
    if (dsbJoint2) {
        delete dsbJoint2;
        dsbJoint2 = nullptr;
    }
    if (dsbJoint3) {
        delete dsbJoint3;
        dsbJoint3 = nullptr;
    }
    if (dsbJoint4) {
        delete dsbJoint4;
        dsbJoint4 = nullptr;
    }
    if (dsbJoint5) {
        delete dsbJoint5;
        dsbJoint5 = nullptr;
    }
    if (dsbJoint6) {
        delete dsbJoint6;
        dsbJoint6 = nullptr;
    }
    // Group
    if (gbJoints) {
        delete gbJoints;
        gbJoints = nullptr;
    }
}

// All joints in radiant
Array<double, 6, 1> Joint::get_joints_rad() {
    Array<double, 6, 1> j;
    j << this->dsbJoint1->value() * M_PI / 180.0,
        this->dsbJoint2->value() * M_PI / 180.0,
        this->dsbJoint3->value() * M_PI / 180.0,
        this->dsbJoint4->value() * M_PI / 180.0,
        this->dsbJoint5->value() * M_PI / 180.0,
        this->dsbJoint6->value() * M_PI / 180.0;
    return j;
}

void Joint::set_joints_rad(Array<double, 6, 1> j) {
    this->dsbJoint1->setValue(j(0) * 180.0 / M_PI);
    this->dsbJoint2->setValue(j(1) * 180.0 / M_PI);
    this->dsbJoint3->setValue(j(2) * 180.0 / M_PI);
    this->dsbJoint4->setValue(j(3) * 180.0 / M_PI);
    this->dsbJoint5->setValue(j(4) * 180.0 / M_PI);
    this->dsbJoint6->setValue(j(5) * 180.0 / M_PI);
}

Array<double, 6, 1> Joint::get_joints_deg() {
    Array<double, 6, 1> j;
    j << this->dsbJoint1->value(),
        this->dsbJoint2->value(),
        this->dsbJoint3->value(),
        this->dsbJoint4->value(),
        this->dsbJoint5->value(),
        this->dsbJoint6->value();
    return j;
}

void Joint::set_joints_deg(Array<double, 6, 1> j) {
    this->dsbJoint1->setValue(j(0));
    this->dsbJoint2->setValue(j(1));
    this->dsbJoint3->setValue(j(2));
    this->dsbJoint4->setValue(j(3));
    this->dsbJoint5->setValue(j(4));
    this->dsbJoint6->setValue(j(5));
}

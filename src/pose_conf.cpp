#include "pose_conf.h"

#include <QHBoxLayout>

PoseConf::PoseConf(char16_t fb, char16_t ud, char16_t pn){
    cbFrontBack = new QComboBox();
    cbFrontBack->addItem("F",QChar('F'));
    cbFrontBack->addItem("B",QChar('B'));

    cbUpDown = new QComboBox();
    cbUpDown->addItem("U",QChar('U'));
    cbUpDown->addItem("D",QChar('D'));

    cbPosNeg = new QComboBox();
    cbPosNeg->addItem("P",QChar('P'));
    cbPosNeg->addItem("N",QChar('N'));

    this->gbGroup = new QGroupBox();
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(cbFrontBack);
    hBoxLayout->addWidget(cbUpDown);
    hBoxLayout->addWidget(cbPosNeg);
    this->gbGroup->setLayout(hBoxLayout);

    this->set_front_back(fb);
    this->set_up_down(ud);
    this->set_pos_neg(pn);
}

PoseConf::~PoseConf(){
    if (cbFrontBack) {
        delete cbFrontBack;
        cbFrontBack = nullptr;
    }
    if (cbUpDown) {
        delete cbUpDown;
        cbUpDown = nullptr;
    }
    if (cbPosNeg) {
        delete cbPosNeg;
        cbPosNeg = nullptr;
    }
    if (gbGroup) {
        delete gbGroup;
        gbGroup = nullptr;
    }
}

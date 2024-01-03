#include "pose_conf.h"

#include <QHBoxLayout>

PoseConf::PoseConf(string cfg){
    cbPoseConf = new QComboBox();
    cbPoseConf->addItem("FUP",QChar('FUP'));
    cbPoseConf->addItem("FUN",QChar('FUN'));
    cbPoseConf->addItem("FDP",QChar('FDP'));
    cbPoseConf->addItem("FDN",QChar('FDN'));
    cbPoseConf->addItem("BUP",QChar('BUP'));
    cbPoseConf->addItem("BUN",QChar('BUN'));
    cbPoseConf->addItem("BDP",QChar('BDP'));
    cbPoseConf->addItem("BDN",QChar('BDN'));
    cbPoseConf->addItem("###",QChar('###'));

    this->gbGroup = new QGroupBox();
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(cbPoseConf);
    this->gbGroup->setLayout(hBoxLayout);

    this->set_conf(cfg);
}

PoseConf::~PoseConf(){
    if (cbPoseConf) {
        delete cbPoseConf;
        cbPoseConf = nullptr;
    }
    if (gbGroup) {
        delete gbGroup;
        gbGroup = nullptr;
    }
}

void PoseConf::set_conf(string cfg) {
    int found = cbPoseConf->findText(QString::fromStdString(cfg));
    if ( found>=0 ) cbPoseConf->setCurrentIndex( found );
    // return;
    if (cfg=="FUP")
        cbPoseConf->setCurrentText(QString::fromStdString("FUP"));
    else if (cfg=="FUN")
        cbPoseConf->setCurrentText(QString::fromStdString("FUN"));
    else if (cfg=="FDP")
        cbPoseConf->setCurrentText(QString::fromStdString("FDP"));
    else if (cfg=="FDN")
        cbPoseConf->setCurrentText(QString::fromStdString("FDN"));
    else if (cfg=="BUP")
        cbPoseConf->setCurrentText(QString::fromStdString("BUP"));
    else if (cfg=="BUN")
        cbPoseConf->setCurrentText(QString::fromStdString("BUN"));
    else if (cfg=="BDP")
        cbPoseConf->setCurrentText(QString::fromStdString("BDP"));
    else if (cfg=="BDN")
        cbPoseConf->setCurrentText(QString::fromStdString("BDN"));
}


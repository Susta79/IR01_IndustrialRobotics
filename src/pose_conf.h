#ifndef POSE_CONF_H
#define POSE_CONF_H

//#include <string.h>
#include <QGroupBox>
#include <QComboBox>

using namespace std;

class PoseConf
{
private:
    QComboBox* cbPoseConf;

public:
    QGroupBox *gbGroup;

    PoseConf() { new (this) PoseConf("FUP"); }
    PoseConf(string cfg);
    ~PoseConf();

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

#endif // POSE_CONF_H
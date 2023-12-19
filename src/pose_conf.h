#ifndef POSE_CONF_H
#define POSE_CONF_H

#include <QGroupBox>
#include <QComboBox>

class PoseConf
{
private:
    QComboBox* cbFrontBack;
    QComboBox* cbUpDown;
    QComboBox* cbPosNeg;

public:
    QGroupBox *gbGroup;

    PoseConf() { new (this) PoseConf('F', 'U', 'P'); }
    PoseConf(char16_t fb, char16_t ud, char16_t pn);
    ~PoseConf();

    // FrontBack
    char16_t get_front_back() { return this->cbFrontBack->itemData(cbFrontBack->currentIndex()).toChar().unicode(); }
    void set_front_back(char16_t c) { if ( cbFrontBack->findData(c) ) cbFrontBack->setCurrentIndex(cbFrontBack->findData(c)); }

    // UpDown
    char16_t get_up_down() { return this->cbUpDown->itemData(cbUpDown->currentIndex()).toChar().unicode(); }
    void set_up_down(char16_t c) { if ( cbUpDown->findData(c) ) cbUpDown->setCurrentIndex(cbUpDown->findData(c)); }

    // PosNeg
    char16_t get_pos_neg() { return this->cbPosNeg->itemData(cbPosNeg->currentIndex()).toChar().unicode(); }
    void set_pos_neg(char16_t c) { if ( cbPosNeg->findData(c) ) cbPosNeg->setCurrentIndex(cbPosNeg->findData(c)); }

};

#endif // POSE_CONF_H
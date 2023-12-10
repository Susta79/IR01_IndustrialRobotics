#include "trajectory.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <Eigen/Dense>

Trajectory::Trajectory(){
    this->Init();
}

Trajectory::Trajectory(Affine3d m){
    this->Init();
    this->set_pose(m);
}

Trajectory::~Trajectory(){
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
    // Group
    if (gbPose) {
        delete gbPose;
        gbPose = nullptr;
    }
}

void Trajectory::Init(){
    // Group Links
    this->dsbX = new QDoubleSpinBox;
    this->dsbX->setRange(-9999.0, 9999.0);
    this->dsbX->setSingleStep(1.0);
    this->dsbX->setSuffix("mm");
    this->dsbX->setValue(0.0);
    this->dsbX->setDecimals(1);

    this->dsbY = new QDoubleSpinBox;
    this->dsbY->setRange(-9999.0, 9999.0);
    this->dsbY->setSingleStep(1.0);
    this->dsbY->setSuffix("mm");
    this->dsbY->setValue(0.0);
    this->dsbY->setDecimals(1);

    this->dsbZ = new QDoubleSpinBox;
    this->dsbZ->setRange(-9999.0, 9999.0);
    this->dsbZ->setSingleStep(1.0);
    this->dsbZ->setSuffix("mm");
    this->dsbZ->setValue(0.0);
    this->dsbZ->setDecimals(1);

    this->dsbA = new QDoubleSpinBox;
    this->dsbA->setRange(-360.0, 360.0);
    this->dsbA->setSingleStep(1.0);
    this->dsbA->setSuffix("°");
    this->dsbA->setValue(0.0);
    this->dsbA->setDecimals(1);

    this->dsbB = new QDoubleSpinBox;
    this->dsbB->setRange(-360.0, 360.0);
    this->dsbB->setSingleStep(1.0);
    this->dsbB->setSuffix("°");
    this->dsbB->setValue(0.0);
    this->dsbB->setDecimals(1);

    this->dsbC = new QDoubleSpinBox;
    this->dsbC->setRange(-360.0, 360.0);
    this->dsbC->setSingleStep(1.0);
    this->dsbC->setSuffix("°");
    this->dsbC->setValue(0.0);
    this->dsbC->setDecimals(1);

    this->gbPose = new QGroupBox("Pose");
    QFormLayout *layoutJoints = new QFormLayout;
    layoutJoints->addRow(new QLabel("X:"), dsbX);
    layoutJoints->addRow(new QLabel("Y:"), dsbY);
    layoutJoints->addRow(new QLabel("Z:"), dsbZ);
    layoutJoints->addRow(new QLabel("A:"), dsbA);
    layoutJoints->addRow(new QLabel("B:"), dsbB);
    layoutJoints->addRow(new QLabel("C:"), dsbC);
    this->gbPose->setLayout(layoutJoints);
}

// pose
Affine3d Trajectory::get_pose(){
    Affine3d p = Eigen::Affine3d::Identity();
    p.translation() = Eigen::Vector3d(this->dsbX->value(), this->dsbY->value(), this->dsbZ->value());
    Matrix3d rot;
    rot = AngleAxisd(this->dsbA->value() * M_PI / 180.0, Vector3d::UnitZ())
        * AngleAxisd(this->dsbB->value() * M_PI / 180.0, Vector3d::UnitY())
        * AngleAxisd(this->dsbC->value() * M_PI / 180.0, Vector3d::UnitX());
    p.linear() = rot;
    return p;
}
void Trajectory::set_pose(Affine3d m){
    Vector3d t = m.translation();
    this->dsbX->setValue(t.x());
    this->dsbY->setValue(t.y());
    this->dsbZ->setValue(t.z());
    Vector3d ea = m.rotation().eulerAngles(2, 1, 0) * 180.0 / M_PI;
    this->dsbA->setValue(ea.z());
    this->dsbB->setValue(ea.y());
    this->dsbC->setValue(ea.x());
}

// x
double Trajectory::get_x()
{
    return this->dsbX->value();
}
void Trajectory::set_x(double val)
{
    this->dsbX->setValue(val);
}

// y
double Trajectory::get_y()
{
    return this->dsbY->value();
}
void Trajectory::set_y(double val)
{
    this->dsbY->setValue(val);
}

// z
double Trajectory::get_z()
{
    return this->dsbZ->value();
}
void Trajectory::set_z(double val)
{
    this->dsbZ->setValue(val);
}

// a
double Trajectory::get_a()
{
    return this->dsbA->value();
}
void Trajectory::set_a(double val)
{
    this->dsbA->setValue(val);
}

// b
double Trajectory::get_b()
{
    return this->dsbB->value();
}
void Trajectory::set_b(double val)
{
    this->dsbB->setValue(val);
}

// c
double Trajectory::get_c()
{
    return this->dsbC->value();
}
void Trajectory::set_c(double val)
{
    this->dsbC->setValue(val);
}

void Trajectory::Line(){
   double x0, y0, x1, y1;
   double L;
   double V, A, J;
   double t1,v1,d1;
   double t2,v2,d2;
   double t3,v3,d3;
   double t4,v4,d4;
   double t5,v5,d5;
   double t6,v6,d6;
   double t7,v7,d7;

   double t,j,a,v,d;
   double t_arr[500];
   double j_arr[500];
   double a_arr[500];
   double v_arr[500];
   double d_arr[500];

   x0=500.0;
   y0=450.0;
   x1=-500.0;
   y1=450.0;

   L=sqrt(pow(x1-x0,2) + pow(y1-y0,2));

   V=2000;     // 2mm/s
   A=10000;    // 10000 mm/s^2
   J=100000;   // 100000 mm/s^3
   
   t1=A/J;
   v1=(J*pow(t1,2))/2;
   d1=(J*pow(t1,3))/6;

   t2=(V/A)-(A/J);
   v2=v1+A*t2;
   d2=v1*t2+(A*pow(t2,2))/2;
   
   t3=t1;
   v3=V-(J*pow(((A/J)-t3),2))/2;
   d3=V*t3-(J*pow(t3,3))/6;
   
   d4=L-2*(d1+d2+d3);
   v4=V;
   t4=d4/v4;

   t5=t3;
   v5=V-(J*pow(t5,2))/2;
   d5=d3;

   t6=t2;
   v6=v5-A*t6;
   d6=d2;

   t7=t1;
   v7=(J*pow((A/J)-t7,2))/2;
   d7=d1;

   for (size_t i = 0; i < 500; i++){
      t_arr[i]=(double(i+1))/100.0;
      if (t_arr[i]<=t1){
         // 1st
         t=t_arr[i];
         j=J;
         a=J*t;
         v=(J*pow(t,2))/2;
         d=(J*pow(t,3))/6;
      } else if (t_arr[i]<=(t1+t2))
      {
         //2nd
         t = t_arr[i]-t1;
         j=0;
         a=A;
         v=v1+A*t;
         d=d1+v1*t+(A*pow(t,2))/2;
      } else if (t_arr[i]<=(t1+t2+t3))
      {
         //3rd
         t=t_arr[i]-t1-t2;
         j=-J;
         a=A-J*t;
         v=V-(J*pow(((A/J)-t),2))/2;
         d=d1+d2+(V*t-(J*pow(t,3))/6-(pow(A,2)*t)/(2*J)+(A*pow(t,2))/2);
      } else if (t_arr[i]<=(t1+t2+t3+t4))
      {
         //4th
         t=t_arr[i]-t1-t2-t3;
         j=0;
         a=0;
         v=V;
         d=d1+d2+d3+V*t;
      } else if (t_arr[i]<=(t1+t2+t3+t4+t5))
      {
         //5th
         t=t_arr[i]-t1-t2-t3-t4;
         j=-J;
         a=-J*t;
         v=V-(J*pow(t,2))/2;
         d=d1+d2+d3+d4+(V*t-(J*pow(t,3))/6);
      } else if (t_arr[i]<=(t1+t2+t3+t4+t5+t6))
      {
         //6th
         t=t_arr[i]-t1-t2-t3-t4-t5;
         j=0;
         a=-A;
         v=v5-A*t;
         d=d1+d2+d3+d4+d5+(V-v1)*t -(A*pow(t,2))/2;
      } else if (t_arr[i]<=(t1+t2+t3+t4+t5+t6+t7))
      {
         //7th
         t=t_arr[i]-t1-t2-t3-t4-t5-t6;
         j=J;
         a=J*t-A;
         v=(J*pow(A/J-t,2))/2;
         d=d1+d2+d3+d4+d5+d6+(J*pow(t,3))/6-(A*pow(t,2))/2+(pow(A,2)*t/J)/2;
      } else
      {
         j=0;
         a=0;
         v=0;
         d=L;
      }
      j_arr[i]=j;
      a_arr[i]=a;
      v_arr[i]=v;
      d_arr[i]=d;
   }

   return;
}
#include "trajectory.h"

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <Eigen/Dense>

Trajectory::Trajectory(){
   // From pose
   Matrix3d rot0;
   Affine3d p0 = Affine3d::Identity();
   p0.translation() = Vector3d(1200, -1000, 2400);
   rot0 = AngleAxisd(0 * M_PI / 180.0, Vector3d::UnitZ()) *
      AngleAxisd(90 * M_PI / 180.0, Vector3d::UnitY()) *
      AngleAxisd(0 * M_PI / 180.0, Vector3d::UnitX());
   p0.linear() = rot0;
   this->pFromPose = new Pose("From", p0, "FUP");

   // To pose
   Matrix3d rot1;
   Affine3d p1 = Affine3d::Identity();
   p1.translation() = Vector3d(1200, 1000, 2400);
   rot1 = AngleAxisd(0 * M_PI / 180.0, Vector3d::UnitZ()) *
      AngleAxisd(90 * M_PI / 180.0, Vector3d::UnitY()) *
      AngleAxisd(0 * M_PI / 180.0, Vector3d::UnitX());
   p1.linear() = rot1;
   this->pToPose = new Pose("To", p1, "FUP");

   this->dsbMaxSpeed = new QDoubleSpinBox;
   this->dsbMaxSpeed->setRange(0, 10000);
   this->dsbMaxSpeed->setSingleStep(100.0);
   this->dsbMaxSpeed->setSuffix("mm/s");
   this->dsbMaxSpeed->setValue(2000);
   this->dsbMaxSpeed->setDecimals(0);

   this->dsbMaxAccDec = new QDoubleSpinBox;
   this->dsbMaxAccDec->setRange(0, 1000000);
   this->dsbMaxAccDec->setSingleStep(100.0);
   this->dsbMaxAccDec->setSuffix("mm/s^2");
   this->dsbMaxAccDec->setValue(10000);
   this->dsbMaxAccDec->setDecimals(0);

   this->dsbMaxJerk = new QDoubleSpinBox;
   this->dsbMaxJerk->setRange(0, 1000000);
   this->dsbMaxJerk->setSingleStep(100.0);
   this->dsbMaxJerk->setSuffix("mm/s^3");
   this->dsbMaxJerk->setValue(100000);
   this->dsbMaxJerk->setDecimals(0);

   this->pbLinear = new QPushButton("Linear");
   this->pbJoint = new QPushButton("Joint");

   QHBoxLayout *layoutPose = new QHBoxLayout();
   layoutPose->addWidget(pFromPose->gbGroup);
   layoutPose->addWidget(pToPose->gbGroup);

   QWidget *widgetPose = new QWidget();
   widgetPose->setLayout(layoutPose);

   QFormLayout *layoutSettings = new QFormLayout();
   layoutSettings->addRow(new QLabel("Max speed:"), dsbMaxSpeed);
   layoutSettings->addRow(new QLabel("Max acc:"), dsbMaxAccDec);
   layoutSettings->addRow(new QLabel("Max jerk:"), dsbMaxJerk);
   layoutSettings->addRow(new QLabel(""), pbLinear);
   layoutSettings->addRow(new QLabel(""), pbJoint);

   QWidget *widgetSettings = new QWidget();
   widgetSettings->setLayout(layoutSettings);

   QHBoxLayout *hBoxLayout = new QHBoxLayout();
   hBoxLayout->addWidget(widgetPose);
   hBoxLayout->addWidget(widgetSettings);

   // Group Main
   this->gbGroup = new QGroupBox("PTP");
   gbGroup->setLayout(hBoxLayout);

   connect(pbLinear, &QPushButton::released, this, &Trajectory::pbLinear_released);
   connect(pbJoint, &QPushButton::released, this, &Trajectory::pbJoint_released);
}

Trajectory::~Trajectory(){
    if (pFromPose) {
        delete pFromPose;
        pFromPose = nullptr;
    }
    if (pToPose) {
        delete pToPose;
        pToPose = nullptr;
    }
    if (dsbMaxSpeed) {
        delete dsbMaxSpeed;
        dsbMaxSpeed = nullptr;
    }
    if (dsbMaxAccDec) {
        delete dsbMaxAccDec;
        dsbMaxAccDec = nullptr;
    }
    if (dsbMaxJerk) {
        delete dsbMaxJerk;
        dsbMaxJerk = nullptr;
    }
    if (pbLinear) {
        delete pbLinear;
        pbLinear = nullptr;
    }
    if (pbJoint) {
        delete pbJoint;
        pbJoint = nullptr;
    }
    if (gbGroup) {
        delete gbGroup;
        gbGroup = nullptr;
    }
}

void Trajectory::pbLinear_released()
{
  // 
  this->Linear(this->pFromPose, this->pToPose);
}

void Trajectory::pbJoint_released()
{
  // 
  this->Joint();
}

/*
void Trajectory::Linear(){
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
*/

// Inizio calcolando solo la traslazione. La rotazione non la considero proprio!
void Trajectory::Linear(Pose* pPose0, Pose* pPose1){
   //double x0, y0, x1, y1;
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

   Vector3d p0 = pPose0->get_pose().translation();
   Vector3d p1 = pPose1->get_pose().translation();

   //x0=500.0;
   //y0=450.0;
   //x1=-500.0;
   //y1=450.0;

   L=sqrt(pow(p1.x()-p0.x(),2) + pow(p1.y()-p0.y(),2) + pow(p1.z()-p0.z(),2));

   //Max speed in mm/s
   V=dsbMaxSpeed->value();
   //Max acceleration in mm/s^2
   A=dsbMaxAccDec->value();
   //Max jerk in mm/s^3
   J=dsbMaxJerk->value();
   
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

void Trajectory::Joint(){
   return;
}
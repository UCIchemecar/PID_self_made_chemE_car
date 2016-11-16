#include "DualMC33926MotorShield.h"
#include <PololuWheelEncoders.h>
#include <Wire.h>
long prevT=0; //The first value of millis()
long inter=200; //interval that checks for discepancy between encoder
DualMC33926MotorShield md;

void setup() {
  Serial.begin(115200);
  Serial.println("Dual MC33926 Motor Shield");
  Serial.print("M1");
  Serial.println("       M2");
  md.init();
  PololuWheelEncoders::init(6,11,3,5);//Tell the arduino what port number the encoders are using
}

void loop() {
  int j=PololuWheelEncoders::getCountsAndResetM2();
  int i=PololuWheelEncoders::getCountsAndResetM1();
  static int prevdif1=0;
  static int prevdif2=0;
  static long int count=0;
  static int s1=1700;// the number of ticks per cycle that motor 1 is to rotate
  static int s2=1700;
  static double timer=0;
  int dif1=s1-abs(i);
  int dif2=s2-abs(j);
  Serial.println("dif");
  Serial.print(dif1); Serial.print("    ");
  Serial.println(dif2);
  
  if(count==0)
  {
  int difdif1=dif1-dif1;
  int difdif2=dif1-dif1;
  }
  else
  {
  int difdif1=dif1-prevdif1;
  int difdif2=dif1-prevdif2;
  }

  static float kp1=0.08;//proportional coefficient
  static float kp2=0.08;
  static float ki1=0.02;
  static float ki2=0.02;
  static float kd1=0.01;
  static float kd2=0.01;

  static int totaldif1=0;
  static int totaldif2=0;
  int speed1=293;
  int speed2=293;
  
  totaldif1=totaldif1+dif1;
  totaldif2=totaldif2+dif2;
  Serial.println("total dif");
  Serial.print(totaldif1); Serial.print("    ");
  Serial.println(totaldif2);
  unsigned long currT=millis();
  static float total2;
  static float total1;
  total2=total2+abs(j/3591.84);
  total1=total1+abs(i/3591.84);
  speed1=speed1+kp1*dif1+ki1*totaldif1;
  speed2=speed2+kp2*dif2+ki2*totaldif2;
  /*
  speed1=speed1+kp1*dif1+ki1*totaldif1+kd1*difdif1;
  speed2=speed2+kp2*dif2+ki2*totaldif2+kd2*difdif2;
   */
  Serial.println("speed");
  Serial.print(speed1); Serial.print("    ");
  Serial.println(speed2);
  md.setM1Speed(abs(speed1));
  md.setM2Speed(abs(speed2));
  Serial.println("traveled");
  Serial.print(abs(i)); Serial.print("    ");
  Serial.println(abs(j));
  Serial.println();
  prevdif1=dif1;
  prevdif2=dif2;
  count+=1;
  delay(2);
}

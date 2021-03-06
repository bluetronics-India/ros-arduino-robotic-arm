/*
 * ROS Demo
 * arduino-based rc servo-controlled 3 dof manipulator
 * written by aneesh on 160317
 * controls 3 rc servos connected with pots
 * 
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

Servo servo1, servo2, servo3;

void servo_cb1( const std_msgs::UInt16& cmd_msg){
  int target_angle = cmd_msg.data;
  int initial_angle = servo1.read();
  if (target_angle>initial_angle) 
   {
    for(int i = initial_angle; i < target_angle; i++) {
    servo1.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
  
  else {
    for(int i = initial_angle; i > target_angle; i--) {
    servo1.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
}

void servo_cb2( const std_msgs::UInt16& cmd_msg){
  int target_angle = cmd_msg.data;
  int initial_angle = servo2.read();
  if (target_angle>initial_angle) 
   {
    for(int i = initial_angle; i < target_angle; i++) {
    servo2.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
  
  else {
    for(int i = initial_angle; i > target_angle; i--) {
    servo2.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
}


void servo_cb3( const std_msgs::UInt16& cmd_msg){
  int target_angle = cmd_msg.data;
  int initial_angle = servo3.read();
  if (target_angle>initial_angle) 
   {
    for(int i = initial_angle; i < target_angle; i++) {
    servo3.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
  
  else {
    for(int i = initial_angle; i > target_angle; i--) {
    servo3.write(i); //set servo angle, should be from 0-180  
    delay(15);
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
    }
  }
}

ros::Subscriber<std_msgs::UInt16> sub1("servo1", servo_cb1); //subscriber for servo1 topic, servo_cb1 is the callback
ros::Subscriber<std_msgs::UInt16> sub2("servo2", servo_cb2);
ros::Subscriber<std_msgs::UInt16> sub3("servo3", servo_cb3);

void demo1(){  
  for(int i=0; i<180; i++) {
    servo1.write(i);
    delay(15);
  }
  for(int i=180; i>90; i--) {
    servo1.write(i);
    delay(15);
  }  
}

void demo2(){  
  for(int i=0; i<180; i++) {
    servo2.write(i);
    delay(15);
  }
  for(int i=180; i>0; i--) {
    servo2.write(i);
    delay(15);
  }  
}
  
void demo3(){  
  for(int i=0; i<180; i++) {
    servo3.write(i);
    delay(15);
  }
  for(int i=180; i>0; i--) {
    servo3.write(i);
    delay(15);
  }  
}
  void homeBase() {
    for(int i=90; i>0; i--) {
    servo1.write(i);
    delay(15);
   }
  }


void setup(){
  pinMode(13, OUTPUT); //for blinking

  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  
  delay(10);
  servo1.attach(9);   // attach servo1
  demo1();
  delay(50);
  
  servo2.attach(10);  // attach servo2
  demo2();
  delay(50);
  
  servo3.attach(11);  // attach servo3
  demo3();
  Serial.begin(9600); //for serial monitor
  
  homeBase();
  
}

void loop(){
//for ros control
nh.spinOnce();
delay(1);
}

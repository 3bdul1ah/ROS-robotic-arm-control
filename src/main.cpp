#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>

HardwareSerial Serial1(PA3, PA2);

ros::NodeHandle nh;

Servo servoX;
Servo servoY;

std_msgs::UInt16 servoXMsg;
std_msgs::UInt16 servoYMsg;

ros::Publisher pubX("servo_x_position", &servoXMsg);
ros::Publisher pubY("servo_y_position", &servoYMsg);

void toggleStatusLED() {
  digitalWrite(PC13, HIGH - digitalRead(PC13));
}

void setServoXPosition(const std_msgs::UInt16& msg) {
  servoX.write(msg.data);
  servoXMsg.data = msg.data;
  pubX.publish(&servoXMsg);
}

void setServoYPosition(const std_msgs::UInt16& msg) {
  servoY.write(msg.data);
  servoYMsg.data = msg.data;
  pubY.publish(&servoYMsg);
}



ros::Subscriber<std_msgs::UInt16> subX("servo_x", setServoXPosition);
ros::Subscriber<std_msgs::UInt16> subY("servo_y", setServoYPosition);

void setup() {
  Serial.begin(57600);
  servoX.attach(PA8);
  servoY.attach(PA9);

  nh.initNode();
  nh.subscribe(subX);
  nh.subscribe(subY);

  nh.advertise(pubX);
  nh.advertise(pubY);

  pinMode(PC13, OUTPUT);
}

void loop() {
  nh.spinOnce();
  delay(1);  
}

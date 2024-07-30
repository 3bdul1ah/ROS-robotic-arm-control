#!/usr/bin/env python3

import rospy
from std_msgs.msg import UInt16

def update_parameters():
    global servo_x, servo_y
    try:
        angles = rospy.get_param('servo_angles', [0, 0])
        servo_x, servo_y = angles
        rospy.loginfo(f"Updated parameters: Servo X: {servo_x}, Servo Y: {servo_y}")
    except KeyError as e:
        rospy.logwarn(f"Parameter not found: {e}")

def publish_servo_angles():
    global servo_x, servo_y
    
    rospy.init_node('servo_angle_publisher', anonymous=True)
    
    pub_x = rospy.Publisher('servo_x', UInt16, queue_size=10)
    pub_y = rospy.Publisher('servo_y', UInt16, queue_size=10)
    
    rate = rospy.Rate(10)  

    global servo_x, servo_y
    angles = rospy.get_param('servo_angles', [0, 0])
    servo_x, servo_y = angles
    
    rospy.loginfo(f"Initial parameters: Servo X: {servo_x}, Servo Y: {servo_y}")

    while not rospy.is_shutdown():
        update_parameters()  
        
        pub_x.publish(UInt16(servo_x))
        pub_y.publish(UInt16(servo_y))
        
        rospy.loginfo(f"Published angles: Servo X: {servo_x}, Servo Y: {servo_y}")
        rate.sleep()

if __name__ == '__main__':
    try:
        publish_servo_angles()
    except rospy.ROSInterruptException:
        pass

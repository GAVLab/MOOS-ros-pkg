#!/usr/bin/env python

from time import sleep
from pprint import pprint

import roslib; roslib.load_manifest('MOOS2ROS')
from roslib.packages import InvalidROSPkgException
import rospy
import rostopic

from pymoos.MOOSCommClient import MOOSCommClient

class MOOS2ROSMap(object):
    """Represents a map between MOOS and ROS msgs"""
    def __init__(self):
        self.
        

class MOOS2ROSApp(MOOSCommClient):
    """docstring for MyMOOSApp"""
    def __init__(self):
        MOOSCommClient.__init__(self)
        self.SetOnConnectCallBack(self.onConnect)
        self.SetOnMailCallBack(self.onMail)

    def onConnect(self):
        print("In onConnect")
        return True

    def onMail(self):
        print("In onMail")
        return True

    def add_moos2ros_map(self, name, params):
        # Make sure the msg_type is valid
        split_msg_type = params['msg_type'].split('/')
        if len(split_msg_type) != 2:
            raise ValueError("Invalid msg_type given by " + 
                "%s, should take the form ros_pkg/MsgType" % name)
        msg_pkg, msg_type = split_msg_type
        try:
            roslib.load_manifest(msg_pkg)
            eval("from %s.msgs import %s as msg_obj" % (msg_pkg, msg_type))
        except (ImportError, InvalidROSPkgException) as e:
            raise ValueError("Cannot find msg_type given by " + 
                "%s, should take the form ros_pkg/MsgType: %s" % (name, str(e)))
        

def main():
    # Setup MOOS App
    m = MOOS2ROSApp()
    m.Run("127.0.0.1", 9000, "moos2ros")
    for x in range(10):
        sleep(0.1)
        if m.IsConnected():
            print("Connected to MOOSDB")
            break
    # Setup ROS node
    rospy.init_node('moos2ros')
    # Get the MOOS2ROS configurations
    # data_map = rospy.get_param('DataMap')
    import yaml
    data_map = yaml.load(open('config/example_parameters.yaml', 'r'))
    pprint(data_map)
    moos2ros_map = data_map['MOOS2ROS']
    for name in moos2ros_map:
        m.add_moos2ros_map(name, moos2ros_map[name])

if __name__ == '__main__':
    main()

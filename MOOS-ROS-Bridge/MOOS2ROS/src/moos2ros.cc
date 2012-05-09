#include "MOOS2ROS/moos2ros.h"

#include <MOOSGenLib/MOOSGenLibGlobalHelper.h>
#include <MOOSGenLib/MOOSAssert.h>

MOOS2ROSApp::MOOS2ROSApp() {
    this->node_handle = ros::NodeHandle("MOOS");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    this->SetQuitOnFailedIterate(true);
}

MOOS2ROSApp::~MOOS2ROSApp() {
    ros::shutdown();
}

bool MOOS2ROSApp::OnNewMail(MOOSMSG_LIST &mail_list) {
    MOOSMSG_LIST::iterator p;
    
    for (p = mail_list.begin(); p != mail_list.end(); ++p) {
        CMOOSMsg &msg = *p;
        
        if (msg.IsString() || msg.IsDouble())
            this->handleMsg(msg);
    }
    
    return true;
}

void MOOS2ROSApp::handleMsg(CMOOSMsg &msg) {
    // If the variable doesn't have a publisher
    if (this->publishers.find(msg.GetKey()) == this->publishers.end()) {
        if (msg.IsString()) {
            this->publishers[msg.GetKey()] = 
                this->node_handle.advertise<MOOS_msgs::MOOSString>(msg.GetKey(), 1000);
        } else {
            this->publishers[msg.GetKey()] = 
                this->node_handle.advertise<MOOS_msgs::MOOSDouble>(msg.GetKey(), 1000);
        }
    }
    // Publish
    if (msg.IsString()) {
        MOOS_msgs::MOOSString ros_msg;
        ros_msg.header.stamp = ros::Time(msg.GetTime());
        ros_msg.header.frame_id = "MOOS";
        ros_msg.msg = msg.GetString();
        this->publishers[msg.GetKey()].publish(ros_msg);
    } else {
        MOOS_msgs::MOOSDouble ros_msg;
        ros_msg.header.stamp = ros::Time(msg.GetTime());
        ros_msg.header.frame_id = "MOOS";
        ros_msg.msg = msg.GetDouble();
        this->publishers[msg.GetKey()].publish(ros_msg);
    }
}

bool MOOS2ROSApp::Iterate() {
    if (!ros::ok())
        return false;
    
    this->lookForNewVariables();
    
    return true;
}

void MOOS2ROSApp::lookForNewVariables() {
    if (true) { // Reserved
        MOOSMSG_LIST in_mail;
        if (m_Comms.ServerRequest("VAR_SUMMARY", in_mail, 2.0, false)) {
            MOOSAssert(in_mail.size()==1);
            std::string var_summary(in_mail.begin()->GetString());
            bool there_are_new_vars = false;
            
            while (!var_summary.empty()) {
                std::string var_name = MOOSChomp(var_summary);
                if (GetMOOSVar(var_name) == NULL) {
                    AddMOOSVariable(var_name, var_name, "", 0.0);
                    MOOSTrace("Added variable: %s\n", var_name.c_str());
                    there_are_new_vars = true;
                }
            }
            
            if (there_are_new_vars)
                RegisterMOOSVariables();
        }
    }
}

int main(int argc ,char * argv[]) {
    ros::init(argc, argv, "moos2ros", ros::init_options::NoSigintHandler);
    
    const char * mission_file = "Mission.moos";
    
    const char * app_name = "MOOS2ROS";
    
    switch(argc) {
        case 3:
            app_name = argv[2];
        case 2:
            mission_file = argv[1];
    }
    
    MOOS2ROSApp app;
    
    app.Run(app_name, mission_file);
    
    return 0;
}

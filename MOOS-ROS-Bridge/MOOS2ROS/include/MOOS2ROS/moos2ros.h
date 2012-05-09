#ifndef SIMPLEAPPH
#define SIMPLEAPPH

#include <MOOSLIB/MOOSApp.h>

#include "ros/ros.h"
#include "MOOS_msgs/MOOSString.h"
#include "MOOS_msgs/MOOSDouble.h"

class MOOS2ROSApp : public CMOOSApp {
public:
    //standard construction and destruction
    MOOS2ROSApp();
    virtual ~MOOS2ROSApp();
    
protected:
    //where we handle new mail
    bool OnNewMail(MOOSMSG_LIST &mail_list);
    
    //where we do the work
    bool Iterate();
    
    // Look for new unbridged variables
    void lookForNewVariables();
    
private:
    void handleMsg(CMOOSMsg &msg);
    
    ros::NodeHandle node_handle;
    std::map<std::string, ros::Publisher> publishers;
    
};

#endif
#include "MOOS2ROS/moos2ros.h"

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
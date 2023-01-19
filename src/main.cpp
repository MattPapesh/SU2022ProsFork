#include "main.h"

#include "Subsystems/RobotBuilder.h"
#include "Programs/Driver.h"
#include "Programs/Autonomous.h"
#include "TuneFlywheel.h"

//#define IS_FIFTEEN // uncomment for 15, comment for 18

#ifdef IS_FIFTEEN
    #define IS_TWO_TILE
    Robot robot = getRobot15();
    Driver driver(robot, TANK_DRIVE);
#else
    #define IS_THREE_TILE
    Robot robot = getRobot18();
    Driver driver(robot, ARCADE_DRIVE);
#endif


#define RUN_TEST
//#define RUN_AUTON // uncomment to run auton, comment to run teleop / actual comp
//#define TUNE_FLYWHEEL // uncomment to run flywheel tuning program intsead, comment to disable this

using namespace pros;

bool centerButtonReady = false;

void ready() {
    centerButtonReady = true;
}

void initialize() {

    pros::lcd::initialize();
    pros::lcd::register_btn1_cb (ready);

	
	if (robot.localizer) robot.localizer->init();
    robot.localizer->setHeading(getRadians(0));
	pros::lcd::print(0, "initialized.");

    #ifdef RUN_AUTON
    #ifndef TUNE_FLYWHEEL
    while (!centerButtonReady) {
        pros::lcd::print(1, "Heading (deg): %f", robot.localizer->getHeading() * 180 / 3.1415);
        pros::delay(10);
    }
    #endif
    #endif

}

  
void disabled() {}


void competition_initialize() {}


void autonomous() {    

    #ifdef RUN_TEST
    testAuton(robot);
    return;
    #endif

    #ifdef IS_THREE_TILE
    threeTileAuton(robot);
    #endif
    #ifndef IS_THREE_TILE
    twoTileAuton(robot);
    #endif
}




void opcontrol() {

    #ifdef TUNE_FLYWHEEL
    tuneFlywheel(robot, driver.controller);
    return;
    #endif

	
    if (true && robot.flywheel) {
        pros::Task taskFlywheel([&] {
            robot.flywheel->maintainVelocityTask();
        });
    }

    if (false && robot.localizer) {
        pros::Task taskLocalizer([&] {
            robot.localizer->updatePositionTask();
        });
    }

	#ifdef RUN_AUTON
	autonomous();
	return;
	#endif

	driver.runDriver();
	
}

#include "main.h"

#include "Subsystems/RobotBuilder.h"
#include "Programs/Driver.h"
#include "Programs/CompetitionDriver.h"
#include "Programs/TuningDriver.h"
#include "Programs/Autonomous.h"
#include "TuneFlywheel.h"
#include "Programs/TestFunction/TurnTest.h"
#include "Programs/TestFunction/ForwardTest.h"

#define IS_FIFTEEN // uncomment for 15, comment for 18
bool isSkills = true;
//#define TEST_TUNE_PID // uncomment to adjust pid using TuningDriver class. Should comment out RUN_AUTON

#ifdef IS_FIFTEEN
    //#define IS_THREE_TILE
    Robot robot = getRobot15(isSkills);
#else
    #define IS_TWO_TILE
    Robot robot = getRobot18(isSkills);
#endif

#ifdef TEST_TUNE_PID
    TuningDriver driver(robot, std::make_unique<ForwardTest>());
#else
    CompetitionDriver driver(robot, TANK_DRIVE, 2400); 
#endif

//#define RUN_TEST
#define RUN_AUTON // uncomment to run auton, comment to run teleop / actual comp
//#define TUNE_FLYWHEEL // uncomment to run flywheel tuning program intsead, comment to disable this

using namespace pros;

bool centerButtonReady = false;

void ready() {
    centerButtonReady = true;
}

void initialize() {

    pros::lcd::initialize();
    pros::lcd::register_btn1_cb (ready);

    robot.shooterFlap->set_value(true); // start flap up

	
	if (robot.localizer) robot.localizer->init();
    // robot.localizer->setHeading(getRadians(0));

    #ifdef RUN_AUTON
    #ifndef TUNE_FLYWHEEL
    while (!centerButtonReady) {
        pros::lcd::print(3, "Heading (deg): %f", robot.localizer->getHeading() * 180 / 3.1415);
        pros::delay(10);
    }
    #endif
    #endif

}

  
void disabled() {}


void competition_initialize() {}


void autonomous() {  

    robot.shooterFlap->set_value(false); // flap down  

    if (true && robot.flywheel) {
        pros::Task taskFlywheel([&] {
            robot.flywheel->maintainVelocityTask();
        });
    }

    if (true && robot.localizer) {
        pros::Task taskOdometry([&] {
            robot.localizer->updatePositionTask();
        });
    }

    try {

        #ifdef RUN_TEST
        testAuton(robot);
        return;
        #endif

        #ifdef IS_THREE_TILE
        if (isSkills) threeTileSkills(robot);
        else threeTileAuton(robot);
        #endif

        #ifndef IS_THREE_TILE
        if (isSkills) twoTileSkills(robot);
        else twoTileAuton(robot);
        #endif

    } catch (std::runtime_error &e) {
        pros::lcd::clear();
        pros::lcd::print(0, "IMU disconnect, force shutdown.");
        robot.drive->stop();
        robot.intake->brake();
    }

    
}




void opcontrol() {

    #ifdef TUNE_FLYWHEEL
    tuneFlywheel(robot, driver.controller);
    return;
    #endif



	#ifdef RUN_AUTON
	autonomous();
	return;
	#endif


	driver.runDriver();
	
}

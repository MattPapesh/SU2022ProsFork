#include "Subsystems/RobotBuilder.h"
#include "Programs/Driver.h"
#include "AutonomousFunctions/DriveFunctions.h"
#include "Algorithms/SingleBoundedPID.h"
#include "Algorithms/SimplePID.h"
#include "Algorithms/DoubleBoundedPID.h"
#include "Algorithms/NoPID.h"
#include "Algorithms/Alternator.h"
#include "Algorithms/Shooter.h"
#include "misc/MathUtility.h"
#include "misc/ProsUtility.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

#define GFU_DIST(maxSpeed) SingleBoundedPID({0.1, 0, 0, 0.12, maxSpeed})
#define GFU_DIST_PRECISE(maxSpeed) DoubleBoundedPID({0.1, 0, 0, 0.12, maxSpeed}, 0.1, 3)
#define GFU_TURN SimplePID({1, 0, 0.1, 0.0, 1})
#define GTU_TURN DoubleBoundedPID({1.25, 0, 0.095, 0.15, 1}, getRadians(1.5), 3)
#define GTU_TURN_PRECISE DoubleBoundedPID({1.25, 0, 0.095, 0.15, 1}, getRadians(0.75), 3)
#define GCU_CURVE SimplePID({2.5/*2.25*//*1.7*/, 0, 0})

// don't stop motors at end
#define NO_SLOWDOWN(maxSpeed) NoPID(maxSpeed)

void startIntake(Robot& robot) {
    pros::delay(300);
    setEffort(*robot.intake, 1);
}

void delayResetIndexer(Robot& robot) {
    pros::delay(300);
    robot.indexer->set_value(false);
    setEffort(*robot.intake, 1);
}

// shoot a 3-burst round. First two rounds are short burst (110ms with 220ms break), third is longer (300ms)
void shoot(Robot& robot) {

    setEffort(*robot.intake, 1);
    robot.indexer->set_value(true);
    pros::delay(500);

    // wait for spinup
    if (!robot.flywheel->atTargetVelocity()) {

        constexpr uint32_t TIMEOUT_MS = 3000; // maximum time to wait for spinup to proper velocity

        setEffort(*robot.intake, 0);
        uint32_t start = pros::millis();
        while (!robot.flywheel->atTargetVelocity() && pros::millis() - start < TIMEOUT_MS) {
            pros::delay(10);
        }
    }

    uint32_t start = pros::millis();
    Shooter shooter;
    while (pros::millis() - start < 6000) {
        setEffort(*robot.intake, shooter.tickIntakeShootingSpeed(robot));
    }

    // reset indexer after 500ms, nonblocking
    //pros::Task([&] {delayResetIndexer(robot); });
}

void threeTileAuton(Robot& robot) {

    // GENERATED C++ CODE FROM PathGen 3.4.3
// Exported: Sun Jan 15 22:06:32 2023

// Robot assumes a starting position of (18.5,91.2) at heading of 0.0 degrees.
robot.flywheel->setVelocity(3212); // Preemptively set speed for next shot
setEffort(*robot.intake, 1); // Start running intake immediately
robot.drive->setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

goTurnU(robot, GTU_TURN_PRECISE, getRadians(44.88));
goForwardU(robot, GFU_DIST_PRECISE(0.6), GFU_TURN, 17.46, getRadians(44.88));
pros::delay(260);
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, -4.63, getRadians(404.87));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(315.27));
goForwardU(robot, GFU_DIST_PRECISE(1), GFU_TURN, -19.67, getRadians(315.27));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(360.01));
goForwardU(robot, GFU_DIST_PRECISE(0.48), GFU_TURN, -3.48, getRadians(360.01));
goForwardU(robot, GFU_DIST_PRECISE(0.55), GFU_TURN, 3.62, getRadians(359.99));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(5.18));

shoot(robot);
robot.flywheel->setVelocity(3148); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(306.76));
setEffort(*robot.intake, 1);
goForwardU(robot, GFU_DIST_PRECISE(0.37), GFU_TURN, 33.02, getRadians(306.76));
pros::delay(320);
goTurnU(robot, GTU_TURN_PRECISE, getRadians(23.07));

shoot(robot);
robot.flywheel->setVelocity(3212); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(36.24));
setEffort(*robot.intake, 1);
goForwardU(robot, GFU_DIST_PRECISE(0.45), GFU_TURN, 7.96, getRadians(36.24));
goForwardU(robot, GFU_DIST_PRECISE(0.55), GFU_TURN, -5.8, getRadians(396.23));
pros::delay(260);
goTurnU(robot, GTU_TURN_PRECISE, getRadians(220.72));
goForwardU(robot, GFU_DIST_PRECISE(0.49), GFU_TURN, 18.2, getRadians(220.72));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(23.94));

shoot(robot);
robot.flywheel->setVelocity(3245); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(291.99));
setEffort(*robot.intake, 1);
goForwardU(robot, GFU_DIST_PRECISE(0.82), GFU_TURN, 17.64, getRadians(291.99));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(348.75));
goForwardU(robot, GFU_DIST_PRECISE(1), GFU_TURN, 17.03, getRadians(348.75));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(40.56));

shoot(robot);

// ================================================





}

void twoTileAuton(Robot& robot) {// GENERATED C++ CODE FROM PathGen 3.4.3
// GENERATED C++ CODE FROM PathGen 3.4.3

// Robot assumes a starting position of (88.0,15.9) at heading of 42.48 degrees.
// GENERATED C++ CODE FROM PathGen 3.4.3

// Robot assumes a starting position of (88.0,15.9) at heading of 42.48 degrees.
robot.flywheel->setVelocity(3148); // Preemptively set speed for next shot
setEffort(*robot.intake, 1); // Start running intake immediately
robot.drive->setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

goForwardU(robot, GFU_DIST_PRECISE(0.51), GFU_TURN, 20.68, getRadians(42.48));
pros::delay(1000);
goTurnU(robot, GTU_TURN_PRECISE, getRadians(485.77));
goForwardU(robot, GFU_DIST_PRECISE(0.51), GFU_TURN, -18.01, getRadians(485.77));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(151.49));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, 19.8, getRadians(151.49));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(72.16));

shoot(robot);
robot.flywheel->setVelocity(3000); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(133.26));
goForwardU(robot, GFU_DIST_PRECISE(0.51), GFU_TURN, 44.84, getRadians(133.26));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(48.36));

shoot(robot);
robot.flywheel->setVelocity(3000); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(356.35));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, 10.12, getRadians(356.35));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(483.32));
goForwardU(robot, GFU_DIST_PRECISE(0.49), GFU_TURN, -18.77, getRadians(483.32));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(37.88));
goForwardU(robot, GFU_DIST_PRECISE(0.51), GFU_TURN, 4.9, getRadians(37.88));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(64.42));

shoot(robot);
robot.flywheel->setVelocity(3000); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(240.85));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, 25.58, getRadians(240.85));
goForwardU(robot, GFU_DIST_PRECISE(1), GFU_TURN, -24.92, getRadians(240.84));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(64.4));

shoot(robot);
robot.flywheel->setVelocity(3300); // Preemptively set speed for next shot

goTurnU(robot, GTU_TURN_PRECISE, getRadians(207.8));
goForwardU(robot, GFU_DIST_PRECISE(1), GFU_TURN, 28.88, getRadians(207.8));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(241.69));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, -10.6, getRadians(241.69));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(184.18));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, 8.83, getRadians(184.18));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(224.28));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, -12.0, getRadians(224.28));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(186.0));
goForwardU(robot, GFU_DIST_PRECISE(0.52), GFU_TURN, 8.21, getRadians(186.0));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(57.22));
goForwardU(robot, GFU_DIST_PRECISE(0.51), GFU_TURN, 15.08, getRadians(57.22));
goTurnU(robot, GTU_TURN_PRECISE, getRadians(49.19));

shoot(robot);

// ================================================
}

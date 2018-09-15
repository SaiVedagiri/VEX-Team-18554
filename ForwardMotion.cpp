#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void forwardMotion(int MotorPercentage) {
    // Set the power of the motor
    LeftMotor.setVelocity(MotorPercentage, vex::velocityUnits::pct);
    RightMotor.setVelocity(MotorPercentage, vex::velocityUnits::pct);
    // Set the direction of the motor spin
    LeftMotor.spin(vex::directionType::fwd);
    RightMotor.spin(vex::directionType::fwd);
}



void pre_auton( void ) {
    
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...
    //Wait 2 seconds or 2000 milliseconds before starting the program.
    vex::task::sleep(2000);
    //Print to the screen that the program has started.
    Brain.Screen.print("User Program has Started.");
    while (1){
        // This is the main execution loop for the user control program.
        // Each time through the loop your program should update motor + servo 
        // values based on feedback from the joysticks.
        // Set the motor speed based on the position of the controller
        int motorSpeed = Controller.Axis2.position(percentUnits::pct);
        forwardMotion(motorSpeed);
        // ........................................................................
        // Insert user code here. This is where you use the joystick values to 
        // update your motors, etc.
        // ........................................................................
        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
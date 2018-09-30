#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    DriverControl;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int FineMotionPower = 30;
int minTurn = 20;
int FrontWheelRotation = 5;
int handRotateVelocity = 50;
int handVelocity = 50;
double clawRotations = 0.5;
void move2D(int MotorPower, int TurnPower);
void setFrontWheel(int frontDirection);
void armMotion(int armPower);
void handMotion(int handPower);
void handRotateMotion(int handRotatePower);
int clawState = 0;

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
    FrontMotor.setVelocity(50,vex::velocityUnits::pct);
    FrontMotor.rotateFor(10, vex::rotationUnits::rev, false);
   // ClawMotor.rotateFor(clawRotations, vex::rotationUnits::rev, false);

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
    //Brain.Screen.print("Autonomous has started.");
  // ..........................................................................
    Brain.Screen.print(Brain.Battery.capacity());
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
    //Brain.Screen.print(Brain.Battery.capacity());
  // User control code here, inside the loop

    // All activities that occur before the competition starts

    // Example: clearing encoders, setting servo positions, ...

    //Wait 2 seconds or 2000 milliseconds before starting the program.

    vex::task::sleep(2000);

    //Print to the screen that the program has started.

    //Brain.Screen.print("User Program has Started.");

    while (1){

        // This is the main execution loop for the user control program.

        // Each time through the loop your program should update motor + servo 

        // values based on feedback from the joysticks.

        // Set the motor speed based on the position of the controller
        int MotorSpeed = Controller1.Axis3.position(percentUnits::pct);
        int TurnSpeed = Controller1.Axis4.position(percentUnits::pct);
        if (Controller1.ButtonUp.pressing()){
           MotorSpeed += FineMotionPower;
        }
        
        if (Controller1.ButtonLeft.pressing()){
           TurnSpeed -= FineMotionPower;
        }
        
        if (Controller1.ButtonRight.pressing()){
           TurnSpeed += FineMotionPower;
        }
        
        if (Controller1.ButtonDown.pressing()){
           MotorSpeed -= FineMotionPower;
        }        
        
        move2D(MotorSpeed, TurnSpeed);
        
        if (Controller1.ButtonR1.pressing()){
           PuncherMotor.rotateFor(5.2, vex::rotationUnits::rev, false);
        }
        if (Controller1.ButtonL1.pressing() ) {
            setFrontWheel(-1);
            //add function
        }
       if (!(Controller1.ButtonL1.pressing() )) {
            setFrontWheel(0);
            //add function
        }
        if (Controller1.ButtonL2.pressing()) {
            setFrontWheel(1);
        }
       
        int armSpeed = Controller1.Axis2.position(percentUnits::pct);
        armMotion(armSpeed);
        
        if(Controller1.ButtonX.pressing()) {
            handMotion(handVelocity);
        }
        if(Controller1.ButtonB.pressing()) {
            handMotion(-handVelocity);
        }
        if(Controller1.ButtonR2.pressing()) {
            handRotateMotion(handRotateVelocity);
        }
      
        if(Controller1.ButtonY.pressing() && clawState == 0) {
            Brain.Screen.print("clawState = " + clawState);
            clawState = 1;
            ClawMotor.rotateFor(-clawRotations,vex::rotationUnits::rev,5,velocityUnits::pct);
        }
        if(Controller1.ButtonA.pressing() && clawState == 1) {
            Brain.Screen.print("clawState = " + clawState);            clawState = 0;
            ClawMotor.rotateFor(clawRotations,vex::rotationUnits::rev,5,velocityUnits::pct);

        }
        
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
    autonomous();
    usercontrol();
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}

void move2D(int MotorPower, int TurnPower) {

    // Set the power of the motor
    if (abs(TurnPower) > minTurn) {
        TurnPower -= abs(TurnPower)/TurnPower *minTurn;
    }
    else TurnPower = 0;
    
    TurnPower /=2;
    int leftPower = MotorPower - TurnPower;
    int rightPower = MotorPower + TurnPower;
    if (abs(leftPower)> 100){
        leftPower = 100*(leftPower/abs(leftPower));
    }
    if (abs(rightPower) > 100) {
        rightPower = 100*(rightPower/abs(rightPower));
    }
    
    LeftMotor.setVelocity(leftPower, vex::velocityUnits::pct);

    RightMotor.setVelocity(rightPower, vex::velocityUnits::pct);
    
    
    // Set the direction of the motor spin

    LeftMotor.spin(vex::directionType::fwd);

    RightMotor.spin(vex::directionType::fwd);
    
    

}

void setFrontWheel(int frontDirection) {
    int frontVelocity = -50*frontDirection;
    FrontMotor.setVelocity(frontVelocity, vex::velocityUnits::pct);
    FrontMotor.spin(vex::directionType::fwd);
    //FrontMotor.rotateFor(turns, vex::rotationUnits::rev, false);
}




void armMotion(int armPower){
    ArmMotor.setVelocity(armPower, vex::velocityUnits::pct);
    ArmMotor.spin(vex::directionType::fwd);

}

void handMotion(int handPower){
    HandMotor.setVelocity(handPower, vex::velocityUnits::pct);
    HandMotor.spin(vex::directionType::fwd);

}

void handRotateMotion(int handRotatePower){
    HandRotateMotor.setVelocity(handRotatePower, vex::velocityUnits::pct);
    HandRotateMotor.spin(vex::directionType::fwd);

}

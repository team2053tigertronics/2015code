// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/RotatetoAngle.h"
#include "Commands/ZeroYaw.h"
#include "Commands/driveAuto.h"
#include "Commands/driveCommand.h"
#include "Commands/WinchControl.h"
#include "Commands/LEDBright.h"
#include "Commands/LEDDim.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	joystick1 = new Joystick(0);
	joystick2 = new Joystick(1);
	bright_button = new JoystickButton(joystick1, 8);
	dim_button = new JoystickButton(joystick1, 7);
	RotateReverse = new JoystickButton(joystick1, 1);
        // SmartDashboard Buttons

	SmartDashboard::PutData("ZeroYaw", new ZeroYaw());
	dim_button->WhenPressed(new LEDDim());
	bright_button->WhenPressed(new LEDBright());
	RotateReverse->WhenPressed(new RotatetoAngle(180, .5));

        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

Joystick* OI::getJoystick1() {
	return joystick1;
}

Joystick* OI::getJoystick2() {
	return joystick2;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

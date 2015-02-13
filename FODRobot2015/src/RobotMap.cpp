// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
CANJaguar* RobotMap::driveBaseSubFrontRightJag = NULL;
CANJaguar* RobotMap::driveBaseSubFrontLeftJag = NULL;
CANJaguar* RobotMap::driveBaseSubBackRightJag = NULL;
CANJaguar* RobotMap::driveBaseSubBackLeftJag = NULL;
RobotDrive* RobotMap::driveBaseSubRobotDrive = NULL;
DoubleSolenoid* RobotMap::RightGripper = NULL;
DoubleSolenoid* RobotMap::LeftGripper = NULL;
CANJaguar* RobotMap::winchJag = NULL;
DigitalInput* RobotMap::bottomSwitch = NULL;
Compressor* RobotMap::compressor = NULL;
Relay* RobotMap::compressor_spike = NULL;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	//LiveWindow* lw = LiveWindow::GetInstance();

	RightGripper = new DoubleSolenoid(0,1);

	LeftGripper = new DoubleSolenoid(2,3);

	winchJag = new CANJaguar(3);

	driveBaseSubFrontRightJag = new CANJaguar(6);
	
	
	driveBaseSubFrontLeftJag = new CANJaguar(8);
	
	
	driveBaseSubBackRightJag = new CANJaguar(2);
	
	
	driveBaseSubBackLeftJag = new CANJaguar(9);
	
	bottomSwitch = new DigitalInput(0);
	
	compressor = new Compressor(0);

	compressor_spike = new Relay(0);

	driveBaseSubRobotDrive = new RobotDrive(driveBaseSubFrontLeftJag, driveBaseSubBackLeftJag,
              driveBaseSubFrontRightJag, driveBaseSubBackRightJag);
	
	driveBaseSubRobotDrive->SetSafetyEnabled(false);
        driveBaseSubRobotDrive->SetExpiration(0.1);
        driveBaseSubRobotDrive->SetSensitivity(0.5);
        driveBaseSubRobotDrive->SetMaxOutput(1.0);

        driveBaseSubRobotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
        driveBaseSubRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
        driveBaseSubRobotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, false);
        driveBaseSubRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, false);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

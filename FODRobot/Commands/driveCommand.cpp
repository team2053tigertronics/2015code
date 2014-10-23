// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "driveCommand.h"
#include "../IMUlib/IMU.h"
#include <math.h>

float XAxis;
float YAxis;
float RotateAxis;
float imu_yaw;
//float pi = 3.141526;
//float current_gyro_angle_radians;
//float temp;
bool is_calibrating;
SerialPort *serial_port;
IMU *imu;

driveCommand::driveCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveBaseSub);
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void driveCommand::Initialize() {
	XAxis = 0;
	YAxis = 0;
	RotateAxis = 0;
	serial_port = new SerialPort(57600);
	imu = new IMU(serial_port, 50);
}

// Called repeatedly when this Command is scheduled to run
void driveCommand::Execute() {
	imu_yaw = imu->GetYaw();
	is_calibrating = imu->IsCalibrating();
	//current_gyro_angle_radians = imu_yaw * pi/180;
	printf("%f0.002\n", imu_yaw);
	printf("%d\n", is_calibrating);
	XAxis = Robot::oi->getJoystick1()->GetRawAxis(1);
	YAxis = Robot::oi->getJoystick1()->GetRawAxis(2);
	RotateAxis = Robot::oi->getJoystick1()->GetRawAxis(4);
	if(XAxis < 0.20 && XAxis > -0.20)
	{
		XAxis = 0;
	}
	if(YAxis < 0.20 && YAxis > -0.20)
	{
		YAxis = 0;
	}
	if(RotateAxis < 0.20 && RotateAxis > -0.20)
	{
		RotateAxis = 0;
	}
	//current_gyro_angle_radians = imu_yaw * pi/180;
	//temp = YAxis * cos(current_gyro_angle_radians) + XAxis * sin(current_gyro_angle_radians);
	//XAxis = -YAxis * sin(current_gyro_angle_radians) + XAxis * cos(current_gyro_angle_radians);
	Robot::driveBaseSub->MechDrive(XAxis,YAxis,RotateAxis,imu_yaw);
}

// Make this return true when this Command no longer needs to run execute()
bool driveCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void driveCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void driveCommand::Interrupted() {

}

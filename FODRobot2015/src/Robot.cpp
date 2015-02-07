// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Commands/DoNothingAuto.h"
#include "Commands/DriveForwardAuto.h"
#include "Commands/FullAutoShort.h"
#include "Commands/FullAutoWide.h"
#include "Commands/GrabNGoAuto.h"
#include "SmartDashboard/SmartDashboard.h"
//Vision Includes
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Vision2015/YellowToteFinder.h"
using namespace cv;
using namespace std;
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveBaseSub* Robot::driveBaseSub = 0;
Winch* Robot::winch = 0;
GripperArm* Robot::gripperArm = 0;
OI* Robot::oi = 0;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveBaseSub = new DriveBaseSub();
	winch = new Winch();
	gripperArm = new GripperArm();
	autoChooser = new SendableChooser();
	autoChooser->AddDefault("Full Auto Wide", new FullAutoWide());
	autoChooser->AddObject("Full Auto Short", new FullAutoShort());
	autoChooser->AddObject("Drive Forward Only", new DriveForwardAuto());
	autoChooser->AddObject("Grab And Go Auto",  new GrabNGoAuto());
	autoChooser->AddObject("Do Nothing", new DoNothingAuto());
	SmartDashboard::PutData("Auto Mode Chooser", autoChooser);
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	driveBaseSub->pRobot_IMU->ZeroYaw();

	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = (Command *) autoChooser->GetSelected();
	if (autonomousCommand != NULL) {
		autonomousCommand->Start();
	}

}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
	std::string videoStreamAddress = "http://169.254.149.22/mjpg/video.mjpg";
	Mat frame;
	VideoCapture vidcap;
	vidcap.open(videoStreamAddress);
	vidcap >> frame;
	YellowToteFinder ytf = YellowToteFinder();
	bool found = ytf.findTote(&frame);
	float inches_away = ytf.getDistanceToTote();
	if(found == true)
	{
		cout << "Found a tote, it is " << inches_away << "inches away!" <<endl;
	}
	else
	{
		cout << "We did not find a tote!" << endl;
	}
	//vector<int> param = vector<int>(2);
	//param[0] = CV_IMWRITE_JPEG_QUALITY;
	//param[1] = 80;
	//vector<uchar> img_data;
	//imwrite("/tmp/frame.jpg", imencode(".jpg", frame, img_data, param));
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);


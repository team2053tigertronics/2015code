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
#include <sys/time.h>
using namespace cv;
using namespace std;
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveBaseSub* Robot::driveBaseSub = 0;
Winch* Robot::winch = 0;
GripperArm* Robot::gripperArm = 0;
OI* Robot::oi = 0;
std::string videoStreamAddress = "http://169.254.149.21/mjpg/video.mjpg";
Task* visionTask;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

static void Vision(Robot* robot) {
	int rc;
	Mat frame;
	Mat rgba;
	VideoCapture vidcap;
	YellowToteFinder ytf = YellowToteFinder();
	Image* myImaqImage = imaqCreateImage(IMAQ_IMAGE_RGB,  0);

	vidcap.open(videoStreamAddress);
	if (!vidcap.isOpened()) {
		cout << "OpenCV could not open webcam!!" << endl;
		return;
	} else cout << "Found camera!!" << endl;

	while(true)
	{
		for(int i = 0; i < 4; i++)
		{
			vidcap >> frame;
		}
		bool found = ytf.findTote(&frame);
		float inches_away = ytf.getDistanceToTote();
		if(found == true)
			cout << "Found a tote, it is " << inches_away << " inches away!" <<  endl;

		/*if(!frame.isContinuous())
		{
			cout << "Not Continuous!" << endl;
			frame = frame.clone();
		}*/

		cvtColor(frame, rgba, CV_BGR2BGRA, 4);


		int rc = imaqArrayToImage(myImaqImage, rgba.data, frame.cols, frame.rows);

		if(rc != 1)
			return;

		CameraServer::GetInstance()->SetImage(myImaqImage);
	}

}

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
	// instantiate the command used for the autonomous period//hi
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	visionTask = new Task("Vision",(FUNCPTR)Vision,Task::kDefaultPriority + 1);
	visionTask->Start((int)this);
	RobotMap::LED_spike->Set(RobotMap::LED_spike->Value::kForward);
	RobotMap::Red_LED->SetPWMRate(10);
	RobotMap::Green_LED->SetPWMRate(10);
	RobotMap::Blue_LED->SetPWMRate(10);
	RobotMap::Red_LED->EnablePWM(0);
	RobotMap::Blue_LED->EnablePWM(.5);
	RobotMap::Green_LED->EnablePWM(1);
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	RobotMap::compressor->Stop();
	RobotMap::LED_spike->Set(RobotMap::LED_spike->Value::kForward);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = (Command *) autoChooser->GetSelected();
	if (autonomousCommand != NULL) {
		autonomousCommand->Start();
	}
	RobotMap::compressor->Start();
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
	RobotMap::compressor->Start();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);


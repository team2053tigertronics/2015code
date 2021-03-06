#include <Commands/PneumaticsAuto.h>
#include "GrabNGoAuto.h"
#include "DriveWhileWinching.h"
#include "PneumaticsAuto.h"
#include "WinchAuto.h"
#include "Commands/SetOffSet.h"
GrabNGoAuto::GrabNGoAuto()
{
	AddSequential(new SetOffSet(180));
	//FALSE IS CLOSE, TRUE IS OPEN
	printf("grabandgoauto 0\n");
	//side, fow, rot, yaw, time
	AddSequential(new PneumaticsAuto(true, true, false));
	//printf("grabandgoauto 1\n");
	AddSequential(new DriveWhileWinching(0.0, 0.5, 0.0, 0.0, 1.95, 1, 1));
	//printf("grabandgoauto 2\n");
	//printf("grabandgoauto 3\n");
}
//robot.run

#include "CGAME.h"
#include "Menu.h"
#include "SetUp.h"
#include <thread>

CGAME cg;
char MOVING;
int maxBird = 6, 
	maxDino = 6,
	maxCar = 6, 
	maxTruck = 6;
int minX = 30,
	minY = 6,
	maxX = 91,
	maxY = 26;

void subThread() 
{
	while (true) 
	{
		
		if (!cg.getPeople().isDead()) 
		{
			cg.updatePosPeople(MOVING);
		}
		MOVING = ' ';

		cg.updatePosAnimal();
		cg.updatePosVehicle();
		cg.drawGame();
		Sleep(10);
		cg.clrScr();
		if (cg.getPeople().isImpactVehi(cg.getVehicle()) || cg.getPeople().isImpactAni(cg.getAnimal())) {
			//cg.setDead();
			cout << "Haha";
		}
		if (cg.getPeople().isFinish()) {

		}
		
	}
}

int main() 
{
	ShowConsoleCursor(false);
	FixConsoleWindow();

	cg = *new CGAME();

	int temp;

	cg.startGame();
	thread t1(subThread);
	while (1) {
		temp = toupper(_getch());
		if (!cg.getPeople().isDead()) {
			if (temp == 27) {
				cg.exitGame(t1.native_handle());
				return 0;
			}
			else if (temp == 'P') {
				cg.pauseGame(t1.native_handle());
			}
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;
			}
		}
		else {
			if (temp == 'Y') cg.startGame();
			else {
				cg.exitGame(t1.native_handle());
				return 0;
			}
		}
	}

	return 0;
}
#include "BlankApp.h"
#include "RocketApp.h"
#include "BallsInABoxApp.h"
#include "SpringsApp.h"

int main()
{
	auto app = new BallsInABoxApp();
	app->run("2D Physics", 1280, 720, false);
	delete app;
	return 0;
}
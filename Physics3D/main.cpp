#include "PhysicsApp3D.h"

int main()
{	
	auto app = new PhysicsApp3D();
	app->run("3D Physics", 1280, 720, false);
	delete app;
	return 0;
}
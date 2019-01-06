#include "Window.h"
#include "Logger.h"

int main(int argc, char* argv)
{
	Window mainWindow(500, 500, "SandbocEngine", false);
	Logger.LogCrash("test");

	while (true);
}

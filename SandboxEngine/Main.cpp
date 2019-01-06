#include "Window.h"
#include "Logger.h"

int main(int argc, char* argv)
{
	Window mainWindow(640, 480, "SandboxEngine", false);
	LogCrash("test");

	while (true);
}

#include "Window.h"
#include "Logger.h"
#include "Resource.h"
#include "World.h"
#include "Chunk.h"
#include "BlockAir.h"

#include <GLFW/glfw3.h>

class TestBlock : BlockBase
{
};

int main(int argc, char* argv)
{
	World testWorld;

	auto& chunk = testWorld.GetChunk();

	auto test = ResourceCache.Get<Texture>("test");

	Window mainWindow(640, 480, "SandboxEngine", false);
	auto startTime = glfwGetTime();
	for (auto i = 0; i < 1000000000; ++i)
		auto block = chunk.GetBlock(0, 0, 0);
	auto endTime = glfwGetTime();
	LogWarning("time " + std::to_string(endTime - startTime));

	mainWindow.Run();
}

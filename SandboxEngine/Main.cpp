#include "Window.h"
#include "Logger.h"
#include "Resource.h"
#include "World.h"
#include "Chunk.h"
#include "BlockAir.h"

class TestBlock : BlockBase
{
};

int main(int argc, char* argv)
{
	World testWorld;
	auto block = testWorld.GetChunk().GetBlock(0, 0, 0)->As<BlockAir>();
	auto test = ResourceCache.Get<Texture>("test");

	Window mainWindow(640, 480, "SandboxEngine", false);
	mainWindow.Run();
}

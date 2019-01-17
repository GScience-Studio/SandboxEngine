#include "../SandboxEngine.h"
#include <vector>

void InitBlock(const SBE_ModBlockInitializerInfo* blockInitializerInfo)
{
	std::vector<SBE_BlockRegisterFunInfo> infos;
	const auto blockRegisterFun = *blockInitializerInfo->RegisterFunPtr;
	infos.push_back({ "TestEvent", nullptr });
	blockRegisterFun("ExampleBlock", infos.size(), &infos[0]);
}

SBE_ModInitializerFun
{
	switch (type)
	{
	case ModInitializer:
		break;
	case BlockInitializer:
		InitBlock(reinterpret_cast<const SBE_ModBlockInitializerInfo*>(data));
		break;
	default:
		break;
	}
}
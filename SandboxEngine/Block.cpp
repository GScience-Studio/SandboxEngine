#include "../SandboxEngine.h"
#include "Block.h"
#include "BlockAir.h"
#include <Windows.h>
#include "ModBlock.h"

#undef BlockRegistry

//单例，分享给SBE_BlockRegisterFun
BlockRegistry* BlockRegistryInstance;

void SBE_BlockRegisterFun(const char* blockName, const int infoNum, SBE_BlockRegisterFunInfo* infos)
{
	std::vector<EventBinding> infoList;
	infoList.reserve(infoNum);
	for (auto i = 0; i < infoNum; ++i)
	{
		EventBinding eventBinding;
		eventBinding.eventName = infos->name;
		eventBinding.binding = infos++->func;
		infoList.emplace_back(eventBinding);
	}
	const std::string blockNameStr = blockName;
	const auto modBlock = std::static_pointer_cast<ModBlock>(ModBlock::Constructor(blockNameStr, infoList));
	BlockRegistryInstance->Register(blockName,
	                                [=](Chunk& chunk, const int x, const int y, const int z)
	                                {
		                                 return modBlock->Clone(chunk, x, y, z);
	                                }
	);
}

BlockRegistry::BlockRegistry()
{
	BlockRegistryInstance = this;

	//注册内置Block
	RegisterBlock(BlockAir);
	//加载Mod的Block
	const auto mod = LoadLibraryExA("SandboxEngineMod.dll", nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	const auto ptr = reinterpret_cast<SBE_ModInitializer>(GetProcAddress(mod, SBE_NameToStr(SBE_ModMain)));
	const SBE_ModBlockInitializerInfo modInitializerInfo
	{
		static_cast<SBE_BlockRegisterFunPtr>(&SBE_BlockRegisterFun)
	};
	ptr(BlockInitializer, reinterpret_cast<const void*>(&modInitializerInfo));
	//FreeLibrary(mod);
}

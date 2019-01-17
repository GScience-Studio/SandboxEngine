#include "ModBlock.h"
#include "Logger.h"
#include <map>

Block ModBlock::Constructor(const std::string& blockName, const std::vector<EventBinding>& eventBindings)
{
	auto block = std::static_pointer_cast<ModBlock>(Block(static_cast<BlockBase*>(new ModBlock())));
	auto eventMap = block->GetEventMap();

	for (auto& eventBinding : eventBindings)
	{
		const auto findResult = eventMap.find(eventBinding.eventName);
		if (findResult == eventMap.end())
			LogError("Failed to bind block event " + eventBinding.eventName);

		findResult->second += eventBinding.binding;
	}

	block->mOnBlockCreated.Do({ std::static_pointer_cast<BlockBase>(block->shared_from_this()),eventMap });
	return block;
}

std::map<std::string, EventRawPtr> ModBlock::GetEventMap()
{
	std::map<std::string, EventRawPtr> eventMap;
	eventMap["onBlockPlaced"] = EventRawPtr(&onBlockPlaced);
	eventMap["mOnBlockCreated"] = EventRawPtr(&mOnBlockCreated);
	return eventMap;
}

Block ModBlock::Clone(Chunk& chunk, const int x, const int y, const int z) const
{
	auto clonedBlock = std::static_pointer_cast<ModBlock>(Block(static_cast<BlockBase*>(new ModBlock(*this))));
	clonedBlock->mChunk = &chunk;
	clonedBlock->mX = x;
	clonedBlock->mY = y;
	clonedBlock->mZ = z;

	return clonedBlock;
}
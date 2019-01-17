#include "World.h"
#include "Chunk.h"
#include "Block.h"
#include "Logger.h"

World::World()
{
	auto blockInfoList = BlockRegistry.GetBlockList();
	if (blockInfoList.size() > USHRT_MAX)
	LogError("There are " + std::to_string(blockInfoList.size()) + " blocks. But support only " + std::to_string(
		USHRT_MAX));

	//³õÊ¼»¯BlockË÷Òý
	for (const auto& blockInfo : blockInfoList)
	{
		mBlockNameToId[blockInfo.first] = static_cast<uint16_t>(mBlockNameToId.size());
		mBlockIdToConstructor[static_cast<uint16_t>(mBlockIdToConstructor.size())] = blockInfo.second;
	}
}

Chunk& World::GetChunk()
{
	auto newChunkPtr = std::unique_ptr<Chunk>(new Chunk(*this));
	mChunkList.emplace_back(std::move(newChunkPtr));
	return *mChunkList.back();
}

uint16_t World::GetBlockIdFromName(const char* blockName)
{
	const auto blockId = mBlockNameToId.find(blockName);
	if (blockId == mBlockNameToId.end())
	LogError("Invalid blockName: " + blockName);
	return blockId->second;
}

BlockBase::BlockConstructor World::GetBlockConstructorFromId(const uint16_t blockId)
{
	const auto blockConstructor = mBlockIdToConstructor.find(blockId);
	if (blockConstructor == mBlockIdToConstructor.end())
	LogError("Invalid blockId: " + std::to_string(blockId));
	return blockConstructor->second;
}

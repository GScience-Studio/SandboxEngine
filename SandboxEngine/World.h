#pragma once
#include <map>
#include <string>
#include <vector>
#include "Block.h"
#include "NonCopyable.h"

/*
 * 世界信息\n
 * 每个世界都有一套自己的方块ID索引
 */
class World : NonCopyable
{
	//方块名称索引
	std::map<std::string, uint16_t> mBlockNameToId;

	//方块类型索引
	std::map<uint16_t, BlockBase::BlockConstructor> mBlockIdToConstructor;
	std::vector<std::unique_ptr<Chunk>> mChunkList;
public:
	//从方块名称获取方块的Id
	uint16_t GetBlockIdFromName(const char* blockName);
	//从Id获取方块构造器
	BlockBase::BlockConstructor GetBlockConstructorFromId(uint16_t blockId);

	Chunk& GetChunk();
	World();
};
#pragma once
#include <map>
#include <string>
#include <vector>
#include "Block.h"
#include "NonCopyable.h"

/*
 * ������Ϣ\n
 * ÿ�����綼��һ���Լ��ķ���ID����
 */
class World : NonCopyable
{
	//������������
	std::map<std::string, uint16_t> mBlockNameToId;

	//������������
	std::map<uint16_t, BlockBase::BlockConstructor> mBlockIdToConstructor;
	std::vector<std::unique_ptr<Chunk>> mChunkList;
public:
	//�ӷ������ƻ�ȡ�����Id
	uint16_t GetBlockIdFromName(const char* blockName);
	//��Id��ȡ���鹹����
	BlockBase::BlockConstructor GetBlockConstructorFromId(uint16_t blockId);

	Chunk& GetChunk();
	World();
};
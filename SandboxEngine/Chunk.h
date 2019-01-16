#pragma once
#include "Block.h"
#include <memory>

class World;

/*
 * ������Ϣ
 */
struct BlockData
{
	unsigned int blockId : 16;
	unsigned int lightR : 4;
	unsigned int lightG : 4;
	unsigned int lightB : 4;

	BlockData() : blockId(0), lightR(0), lightG(0), lightB(0) {}
};

/*
 * ����\n
 * ÿ������Ĵ�СΪ16*16*16
 */
class Chunk : NonCopyable
{
	friend class World;

	//�������Chunk������
	World& mWorld;
	//Chunk������Block����Ϣ
	BlockData mBlockData[16][16][16];

	//ֻ����World�ഴ��Chunk
	Chunk(World& world) : mWorld(world) {}

public:
	Block GetBlock(int x, int y, int z);
};
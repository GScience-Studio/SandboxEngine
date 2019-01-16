#pragma once
#include "Block.h"
#include <memory>

class World;

/*
 * 方块信息
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
 * 区块\n
 * 每个区块的大小为16*16*16
 */
class Chunk : NonCopyable
{
	friend class World;

	//创建这个Chunk的世界
	World& mWorld;
	//Chunk内所有Block的信息
	BlockData mBlockData[16][16][16];

	//只允许World类创建Chunk
	Chunk(World& world) : mWorld(world) {}

public:
	Block GetBlock(int x, int y, int z);
};
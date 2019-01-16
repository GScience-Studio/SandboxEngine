#include "World.h"
#include "Chunk.h"

Block Chunk::GetBlock(const int x, const int y, const int z)
{
	return mWorld.GetBlockConstructorFromId(mBlockData[x][y][z].blockId)(*this, x, y, z);
}
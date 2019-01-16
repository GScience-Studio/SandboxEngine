#include "Block.h"
#include "BlockAir.h"

#undef BlockRegistry

BlockRegistry::BlockRegistry()
{
	Register(BlockAir);
}

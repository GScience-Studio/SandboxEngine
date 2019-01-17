#pragma once
#include "Block.h"
#include "string"
#include "Event.h"
#include <map>

struct EventBinding
{
	std::string eventName;
	void* binding;
};

class ModBlock : public BlockBase
{
	ModBlock(Chunk& chunk, int x, int y, int z);

	static std::map<std::string, EventRawPtr>& GetEventMap();
public:
	//°ó¶¨Mod BlockÊÂ¼þ
	static Block Constructor(Chunk& chunk, int x, int y, int z, const std::vector<EventBinding>& eventBindings);
};

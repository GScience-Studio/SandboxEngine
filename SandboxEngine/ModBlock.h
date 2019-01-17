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

/*
 * Mod Block
 */
class ModBlock : public BlockBase
{
	friend class ModBlockEventInitializer;

	std::map<std::string, EventRawPtr> GetEventMap();

	/*
	 * 方块事件
	 */
	//当方块被初始化时调用（即被获得时）
	Event<EventHandler<BlockEventOnCreated>> mOnBlockCreated;

public:
	//绑定Mod Block事件
	static Block Constructor(const std::string& blockName, const std::vector<EventBinding>& eventBindings);

	Block Clone(Chunk& chunk, int x, int y, int z) const;
};
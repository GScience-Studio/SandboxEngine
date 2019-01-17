#include "ModBlock.h"
#include "Logger.h"
#include <map>

Block ModBlock::Constructor(Chunk& chunk, const int x, const int y, const int z,
                            const std::vector<EventBinding>& eventBindings)
{
	auto map = GetEventMap();

	for (auto& eventBinding : eventBindings)
	{
		const auto findResult = map.find(eventBinding.eventName);
		if (findResult == map.end())
		LogError("Failed to bind block event " + eventBinding.eventName);

		findResult->second += eventBinding.binding;
	}
	return Block(static_cast<BlockBase*>(new ModBlock(chunk, x, y, z)));
}

ModBlock::ModBlock(Chunk& chunk, const int x, const int y, const int z) : BlockBase(chunk, x, y, z)
{
}

Event<EventHandler<int>> testEvent;

std::map<std::string, EventRawPtr>& ModBlock::GetEventMap()
{
	static std::map<std::string, EventRawPtr> eventMap;

	eventMap["TestEvent"] = EventRawPtr(&testEvent);
	return eventMap;
}

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
	 * �����¼�
	 */
	//�����鱻��ʼ��ʱ���ã��������ʱ��
	Event<EventHandler<BlockEventOnCreated>> mOnBlockCreated;

public:
	//��Mod Block�¼�
	static Block Constructor(const std::string& blockName, const std::vector<EventBinding>& eventBindings);

	Block Clone(Chunk& chunk, int x, int y, int z) const;
};
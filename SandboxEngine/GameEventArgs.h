#pragma once
#include <memory>
#include <map>
#include "EventRawPtr.h"

/*
 * �����¼�
 */
class BlockBase;

struct BlockEventArgs
{
	std::shared_ptr<BlockBase> owner;
};

struct BlockEventOnCreated
{
	std::shared_ptr<BlockBase> owner;
	std::map<std::string, EventRawPtr>& eventMap;
};
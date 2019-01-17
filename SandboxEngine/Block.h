#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "NonCopyable.h"
#include "EventArgs.h"
#include "Event.h"

class Chunk;

/*
 * 方块渲染接口
 */
class IBlockRenderer
{
};

class BlockBase;
//Block类型
using Block = std::shared_ptr<BlockBase>;

/*
 * 方块基础类\n
 * 所有方块都应继承于此\n
 * Block写法示例：
 * Class MyFirstBlock : public BlockBase
 * {
 *     //创建Block的构造函数
 *     BlockConstructorHelper(MyFirstBlock, BlockBase);
 *     //
 *     // 以下是你的自定义代码
 *     //
 * }
 */
class BlockBase : public std::enable_shared_from_this<BlockBase>, protected Copyable
{
	friend class Chunk;

protected:
	Chunk* mChunk = nullptr;
	//方块的区块内坐标
	int mX = 0, mY = 0, mZ = 0;

	BlockBase() = default;

	//BlockBase构造
	BlockBase(Chunk& chunk, const int x, const int y, const int z) : mChunk(&chunk), mX(x), mY(y), mZ(z)
	{
	}
public:
	//方块坐标
	const int &x = mX, &y = mY, &z = mY;
	//所在区块
	Chunk& chunk = *mChunk;

	/*
	 * 方块事件
	 */
	//当方块放置时调用
	Event<EventHandler<BlockEventArgs>> onBlockPlaced;

	//Block构造器
	using BlockConstructor = std::function<Block(Chunk& chunk, int x, int y, int z)>;

	//Block类型转换
	template <class BlockType, class = std::enable_if_t<std::is_base_of<BlockBase, BlockType>::value>>
	std::shared_ptr<BlockType> As()
	{
		return std::static_pointer_cast<BlockType>(shared_from_this());
	}

	virtual ~BlockBase() = default;
};

/*
 * 方块注册表，储存方块名称及其对应的构造函数
 */
class BlockRegistry : NonCopyable
{
	//方块名称和构造函数表
	std::vector<std::pair<std::string, BlockBase::BlockConstructor>> mBlockList;
	BlockRegistry();
public:
	//获取方块列表
	const decltype(mBlockList)& GetBlockList() const
	{
		return mBlockList;
	}

	//获取实例
	static BlockRegistry& GetInstance()
	{
		static BlockRegistry blockRegistry;
		return blockRegistry;
	}

	//注册方块
	void Register(const char* blockName, BlockBase::BlockConstructor blockConstructor)
	{
		mBlockList.emplace_back(std::make_pair(blockName, blockConstructor));
	}
};

//自动创建Block的结构
#define BlockConstructorHelper(type, base)\
private:\
	type(Chunk& chunk, const int x, const int y, const int z) : base(chunk, x, y, z) {} \
public:\
	static Block Constructor(Chunk& chunk, const int x, const int y, const int z)\
	{\
		return Block(static_cast<BlockBase*>(new type(chunk, x, y, z)));\
	}private:class _____{}

//获取BlockRegistry实例
#define BlockRegistry BlockRegistry::GetInstance()
#define RegisterBlock(type) Register(#type, &type::Constructor)

#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "NonCopyable.h"
#include "EventArgs.h"
#include "Event.h"

class Chunk;

/*
 * ������Ⱦ�ӿ�
 */
class IBlockRenderer
{
};

class BlockBase;
//Block����
using Block = std::shared_ptr<BlockBase>;

/*
 * ���������\n
 * ���з��鶼Ӧ�̳��ڴ�\n
 * Blockд��ʾ����
 * Class MyFirstBlock : public BlockBase
 * {
 *     //����Block�Ĺ��캯��
 *     BlockConstructorHelper(MyFirstBlock, BlockBase);
 *     //
 *     // ����������Զ������
 *     //
 * }
 */
class BlockBase : public std::enable_shared_from_this<BlockBase>, protected Copyable
{
	friend class Chunk;

protected:
	Chunk* mChunk = nullptr;
	//���������������
	int mX = 0, mY = 0, mZ = 0;

	BlockBase() = default;

	//BlockBase����
	BlockBase(Chunk& chunk, const int x, const int y, const int z) : mChunk(&chunk), mX(x), mY(y), mZ(z)
	{
	}
public:
	//��������
	const int &x = mX, &y = mY, &z = mY;
	//��������
	Chunk& chunk = *mChunk;

	/*
	 * �����¼�
	 */
	//���������ʱ����
	Event<EventHandler<BlockEventArgs>> onBlockPlaced;

	//Block������
	using BlockConstructor = std::function<Block(Chunk& chunk, int x, int y, int z)>;

	//Block����ת��
	template <class BlockType, class = std::enable_if_t<std::is_base_of<BlockBase, BlockType>::value>>
	std::shared_ptr<BlockType> As()
	{
		return std::static_pointer_cast<BlockType>(shared_from_this());
	}

	virtual ~BlockBase() = default;
};

/*
 * ����ע������淽�����Ƽ����Ӧ�Ĺ��캯��
 */
class BlockRegistry : NonCopyable
{
	//�������ƺ͹��캯����
	std::vector<std::pair<std::string, BlockBase::BlockConstructor>> mBlockList;
	BlockRegistry();
public:
	//��ȡ�����б�
	const decltype(mBlockList)& GetBlockList() const
	{
		return mBlockList;
	}

	//��ȡʵ��
	static BlockRegistry& GetInstance()
	{
		static BlockRegistry blockRegistry;
		return blockRegistry;
	}

	//ע�᷽��
	void Register(const char* blockName, BlockBase::BlockConstructor blockConstructor)
	{
		mBlockList.emplace_back(std::make_pair(blockName, blockConstructor));
	}
};

//�Զ�����Block�Ľṹ
#define BlockConstructorHelper(type, base)\
private:\
	type(Chunk& chunk, const int x, const int y, const int z) : base(chunk, x, y, z) {} \
public:\
	static Block Constructor(Chunk& chunk, const int x, const int y, const int z)\
	{\
		return Block(static_cast<BlockBase*>(new type(chunk, x, y, z)));\
	}private:class _____{}

//��ȡBlockRegistryʵ��
#define BlockRegistry BlockRegistry::GetInstance()
#define RegisterBlock(type) Register(#type, &type::Constructor)

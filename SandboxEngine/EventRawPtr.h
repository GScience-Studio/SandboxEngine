#pragma once
#include <functional>

/*
 * ÊÂ¼þÖ¸Õë
 */
class EventRawPtr
{
	std::function<void(void*)> mAdd;
	std::function<void()> mClear;
public:
	EventRawPtr() = default;

	template <class EventType>
	EventRawPtr(EventType* eventPtr = nullptr)
	{
		mAdd = [eventPtr](void* fun)
		{
			typename EventType::EventHandlerType::EventHandler::EventHandlerFuncType cppFun =
				*reinterpret_cast<void(*)(typename EventType::EventHandlerType::EventHandlerArgs)>(fun);
			auto& event = *reinterpret_cast<EventType*>(eventPtr);
			event += cppFun;
		};
		mClear = [eventPtr]
		{
			reinterpret_cast<EventType*>(eventPtr)->Clear();
		};
	}

	void operator +=(void* fun) const
	{
		mAdd(fun);
	}

	void Clear() const
	{
		mClear();
	}
};

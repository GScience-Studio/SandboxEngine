#pragma once
#include <type_traits>
#include <vector>
#include <functional>
#include "NonCopyable.h"

template <class EventHandlerArgsType>
class EventHandler
{
public:
	using EventHandlerArgs = EventHandlerArgsType;
	using EventHandlerFuncType = std::function<void(EventHandlerArgs)>;
	const EventHandlerFuncType fun;

	EventHandler(EventHandlerFuncType& fun) : fun(fun)
	{
	}

	EventHandler(const EventHandlerFuncType&& fun) : fun(std::move(fun))
	{
	}

	operator const EventHandlerFuncType() const
	{
		return fun;
	}
};

class EventRawPtr;

/*
 * 事件模板
 */
template <class Type>
class Event : NonCopyable
{
	friend class EventRawPtr;
public:
	using EventHandlerType = Type;

private:
	std::vector<EventHandlerType> mEventHandlers;

public:
	void Do(typename EventHandlerType::EventHandlerArgs args) const
	{
		for (auto eventHandler : mEventHandlers)
		{
			eventHandler.fun(args);
		}
	}

	EventHandlerType& operator +=(decltype(EventHandlerType::fun)&& eventHandler)
	{
		mEventHandlers.emplace_back(EventHandlerType(std::move(eventHandler)));
		return mEventHandlers.back();
	}

	EventHandlerType& operator +=(decltype(EventHandlerType::fun)& eventHandler)
	{
		mEventHandlers.push_back(EventHandlerType(std::move(eventHandler)));
		return mEventHandlers.back();
	}

	void operator -=(EventHandlerType& eventHandler)
	{
		auto pos = std::find(mEventHandlers.begin(), mEventHandlers.end(), eventHandler);

		if (pos != mEventHandlers.end())
			mEventHandlers.erase(pos);
	}
};

/*
 * 事件指针
 */
class EventRawPtr
{
	std::function<void(void*)> mAdd;
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
	}

	void operator +=(void* fun) const
	{
		mAdd(fun);
	}
};

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
 * ÊÂ¼þÄ£°å
 */
template <class Type>
class Event
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
			eventHandler.fun(args);
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
	void Clear()
	{
		mEventHandlers.clear();
	}
};
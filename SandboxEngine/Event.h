#pragma once
#include <type_traits>
#include <vector>
#include <functional>

template<class EventHandlerArgsType> class EventHandler
{
public:
	using EventHandlerArgs = EventHandlerArgsType;
	using EventHandlerFuncType = std::function<void(EventHandlerArgs)>;
	const EventHandlerFuncType fun;
	EventHandler(const EventHandlerFuncType&& fun) :fun(fun){}

	operator const EventHandlerFuncType() const
	{
		return fun;
	}
};

/*
 * ÊÂ¼þÄ£°å
 */
template<class EventHandlerType> class Event
{
	std::vector<EventHandlerType> mEventHandlers;

public:
	void Do(typename EventHandlerType::EventHandlerArgs args) const
	{
		for(auto eventHandler : mEventHandlers)
		{
			eventHandler.fun(args);
		}
	}

	EventHandlerType& operator +=(decltype(EventHandlerType::fun)&& eventHandler)
	{
		mEventHandlers.emplace_back(std::move(eventHandler));
		return mEventHandlers.back();
	}

	void operator -=(EventHandlerType& eventHandler)
	{
		auto pos = std::find(mEventHandlers.begin(), mEventHandlers.end(), eventHandler);

		if (pos != mEventHandlers.end())
			mEventHandlers.erase(pos);
	}
};

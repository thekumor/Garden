// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/events.cpp
//	Desc: Event system dispatcher and listener,
//	event types and event structure.
// 
//	Modified: 2026/01/18 4:30 PM
//	Created: 2026/01/16 8:20 PM
//	Authors: The Kumor
// 
// ================================================

#include "events.h"

namespace grd
{

	Event::Event(EventType type, EventData data)
		: m_Type(type), m_Data(data)
	{
	}

	void EventListener::Subscribe(EventDispatcher* dispatcher)
	{
		m_Dispatcher = dispatcher;
		
		if (dispatcher)
			dispatcher->m_Listeners.push_back(this);
	}

	void EventListener::AddCallback(EventType type, EventCallback callback)
	{
		m_Callbacks[type] = callback;
	}

	void EventListener::CallEvent(Event ev)
	{
		auto it = m_Callbacks.find(ev.m_Type);

		if (it != m_Callbacks.end())
			it->second(ev.m_Data);
	}

	void EventDispatcher::CallEvent(Event ev)
	{
		for (EventListener* listener : m_Listeners)
			listener->CallEvent(ev);
	}

}
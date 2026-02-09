// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/events.cpp
//	Desc: Event system dispatcher and listener,
//	event types and event structure.
// 
//	Modified: 2026/02/09 2:16 PM
//	Created: 2026/01/16 8:20 PM
//	Authors: The Kumor
// 
// ================================================

#include "events.h"

namespace grd
{

	Event::Event(EventType type, EventData data)
		: m_Type(type), m_Data(data)
	{}

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

	Handle<EventListener*>* EventDispatcher::GetListenerHandle(EventListener* listener)
	{
		for (auto& handle : m_Listeners)
			if (handle.IsValid() && *handle == listener)
				return &handle;

		return nullptr;
	}

	Handle<EventListener*> EventDispatcher::PinListener(EventListener* listener)
	{
		return m_WaitingListeners.emplace_back(Handle<EventListener*>(listener));
	}

	void EventDispatcher::CallEvent(Event ev)
	{
		for (Handle<EventListener*> listener : m_Listeners)
			if (listener.IsValid())
				(*listener)->CallEvent(ev);
	}

	void EventDispatcher::UnpinInvalidListeners()
	{
		for (std::int32_t i = 0; i < m_Listeners.size(); i++)
			if (!m_Listeners[i].IsValid())
			{
				m_Listeners.erase(m_Listeners.begin() + i);
				i--;
			}
	}

	void EventDispatcher::PinWaitingListeners()
	{
		for (Handle<EventListener*> listener : m_WaitingListeners)
			m_Listeners.push_back(listener);
		
		m_WaitingListeners.clear();
	}

}
// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/events.h
//	Desc: Event system dispatcher and listener,
//	event types and event structure.
// 
//	Modified: 2026/02/24 9:05 AM
//	Created: 2026/01/16 8:20 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>

// Garden
#include <grd/util.h>

#define GRD_EVDATA_CAST(data, type) *reinterpret_cast<type*>(data)
#define GRD_EVDATA_CREATE(value, type) reinterpret_cast<void*>(&value)

namespace grd
{
	class EventListener;
	class EventDispatcher;

	typedef void* event_qualifier;

	// Used as a global event dispatcher for the application.
	// Note that dispatchers can be local too!
	extern EventDispatcher g_EventDispatcher;

	enum class EventType : std::uint8_t
	{
		None = 0,
		WindowClose,
		WindowResize,
		KeyPressed,
		GridSizeChanged,
		MousePressed,
		Draw
	};

	using EventData = void*;

	// ---------------------------------------------------
	//	Represents an event with a type and data.
	// ---------------------------------------------------
	struct Event
	{
		Event(EventType type, EventData data);
		Event() = default;

		EventType m_Type = EventType::None;
		EventData m_Data;
	};

	// ---------------------------------------------------
	//	Handles dispatching events to listeners.
	// ---------------------------------------------------
	class EventDispatcher
	{
	public:
		friend class EventListener;

		EventDispatcher() = default;

		Handle<EventListener*>* GetListenerHandle(EventListener* listener);
		Handle<EventListener*> PinListener(EventListener* listener);
		void UnpinInvalidListeners();
		void PinWaitingListeners();
		void CallEvent(Event ev);
		void CallEventQ(Event ev, event_qualifier q);

	private:
		std::vector<Handle<EventListener*>> m_Listeners;
		std::vector<Handle<EventListener*>> m_WaitingListeners;
	};

	using EventCallback = std::function<void(EventData)>;

	// ---------------------------------------------------
	//	Handles listening for events and calling callbacks.
	// ---------------------------------------------------
	class EventListener
	{
	public:
		EventListener();

		inline const event_qualifier GetQualifier() const { return m_Qualifier; }
		void AddCallback(EventType type, EventCallback callback);
		void CallEvent(Event ev);
		void SetQualifier(event_qualifier q);

	private:
		std::unordered_map<EventType, EventCallback> m_Callbacks;
		event_qualifier m_Qualifier;
	};

}